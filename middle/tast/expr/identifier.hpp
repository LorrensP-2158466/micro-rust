#pragma once

#include "../../type.hpp"
#include "./expr.hpp"
#include <string>

namespace mr {
    namespace middle {
        namespace tast {

            struct Identifier : public Expr {
                std::string symbol;

                Identifier(std::string s, types::Ty t) : Expr(t), symbol(s) {}
            };
        } // namespace tast

    } // namespace middle

} // namespace mr
