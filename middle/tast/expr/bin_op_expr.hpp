#pragma once

#include "../../ir/values.hpp"
#include "../../type.hpp"
#include "./expr.hpp"
#include "mr_util.hpp"
#include "string"

namespace mr {
    namespace middle {
        namespace tast {
            struct BinOpExpr : public Expr {
                Unique<Expr> left, right;
                ir::BinOp    op;

                BinOpExpr(Unique<Expr> l, ir::BinOp op, Unique<Expr> r, types::Ty t)
                    : Expr(t), left(std::move(l)), op(op), right(std::move(r)) {}

                static Unique<Expr> unique(Unique<Expr> l, ir::BinOp op, Unique<Expr> r,
                                           types::Ty t) {
                    return std::unique_ptr<Expr>(
                        new BinOpExpr(std::move(l), op, std::move(r), t));
                }
            };

        } // namespace tast
    } // namespace middle

} // namespace mr
