#pragma once

#include "../../type.hpp"
#include "../stmt.hpp"
#include "./expr.hpp"
#include "mr_util.hpp"
#include <memory>
#include <string>
#include <vector>

namespace mr {
    namespace middle {
        namespace tast {

            struct BlockExpr : public Expr {
                std::vector<Stmt> _statements;
                Unique<Expr>      _tail;

                ~BlockExpr() = default;

                BlockExpr(std::vector<Stmt> s, Unique<Expr> tail, types::Ty t)
                    : Expr(t), _statements(std::move(s)), _tail(std::move(tail)) {}

                static Unique<Expr> unique(std::vector<Stmt> s, Unique<Expr> tail,
                                           types::Ty t) {
                    return std::unique_ptr<Expr>(
                        new BlockExpr(std::move(s), std::move(tail), t));
                }
            };
        } // namespace tast

    } // namespace middle

} // namespace mr
