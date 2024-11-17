#pragma once

#include "../../type.hpp"
#include "./expr.hpp"
#include "block_expr.hpp"
#include <iostream>

namespace mr {
    namespace middle {
        namespace tast {
            struct WhileLoop : public Expr {
                Unique<Expr>      cond;
                Unique<BlockExpr> body;

                WhileLoop(Unique<Expr> c, Unique<BlockExpr> b)
                    : Expr(types::Ty{types::UnitTy{}}), cond(std::move(c)),
                      body(std::move(b)) {}
            };
        } // namespace tast

    } // namespace middle

} // namespace mr
