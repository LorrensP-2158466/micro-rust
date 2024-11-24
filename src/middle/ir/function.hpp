#pragma once

#include "../build/basic_blocks.hpp"
#include "block.hpp"
#include "local.hpp"
#include <unordered_map>
#include <vector>
namespace mr {
    namespace middle {
        namespace ir {
            struct Function {
                std::string        name; // debugging still
                build::BasicBlocks _blocks;
                // Local declarations:
                // - return type is always first
                // - arguments
                // - user declared
                std::vector<Local> locals;
                size_t             arg_count;
            };
        } // namespace ir

    } // namespace middle

} // namespace mr
