#pragma once

#include "fmt/format.h"
#include "high/expr/module.hpp"
#include "mr_util.hpp"
#include <iostream>
#include <variant>
#include <vector>

/**
 * A Type can be
 *  a primitive type:
 *      - bool
 *      - Numeric: Float or Int
 *      - Text: str or char
 *  Sequence Type:
 *      - Tuple
 *      - Array
 *      - Slice
 *  User defined Type:
 *      - Struct | TupleStruct
 *      - Enum
 *  Function Types:
 *      - closure
 *      - function
 *  Pointer types (no raw):
 *      - mut ref
 *      - ref
 *
 * But when were parsing types they can be any "name" (in rust a Path)
 * so at the ast level we only remember if it is a primitive or a path (user
 * defined)
 */

namespace mr {
    namespace ast {
        // forward declare Type so we can use it in tuple, array, slice, ref, ...

        ENUM_DEFINE(
            primitive_type, Unit, I8, I16, I32, I64, ISIZE, U8, U16, U32, U64, USIZE,
            Char, BOOL
        )

        // we don't know the exact type when were parsing a specific typename
        // we only know the NAME itself;
        // primitive types we know and love, the rest we don't
        // we still remember if it is a & or a &mut
        struct Type {
            using Tuple = std::vector<Type>;
            // [Type; N]: where N is an constant expression that must evaluate to a usize
            using Array = std::pair<U<Type>, U<expr::Expr>>;
            using Str = std::string; // no utf-8 bull
            // for now a placeholder for errors when declaring type so we can still go
            // through with compiling and catch more errors
            struct Infer {};
            using TypeKind = std::variant<Infer, primitive_type, Str, Tuple, Array>;

            TypeKind kind;

            Type() : kind(primitive_type::Unit) {}
            Type(TypeKind k) : kind(std::move(k)) {}

            static inline Type infer() noexcept { return Type(Infer{}); }

            bool is_primitive() const {
                return std::holds_alternative<primitive_type>(kind);
            }

            std::string to_string() const {
                return std::visit(
                    overloaded{
                        [](const primitive_type& pt) -> std::string {
                            return primitive_type_to_string(pt);
                        },
                        [](const Str&) { return std::string("&str"); },
                        [](const Tuple& t) {
                            std::string s = "(";
                            for (const auto& ty : t) {
                                s += ty.to_string() + ", ";
                            }
                            s += ")";
                            return s;
                        },

                        [](const Array& t) {
                            return fmt::format("[{}; N]", t.first->to_string());
                        },
                        [](const Infer t) { return std::string("`_`"); },
                        [](const auto&) -> std::string {
                            TODO("USER DEFINED TYPES NOT SUPPORTED");
                            return "";
                        },
                    },
                    kind
                );
            } // namespace ast
        }; // namespace mr
    } // namespace ast
} // namespace mr