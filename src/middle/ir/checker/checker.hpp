#pragma once

#include "analyzers.hpp"
#include "datastructures.hpp"
#include "errors/ctx.hpp"
#include "ir/module.hpp"
#include "ir/visitor.hpp"

namespace mr { namespace middle { namespace ir { namespace checker {
    // currently only checks inits and assign to non mut
    // can be used for borrow checking in future
    class Checker : public Visitor {
        const Function &fn;
        error::ErrorCtx &ecx;
        MaybeUninit::Results uninit_entry_states;
        MaybeInit::Results init_entry_states;

        // if we report an error on a particular error, we don't report any more errors on that local
        // because we can't be sure that that error occured because of the first one.
        // this is the programmers duty
        BitSet<LocalId> tainter_by_error;

      public:
        Checker(const Function &fn, error::ErrorCtx &ecx)
            : fn(fn)
            , ecx(ecx)
            , uninit_entry_states(MaybeUninit().iterate_till_fixpoint(fn))
            , init_entry_states(MaybeInit().iterate_till_fixpoint(fn))
            , tainter_by_error(fn.all_locals().size()) {}

        void check() { Visitor::visit_fn(fn); }

        void visit_local(const LocalId &local, PlaceCtx ctx, Location l) override {
            // based on ctx, we know what to do
            auto &uninit_state = uninit_entry_states.at(l.basic_block.id());
            auto &init_state = init_entry_states.at(l.basic_block.id());
            std::visit(overloaded{[&](const MutUseCtx cx) {
                                      // we don't have drops so we can use the maybe init to know that a
                                      // variable is initalized somewhere before this location
                                      if (init_state.contains(local) && !fn.all_locals()[local.id()].is_mutable()) {
                                          spdlog::info("Can't assign twice to immutable variable: {}", local.id());
                                          return;
                                      }
                                      uninit_state.remove(local);
                                      init_state.insert(local);
                                  },
                                  [&](const NonMutUseCtx cx) {
                                      auto uninitialized = !init_state.contains(local) ^ uninit_state.contains(local);
                                      if (uninitialized) {
                                          // TODO error
                                          spdlog::info("local: {} is uninitalized when used", local.id());
                                      }
                                  }},
                       ctx);
        }
    };

    static inline void check_ir(const Ir &ir, error::ErrorCtx &ecx) {
        for (const auto &[name, fn] : ir.functions()) {
            spdlog::info("CHECKING IR OF `{}`", name);
            Checker(fn, ecx).check();
        }
    }
}}}} // namespace mr::middle::ir::checker