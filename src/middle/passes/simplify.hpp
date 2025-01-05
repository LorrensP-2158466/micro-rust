
#pragma once

#include "../ir/module.hpp"
#include "../traversal/preorder.hpp"
#include "mr_util.hpp"
#include "pass.hpp"
#include <algorithm>
#include <fmt/ranges.h>
#include <numeric>
#include <spdlog/spdlog.h>
#include <vector>

namespace mr {
    namespace middle {
        namespace ir_pass {
            using namespace middle::ir;

            struct Simplifier {
                BasicBlocks&              blocks;
                std::vector<unsigned int> predecessor_count;

                Simplifier(BasicBlocks& blocks)
                    : blocks(blocks),
                      predecessor_count(std::vector<unsigned int>(blocks.size())) {
                    predecessor_count[0] = 1;
                    for (const auto& [idx, data] : traversal::PreOrder(blocks)) {
                        for (const auto target : data.terminator().successors()) {
                            predecessor_count[target.id()] += 1;
                        }
                    }
                }

                static void remove_dead_blocks(BasicBlocks& blocks) {
                    fmt::println("removing dead blocks");
                    const auto reachable = traversal::reachable_bitset(blocks);

                    // if everything is reachable, do nothing
                    const auto blocks_amt = blocks.size();
                    if (blocks_amt ==
                        std::count(reachable.cbegin(), reachable.cend(), true)) {
                        return;
                    }

                    // we have to change the terminators that go to another block so they
                    // go the right index because we will be shrinking the list of blocks
                    // say we have this:
                    // bb1 -> bb2
                    // bb2 -> bb3 (bb2 is empty)
                    // bb3 -> bb1, bb3 -> bb4
                    // bb4 return
                    // when we remove bb2 we can't let the indices stay, the have to be
                    // *replaced*
                    std::vector<BlockId> replacements(blocks_amt);
                    for (size_t i = 0; i < blocks_amt; i++) {
                        replacements[i] = BlockId{i};
                    }

                    size_t original_index = 0;
                    size_t used_index = 0;
                    std::erase_if(blocks.raw_blocks(), [&](auto&) {
                        if (!reachable[original_index]) {
                            original_index += 1;
                            return true;
                        }
                        replacements[original_index] = BlockId{used_index};
                        original_index += 1;
                        used_index += 1;
                        return false;
                    });

                    // replace the original go to's with the new ones
                    for (auto& block : blocks) {
                        for (auto& target : block.terminator().successors()) {
                            target = replacements[target.id()];
                        }
                    }
                }

                void simplify() {
                    std::vector<ir::BlockId> merged_blocks{};
                    bool                     changed;
                    do {
                        changed = false;
                        for (const auto bb : blocks.indices()) {
                            // if block is not reachable, skip it because it will never be
                            // made reachable
                            if (predecessor_count[bb.id()] == 0) continue;
                            fmt::println("doing: {}", bb);
                            auto terminator_opt = take(blocks.block(bb)._terminator);
                            if (!terminator_opt)
                                throw std::runtime_error("INVALID TERMINATOR");
                            auto terminator = *terminator_opt;
                            for (auto& succ : terminator.successors()) {
                                collapse_goto_chain(succ, changed);
                            }

                            merged_blocks.clear();
                            bool inner_changed = true;
                            while (inner_changed) {
                                inner_changed = false;
                                inner_changed |=
                                    merge_successors(merged_blocks, terminator);
                                changed |= inner_changed;
                            }

                            const auto stmts_to_merge = std::accumulate(
                                merged_blocks.begin(),
                                merged_blocks.end(),
                                0,
                                [&](size_t sum, BlockId bb) {
                                    return sum + blocks.block(bb).statements.size();
                                }
                            );

                            if (stmts_to_merge > 0) {
                                std::vector<Statement> statements =
                                    std::move(blocks.block(bb).statements);

                                statements.reserve(statements.size() + stmts_to_merge);

                                for (BlockId from : merged_blocks) {
                                    auto& from_statements = blocks.block(from).statements;
                                    statements.insert(
                                        statements.end(),
                                        std::make_move_iterator(from_statements.begin()),
                                        std::make_move_iterator(from_statements.end())
                                    );
                                    from_statements.clear();
                                }

                                blocks.block(bb).statements = std::move(statements);
                            }
                            blocks.block(bb)._terminator = terminator;
                        }
                    } while (changed);
                    // after all of this simplifying, we also want to remove goto's to
                    // empty blocks with only a return, by replacing that goto with a
                    // return
                    remove_dead_blocks(blocks);
                    remove_simple_returns();

                    remove_dead_blocks(blocks);
                }

                void remove_simple_returns() {
                    fmt::println("simple returns");
                    fmt::println("{}", predecessor_count);

                    std::vector<bool> simple_returns(blocks.size());
                    for (const auto bb_idx : blocks.indices()) {
                        fmt::println("doing: {}", bb_idx);

                        if (blocks[bb_idx].statements.empty() &&
                            has_variant<ir::Return>(blocks[bb_idx].terminator())) {
                            simple_returns[bb_idx.id()] = true;
                        }
                    }
                    fmt::println("here");
                    for (auto& bb : blocks) {
                        std::visit(
                            overloaded{
                                [&](const GoTo& go) {
                                    if (simple_returns[go.target.id()]) {
                                        bb.terminator() = Terminator(ir::Return{});
                                    }
                                },
                                [](const auto&) {}
                            },
                            bb.terminator()
                        );
                    }
                }

                std::optional<ir::Terminator>
                take_terminator_if_simple_goto(ir::BlockId block) {
                    // Example logic: return a Goto terminator if it exists and matches
                    // criteria
                    const auto& bb = blocks.block(block);
                    if (std::holds_alternative<ir::GoTo>(bb.terminator()) &&
                        bb.statements.empty()) {
                        return take(blocks.block(block)._terminator);
                    }
                    return {};
                }

                void collapse_goto_chain(ir::BlockId& start, bool& changed) {
                    std::vector<std::pair<ir::BlockId, Terminator>> terminators{};

                    ir::BlockId current = start;

                    std::optional<Terminator> terminator_opt;
                    while ((terminator_opt = take_terminator_if_simple_goto(current))) {
                        // Check if it's a Goto kind
                        if (!terminator_opt) throw std::runtime_error("HERE WTF");
                        auto        terminator = std::get<ir::GoTo>(*terminator_opt);
                        ir::BlockId target = terminator.target;
                        terminators.emplace_back(current, std::move(terminator));
                        current = target;
                    }

                    BlockId last = current;
                    start = last;
                    // Rewrite the chain
                    while (!terminators.empty()) {
                        auto [current, terminator] = std::move(terminators.back());
                        // terminator is a GoTo
                        BlockId& target = std::get<ir::GoTo>(terminator).target;
                        changed |= (target != last);
                        target = last;
                        if (predecessor_count[current.id()] == 1) {
                            // This is the last reference to current
                            predecessor_count[current.id()] = 0;
                        } else {
                            predecessor_count[target.id()] += 1;
                            predecessor_count[current.id()] -= 1;
                        }

                        blocks.block(current)._terminator = std::move(terminator);

                        terminators.pop_back();
                    }
                }

                // we can merge blocks on 1 condition:
                //  - the terminator must be a goto terminator
                //  - the successor of the terminator can only have 1 predecessor (the
                //  block of the terminator)
                // in this case, it doesnt matter if the blocks are split or not, since
                // the flow of the program is straight forward.
                bool merge_successors(std::vector<BlockId>& to_merge, Terminator& term) {
                    if (const auto* goto_term = std::get_if<GoTo>(&term);
                        goto_term && predecessor_count[goto_term->target.id()] == 1) {
                        BlockId target = goto_term->target;
                        auto    target_term = take(blocks.block(target)._terminator);
                        // this is weird, but handle it like nothing is wrong
                        if (!target_term) return false;
                        term = *target_term;

                        // we have a merge
                        to_merge.push_back(target);
                        predecessor_count[target.id()] = 0;
                        return true;
                    }
                    return false;
                }
            };

            class Simplify : public IrPass {
              public:
                ~Simplify() = default;
                const char* name() const noexcept override { return "Simplify Ir"; }

                void run(Function& body) const override {
                    Simplifier(body._blocks).simplify();
                }
            };
        } // namespace ir_pass
    } // namespace middle

} // namespace mr
