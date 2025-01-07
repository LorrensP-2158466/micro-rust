#pragma once

#include "expr.hpp"
#include "mr_util.hpp"
#include "string"

namespace mr { namespace expr {
    ENUM_DEFINE(
        BinOp,
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
    )

    static const char *binop_to_str(BinOp bo) {
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
        U<Expr> left, right;
        BinOp op;

        BinOpExpr(U<Expr> left, BinOp bo, U<Expr> right)
            : Expr(left->loc + right->loc)
            , left(std::move(left))
            , right(std::move(right))
            , op(bo) {}

        ~BinOpExpr() = default;

        void print(const int depth) const override {
            const auto indent = std::string(depth, '\t');
            std::cout << indent << "BinOp(" << binop_to_str(op) << "):\n";
            std::cout << indent << "  left:\n";
            left->print(depth + 1);
            std::cout << indent << "  right:\n";
            right->print(depth + 1);
        }
    };

}} // namespace mr::expr
