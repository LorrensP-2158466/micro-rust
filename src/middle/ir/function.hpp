#pragma once

#include "basic_blocks.hpp"
#include "local.hpp"
#include <span>
#include <unordered_map>
#include <vector>
namespace mr {
    namespace middle {
        namespace ir {
            struct Function {
                std::string name; // debugging still
                BasicBlocks _blocks;
                // Local declarations:
                // - return type is always first
                // - arguments
                // - user declared/temps
                std::vector<Local> locals;
                size_t             arg_count;

                std::span<const Local> all_locals() const { return std::span(locals); }
                std::span<const Local> args() const {
                    return std::span(locals.begin() + 1, locals.begin() + 1 + arg_count);
                };

                // locals without return place or args
                std::span<const Local> fn_locals() const {
                    return std::span(locals.begin() + 1 + arg_count, locals.end());
                };
            };
        } // namespace ir

    } // namespace middle

} // namespace mr
