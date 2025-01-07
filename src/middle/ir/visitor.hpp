#pragma once

#include <variant>

#include "block_id.hpp"
#include "ir.hpp"
#include "mr_util.hpp"
#include "statement.hpp"
#include "terminator.hpp"
#include <iostream>

namespace mr { namespace middle { namespace ir {

    // we have to know what context the place is used in
    enum class MutUseCtx { Write, Call };
    enum class NonMutUseCtx { Copy, Move, Proj };

    struct PlaceCtx : public std::variant<MutUseCtx, NonMutUseCtx> {
        friend std::ostream &operator<<(std::ostream &o, PlaceCtx cx) {
            return std::visit(
                overloaded{
                    [&o](const MutUseCtx &) -> std::ostream & { return (o << "Mut Use"); },
                    [&o](const NonMutUseCtx &) -> std::ostream & { return (o << "Non Mut Use"); }

                },
                cx
            );
        } // namespace ir
    }; // namespace middle

    class Visitor {
      public:
        virtual void visit_fn(const Function &f) {
            for (const auto &[idx, bb] : iterators::zip(f._blocks.indices(), f._blocks)) {
                visit_bb(idx, bb);
            }
        } // namespace ir

        virtual void visit_bb(BlockId bb_idx, const Block &bb) {
            auto idx = 0ul;
            for (const auto &stmt : bb.statements) {
                visit_stmt(stmt, Location{bb_idx, idx++});
            }
            if (bb._terminator)
                visit_terminator(*bb._terminator, Location{bb_idx, idx});
        }
        virtual void visit_stmt(const Statement &f, Location l) {
            std::visit(
                overloaded{
                    [&](const Assign &a) { visit_assign(a, l); },
                    [&](const FPrintLn &fp) { visit_format_print(fp, l); },
                    [&](const SPrintLn &p) { visit_print(p, l); }
                },
                f
            );
        }

        virtual void visit_assign(const Assign &as, Location l) {
            visit_place(as.place, PlaceCtx(MutUseCtx::Write), l);
            visit_rvalue(as.value, l);
        }
        virtual void visit_format_print(const FPrintLn &fp, Location l) {
            if (fp.start)
                visit_operand(*fp.start, l);
            for (const auto &[s, op] : fp._format_structure) {
                visit_operand(op, l);
            }
        }
        virtual void visit_print(const SPrintLn, Location) {}

        virtual void visit_terminator(const Terminator &term, Location l) {
            std::visit(
                overloaded{
                    [&](const GoTo &) {},
                    // we have to visit the return local, because we "use" it
                    [&](const Return &c) {
                        visit_local(RETURN_LOCAL, PlaceCtx(NonMutUseCtx::Move), l);
                    },
                    [&](const Assert &c) {},
                    [&](const CondGoTo &cgt) { visit_operand(cgt.op, l); },
                    [&](const Call &c) {
                        for (const auto &op : c.args) {
                            visit_operand(op, l);
                        }
                        visit_place(c.dest_place, PlaceCtx(MutUseCtx::Call), l);
                    }
                },
                term
            );
        }
        virtual void visit_local(const LocalId, PlaceCtx, Location) {}
        virtual void visit_operand(const Operand &op, Location l) {
            std::visit(
                overloaded{
                    [&](const Copy &c) { visit_place(c.val, PlaceCtx(NonMutUseCtx::Copy), l); },
                    [&](const Move &m) { visit_place(m.val, PlaceCtx(NonMutUseCtx::Move), l); },
                    [](const auto &) { /* Dont have a visitor for this*/ }
                },
                op
            );
        }
        virtual void visit_rvalue(const RValue &rv, Location l) {
            std::visit(
                overloaded{
                    [&](const AsIs &a) { visit_operand(a.op, l); },
                    [&](const BinaryOp &bin_op) {
                        visit_operand(bin_op.left, l);
                        visit_operand(bin_op.right, l);
                    },
                    [&](const UnaryOp &un_op) { visit_operand(un_op.operand, l); },
                    [&](const Aggregate &aggr) {
                        for (const auto &op : aggr.values) {
                            visit_operand(op, l);
                        }
                    }
                },
                rv
            );
        }
        virtual void visit_place(const Place &p, PlaceCtx ctx, Location l) {
            visit_local(p.local, ctx, l);
        }
    }; // namespace middle
}}} // namespace mr::middle::ir