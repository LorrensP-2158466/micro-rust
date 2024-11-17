#pragma once

#include "../type.hpp"
#include "./expr/module.hpp"
#include "stmt.hpp"

namespace mr {
    namespace middle {
        namespace tast {

            struct Param {
                std::string id;
                types::Ty   type;
                bool        mut;
            };
            // Typed AST of a single function
            struct TAst {
                std::string        name;
                std::vector<Param> params;
                Unique<BlockExpr>  body;
                types::Ty          ret_type;
            };
        } // namespace tast

    } // namespace middle

} // namespace mr
