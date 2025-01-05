#pragma once

#include "datastructures.hpp"
#include "errors/ctx.hpp"
#include "ir_analysis/maybe_init.hpp"
#include "ir_analysis/maybe_uninit.hpp"
#include "module.hpp"
#include "visitor.hpp"

namespace mr {
    namespace middle {
        namespace ir {
            // currently only checks inits and assign to non mut
            // can be used for borrow checking in future
            class Checker : public Visitor {
                const Function &fn;
                error::ErrorCtx &ecx;
                std::vector<BitSet<LocalId>> uninit_entry_states;
                std::vector<BitSet<LocalId>> init_entry_states;

              public:
                Checker(const Function &fn, error::ErrorCtx &ecx)
                    : fn(fn)
                    , ecx(ecx)
                    , uninit_entry_states(analysis::MaybeUninit().iterate_till_fixpoint(fn))
                    , init_entry_states(analysis::MaybeInit().iterate_till_fixpoint(fn)) {}

                void check() { Visitor::visit_fn(fn); }

                void visit_local(const LocalId &local, PlaceCtx ctx, Location l) override {
                    // based on ctx, we know what to do
                    auto &uninit_state = uninit_entry_states.at(l.basic_block.id());
                    auto &init_state = init_entry_states.at(l.basic_block.id());
                    std::visit(overloaded{[&](const MutUseCtx cx) {
                                              uninit_state.remove(local);
                                              init_state.insert(local);
                                          },
                                          [&](const NonMutUseCtx cx) {
                                              // we use it as a value that should be initialized
                                              // if init_state = true and uninit_state is false, we are 100% sure this
                                              // local is initialized
                                              // so the reverse is uninitialized
                                              auto uninitialized =
                                                  !init_state.contains(local) ^ uninit_state.contains(local);
                                              if (uninitialized) {
                                                  // TODO error
                                                  spdlog::info("local: {} is uninitalized when used", local.id());
                                                  // ICE("CAN'T RESOLVE UNINIT VARIABLE BEING USED...");
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
        } // namespace ir
    } // namespace middle
} // namespace mr