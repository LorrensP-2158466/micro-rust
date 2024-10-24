#pragma once

#include "block_expr.hpp"
#include "expr.hpp"
#include "mr_util.hpp"
#include <optional>
#include <string>

namespace mr {
    namespace expr {
        class IfElse : public Expr {
          private:
            Unique<Expr>      _conditional_expr;
            Unique<BlockExpr> _then_block;
            OptUnique<Expr>   _else_block;

          public:
            IfElse(Unique<Expr> cond_expr, Unique<BlockExpr> then,
                   OptUnique<Expr> els = std::nullopt)
                : Expr(), _conditional_expr(std::move(cond_expr)),
                  _then_block(std::move(then)), _else_block(std::move(els)) {};
            ~IfElse() = default;

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "If Expression:\n";
                std::cout << indent << "  conditional expr:\n";
                _conditional_expr->print(depth + 1);
                std::cout << indent << "  then block:\n";
                _then_block->print(depth + 1);
                if (_else_block) {
                    std::cout << indent << "  else block:\n";
                    (*_else_block)->print(depth + 1);
                }
            }
        };

    } // namespace expr

} // namespace mr
