#pragma once

#include "expr.hpp"

namespace mr {
    namespace expr {
        enum class UnaryOp {
            Borrow,      // &
            MutBorrow,   // &mut
            Deref, // *
            Not,         // !
            Negate,      // -
        };

        static const char* const unary_op_to_str(UnaryOp op){
            switch (op)
            {
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

        class UnaryOpExpr : public Expr {
            UnaryOp      _op;
            Unique<Expr> _expr;

          public:
            UnaryOpExpr(UnaryOp op, Unique<Expr> expr)
                : Expr(), _op(op), _expr(std::move(expr)) {}


            void print(const int depth) const override{
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "UnaryOp(" << unary_op_to_str(_op) << "):\n";
                std::cout << indent << "  expr:\n";
                _expr->print(depth + 1);
            }
        };
    } // namespace expr

} // namespace mr
