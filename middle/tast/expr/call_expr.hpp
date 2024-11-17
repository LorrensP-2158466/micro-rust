#pragma once

#include "../../type.hpp"
#include "./expr.hpp"

namespace mr {
    namespace middle {
        namespace tast {
            struct CallExpr : public Expr {
                std::string               id;
                std::vector<Unique<Expr>> args;

                CallExpr(std::string i, std::vector<Unique<Expr>> a, types::Ty t)
                    : Expr(t), id(i), args(std::move(a)) {}
            };
        } // namespace tast
    } // namespace middle

} // namespace mr
