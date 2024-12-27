#pragma once

#include "consts/checked_int_ops.hpp"
#include "consts/scalar.hpp"
#include "middle/ir/module.hpp"
#include "mr_util.hpp"
#include "pass.hpp"
#include "traversal/preorder.hpp"

#include <optional>

namespace mr {
    namespace middle {
        namespace ir_pass {
            using namespace middle::ir;

            // doesnt do real constant folding with dataflow analysis
            // just keeps track of any immutable locals with constant initalizers and
            // inlines them also tries to evaluate expressions as constants for
            // assignments/initializers
            class ConstEval {

                Function&                         body;
                std::vector<std::optional<Const>> _consts;

              public:
                // indexed by local.id for now, some locals can't have a constant value so
                // we make it optional
                ConstEval(Function& body)
                    : body(body), _consts(body.all_locals().size()) {}
                void eval() {
                    // since we are doing simple find and replace with some evaluation, we
                    // can just visit in preorder this ensures that we always visit the
                    // predecessor of a block before the block
                    auto& blocks = body._blocks;
                }

              private:
                void visit_stmt(ir::Statement& stmt) {
                    std::visit(
                        overloaded{
                            [&](ir::Assign& assign) {
                                interp_rvalue_into_place(assign.place, assign.value);
                            },
                            [&](ir::FPrintLn& formatted) { visit_format(formatted); },
                            [&](ir::SPrintLn& print) {
                                fmt::println("{}", print._string);
                            }
                        },
                        stmt
                    );
                }

                void visit_format(const ir::FPrintLn& format) const {}

                void visit_terminator(const ir::Terminator term) {
                    std::visit(
                        overloaded{
                            [&](const ir::CondGoTo& cgt) {

                            },
                            [&](const ir::Call& call) {

                            },
                            [&](const auto& _skip) {}
                        },
                        term
                    );
                }

                void interp_rvalue_into_place(
                    const ir::Place& place, const ir::RValue& value
                ) {
                    // visit place
                    std::visit(
                        overloaded{
                            [&](const ir::AsIs& as_is) {

                            },
                            [&](const ir::BinaryOp& bin_op) {

                            },
                            [&](const ir::UnaryOp& un_op) {}
                        },
                        value
                    );
                }
            };

            class ConstFold : public IrPass {
              public:
                ~ConstFold() = default;
                const char* name() const noexcept { return "Constant-Fold"; }
                // more than 50 blocks, oh well, my const folder is probabbly very slow,
                // so were not doing that;
                const static inline size_t BLOCK_LIMIT = 50;

                void run(Function& body) const {
                    if (body._blocks.size() > BLOCK_LIMIT) return;

                    auto folder = ConstEval(body);

                    folder.eval();
                }
            };
        } // namespace ir_pass
    } // namespace middle

} // namespace mr
