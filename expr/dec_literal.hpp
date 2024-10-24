#pragma once

#include "expr.hpp"

namespace mr {
    namespace expr {
        struct DecLiteral : public Expr {
            std::size_t _value;

            DecLiteral(std::size_t value) : Expr(), _value(value) {}
            ~DecLiteral() = default;

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "Decimal Literal: " << _value
                          << std::endl;
            }
        };

    } // namespace expr

} // namespace mr
