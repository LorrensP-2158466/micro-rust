#pragma once

#include "../../type.hpp"
#include "./expr.hpp"

namespace mr {
    namespace middle {
        namespace tast {
            enum class UnaryOp {
                Borrow,    // &
                MutBorrow, // &mut
                Deref,     // *
                Not,       // !
                Negate,    // -
            };

            static const char* const unary_op_to_str(UnaryOp op) {
                switch (op) {
                case UnaryOp::Borrow:
                    return "'&'";
                case UnaryOp::MutBorrow:
                    return "'&mut'";
                case UnaryOp::Deref:
                    return "'*'";
                case UnaryOp::Not:
                    return "'!'";
                case UnaryOp::Negate:
                    return "'-'";
                default:
                    break;
                }
            }

            UnaryOp un_op_from_ast(expr::UnaryOp op) {
                return (UnaryOp)op;
            }

            struct UnaryOpExpr : public Expr {
                UnaryOp      op;
                Unique<Expr> expr;

                UnaryOpExpr(expr::UnaryOp o, Unique<Expr> e, types::Ty t)
                    : Expr(t), op(un_op_from_ast(o)), expr(std::move(e)) {}

                static Unique<Expr> unique(expr::UnaryOp o, Unique<Expr> e, types::Ty t) {
                    return std::unique_ptr<Expr>(new UnaryOpExpr(o, std::move(e), t));
                }
            };
        } // namespace tast
    } // namespace middle

} // namespace mr
