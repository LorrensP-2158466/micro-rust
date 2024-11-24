#pragma once

/**
 *
 * Convenience structure for holding and updating a collection of basic blocks that all
 * point to eachother
 *
 * A CFG if you will
 */

#include "../ir/module.hpp"
#include "../type.hpp"
#include "mr_util.hpp"
#include <vector>

namespace mr {
    namespace middle {
        namespace build {
            using namespace ir;
            // Define a custom hash function for the BlockId
            struct BlockIdHasher {
                // this effectivly creates a index vec i think?
                // because im assuring that the id's are "unique"
                size_t operator()(const BlockId& p) const { return p.id; }
            };
            class BasicBlocks {
                std::vector<Block> _blocks;

                void push_stmt(BlockId block, Statement stmt) {
                    _blocks.at(block.id).statements.push_back(std::move(stmt));
                }

              public:
                BasicBlocks() = default;
                BasicBlocks(BasicBlocks&& other) : _blocks(std::move(other._blocks)) {}

                auto begin() { return _blocks.begin(); }
                auto end() { return _blocks.end(); }

                auto begin() const { return _blocks.begin(); }
                auto end() const { return _blocks.end(); }
                auto cbegin() const { return _blocks.cbegin(); }
                auto cend() const { return _blocks.cend(); }

                size_t size() const noexcept { return _blocks.size(); }

                BlockId create_new_block() {
                    const auto id = BlockId{_blocks.size()};
                    _blocks.emplace_back();
                    return id;
                }

                void terminate(BlockId block, Terminator term) {
                    _blocks.at(block.id).terminator =
                        std::make_unique<Terminator>(Terminator(term));
                }

                void go_to(BlockId from, BlockId target) {
                    assert(target.id < _blocks.size());
                    terminate(from, Terminator(GoTo{target}));
                }

                void push_assign(BlockId block, Place lhs, RValue rhs) {
                    return push_stmt(block, Assign{lhs, rhs});
                }

                void push_unit_assign(BlockId block, Place lhs) {
                    return push_stmt(
                        block,
                        Assign{
                            lhs,
                            RValue(AsIs(Operand::const_(Scalar{0}, types::Ty::unit())))
                        }
                    );
                }
            };
        } // namespace build

    } // namespace middle

} // namespace mr
