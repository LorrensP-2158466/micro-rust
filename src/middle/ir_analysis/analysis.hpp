#pragma once

#include "datastructures.hpp"
#include "ir/module.hpp"
#include "traversal/postorder.hpp"

namespace mr {
    namespace middle {
        namespace analysis {
            using namespace ir;
            // only analyze on locals fuck that
            using State = BitSet<LocalId>;
            class ForwardAnalysis {
              public:
                virtual State bottom_value(const Function &f) = 0;
                virtual void init_start_bb(const Function &f, State &state) = 0;
                virtual void apply_statement(State &state, const Statement &stmt) = 0;
                virtual void apply_call(State &state, const Place &) = 0;

                // returns state for every block
                std::vector<State> iterate_till_fixpoint(const Function &f) {
                    auto result_states = std::vector<State>(f._blocks.size(), State(f.locals.size()));
                    for (size_t i = 0; i < f._blocks.size(); ++i) {
                        result_states[i] = bottom_value(f);
                    }
                    init_start_bb(f, result_states.front());

                    auto queue = WorkQueue<BlockId>(f._blocks.size());
                    for (const auto &[idx, _] : traversal::reverse_postorder(f._blocks)) {
                        queue.insert(idx);
                    }
                    auto state = bottom_value(f);
                    while (auto bb_idx = queue.pop()) {
                        state = result_states[bb_idx->id()];

                        auto &bb = f._blocks[*bb_idx];
                        for (const auto &statement : bb.statements) {
                            apply_statement(state, statement);
                        }

                        const auto propogate = [&](BlockId target, State &target_state) {
                            auto changed = target_state.union_changed(state);
                            // if it changed, we need to check it again
                            if (changed) {
                                queue.insert(target);
                            }
                        };

                        std::visit(overloaded{[&](const Call &r) {
                                                  apply_call(state, r.dest_place);
                                                  const auto target = r.successors()[0].id();
                                                  propogate(target, result_states[target]);
                                              },
                                              [&](const auto &t) {
                                                  for (const auto bb : t.successors()) {
                                                      propogate(bb, result_states[bb.id()]);
                                                  }
                                              }},
                                   bb.terminator());
                    }
                    return result_states;
                }
            };
        } // namespace analysis
    } // namespace middle
} // namespace mr