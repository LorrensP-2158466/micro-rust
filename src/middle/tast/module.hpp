#pragma once

#include "expr.hpp"
#include "stmt.hpp"
#include "types/type.hpp"

namespace mr { namespace middle { namespace tast {

    struct Param {
        std::string id;
        types::Ty type;
        ir::Mutability mut;
    };
    // Typed AST of a single function
    struct TAst {
        std::string name;
        std::vector<Param> params;
        BlockExpr body;
        types::Ty ret_type;
    };
}}} // namespace mr::middle::tast
