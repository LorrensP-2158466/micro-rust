#pragma once

#include "module.hpp"
#include <string>

namespace mr {
    namespace expr {
        struct TupleExpr : public Expr {
            std::vector<U<Expr>> values;

            TupleExpr(std::vector<U<Expr>> es) : Expr(), values(std::move(es)) {}

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "Tuple Expression\n";
                size_t i = 0;
                for (const auto& e : values) {
                    std::cout << indent << "  " << i++ << ":\n";
                    e->print(depth + 1);
                }
            }
        };
    } // namespace expr

} // namespace mr
