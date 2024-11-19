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
                build::BasicBlocks _blocks;
                // Local declarations:
                // - return type is always first
                // - arguments
                // - user declared
                std::vector<Local> locals;
            };
        } // namespace ir

    } // namespace middle

} // namespace mr
