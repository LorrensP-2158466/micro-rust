#pragma once

#include "const_fold.hpp"
#include "mr_util.hpp"
#include "pass.hpp"
#include "remove_unused_locals.hpp"
#include "simplify.hpp"
#include <array>

namespace mr {
    namespace middle {
        namespace ir_pass {
            class PassManager {
                static inline const std::array<U<IrPass>, 2> passes = {
                    std::make_unique<Simplify>(), std::make_unique<RemovedUnusedLocals>()
                };

              public:
                void run_passes(ir::Ir& ir) const {
                    spdlog::info("running passes");
                    for (auto& [name, body] : ir.functions()) {
                        for (const auto& pass : passes) {
                            spdlog::info(
                                "Running pass: `{}` on function: `{}`", pass->name(), name
                            );
                            pass->run(body);
                        }
                    }
                }
            };
        } // namespace ir_pass
    } // namespace middle

} // namespace mr
