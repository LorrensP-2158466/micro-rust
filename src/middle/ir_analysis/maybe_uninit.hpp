#pragma once

#include "analysis.hpp"

namespace mr {
    namespace middle {
        namespace analysis {

            // tracks for every block, the locals that are potentially uninitialized
            // 0 => init
            // 1 => uninit
            class MaybeUninit : public ForwardAnalysis {
                State bottom_value(const Function &f) override {
                    // everything is uninit, check for counter evidence
                    return State::all_set(f.locals.size());
                }
                void init_start_bb(const Function &f, State &state) override {
                    // args are surely init
                    for (const auto l : f.args_indices()) {
                        state.insert(l);
                    }
                }
                void apply_statement(State &state, const Statement &stmt) override {
                    if (!has_variant<Assign>(stmt))
                        return;
                    const auto &assign = std::get<Assign>(stmt);
                    // partial?
                    if (!assign.place.projections.empty())
                        return;
                    // this is not uninit
                    state.remove(assign.place.local);
                }
                void apply_call(State &state, const Place &p) override {
                    if (!p.projections.empty())
                        return;
                    state.insert(p.local);
                }
            };
        } // namespace analysis
    } // namespace middle
} // namespace mr