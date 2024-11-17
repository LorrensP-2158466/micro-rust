#pragma once

#include "block.hpp"
#include "local.hpp"
#include <unordered_map>
#include <variant>
#include <vector>

namespace mr {
    namespace middle {
        namespace ir {

            // goes to the block with index of `block_target` inside the current function
            struct GoTo {
                BlockId block_target;
            };
            // returns out of the current function with the value currently in 0_return
            struct Return {};

            // used for assert
            struct Assert {};

            struct SwitchInt {
                Operand op;
                // hahahahah
                std::unordered_map<size_t, BlockId> targets;
                BlockId                             otherwise_target;
            };
            using terminator_variant_t = std::variant<GoTo, Return, Assert, SwitchInt>;
            struct Terminator : terminator_variant_t {};
        } // namespace ir

    } // namespace middle

} // namespace mr
