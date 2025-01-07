#pragma once

#include "../middle/ir/module.hpp"
#include "mr_util.hpp"
#include "pass.hpp"

namespace mr { namespace middle { namespace ir { namespace passes {

    // keeps track of amount of uses of a local
    class UnUsedMap {};

    // Removed locals invalidate the maps of the locals, so we need to remap them
    class ReMapper {};

    class RemovedUnusedLocals : public IrPass {
      public:
        ~RemovedUnusedLocals() = default;
        const char *name() const noexcept { return "Removed_Unused_Locals"; }

        void run(Function &body) const {}
    };
}}}} // namespace mr::middle::ir::passes
