#pragma once

#include "../type.hpp"
#include <string>

namespace mr {
    namespace middle {
        namespace ir {
            struct Local {
                std::string id; // error reporting

                // for later when references are introduced, we have to remember the type
                types::Ty ty;

                bool mut; // used for borrow check, can't take mutable reference to non
                          // mutable
            };

            struct LocalId {
                size_t id;
            };
        } // namespace ir

    } // namespace middle

} // namespace mr