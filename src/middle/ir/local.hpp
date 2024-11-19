#pragma once

#include "../type.hpp"
#include <iostream>
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

                friend std::ostream& operator<<(std::ostream& o, const LocalId id) {
                    o << '_' << id.id;
                    return o;
                }
            };
        } // namespace ir

    } // namespace middle

} // namespace mr