#pragma once

#include "block_id.hpp"
#include "local.hpp"
#include "mr_util.hpp"
#include "values.hpp"
#include <fmt/ostream.h>
#include <iostream>
#include <span>
#include <unordered_map>
#include <variant>
#include <vector>

namespace mr {
    namespace middle {
        namespace ir {

            // goes to the block with index of `block_target` inside the current function
            struct GoTo {
                BlockId target;

                std::span<const BlockId> successors() const {
                    return std::span(&target, 1);
                }

                std::span<BlockId> successors() { return std::span(&target, 1); }

                friend std::ostream& operator<<(std::ostream& o, const GoTo& t) {
                    o << "goto -> bb" << t.target.id();
                    return o;
                }
            };
            // returns out of the current function with the value currently in 0_return
            struct Return {
                std::span<const BlockId> successors() const { return {}; }
                std::span<BlockId>       successors() { return {}; }

                friend std::ostream& operator<<(std::ostream& o, const Return&) {
                    o << "return;";
                    return o;
                }
            };

            // used for assert
            struct Assert {
                std::span<const BlockId> successors() const { return {}; }
                std::span<BlockId>       successors() { return {}; }
                friend std::ostream&     operator<<(std::ostream& o, const Assert&) {
                    o << "ASSERT";
                    return o;
                }
            };

            // this make interpreting much much easiear, because we were we call, but
            // which this we can updating stack, program counter, is much more
            // nicer/easier if we make a call a terminator of a block. INFO: rustc mainly
            // does this for unwinding purposes, we can add this later if we want
            struct Call {
                std::string              fun;
                std::vector<Operand>     args;
                Place                    dest_place;
                BlockId                  target;
                std::span<const BlockId> successors() const {
                    return std::span(&target, 1);
                }
                std::span<BlockId>   successors() { return std::span(&target, 1); }
                friend std::ostream& operator<<(std::ostream& o, const Call& call) {
                    o << '_' << call.dest_place.local.id() << " = " << call.fun << '(';
                    std::copy(
                        call.args.begin(),
                        call.args.end(),
                        std::ostream_iterator<Operand>(o, ", ")
                    );
                    o << ") -> " << call.target;
                    return o;
                }
            };

            struct CondGoTo {
                Operand op;
                // [0] = false branch
                // [1] == true branch
                BlockId                  targets[2];
                std::span<const BlockId> successors() const { return std::span(targets); }
                std::span<BlockId>       successors() { return std::span(targets); }

                friend std::ostream& operator<<(std::ostream& o, const CondGoTo& t) {
                    o << "Cond GoTo(" << t.op << ") -> [false: " << t.targets[0]
                      << ", true: " << t.targets[1] << "]";
                    return o;
                }
            };
            using terminator_variant_t =
                std::variant<GoTo, Return, Assert, CondGoTo, Call>;
            struct Terminator : terminator_variant_t {

                std::span<const BlockId> successors() const {
                    return std::visit(
                        overloaded{[&](const auto& t) { return t.successors(); }}, *this
                    );
                }

                // these pointers are always live as long as terminator is alive
                std::span<BlockId> successors() {
                    return std::visit(
                        overloaded{[&](auto& t) { return t.successors(); }}, *this
                    );
                }

                friend std::ostream& operator<<(std::ostream& o, const Terminator& t) {
                    std::visit(overloaded{[&o](const auto& term) { o << term; }}, t);
                    return o;
                }
            };
        } // namespace ir

    } // namespace middle

} // namespace mr

OSTREAM_FORMATTER(mr::middle::ir::Terminator)