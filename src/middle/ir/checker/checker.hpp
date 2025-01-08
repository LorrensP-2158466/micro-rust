#pragma once

#include "./errors.hpp"
#include "analyzers.hpp"
#include "datastructures.hpp"
#include "errors/ctx.hpp"
#include "ir/module.hpp"
#include "ir/visitor.hpp"
#include "location.hh"

namespace mr { namespace middle { namespace ir { namespace checker {
    // currently only checks inits and assign to non mut
    // can be used for borrow checking in future
    class Checker : public Visitor {
        const Function &fn;
        error::ErrorCtx &ecx;
        MaybeUninit::Results uninit_entry_states; // vector<BitSet> bit_set[var_id] == uninit
        MaybeInit::Results init_entry_states;
        EverInit::Results ever_entry_states;

        // if we report an error on a particular error, we don't report any more errors on that
        // local because we can't be sure that that error occured because of the first one. this is
        // the programmers duty
        BitSet<LocalId> tainter_by_error;
        // indexed by localId, this includes location of arguments in function decl
        // init_location of return_type is empty location
        // use to tell user where first init happened when assigning to immutable
        std::vector<std::optional<location>> first_init_locs;

        static inline std::vector<location> declaration_locations(const Function &fn) {
            std::vector<location> decl_locs(fn.locals.size());
            size_t i = 0;
            for (const auto &local : fn.all_locals()) {
                decl_locs[i++] = local.loc;
            }
            return decl_locs;
        }

        bool is_assignable(LocalId local, Location loc) const {
            // we don't have drops so we can use the maybe init state to know that a
            // variable is initalized somewhere before this location
            const auto &ever_state = ever_entry_states[loc.basic_block.id()];
            return !ever_state.contains(local) || fn.all_locals()[local.id()].is_mutable();
        }

        bool is_uninitialized(LocalId local, Location loc) const {
            const auto &uninit_states = uninit_entry_states[loc.basic_block.id()];
            const auto &init_states = init_entry_states[loc.basic_block.id()];
            // return place of unit type is "implicitly" initliazed, in the way that it doesn't
            // write to the return place
            return !is_unit_ret_place(local) &&
                   (uninit_states.contains(local) || !init_states.contains(local));
        }

        inline bool is_unit_ret_place(LocalId local) const {
            return local.id() == 0 && fn.locals[local.id()].ty.is_unit();
        }
        inline const std::string &name_of_loc(LocalId local) const { return fn.local(local).id; }
        inline location decl_loc(LocalId local) const { return fn.local(local).loc; }
        inline location source_loc(Location loc) const {
            const auto &block = fn._blocks[loc.basic_block];
            return loc.stmt_idx >= block.statements.size() ? block.terminator().loc
                                                           : block.statements[loc.stmt_idx].loc;
        }

      public:
        Checker(const Function &fn, error::ErrorCtx &ecx)
            : fn(fn)
            , ecx(ecx)
            , uninit_entry_states(MaybeUninit().iterate_till_fixpoint(fn))
            , init_entry_states(MaybeInit().iterate_till_fixpoint(fn))
            , ever_entry_states(EverInit().iterate_till_fixpoint(fn))
            , tainter_by_error(fn.all_locals().size())
            , first_init_locs(fn.all_locals().size()) {}

        void check() { Visitor::visit_fn(fn); }

        void initialized(const LocalId local, Location loc) {
            auto &uninit_state = uninit_entry_states[loc.basic_block.id()];
            auto &init_state = init_entry_states[loc.basic_block.id()];
            uninit_state.remove(local);
            init_state.insert(local);
        }

        void visit_local(const LocalId local, PlaceCtx ctx, Location loc) override {
            // based on ctx, we know what to do
            const auto &uninit_states = uninit_entry_states[loc.basic_block.id()];
            const auto &init_states = init_entry_states[loc.basic_block.id()];
            const auto init_state = init_states.contains(local);
            const auto uninit_state = uninit_states.contains(local);
            spdlog::info("local {}: init: {}  uninit: {}", local.id(), init_state, uninit_state);
            std::visit(
                overloaded{
                    [&](const MutUseCtx) {
                        if (!is_assignable(local, loc) && tainter_by_error.insert(local)) {
                            DBG("ASSIGN ALREADY ASSIGNED");
                            const auto &[id, ty, mutablity, local_type, l] = fn.local(local);
                            ecx.report_diag(errors::assign_immutable(
                                first_init_locs[local.id()], source_loc(loc), id, ty
                            ));
                            return;
                        }
                        // we can report this as the first initalization
                        // in the case of branches, we thus choose the first branch in the CFG,
                        // rust does this as well, which is the correct way i guess, because the
                        // semantics stay the same
                        // so we get the source location of this statement at IR Location and
                        // set it as first_init_loc
                        // but only do this if first_init isnt already set
                        auto &first_init_loc = first_init_locs[local.id()];
                        if (!first_init_loc)
                            first_init_loc = source_loc(loc);
                        // most of the time a no-op
                        initialized(local, loc);
                    },
                    [&](const NonMutUseCtx) {
                        if (is_uninitialized(local, loc) && tainter_by_error.insert(local)) {
                            DBG("USE UNINIT");

                            const auto &[id, ty, mutablity, local_type, l] = fn.local(local);
                            ecx.report_diag(errors::uninitialized_use(l, source_loc(loc), id, ty));
                        }
                        DBG("USE INIT");
                    }
                },
                ctx
            );
        }
    };

    static inline void check_ir(const Ir &ir, error::ErrorCtx &ecx) {
        for (const auto &[name, fn] : ir.functions()) {
            spdlog::info("CHECKING IR OF `{}`", name);
            Checker(fn, ecx).check();
        }
    }
}}}} // namespace mr::middle::ir::checker