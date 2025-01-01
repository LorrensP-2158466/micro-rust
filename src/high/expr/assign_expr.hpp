#pragma once

#include "module.hpp"
#include <string>

namespace mr {
    namespace expr {
        enum class AssignOp {
            Eq,
            PlusEq,
            MinEq,
            MulEq,
            DivEq
        };

        static const char* assign_op_to_str(const AssignOp op) {
            switch (op) {
            case AssignOp::Eq:
                return "=";
            case AssignOp::MulEq:
                return "*=";
            case AssignOp::PlusEq:
                return "+=";
            case AssignOp::DivEq:
                return "/=";
            case AssignOp::MinEq:
                return "-=";
            }
        }

        struct AssignExpr : public Expr {
            // in rust an assignment can be like this:
            // Expr AssignOp Expr
            // but were not allowing this just yet so we have:
            // identifier AssignOp Expr
            U<Expr>  _assignee;
            AssignOp _op;
            U<Expr>  _expr;

            AssignExpr(U<Expr> assignee, AssignOp op, U<Expr> expr)
                : Expr(), _assignee(std::move(assignee)), _op(op),
                  _expr(std::move(expr)) {};
            ~AssignExpr() = default;

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                const auto assign = indent + "Assignment Expression:\n";
                const auto id = indent + "  assignee:\n";
                _assignee->print(depth + 1);
                const auto op = indent + "  operator: '" + assign_op_to_str(_op) + "'\n";
                const auto expr = indent + "  expr:\n";
                std::cout << assign << id << op << expr;
                _expr->print(depth + 1);
            }
        };
    } // namespace expr

} // namespace mr
