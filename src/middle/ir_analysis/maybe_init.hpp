#pragma once

#include "analysis.hpp"
#include "mr_util.hpp"

namespace mr {
    namespace middle {
        namespace analysis {

            // tracks for every block, the locals that are potentially initiliazed
            // 1 => init
            // 0 => uninit
            class MaybeInit : public ForwardAnalysis {

                State bottom_value(const Function &f) override { return State(f.locals.size()); }
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
                    state.insert(assign.place.local);
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