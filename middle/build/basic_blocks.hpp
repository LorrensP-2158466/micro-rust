#pragma once

/**
 *
 * Convenience structure for holding and updating a collection of basic blocks that all
 * point to eachother
 *
 * A CFG if you will
 */

#include "../ir/module.hpp"
#include "mr_util.hpp"
#include <unordered_map>

namespace mr {
    namespace middle {
        namespace build {
            using namespace ::mr::middle::types;
            using namespace ::mr::middle::tast;
            using namespace ::mr::middle::inference;
            using namespace ::mr::middle::ir;
            // Define a custom hash function for the BlockId
            struct BlockIdHasher {
                // this effectivly creates a index vec i think?
                // because im assuring that the id's are "unique"
                size_t operator()(const BlockId& p) const { return p.id; }
            };
            class BasicBlocks {
                std::unordered_map<BlockId, Block, BlockIdHasher> _blocks;

                void push_stmt(BlockId block, Statement stmt) {
                    _blocks[block].statements.push_back(std::move(stmt));
                }

              public:
                BlockId create_new_block() {
                    const auto id = BlockId{_blocks.size()};
                    _blocks.insert({id, Block()});
                    return id;
                }

                void push_assign(BlockId block, Place lhs, RValue rhs) {
                    return push_stmt(block, Assign{lhs, rhs});
                }
            };
        } // namespace build

    } // namespace middle

} // namespace mr
