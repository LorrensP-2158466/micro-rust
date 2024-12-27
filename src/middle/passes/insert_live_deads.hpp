#pragma once

#include "../middle/ir/module.hpp"
#include "mr_util.hpp"
#include "pass.hpp"

/// the last pass before borrow checking, this inserts where a local goes live and where
/// it goes dead the borrow checker and later the IR converted will use these
namespace mr {
    namespace middle {
        namespace ir_pass {
            using namespace middle::ir;

            class DeadOrAlive : public IrPass {
              public:
                ~DeadOrAlive() = default;
                const char* name() const noexcept { return "DeadOrAlive"; }

                void run(Function& body) const {}
            };
        } // namespace ir_pass
    } // namespace middle

} // namespace mr
