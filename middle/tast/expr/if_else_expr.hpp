#pragma once

#include "../../type.hpp"
#include "./expr.hpp"
#include "block_expr.hpp"
#include "mr_util.hpp"
#include <optional>
#include <string>

namespace mr {
    namespace middle {
        namespace tast {
            struct IfElse : public Expr {
                Unique<Expr>      conditional_expr;
                Unique<BlockExpr> then_block;
                OptUnique<Expr>   else_block;

                IfElse(Unique<Expr> c_expr, Unique<BlockExpr> tb, OptUnique<Expr> eb,
                       types::Ty t)
                    : Expr(t), conditional_expr(std::move(c_expr)),
                      then_block(std::move(tb)), else_block(std::move(eb)) {}

                static Unique<Expr> unique(Unique<Expr> c_expr, Unique<BlockExpr> tb,
                                           OptUnique<Expr> eb, types::Ty t) {
                    return std::unique_ptr<Expr>(
                        new IfElse(std::move(c_expr), std::move(tb), std::move(eb), t));
                }
            };
        } // namespace tast

    } // namespace middle

} // namespace mr
