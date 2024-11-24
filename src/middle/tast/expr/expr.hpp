#pragma once

#include "../../ir/module.hpp"
#include "../../type.hpp"
#include "../../type_inference.hpp"
#include "mr_util.hpp"
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <variant>

namespace mr {
    namespace middle {
        namespace tast {

#define MAKE_EXPR_VARIANT_CONSTR(type)                                                   \
    ExprKind(type value) : expr_variant_t(std::move(value)) {                            \
    }
            struct Expr;
            std::ostream& operator<<(std::ostream& o, const Expr& e);
            struct Stmt;
            struct Unit {
                friend std::ostream& operator<<(std::ostream& o, const Unit& as) {
                    o << "Unit Expr";
                    return o;
                }
            };
            struct AssignExpr {
                std::string  id;
                Unique<Expr> expr;

                AssignExpr(std::string id, Unique<Expr> ex)
                    : id(id), expr(std::move(ex)) {}
                friend std::ostream& operator<<(std::ostream& o, const AssignExpr& as) {
                    o << "ASSIGN: " << as.id << " = " << as.expr;
                    return o;
                }
            };

            struct AssignOpExpr {
                std::string  id;
                ir::BinOp    op;
                Unique<Expr> expr;

                AssignOpExpr(std::string id, ir::BinOp op, Unique<Expr> ex)
                    : id(id), op(op), expr(std::move(ex)) {}

                friend std::ostream& operator<<(std::ostream& o, const AssignOpExpr& as) {
                    o << BinOp_to_string(as.op) << "ASSIGN: " << as.id << " = "
                      << as.expr;
                    return o;
                }
            };

            struct BlockExpr {
                std::vector<Unique<Stmt>> _statements;
                Unique<Expr>              _tail;

                BlockExpr(std::vector<Unique<Stmt>> s, Unique<Expr> tail)
                    : _statements(std::move(s)), _tail(std::move(tail)) {}
                BlockExpr(Unique<Expr> tail) : _statements{}, _tail(std::move(tail)) {}
                friend std::ostream& operator<<(std::ostream& o, const BlockExpr& as) {
                    o << "BLOCK EXPR" << "** to lazy**";
                    return o;
                }
            };

            struct Identifier {
                std::string symbol;

                Identifier(std::string s) : symbol(s) {}
                friend std::ostream& operator<<(std::ostream& o, const Identifier& as) {
                    o << "IDENTIFIER " << as.symbol;
                    return o;
                }
            };

            struct CallExpr {
                std::string               id;
                std::vector<Unique<Expr>> args;

                CallExpr(std::string i, std::vector<Unique<Expr>> a)
                    : id(i), args(std::move(a)) {}
                friend std::ostream& operator<<(std::ostream& o, const CallExpr& call) {
                    o << "CALL EXPR: " << call.id << " WITH ARGS: (";
                    std::copy(
                        call.args.begin(),
                        call.args.end(),
                        std::ostream_iterator<Unique<Expr>>(o, " ")
                    );
                    o << ')';
                    return o;
                }
            };

            ENUM_DEFINE(
                LitIntType, i8, i16, i32, i64, u8, u16, u32, u64, isize, usize, none
            );
            ENUM_DEFINE(LitFloatType, f32, f64);

            struct StrLit {
                std::string value;
            };

            struct Bool {
                bool value;
            };

            struct Int {
                // just for holding bytes
                uint64_t value;
                // no suffix is default to i32
                std::optional<LitIntType> suffix;

                size_t size() const noexcept {
                    switch (suffix.value_or(LitIntType::none)) {
                    case LitIntType::i8:
                    case LitIntType::u8:
                        return 1;
                    case LitIntType::i16:
                    case LitIntType::u16:
                        return 2;
                    case LitIntType::none:
                    case LitIntType::i32:
                    case LitIntType::u32:
                        return 4;
                    case LitIntType::i64:
                    case LitIntType::u64:
                        return 8;
                    case LitIntType::isize:
                    case LitIntType::usize:
                        return sizeof(size_t);
                    }
                }
            };

            struct Float {
                std::string value;
                // no suffix is default to f64
                std::optional<LitFloatType> suffix;

                float  as_float() const { return std::stof(value); }
                double as_double() const { return std::stod(value); }

                uint64_t as_raw_value() const {
                    if (!suffix || *suffix == LitFloatType::f64) return as_double();
                    return as_float();
                }
            };
            using literal_variant_t = std::variant<StrLit, Bool, Int, Float>;
            struct LiteralKind : literal_variant_t {};
            struct Literal {
                LiteralKind          kind;
                friend std::ostream& operator<<(std::ostream& o, const Literal& as) {
                    o << "LITERAL";
                    return o;
                }

                Literal(LiteralKind k) : kind(k) {}
                ~Literal() = default;

                uint64_t raw_value() const {
                    return std::visit(
                        overloaded{
                            [](const StrLit& s) {
                                throw std::runtime_error("THIS CAN't HAPPEN");
                                return 0ull;
                            },
                            [](const Bool& b) -> uint64_t { return b.value; },
                            [](const Int& i) { return i.value; },
                            [](const Float& f) { return f.as_raw_value(); },
                        },
                        kind
                    );
                }

                size_t size() const noexcept { return 8; }

#define CREATE_LITERAL_VALUES(val, r_type, c_type)                                       \
    do {                                                                                 \
        check_fits<c_type>(ival);                                                        \
        return {val, inf.r_type(), LitIntType::r_type};                                  \
    } while (false);

                static std::pair<Literal, types::Ty>
                from_ast_lit(const expr::Literal& lit, inference::TyInferer& inf) {
                    switch (lit.kind) {
                    case expr::LiteralKind::Bool:
                        return {
                            Literal(LiteralKind{Bool{str_to_bool(lit.symbol.c_str())}}),
                            inf.bool_t()
                        };
                    case expr::LiteralKind::Char:
                        throw std::runtime_error("Char literal not supported");
                    case expr::LiteralKind::Integer: {
                        // check suffix
                        const auto [v, t, s] = !lit.suffix ? std::make_tuple(
                                                                 std::stoul(lit.symbol),
                                                                 inf.create_int_var(),
                                                                 std::nullopt
                                                             )
                                                           : [&]()
                            -> std::
                                tuple<uint64_t, types::Ty, std::optional<LitIntType>> {
                                    const auto uval = std::stoul(lit.symbol);
                                    const auto ival = std::stol(lit.symbol);
                                    switch (*lit.suffix) {
                                    case expr::Suffix::i8:
                                        CREATE_LITERAL_VALUES(ival, i8, int8_t);
                                    case expr::Suffix::i16:
                                        CREATE_LITERAL_VALUES(ival, i16, int16_t);
                                    case expr::Suffix::i32:
                                        CREATE_LITERAL_VALUES(ival, i32, int32_t);
                                    case expr::Suffix::i64:
                                        CREATE_LITERAL_VALUES(ival, i64, int64_t)
                                    case expr::Suffix::u8:
                                        CREATE_LITERAL_VALUES(uval, u8, u_int8_t)
                                    case expr::Suffix::u16:
                                        CREATE_LITERAL_VALUES(uval, u16, u_int16_t)
                                    case expr::Suffix::u32:
                                        CREATE_LITERAL_VALUES(uval, u32, u_int32_t)
                                    case expr::Suffix::u64:
                                        CREATE_LITERAL_VALUES(uval, u64, u_int64_t)
                                    case expr::Suffix::isize:
                                        CREATE_LITERAL_VALUES(ival, isize, intmax_t)
                                    case expr::Suffix::usize:
                                        CREATE_LITERAL_VALUES(uval, usize, uintmax_t)
                                    };
                                }();
                        return {
                            Literal(LiteralKind{Int{v, s}}
                            ), t
                        };
                    }
                    case expr::LiteralKind::Float: {
                        // check suffix
                        const auto [t, s] =
                            !lit.suffix
                                ? std::make_pair(inf.create_float_var(), std::nullopt)
                                : [&](
                                  ) -> std::pair<types::Ty, std::optional<LitFloatType>> {
                            switch (*lit.suffix) {
                            case expr::Suffix::f32:
                                return {inf.f32(), LitFloatType::f32};
                            case expr::Suffix::f64:
                                return {inf.f64(), LitFloatType::f64};
                            default:
                                throw std::runtime_error(
                                    "invalid suffix with float literal"
                                );
                            }
                        }();
                    }
                    case expr::LiteralKind::Str:
                        throw std::runtime_error("Str literal not supported");
                    }
                }
                template <std::integral IntegerT> static void check_fits(auto i) {
                    assert(
                        std::numeric_limits<IntegerT>::min() <= i &&
                        i <= std::numeric_limits<IntegerT>::max()
                    );
                }
            };

            struct IfElse {
                Unique<Expr>    conditional_expr;
                BlockExpr       then_block;
                OptUnique<Expr> else_block;

                IfElse(Unique<Expr> c_expr, BlockExpr tb, OptUnique<Expr> eb)
                    : conditional_expr(std::move(c_expr)), then_block(std::move(tb)),
                      else_block(std::move(eb)) {}

                friend std::ostream& operator<<(std::ostream& o, const IfElse& as) {
                    o << "If Else: cond:" << *as.conditional_expr << " fuck die blocks";
                    return o;
                }
            };

            ir::UnOp un_op_from_ast(expr::UnaryOp op) {
                switch (op) {
                case expr::UnaryOp::Not:
                    return ir::UnOp::Not;
                case expr::UnaryOp::Negate:
                    return ir::UnOp::Neg;
                default:
                    throw std::runtime_error(
                        "Can't create binary op from borrow/deref expr"
                    );
                }
            }

            struct UnaryOpExpr {
                ir::UnOp     op;
                Unique<Expr> expr;

                UnaryOpExpr(expr::UnaryOp o, Unique<Expr> e)
                    : op(un_op_from_ast(o)), expr(std::move(e)) {}
                friend std::ostream& operator<<(std::ostream& o, const UnaryOpExpr& as) {
                    o << UnOp_to_string(as.op) << "Unary Operation ON " << as.expr;
                    return o;
                }
            };

            struct BinOpExpr {
                Unique<Expr> left, right;
                ir::BinOp    op;

                BinOpExpr(Unique<Expr> l, ir::BinOp op, Unique<Expr> r)
                    : left(std::move(l)), op(op), right(std::move(r)) {}

                friend std::ostream& operator<<(std::ostream& o, const BinOpExpr& as) {
                    o << BinOp_to_string(as.op) << "Binary Operation ON " << as.left
                      << " AND " << as.right;
                    return o;
                }
            };

            struct Loop {
                Unique<Expr> body;

                Loop(Unique<Expr> b) : body(std::move(b)) {}
                friend std::ostream& operator<<(std::ostream& o, const Loop& as) {
                    o << "Loop ";
                    return o;
                }
            };

            struct Break {
                Unique<Expr> val;

                Break(Unique<Expr> v) : val(std::move(v)) {}
                friend std::ostream& operator<<(std::ostream& o, const Break& as) {
                    o << "Break ";
                    return o;
                }
            };

            using ExprKind = std::variant<
                AssignExpr, AssignOpExpr, BinOpExpr, BlockExpr, CallExpr, Identifier,
                IfElse, Literal, UnaryOpExpr, Unit, Loop, Break>;
            struct Expr {
                types::Ty type;
                ExprKind  kind;
                Expr(ExprKind k, types::Ty t) : kind(std::move(k)), type(t) {}
                Expr(Expr&& other) noexcept = default;
            };
            std::ostream& operator<<(std::ostream& o, const Expr& e) {
                o << "Expr: \n"
                  << "  Type: " << e.type << '\n'
                  << "  kind: ??\n";
                return o;
            }

        } // namespace tast
    } // namespace middle

} // namespace mr
#define FORMAT_TAST_TYPE(ty) OSTREAM_FORMATTER(mr::middle::tast::ty)

MAP(FORMAT_TAST_TYPE, AssignExpr, AssignOpExpr, BinOpExpr, BlockExpr, CallExpr,
    Identifier, IfElse, Literal, UnaryOpExpr, Unit, Loop, Break, ExprKind, Expr)
