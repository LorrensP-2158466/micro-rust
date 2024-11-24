#pragma once

#include "block.hpp"
#include "local.hpp"
#include "mr_util.hpp"
#include <fmt/ostream.h>
#include <iostream>
#include <unordered_map>
#include <variant>
#include <vector>

namespace mr {
    namespace middle {
        namespace ir {

            // goes to the block with index of `block_target` inside the current function
            struct GoTo {
                BlockId target;

                friend std::ostream& operator<<(std::ostream& o, const GoTo& t) {
                    o << "goto -> bb" << t.target.id;
                    return o;
                }
            };
            // returns out of the current function with the value currently in 0_return
            struct Return {
                friend std::ostream& operator<<(std::ostream& o, const Return& t) {
                    o << "return;";
                    return o;
                }
            };

            // used for assert
            struct Assert {
                friend std::ostream& operator<<(std::ostream& o, const Assert& t) {
                    return o;
                }
            };

            struct CondGoTo {
                Operand op;
                BlockId then;
                BlockId otherwise;

                friend std::ostream& operator<<(std::ostream& o, const CondGoTo& t) {
                    o << "Cond GoTo(" << t.op << ") -> [true: bb" << t.then.id << ", false: bb"
                      << t.otherwise.id << "]";
                    return o;
                }
            };
            using terminator_variant_t = std::variant<GoTo, Return, Assert, CondGoTo>;
            struct Terminator : terminator_variant_t {

                friend std::ostream& operator<<(std::ostream& o, const Terminator& t) {
                    std::visit(overloaded{[&o](const auto& term) { o << term; }}, t);
                     return o;
                }
            };
        } // namespace ir

    } // namespace middle

} // namespace mr

OSTREAM_FORMATTER(mr::middle::ir::Terminator)