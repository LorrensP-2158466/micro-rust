#pragma once

#include "expr.hpp"

namespace mr { namespace expr {
    struct CallExpr : public Expr {
        U<Expr> expr;
        std::vector<U<Expr>> _args;

        CallExpr(location loc, U<Expr> _expr, std::vector<U<Expr>> args)
            : Expr(loc)
            , expr(std::move(_expr))
            , _args(std::move(args)) {}

        void print(const int depth) const override {
            const auto indent = std::string(depth, '\t');
            std::cout << indent << "Call Expr:\n";
            std::cout << indent << "id:\n";
            std::cout << indent << " | ";
            expr->print(depth + 1);
            std::cout << indent << "  args:\n";
            int i = 0;
            for (const auto &arg : _args) {
                std::cout << indent << "    arg" << i << ":\n";
                arg->print(depth + 1);
                i++;
            }
        }
    };
}} // namespace mr::expr
