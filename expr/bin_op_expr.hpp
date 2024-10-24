#pragma once

#include "expr.hpp"
#include "mr_util.hpp"
#include "string"

namespace mr {
    namespace expr {
        enum class BinOp {
            Mul,   // *
            Div,   // /
            Plus,  // +
            Min,   // -
            L_AND, // &&
            L_OR,  // ||

            Eq,   // ==
            NEq,  // !=
            Gt,   // >
            Lt,   // <
            GtEq, // >=
            LtEq, // <=
        };

        static const char* binop_to_str(BinOp bo) {
            switch (bo) {
            case BinOp::Plus:
                return "'+'";
            case BinOp::Min:
                return "'-'";
            case BinOp::Mul:
                return "'*'";
            case BinOp::Div:
                return "'/'";
            case BinOp::L_AND:
                return "'&&'";
            case BinOp::Eq:
                return "'=='";
            case BinOp::NEq:
                return "'!='";
            case BinOp::Gt:
                return "'>'";
            case BinOp::Lt:
                return "'<'";
            case BinOp::LtEq:
                return "'<='";
            case BinOp::GtEq:
                return "'>='";
            default:
                throw std::runtime_error("UNKOWN Binary Operator");
            }
        }

        /**
         * BinOpExpr:
         *  Expr BinOp Expr
         */
        struct BinOpExpr : public Expr {
            Unique<Expr> _left, _right;
            BinOp        _bin_op;

            BinOpExpr(Unique<Expr> left, BinOp bo, Unique<Expr> right)
                : _left(std::move(left)), _right(std::move(right)),
                  _bin_op(bo) {}

            ~BinOpExpr() = default;

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "BinOp(" << binop_to_str(_bin_op)
                          << "):\n";
                std::cout << indent << "  left:\n";
                _left->print(depth + 1);
                std::cout << indent << "  right:\n";
                _right->print(depth + 1);
            }
        };

    } // namespace expr

} // namespace mr
