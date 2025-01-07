#pragma once

#include "expr.hpp"
#include "mr_util.hpp"
#include "optional"

namespace mr { namespace expr {
    ENUM_DEFINE(LiteralKind, Bool, Char, Integer, Float, Str)
    ENUM_DEFINE(Suffix, i8, i16, i32, i64, u8, u16, u32, u64, isize, usize, f32, f64)

    static Suffix suffix_from_str(const std::string &suff_str) {
        if (suff_str == "i8")
            return Suffix::i8;
        else if (suff_str == "i16")
            return Suffix::i16;
        else if (suff_str == "i32")
            return Suffix::i32;
        else if (suff_str == "i64")
            return Suffix::i64;
        else if (suff_str == "u8")
            return Suffix::u8;
        else if (suff_str == "u16")
            return Suffix::u16;
        else if (suff_str == "u32")
            return Suffix::u32;
        else if (suff_str == "u64")
            return Suffix::u64;
        else if (suff_str == "isize")
            return Suffix::isize;
        else if (suff_str == "usize")
            return Suffix::usize;
        else if (suff_str == "f32")
            return Suffix::f32;
        else if (suff_str == "f64")
            return Suffix::f64;
        else {
            throw std::runtime_error("Unsupported suffix: " + suff_str);
        };
    }

    struct Literal : public Expr {
        LiteralKind kind;
        std::string symbol;
        std::optional<Suffix> suffix;

        // use makers instead
        Literal(location loc, LiteralKind kind, std::string symbol, std::optional<Suffix> suffix = {})
            : Expr(loc)
            , kind(kind)
            , symbol(symbol)
            , suffix(suffix) {}

        static U<Literal> make_bool_lit(std::string symbol, location loc) {
            return std::make_unique<Literal>(loc, LiteralKind::Bool, symbol);
        }

        static U<Literal> make_int_lit(std::string entire_literal, location loc) {
            size_t pos = entire_literal.find_first_not_of("0123456789");

            std::string number_part = entire_literal.substr(0, pos);
            std::string suffix_part = (pos != std::string::npos) ? entire_literal.substr(pos) : "";
            const std::optional<Suffix> suffix =
                suffix_part.empty() ? std::nullopt : std::make_optional<Suffix>(suffix_from_str(suffix_part));
            return std::make_unique<Literal>(loc, LiteralKind::Integer, number_part, suffix);
        }

        static U<Literal> make_float_lit(std::string symbol, std::optional<Suffix> suff, location loc) {
            return std::make_unique<Literal>(loc, LiteralKind::Float, symbol, suff);
        }

        static U<Literal> make_str_lit(std::string symbol, location loc) {
            return std::make_unique<Literal>(loc, LiteralKind::Str, symbol);
        }

        void print(const int depth) const override {
            const auto indent = std::string(depth, '\t');
            const auto suff = suffix ? Suffix_to_string(*suffix) : "";
            std::cout << indent << LiteralKind_to_string(kind) << " Literal: " << symbol << suff << std::endl;
        }
    };
}} // namespace mr::expr
