#pragma once

#include "../../type.hpp"
#include "../../type_inference.hpp"
#include "expr.hpp"
#include "mr_util.hpp"
#include "optional"
#include <optional>
#include <string>
#include <variant>

namespace mr {
    namespace middle {
        namespace tast {

            ENUM_DEFINE(LitIntType, i8, i16, i32, i64, u8, u16, u32, u64, isize, usize);
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
            };

            struct Float {
                std::string value;
                // no suffix is default to f64
                std::optional<LitFloatType> suffix;
            };
            using literal_variant_t = std::variant<StrLit, Bool, Int, Float>;

            struct LiteralKind : literal_variant_t {};
            struct Literal : public Expr {
                LiteralKind kind;

                Literal(LiteralKind k, types::Ty t) : Expr(t), kind(k) {}
                ~Literal() = default;

#define DO_STUFF(val, r_type, c_type)                                                    \
    do {                                                                                 \
        check_fits<c_type>(ival);                                                        \
        return {val, inf.r_type(), LitIntType::r_type};                                  \
    } while (false);

                static Literal from_ast_lit(const expr::Literal&  lit,
                                            inference::TyInferer& inf) {
                    switch (lit.kind) {
                    case expr::LiteralKind::Bool:
                        return Literal(LiteralKind{Bool{true}}, inf.bool_t());
                    case expr::LiteralKind::Char:
                        throw std::runtime_error("Char literal not supported");
                    case expr::LiteralKind::Integer: {
                        // check suffix
                        const auto [v, t, s] =
                            !lit.suffix
                                ? std::make_tuple(std::stoul(lit.symbol),
                                                  inf.create_int_var(), std::nullopt)
                                : [&]() -> std::tuple<uint64_t, types::Ty,
                                                      std::optional<LitIntType>> {
                            const auto uval = std::stoul(lit.symbol);
                            const auto ival = std::stol(lit.symbol);
                            switch (*lit.suffix) {
                            case expr::Suffix::i8:
                                DO_STUFF(ival, i8, int8_t);
                            case expr::Suffix::i16:
                                DO_STUFF(ival, i16, int16_t);
                            case expr::Suffix::i32:
                                DO_STUFF(ival, i32, int32_t);
                            case expr::Suffix::i64:
                                DO_STUFF(ival, i64, int64_t)
                            case expr::Suffix::u8:
                                DO_STUFF(uval, u8, u_int8_t)
                            case expr::Suffix::u16:
                                DO_STUFF(uval, u16, u_int16_t)
                            case expr::Suffix::u32:
                                DO_STUFF(uval, u32, u_int32_t)
                            case expr::Suffix::u64:
                                DO_STUFF(uval, u64, u_int64_t)
                            case expr::Suffix::isize:
                                DO_STUFF(ival, isize, intmax_t)
                            case expr::Suffix::usize:
                                DO_STUFF(uval, usize, uintmax_t)
                            };
                        }();
                        return Literal(
                            LiteralKind{
                                Int{v, s}
                        },
                            t);
                    }
                    case expr::LiteralKind::Float: {
                        // check suffix
                        const auto [t, s] =
                            !lit.suffix
                                ? std::make_pair(inf.create_float_var(), std::nullopt)
                                : [&]()
                            -> std::pair<types::Ty, std::optional<LitFloatType>> {
                            switch (*lit.suffix) {
                            case expr::Suffix::f32:
                                return {inf.f32(), LitFloatType::f32};
                            case expr::Suffix::f64:
                                return {inf.f64(), LitFloatType::f64};
                            default:
                                throw std::runtime_error(
                                    "invalid suffix with float literal");
                            }
                        }();
                    }
                    case expr::LiteralKind::Str:
                        throw std::runtime_error("Str literal not supported");
                    }
                }
                template <std::integral IntegerT> static void check_fits(auto i) {
                    assert(std::numeric_limits<IntegerT>::min() <= i &&
                           i <= std::numeric_limits<IntegerT>::max());
                }
            };

        } // namespace tast

    } // namespace middle
} // namespace mr
