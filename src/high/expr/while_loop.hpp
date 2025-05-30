#pragma once

#include "block_expr.hpp"
#include "expr.hpp"
#include <iostream>

namespace mr { namespace expr {
    struct WhileLoop : public Expr {
        U<Expr> _cond;
        U<BlockExpr> _body;
        WhileLoop(location while_loc, U<Expr> cond, U<BlockExpr> block)
            : Expr(while_loc + block->loc)
            , _cond(std::move(cond))
            , _body(std::move(block)) {}

        void print(const int depth) const override {
            const auto indent = std::string(depth, '\t');
            std::cout << indent << "While Loop:\n";
            std::cout << indent << "  condition:\n";
            _cond->print(depth + 1);
            std::cout << indent << "  body:\n";
            _body->print(depth + 1);
        }
    };
}} // namespace mr::expr
