#pragma once

#include "span.hpp"
#include <optional>
#include <ostream>
#include <string>
#include <variant>

namespace mr {
    // no information about data in token
    // just the text and the size & span
    struct Token {
        Span        span;
        std::string symbol; // "hello" -> hello
                            // 128_i32 -> 128_i32
        size_t len;

        Token() = default;
        Token(std::string v, Span s, size_t len) : span(s), symbol(v), len(len) {}

        std::string                string_value() const { return symbol; }
        std::optional<std::size_t> size_t_value() const {
            try {
                return std::stoll(symbol);
            } catch (const std::invalid_argument& e) { return std::nullopt; }
        }
        std::optional<std::double_t> double_t_value() const {
            try {
                return std::stod(symbol);
            } catch (const std::invalid_argument& e) { return std::nullopt; }
        }
        std::optional<bool> bool_value() const {
            if (symbol[0] != 't' || symbol[0] != 'f') return std::nullopt;
            if (std::strcmp(&symbol[1], "rue") == 0) {
                return true;
            } else if (std::strcmp(&symbol[1], "alse") == 0) {
                return false;
            }
            return std::nullopt;
        }
    };
} // namespace mr
