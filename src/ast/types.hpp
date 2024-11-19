#pragma once

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
 * so at the ast level we only remeber if it is a primitive or a path (user
 * defined)
 */

namespace mr {
    namespace ast {
        ENUM_DEFINE(primitive_type, Unit, I8, I16, I32, I64, ISIZE, U8, U16, U32, U64,
                    USIZE, Char, Bool)

        // we don't know the exact type when were parsing a specific typename
        // we only know the NAME itself;
        // primitive types we know and love, the rest we don't
        // we still remember if it is a & or a &mut
        using type_variant_t = std::variant<primitive_type, std::string>;
        struct Type : std::variant<primitive_type, std::string> {
            static const unsigned char ref_flag = 0b01;
            static const unsigned char ref_mut_flag = 0b10;
            unsigned char              _reference_flags = 0b00;

            Type() : type_variant_t{primitive_type::Unit}, _reference_flags(0) {}

            Type(primitive_type t, unsigned char flags)
                : type_variant_t{t}, _reference_flags(flags) {}

            Type(std::string s, unsigned char flags)
                : type_variant_t{s}, _reference_flags(flags) {}
            bool is_primitive() const {
                return std::holds_alternative<primitive_type>(*this);
            }

            bool is_ref() const { return _reference_flags == ref_flag; }
            bool is_mut_ref() const { return _reference_flags == ref_mut_flag; }

            std::string to_string() const {
                return std::visit(overloaded{
                                      [](const primitive_type& pt) -> std::string {
                                          return primitive_type_to_string(pt);
                                      },
                                      [](const std::string& s) -> std::string {
                                          TODO("USER DEFINED TYPES NOT SUPPORTED");
                                          return s;
                                      },
                                  },
                                  *this);
            }
        };
    } // namespace ast
} // namespace mr