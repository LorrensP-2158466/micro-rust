#pragma once

#include "../../ir/values.hpp"
#include "../../type.hpp"
#include "expr.hpp"
#include <string>

namespace mr {
    namespace middle {
        namespace tast {
            struct AssignExpr : public Expr {
                std::string  id;
                Unique<Expr> expr;

                AssignExpr(std::string id, Unique<Expr> ex, types::Ty ty)
                    : Expr(ty), id(id), expr(std::move(ex)) {}

                static Unique<Expr> unique(std::string id, Unique<Expr> ex,
                                           types::Ty ty) {
                    return std::unique_ptr<Expr>(new AssignExpr(id, std::move(ex), ty));
                }
            };

            struct AssignOpExpr : public Expr {
                std::string  id;
                ir::BinOp    op;
                Unique<Expr> expr;

                AssignOpExpr(std::string id, ir::BinOp op, Unique<Expr> ex, types::Ty ty)
                    : Expr(ty), id(id), op(op), expr(std::move(ex)) {}

                static Unique<Expr> unique(std::string id, ir::BinOp op, Unique<Expr> ex,
                                           types::Ty ty) {
                    return std::unique_ptr<Expr>(
                        new AssignOpExpr(id, op, std::move(ex), ty));
                }
            };
        } // namespace tast

    } // namespace middle

} // namespace mr
