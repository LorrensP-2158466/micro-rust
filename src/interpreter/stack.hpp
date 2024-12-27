#pragma once

#include "../middle/ir/module.hpp"
#include "value.hpp"
#include <vector>

namespace mr {
    namespace middle_interpreter {
        using namespace middle;

        // location inside a body, if stmt_idx == len(statements), this is the terminator
        struct Location {

            ir::BlockId basic_block;
            size_t      stmt_idx;
        };
        const static inline Location START_LOCATION = Location{0, 0};

        struct Frame {
            // where we are exectuting
            Location loc;
            // the function associated with this frame (named body for when we do consts
            // as well)
            ir::Function& body;

            // somewhat raw stack frame, a struct can for example be stored here in
            // consecutive values.
            // So the localID will index into the beginning of the struct/tuple/enum and
            // projections will give us the actual value we want
            std::vector<Value> values;

            // very weird and propably unsafe, but i have to access the return place
            Value& return_place;

            // if none: root frame so were done running
            // else: the block the caller goes to
            std::optional<ir::BlockId> caller_target;

            Frame(
                Location _loc, ir::Function& _body, std::vector<Value> _vals, Value& _ret,
                std::optional<ir::BlockId> _caller_target = std::nullopt
            )
                : loc(_loc), body(_body), values(std::move(_vals)), return_place(_ret),
                  caller_target(_caller_target) {}
        };

        class Stack {
            std::vector<Frame> _frames;

          public:
            bool  is_empty() const noexcept { return _frames.empty(); }
            void  push_frame(Frame frame) { _frames.push_back(std::move(frame)); }
            Frame pop_frame() {
                auto frame = std::move(_frames.back());
                _frames.pop_back();
                return frame;
            }
            Frame&       frame() { return _frames.back(); }
            const Frame& frame() const { return _frames.back(); }

            ir::Function&       body() { return frame().body; }
            const ir::Function& body() const { return frame().body; }
        };
    } // namespace middle_interpreter
} // namespace mr
