#pragma once

#include "../ast/module.hpp"
#include "expr.hpp"
#include "mr_util.hpp"
#include <memory>
#include <string>
#include <vector>

namespace mr { namespace expr {
    class BlockExpr : public Expr {
        std::vector<U<Stmt>> _statements;
        U<Expr> _implicit_return;

      public:
        BlockExpr(std::vector<U<Stmt>> statements, U<Expr> imlplicit_ret, location loc)
            : Expr(loc)
            , _statements(std::move(statements))
            , _implicit_return(std::move(imlplicit_ret)) {};

        ~BlockExpr() = default;

        void print(const int depth) const override {
            const auto indent = std::string(depth, '\t');
            std::cout << indent << "BlockExpr:\n";
            for (const auto &stmt : _statements) {
                stmt->print(depth + 1);
            }
            std::cout << indent << "Implicit Return expression:\n";
            if (_implicit_return)
                _implicit_return->print(depth + 1);
        }

        const auto &statements() const { return _statements; }

        const Expr *tail_expr() const { return _implicit_return.get(); }
    };
}} // namespace mr::expr
