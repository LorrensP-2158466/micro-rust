#pragma once

#include "datastructures.hpp"
#include "fmt/std.h"
#include "ir/module.hpp"
#include "ir/traversal/postorder.hpp"
#include "spdlog/spdlog.h"
#include <fmt/core.h>
#include <fmt/ranges.h>

namespace mr { namespace middle { namespace ir { namespace analysis {
    // only analyze on locals fuck that
    template <typename DomainT> class ForwardAnalysis {
      public:
        using Domain = DomainT;
        using Results = std::vector<Domain>;
        virtual Domain bottom_value(const Function &f) = 0;
        // Transfer functions
        virtual void init_start_bb(const Function &f, Domain &state) = 0;
        virtual void apply_statement(Domain &state, const Statement &stmt) = 0;
        virtual void apply_call(Domain &state, const Place &) = 0;
        // TODO: when we need terminator transfer, i will add it

        // returns state for every block
        Results iterate_till_fixpoint(const Function &f) {
            Results result_states{};
            result_states.reserve(f._blocks.size());
            for (size_t i = 0; i < f._blocks.size(); ++i) {
                result_states.emplace_back(bottom_value(f));
            }
            init_start_bb(f, result_states.front());

            auto queue = WorkQueue<BlockId>(f._blocks.size());
            for (const auto &[idx, _] : traversal::reverse_postorder(f._blocks)) {
                queue.insert(idx);
            }
            const auto propogate = [&](BlockId target, Domain &state) {
                auto changed = result_states[target.id()].union_changed(state);

                // if it changed, we need to check it again
                if (changed) {
                    queue.insert(target);
                }
            };
            auto state = bottom_value(f);
            while (auto bb_idx = queue.pop()) {
                state = result_states[bb_idx->id()];

                auto &bb = f._blocks[*bb_idx];
                for (const auto &statement : bb.statements) {
                    apply_statement(state, statement);
                }

                std::visit(overloaded{[&](const Call &r) {
                                          apply_call(state, r.dest_place);
                                          const auto target = r.successors()[0].id();
                                          propogate(target, state);
                                      },
                                      [&](const auto &t) {
                                          for (const auto bb : t.successors()) {
                                              propogate(bb, state);
                                          }
                                      }},
                           bb.terminator());
            }
            return result_states;
        }
    };
}}}} // namespace mr::middle::ir::analysis