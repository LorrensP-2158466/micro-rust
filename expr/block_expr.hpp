#pragma once

#include "../ast/module.hpp"
#include "expr.hpp"
#include "mr_util.hpp"
#include <memory>
#include <string>
#include <vector>

namespace mr {
    namespace expr {
        class BlockExpr : public Expr {
            std::vector<Unique<Stmt>> _statements;
            Unique<Expr>              _implicit_return;

          public:
            BlockExpr(std::vector<Unique<Stmt>> statements,
                      Unique<Expr>              imlplicit_ret)
                : Expr(), _statements(std::move(statements)),
                  _implicit_return(std::move(imlplicit_ret)) {};

            ~BlockExpr() = default;

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "BlockExpr:\n";
                for (const auto& stmt : _statements) {
                    stmt->print(depth + 1);
                }
                if (_implicit_return) {
                    std::cout << indent << "Implicit Return expression:\n";
                    _implicit_return->print(depth + 1);
                }
            }
        };
    } // namespace expr

} // namespace mr
