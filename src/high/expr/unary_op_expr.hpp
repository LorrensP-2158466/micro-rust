#pragma once

#include "expr.hpp"

namespace mr {
    namespace expr {
        enum class UnaryOp {
            Borrow,    // &
            MutBorrow, // &mut
            Deref,     // *
            Not,       // !
            Negate,    // -
        };

        static const char* unary_op_to_str(UnaryOp op) {
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

        struct UnaryOpExpr : public Expr {
            UnaryOp _op;
            U<Expr> _expr;

            UnaryOpExpr(UnaryOp op, location op_loc, U<Expr> expr)
                : Expr(op_loc + expr->loc), _op(op), _expr(std::move(expr)) {}

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "UnaryOp(" << unary_op_to_str(_op) << "):\n";
                std::cout << indent << "  expr:\n";
                _expr->print(depth + 1);
            }
        };
    } // namespace expr

} // namespace mr
