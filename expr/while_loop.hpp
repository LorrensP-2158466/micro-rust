#pragma once

#include "expr.hpp"
#include <iostream>
#include "block_expr.hpp"

namespace mr
{
    namespace expr
    {
        struct WhileLoop : public Expr{
            Unique<Expr> _cond;
            Unique<BlockExpr> _body;
            WhileLoop(Unique<Expr> cond, Unique<BlockExpr> block)
                : Expr()
                , _cond(std::move(cond))
                , _body(std::move(block))
                {}

            void print(const int depth) const override{
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "While Loop:\n";
                std::cout << indent << "  condition:\n";
                _cond->print(depth + 1);
                std::cout << indent << "  body:\n";
                _body->print(depth + 1);
            }
        };
    } // namespace expr
    
} // namespace mr
