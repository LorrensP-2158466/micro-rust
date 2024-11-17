#pragma once

#include "function.hpp"
#include "mr_util.hpp"
#include <unordered_map>

namespace mr {
    namespace middle {
        namespace ir {
            class Ir {
                std::unordered_map<std::string, Function> _functions;
            };
        } // namespace ir

    } // namespace middle

} // namespace mr
