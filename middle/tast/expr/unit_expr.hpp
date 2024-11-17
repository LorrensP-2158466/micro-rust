#pragma once
#include "../../type.hpp"
#include "./expr.hpp"
#include <iostream>
#include <string>

namespace mr {
    namespace middle {
        namespace tast {
            // will later be used to create tuple expressions
            struct Unit : public Expr {
                Unit() : Expr(types::Ty{types::UnitTy{}}) {}
            };
        } // namespace tast

    } // namespace middle

} // namespace mr
