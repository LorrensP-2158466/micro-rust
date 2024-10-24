#pragma once

#include "span.hpp"
#include <variant>
#include <string>
#include <ostream>


namespace mr
{
    struct Token{
        typedef std::variant<
            std::string,
            std::size_t,
            std::double_t,
            bool
            > v_value_t;
        Span _span;
        v_value_t _value;

        Token() = default;
        Token(v_value_t v,  Span s)
            : _span(s)
            , _value(v)
            {}

        std::string string_value() const{
            return std::get<std::string>(_value);
        }
        std::size_t size_t_value() const{
            return std::get<std::size_t>(_value);
        }
        std::double_t double_t_value() const{
            return std::get<std::double_t>(_value);
        }
        bool bool_value() const{
            return std::get<bool>(_value);
        }
    };
} // namespace mr
