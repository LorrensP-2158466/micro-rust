#pragma once

#include "../middle/ir/module.hpp"
#include "mr_util.hpp"

namespace mr {
    namespace middle {
        namespace ir_pass {
            using namespace middle::ir;

            class IrPass {
              public:
                virtual ~IrPass() = default;
                virtual const char* name() const noexcept = 0;
                virtual void        run(Function& body) const = 0;
            };
        } // namespace ir_pass
    } // namespace middle

} // namespace mr
