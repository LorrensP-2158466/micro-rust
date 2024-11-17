#pragma once

#include "../../type.hpp"

namespace mr {
    namespace middle {
        namespace tast {
            struct Expr {
                types::Ty type;

                Expr(types::Ty t) : type(t) {}
                virtual ~Expr() = default;
            };
        } // namespace tast
    } // namespace middle

} // namespace mr
