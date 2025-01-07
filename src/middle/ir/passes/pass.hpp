#pragma once

#include "ir/module.hpp"
#include "mr_util.hpp"

namespace mr { namespace middle { namespace ir { namespace passes {

    class IrPass {
      public:
        virtual ~IrPass() = default;
        virtual const char *name() const noexcept = 0;
        virtual void run(Function &body) const = 0;
    };
}}}} // namespace mr::middle::ir::passes
