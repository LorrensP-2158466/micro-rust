
#pragma once

#include "local.hpp"
#include "mr_util.hpp"
#include "scalar.hpp"
#include <functional>
#include <iostream>
#include <variant>
#include <vector>
namespace mr {
    namespace middle {
        namespace ir {

            ENUM_DEFINE(
                BinOp, Add, Sub, Mul, Div, BitXor, BitAnd, BitOr, Eq, Lt, Le, Ne, Ge, Gt,
                Cmp, Offset,
            )
            ENUM_DEFINE(UnOp, Not, Neg)

            // a place is just a location in memory, this will be usefull when
            // doing stuff like: Struct/Tuple Field, slicess, index, deref, ...
            // because when constructing byte code/llvm IR/... this will tell us
            // where in "memory" this is
            // this is again from the rust compiler, but a little different
            // it uses a project list
            struct Place {
                LocalId local;
                // TODO: projections

                Place(LocalId l) : local(l) {}

                friend std::ostream& operator<<(std::ostream& o, const Place& p) {
                    o << p.local;
                    return o;
                }
            };

            // operands, used for borrow checking in the future
            // now everything is just copy because everything is copy
            struct Move {
                Place val;
            };
            struct Copy {
                Place val;
            };
            struct Const {
                Scalar    scalar;
                types::Ty ty;
            };

            struct Operand : std::variant<Copy, Move, Const> {

                static Operand move(Place val) { return Operand{Move{val}}; }
                static Operand copy(Place val) { return Operand{Copy{val}}; }
                // const is a keyword...
                static Operand const_(Scalar s, types::Ty t) {
                    return Operand(Const{s, t});
                }

                friend std::ostream& operator<<(std::ostream& o, const Operand& v) {
                    std::visit(
                        overloaded{
                            [&](const Copy& c) { o << "copy " << c.val; },
                            [&](const Move& c) { o << "move " << c.val; },
                            [&](const Const& c) {
                                o << "const " << c.scalar.data << "_" << c.ty;
                            },
                        },
                        v
                    );
                    return o;
                }
            };

            struct UnaryOp {
                UnOp    op;
                Operand operand;

                friend std::ostream& operator<<(std::ostream& o, const UnaryOp& un_op) {
                    o << UnOp_to_string(un_op.op) << '(' << un_op.operand << ')';
                    return o;
                }
            };

            struct BinaryOp {
                BinOp   op;
                Operand left;
                Operand right;

                friend std::ostream& operator<<(std::ostream& o, const BinaryOp& bin_op) {
                    o << BinOp_to_string(bin_op.op) << '(' << bin_op.left << ", "
                      << bin_op.right << ')';
                    return o;
                }
            };
            // just the value of the local as it is
            struct AsIs {
                Operand op;

                friend std::ostream& operator<<(std::ostream& o, const AsIs& as_is) {
                    o << as_is.op;
                    return o;
                }
            };
            using rvalue_variant_t = std::variant<AsIs, BinaryOp, UnaryOp>;
            struct RValue : public rvalue_variant_t {
                VARIANT_CONSTR(RValue, AsIs, rvalue_variant_t)
                VARIANT_CONSTR(RValue, BinaryOp, rvalue_variant_t)
                VARIANT_CONSTR(RValue, UnaryOp, rvalue_variant_t)

                friend std::ostream& operator<<(std::ostream& o, const RValue& val) {
                    std::visit([&](const auto& v) { o << v; }, val);
                    return o;
                }
            }; // namespace middle

        } // namespace ir

    } // namespace middle

} // namespace mr