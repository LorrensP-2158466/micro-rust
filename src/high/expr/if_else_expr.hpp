#pragma once

#include "block_expr.hpp"
#include "expr.hpp"
#include "mr_util.hpp"
#include <optional>
#include <string>

namespace mr { namespace expr {
    struct IfElse : public Expr {
        location if_loc;
        U<Expr> conditional_expr;
        U<BlockExpr> then_block;
        location else_loc;
        OptUnique<Expr> else_block;

        IfElse(
            location if_loc, U<Expr> cond_expr, U<BlockExpr> then, location el_loc, OptUnique<Expr> els = std::nullopt
        )
            : Expr(if_loc + (els ? (*els)->loc : then->loc))
            , conditional_expr(std::move(cond_expr))
            , then_block(std::move(then))
            , else_block(std::move(els))
            , if_loc(if_loc)
            , else_loc(el_loc) {};
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

}} // namespace mr::expr
