#pragma once

#include "datastructures.hpp"
#include "high/ast/module.hpp"
#include "mr_util.hpp"
#include <algorithm>
#include <assert.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#define STANDARD_TYPE_VARIANT(name)                                                                \
    struct name {                                                                                  \
        friend bool operator==(const name &, const name &) { return true; }                        \
    };

#define TYPE_VARIABLE(name)                                                                        \
    struct name {                                                                                  \
        size_t _id;                                                                                \
        INDEX_TYPE(name, _id)                                                                      \
    };

namespace mr { namespace middle { namespace types {
    using namespace std::literals;
    struct Ty;

    // first forward-declare the types than create the variant type

    // a defined type like:
    // i32, bool
    // fn(i32) -> i32 !! with (mangled?) name because in rust no 2
    // functions are the same (function pointers are!) struct Foo{x:
    // i32} a type is anything with a name or something:

    // i32, i64, u32, ...
    // seperate because this makes it easier for checking operations
    ENUM_DEFINE(IntTy, i8, i16, i32, i64, isize)
    static inline size_t size_of_int_ty(IntTy it) {
        switch (it) {
        case IntTy::i8:
            return 1;
        case IntTy::i16:
            return 2;
        case IntTy::i32:
            return 4;
        case IntTy::i64:
            return 8;
        case IntTy::isize:
            return sizeof(signed long);
        }
    }
    ENUM_DEFINE(UIntTy, u8, u16, u32, u64, usize)
    static inline size_t size_of_u_int_ty(UIntTy ut) {
        switch (ut) {
        case UIntTy::u8:
            return 1;
        case UIntTy::u16:
            return 2;
        case UIntTy::u32:
            return 4;
        case UIntTy::u64:
            return 8;
        case UIntTy::usize:
            return sizeof(size_t);
        }
    }
    ENUM_DEFINE(FloatTy, F32, F64)
    static inline size_t size_of_float_ty(FloatTy ft) {
        switch (ft) {
        case FloatTy::F32:
            return 4;
        case FloatTy::F64:
            return 8;
        }
    }

    // we don't know, used with type variables
    STANDARD_TYPE_VARIANT(UnknownTy);

    // the '!' type, basically something that doesn't exist but has a
    // represenation easiest to explain is this:
    /*
     Say we have an if else initializer:
        let a = if some_condition { 10 } else {return 20;};
    The type of the `then` block will be an integer, so the `else` block needs to
    also match that type, but because of the return statement, there is not value
    of that block, so the type is `never` since it will never be executed. The
    nice thing about `never` is that it can be coerced into every type so when the
    2 conditional blocks have to have an equal type, `never` can work here, since
    we can coerce it into the integer type, yayy
     */
    STANDARD_TYPE_VARIANT(NeverTy);
    STANDARD_TYPE_VARIANT(BoolTy);

    // type variables with id into inferer storage
    TYPE_VARIABLE(TypeVar)
    TYPE_VARIABLE(IntVar)
    TYPE_VARIABLE(FloatVar)

    struct IntVarValue : public std::variant<UnknownTy, IntTy, UIntTy> {
        friend std::ostream &operator<<(std::ostream &o, const IntVarValue &t) {
            o << std::visit(
                overloaded{
                    [](const UnknownTy &) { return "{integer}"; },
                    [](const IntTy &t) { return IntTy_to_string(t); },
                    [](const UIntTy &t) { return UIntTy_to_string(t); }
                },
                t
            );
            return o;
        }

        static inline IntVarValue unify_values(const IntVarValue &val1, const IntVarValue &val2) {
            return std::visit(
                overloaded{
                    [](const UnknownTy &, const UnknownTy &) { return IntVarValue(UnknownTy{}); },
                    [&](const IntTy &, const UnknownTy &) { return val1; },
                    [&](const UIntTy &, const UnknownTy &) { return val1; },
                    [&](const UnknownTy &, const IntTy &) { return val2; },
                    [&](const UnknownTy &, const UIntTy &) { return val2; },
                    [](const auto &, const auto &) {
                        ICE("CANT unify differing integer, we should have resolved them");
                        return unreachable<IntVarValue>();
                    },
                },
                val1,
                val2
            );
        }
    };
    struct FloatVarValue : public std::variant<UnknownTy, FloatTy> {
        friend std::ostream &operator<<(std::ostream &o, const FloatVarValue &t) {
            o << std::visit(
                overloaded{
                    [](const UnknownTy &) { return "{float}"; },
                    [](const FloatTy &t) { return FloatTy_to_string(t); },
                },
                t
            );
            return o;
        }
        static inline FloatVarValue
        unify_values(const FloatVarValue &val1, const FloatVarValue &val2) {
            return std::visit(
                overloaded{
                    [](const UnknownTy &, const UnknownTy &) { return FloatVarValue(UnknownTy{}); },
                    [&](const FloatTy &, const UnknownTy &) { return val1; },
                    [&](const UnknownTy &, const FloatTy &) { return val2; },
                    [](const auto &, const auto &) {
                        ICE("CANT unify differing floats, we should have resolved them");
                        return unreachable<FloatVarValue>();
                    },
                },
                val1,
                val2
            );
        }
    };

    struct InferTy : public std::variant<TypeVar, IntVar, FloatVar> {
        inline const char *infer_ty_to_string() const {
            // yeah this is weird
            switch (this->index()) {
            case 0:
                return "{unknown}";
            case 1:
                return "{integer}";
            case 2:
                return "{float}";
            default:
                mr::unreachable<const char *>();
            }
        }

        bool is_int_var() const { return std::holds_alternative<IntVar>(*this); }

        bool is_float_var() const { return std::holds_alternative<FloatVar>(*this); }

        bool is_infer_var() const { return std::holds_alternative<TypeVar>(*this); }
        friend std::ostream &operator<<(std::ostream &o, const InferTy ft) {
            o << ft.infer_ty_to_string();
            return o;
        }
    };
    STANDARD_TYPE_VARIANT(UnitTy);

    struct TupleTy {
        std::vector<Ty> tys;

        friend bool operator==(const TupleTy &l, const TupleTy &r) = default;
        friend bool operator!=(const TupleTy &l, const TupleTy &r) = default;
    };

    struct FnPointerTy {
        std::vector<Ty> arg_tys;
        const Ty *ret_ty;

        bool operator==(const FnPointerTy &other) const;
        bool operator!=(const FnPointerTy &other) const = default;
    };

    struct FunctionType;
    static std::string function_type_to_string(const FunctionType *ft);

    using type_variant_t = std::variant<
        UnknownTy, NeverTy, InferTy, BoolTy, IntTy, UIntTy, UnitTy, FloatTy, TupleTy,
        const FunctionType *, FnPointerTy>;
    struct Ty : public type_variant_t {

        bool is_known() const noexcept {
            return !std::holds_alternative<InferTy>(*this) &&
                   !std::holds_alternative<UnknownTy>(*this);
        }

        bool is_integral() const noexcept {
            return std::holds_alternative<IntTy>(*this) || std::holds_alternative<UIntTy>(*this);
        }

        bool is_signed_integral() const noexcept { return std::holds_alternative<IntTy>(*this); }

        static Ty unit() { return Ty{UnitTy{}}; }
        inline bool is_unit() const noexcept { return has_variant<UnitTy>(*this); }

        size_t size() const noexcept {
            return std::visit(
                overloaded{
                    [](const FunctionType *const &) { return 8ul; },
                    [](const NeverTy &) { return 0ul; },
                    [](const UnitTy &) { return 0ul; },
                    [](const BoolTy &) { return 8ul; },
                    [](const IntTy &t) { return size_of_int_ty(t); },
                    [](const UIntTy &t) { return size_of_u_int_ty(t); },
                    [](const FloatTy &t) { return size_of_float_ty(t); },
                    [](const TupleTy &t) {
                        return std::accumulate(
                            t.tys.cbegin(),
                            t.tys.cend(),
                            0ul,
                            [](size_t sum, const Ty &ty) {
                                // yeah were keeping it simple
                                return sum + std::max(ty.size(), 8ul);
                            }
                        );
                    },
                    [](const auto &) {
                        std::runtime_error("SIZE OF UNKOWN WTF?!");
                        return 0ul;
                    },
                },
                *this
            );
        }

        friend std::ostream &operator<<(std::ostream &o, const Ty &ft) {
            return (o << ft.to_string());
        }
        std::string to_string() const noexcept {
            return std::visit(
                overloaded{
                    [](const FunctionType *const &t) { return function_type_to_string(t); },
                    [](const FnPointerTy &fp) {
                        return fmt::format(
                            "fn({}) -> {}",
                            fmt::join(
                                fp.arg_tys | std::views::transform([&](const auto &t) {
                                    return t.to_string();
                                }),
                                ", "
                            ),
                            fp.ret_ty->to_string()
                        );
                    },
                    [](const NeverTy &) { return "!"s; },
                    [](const UnitTy &) { return "()"s; },
                    [](const BoolTy &) { return "bool"s; },
                    [](const UnknownTy &) { return "Unknown"s; },
                    [](const InferTy &t) -> std::string { return t.infer_ty_to_string(); },
                    [](const IntTy &t) -> std::string { return IntTy_to_string(t); },
                    [](const UIntTy &t) -> std::string { return UIntTy_to_string(t); },
                    [](const FloatTy &t) -> std::string { return FloatTy_to_string(t); },
                    [](const TupleTy &t) -> std::string {
                        return fmt::format(
                            "({})",
                            fmt::join(
                                t.tys | std::views::transform([&](const auto &t) {
                                    return t.to_string();
                                }),
                                ", "
                            )
                        );
                    },
                    [](const auto &) { return "buhhhhh"s; }
                },
                *this
            );
        }

        static inline Ty unify_values(const Ty &val1, const Ty &val2) {
            return std::visit(
                overloaded{
                    [](const UnknownTy &, const UnknownTy &) { return Ty(UnknownTy{}); },
                    [&](const auto &, const UnknownTy &) { return val1; },
                    [&](const UnknownTy &, const auto &) { return val2; },
                    [](const auto &, const auto &) {
                        ICE("CANT unify differing tys, we should have resolved them");
                        return unreachable<Ty>();
                    },
                },
                val1,
                val2
            );
        }
    }; // namespace middle::types

    struct FunctionType {
        std::string id; // function types are also based on their name:
                        // fn() -> () {foo}
        // we remember the names for convenience
        // but these are not included into the "type"
        std::vector<Ty> arg_types;
        // the return type of the function: -> Ty
        Ty ret_ty;

        std::string to_string() const {
            std::ostringstream o;
            o << *this;
            return o.str();
        }
        friend std::ostream &operator<<(std::ostream &o, const FunctionType &ft) {
            o << "fn(";
            for (const auto &t : ft.arg_types) {
                o << t << ", ";
            }
            o << ") -> " << ft.ret_ty << " {" << ft.id << '}';
            return o;
        }
    };

    static std::string function_type_to_string(const FunctionType *ft) { return ft->to_string(); }
}}} // namespace mr::middle::types

template <> struct fmt::formatter<mr::middle::types::Ty> : fmt::ostream_formatter {};

namespace std {

template <>
struct variant_size<mr::middle::types::Ty> : variant_size<mr::middle::types::type_variant_t> {};

template <std::size_t I>
struct variant_alternative<I, mr::middle::types::Ty>
    : variant_alternative<I, mr::middle::types::type_variant_t> {};
} // namespace std
