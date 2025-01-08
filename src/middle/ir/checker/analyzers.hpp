#pragma once

#include "ir/analysis/analysis.hpp"
#include "mr_util.hpp"

namespace mr { namespace middle { namespace ir { namespace checker {
    using namespace analysis;

    // tracks for every block, the locals that are potentially initiliazed
    // 1 => init
    // 0 => uninit
    class MaybeInit : public ForwardAnalysis<BitSet<LocalId>> {

        ForwardAnalysis::Domain bottom_value(const Function &f) override {
            return BitSet<LocalId>(f.locals.size());
        }
        void init_start_bb(const Function &f, ForwardAnalysis::Domain &state) override {
            // args are surely init
            for (const auto l : f.args_indices()) {
                state.insert(l);
            }
        }
        void apply_statement(ForwardAnalysis::Domain &state, const Statement &stmt) override {
            if (!has_variant<Assign>(stmt))
                return;
            const auto &assign = std::get<Assign>(stmt);
            // partial?
            if (!assign.place.projections.empty())
                return;
            state.insert(assign.place.local);
        }
        void apply_call(ForwardAnalysis::Domain &state, const Place &p) override {
            if (!p.projections.empty())
                return;
            state.insert(p.local);
        }
    };

    // tracks for every block, the locals that are potentially uninitialized
    // 0 => init
    // 1 => uninit
    class MaybeUninit : public ForwardAnalysis<BitSet<LocalId>> {
        ForwardAnalysis::Domain bottom_value(const Function &f) override {
            // everything is uninit, check for counter evidence
            return BitSet<LocalId>(f.locals.size());
        }
        void init_start_bb(const Function &f, ForwardAnalysis::Domain &state) override {
            // args are surely init
            state.complement();
            for (const auto l : f.args_indices()) {
                state.remove(l);
            }
        }
        void apply_statement(ForwardAnalysis::Domain &state, const Statement &stmt) override {
            if (!has_variant<Assign>(stmt))
                return;
            const auto &assign = std::get<Assign>(stmt);
            // partial?
            if (!assign.place.projections.empty())
                return;
            // this is not uninit
            state.remove(assign.place.local);
        }
        void apply_call(ForwardAnalysis::Domain &state, const Place &p) override {
            if (!p.projections.empty())
                return;
            state.remove(p.local);
        }
    };

    // tracks for every block, the locals that are were potentially  initialized before the current
    // block can be used for checking if a immutable can be assigned to 1 => init 0 => uninit
    class EverInit : public ForwardAnalysis<BitSet<LocalId>> {
        ForwardAnalysis::Domain bottom_value(const Function &f) override {
            // everything is uninit, check for counter evidence
            return BitSet<LocalId>(f.locals.size());
        }
        void init_start_bb(const Function &f, ForwardAnalysis::Domain &state) override {
            for (const auto l : f.args_indices()) {
                state.insert(l);
            }
        }
        void apply_statement(ForwardAnalysis::Domain &state, const Statement &stmt) override {
            std::visit(
                overloaded{
                    [&](const Assign &assign) {
                        // ? partial
                        if (!assign.place.projections.empty())
                            return;
                        state.insert(assign.place.local);
                    },
                    // uninit so we can assign to immutables inside of loops
                    // this way, if state is propogated to loop block, these locals are not inside
                    // of that state
                    [&](const Dead &dead) { state.remove(dead.local); },
                    [&](const auto) {}
                },
                stmt
            );
        }
        void apply_call(ForwardAnalysis::Domain &state, const Place &p) override {
            if (!p.projections.empty())
                return;
            state.remove(p.local);
        }
    };
}}}} // namespace mr::middle::ir::checker