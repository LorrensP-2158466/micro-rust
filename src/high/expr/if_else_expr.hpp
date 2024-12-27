#pragma once

#include "block_expr.hpp"
#include "expr.hpp"
#include "mr_util.hpp"
#include <optional>
#include <string>

namespace mr {
    namespace expr {
        struct IfElse : public Expr {
            U<Expr>         conditional_expr;
            U<BlockExpr>    then_block;
            OptUnique<Expr> else_block;

            IfElse(
                U<Expr> cond_expr, U<BlockExpr> then, OptUnique<Expr> els = std::nullopt
            )
                : Expr(), conditional_expr(std::move(cond_expr)),
                  then_block(std::move(then)), else_block(std::move(els)) {};
            ~IfElse() = default;

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "If Expression:\n";
                std::cout << indent << "  conditional expr:\n";
                conditional_expr->print(depth + 1);
                std::cout << indent << "  then block:\n";
                then_block->print(depth + 1);
                if (else_block) {
                    std::cout << indent << "  else block:\n";
                    (*else_block)->print(depth + 1);
                }
            }
        };

    } // namespace expr

} // namespace mr
