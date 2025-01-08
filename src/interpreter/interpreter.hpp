#pragma once

/**
 * The IR interpreter
 *
 * I don't like recursive interpreter (creating stack frames and being recursive ???), but
 * if you make an AST interpreter you really don't have a choice, luckily i tried to
 * "replicate" the middle representation of the rust compiler. As explained, this is a
 * control flow graph with every operation in a somewhat single step. This means we can
 * write a non recursive interpreter yayyy!!! But how you ask?
 *
 * You have to see this IR as an higher level Byte/Machine code, so essentially we can
 * "load" the current statement (an index) every step and execute it fromt the current
 * block, which well have because we have the IR. And if the index is bigger than the
 * amount of statements we interpret the termintor, which will go to another block, **OR**
 * return from the function.
 *
 * But how do you call a function if you cant have access to the place where it is called.
 * Well Every time we call a function we push a frame on to the frame stack (see Frame for
 * more details) and in this frame we hold the current location (block, statement...), but
 * also the return place of the called, so:
 *
 * [Frame 1] -> [Frame 2] -> ...
 * Frame 2's return destination, is a place inside of Frame 1, so when we return from the
 * function of Frame 2, we move the return value in to that place and os it is
 * initialized. Then we pop this frame and go to the location held in Frame 1. Tadaa
 *
 * This way everything is just loaded in place and no recursion happens.
 *
 * This is exactly the same as how a bytecode VM works or machine code, but higher level.
 * We load the instruction (statement) at the program counter (statement and block) and
 * than execute that instruction (statement). A function is just a call (or jump if
 * optimized) and the "ret" combined with popping the stack, which just takes the address
 * of the top of the stack and jumps to that location (go to location of previous frame).
 *
 * Now in code:
 */

#include <spdlog/spdlog.h>

#include <ranges>
#include <vector>

#include "middle/ir/module.hpp"
#include "mr_util.hpp"
#include "stack.hpp"

namespace mr { namespace middle_interpreter {
    using namespace middle;
    class Interpreter {
        ir::Ir _code;
        Stack _stack;

      public:
        Interpreter(ir::Ir code)
            : _code(std::move(code)) {}

        int interp() {
            Value dest{
                Scalar{0, 0}, types::Ty{types::UnitTy{}}
            }; // unit ofcourse, never write to it, but it exists
            init_function_call(
                ir::Call{
                    "main", std::vector<ir::Operand>(), ir::Place{ir::LocalId{0}}, ir::BlockId{0}
                },
                dest
            );
            // as long as we have to do work, we work
            while (interp_curr_block()) {
            }
            return 0;
        }

      private:
        bool interp_curr_block() {
            if (_stack.is_empty()) {
                return false;
            }
            auto &curr_location = _stack.frame().loc;
            const auto &body = _stack.body();
            const auto &block = body._blocks.block(curr_location.basic_block);
            for (const auto &stmt : block.statements) {
                interp_stmt(stmt);
                curr_location.stmt_idx += 1;
            }
            // a call can happen here
            interp_terminator(block.terminator());
            return true;
        }

        /*
        Pushes a frame on to the stack and initalizing arguments
        */
        void init_function_call(
            const ir::Call &call, Value &dest,
            std::optional<ir::BlockId> caller_target = std::nullopt
        ) {
            auto &fn = _code.get_function_by_name(call.fun);
            std::vector<Value> values{};
            values.reserve(fn.locals.size());
            values.emplace_back(local_to_uninit_value(fn.locals[0]));

            std::transform(
                call.args.cbegin(),
                call.args.cend(),
                std::back_inserter(values),
                [&](const ir::Operand &op) { return interp_operand(op); }
            );

            std::transform(
                fn.fn_locals().begin(),
                fn.fn_locals().end(),
                std::back_inserter(values),
                [&](const ir::Local &l) { return Value(Scalar{0, l.ty.size()}, l.ty); }
            );

            auto frame = Frame(ir::START_LOCATION, fn, std::move(values), dest, caller_target);
            _stack.push_frame(std::move(frame));
        }

        void return_from_call() {
            auto old_frame = _stack.pop_frame();
            const auto caller_goto = old_frame.caller_target;
            // write the return_place of the the function to the caller place
            old_frame.return_place = old_frame.values[0];
            // else we popped the root so there won't be anything to do
            if (caller_goto)
                _stack.frame().loc = ir::Location{.basic_block = *caller_goto, .stmt_idx = 0};
        }

        void interp_stmt(const ir::Statement &stmt) {
            std::visit(
                overloaded{
                    [&](const ir::Assign &assign) {
                        interp_rvalue_into_place(assign.place, assign.value);
                    },
                    [&](const ir::FPrintLn &formatted) { interp_format(formatted); },
                    [&](const ir::SPrintLn &print) { fmt::println("{}", print._string); },
                    [&](const auto) {}
                },
                stmt
            );
        }

        void interp_format(const ir::FPrintLn &format) {
            std::string output;
            output.reserve(16);
            output += map_optional_or(
                format.start,
                [&](const ir::Operand &op) { return interp_operand(op).as_program_str(); },
                std::string()
            );

            for (const auto &[str, op] : format._format_structure) {
                output += str + interp_operand(op).as_program_str();
            }

            output += format.end.value_or("");
            fmt::println("{}", output);
        }

        void interp_terminator(const ir::Terminator term) {
            std::visit(
                overloaded{
                    [&](const ir::GoTo &gt) { go_to_block(gt.target); },
                    [&](const ir::Return &) { return_from_call(); },
                    [&](const ir::CondGoTo &cgt) {
                        const auto cond = interp_operand(cgt.op).scalar().to_bool();
                        // false = 0
                        // true = 1
                        // so we can access by index
                        const auto target = cgt.targets[cond];
                        go_to_block(target);
                    },
                    [&](const ir::Call &call) {
                        init_function_call(call, interp_place(call.dest_place), call.target);
                    },
                    [&](const auto &) {}
                },
                term
            );
        }

        void interp_rvalue_into_place(const ir::Place &place, const ir::RValue &value) {
            auto &place_value = interp_place(place);
            place_value = std::visit(
                overloaded{
                    [&](const ir::AsIs &as_is) { return interp_operand(as_is.op); },
                    [&](const ir::BinaryOp &bin_op) { return interp_bin_op(bin_op); },
                    [&](const ir::UnaryOp &un_op) {
                        return interp_un_op(un_op.op, interp_operand(un_op.operand));
                    },
                    [&](const ir::Aggregate &aggr) {
                        std::vector<Value> vals;
                        vals.reserve(aggr.values.size());
                        for (const auto &op : aggr.values) {
                            vals.emplace_back(interp_operand(op));
                        }
                        // we type checked, and don't allow operations that cause UB
                        // this place_value.type is safe
                        return Value(Aggregate(std::move(vals)), place_value.type);
                    }
                },
                value
            );
        }

        Value interp_bin_op(const ir::BinaryOp &bin_op) {
            // we only support this binary op for the primitives, the rest are calls
            // to their impls
            auto left = interp_operand(bin_op.left);
            auto right = interp_operand(bin_op.right);
            // at this point, we don't accept different types in binary ops
            if (left.type != right.type)
                throw std::runtime_error("Unexpected type difference binary op");

            if (!left.type.is_integral() && !right.type.is_integral())
                throw std::runtime_error("Non Integral binary op");

            // we can assume
            const auto &result_type = left.type;

            return std::visit(
                overloaded{
                    [&](const types::IntTy &) { return binary_int_op(bin_op.op, left, right); },
                    [&](const types::UIntTy &) { return binary_int_op(bin_op.op, left, right); },
                    [&](const types::BoolTy &) { return binary_bool_op(bin_op.op, left, right); },
                    [](const auto &) -> Value {
                        throw std::runtime_error("Unsupported type for binop");
                    }
                },
                result_type
            );
        } // namespace middle_interpreter

        Value binary_bool_op(ir::BinOp op, const Value &left, const Value &right) const {
            const auto l = left.scalar().to_bool();
            const auto r = right.scalar().to_bool();
            bool result;
            switch (op) {
            case ir::BinOp::Eq:
                result = l == r;
            case ir::BinOp::Lt:
                result = l < r;
            case ir::BinOp::Le:
                result = l <= r;
            case ir::BinOp::Ne:
                result = l != r;
            case ir::BinOp::Ge:
                result = l >= r;
            case ir::BinOp::Gt:
                result = l > r;
            default:
                throw std::runtime_error("Invalid bool binary_op");
            }
            Value::from_bool(result);
        }
        Value binary_int_op(ir::BinOp op, const Value &left, const Value &right) const {
            const auto &result_type = left.type;
            if (result_type.is_signed_integral()) {
                const auto l = left.scalar().to_isize();
                const auto r = right.scalar().to_isize();
                const auto cmp_op = [](ir::BinOp op, int64_t l, int64_t r) -> std::optional<bool> {
                    switch (op) {
                    case ir::BinOp::Eq:
                        return some(ops::i64::eq(l, r));
                    case ir::BinOp::Lt:
                        return some(ops::i64::lt(l, r));
                    case ir::BinOp::Le:
                        return some(ops::i64::le(l, r));
                    case ir::BinOp::Ne:
                        return some(ops::i64::ne(l, r));
                    case ir::BinOp::Ge:
                        return some(ops::i64::ge(l, r));
                    case ir::BinOp::Gt:
                        return some(ops::i64::gt(l, r));
                    default:
                        return {};
                    }
                }(op, l, r);
                if (cmp_op) {
                    return Value::from_bool(*cmp_op);
                }

                const auto op_fn = [](ir::BinOp op, int64_t l, int64_t r) {
                    switch (op) {
                    case ir::BinOp::Add:
                        return ops::i64::overflowing_add(l, r);
                    case ir::BinOp::Sub:
                        return ops::i64::overflowing_sub(l, r);
                    case ir::BinOp::Mul:
                        return ops::i64::overflowing_mul(l, r);
                    case ir::BinOp::Div: {
                        if (r == 0)
                            throw std::runtime_error("Division by zero");
                        return ops::i64::overflowing_div(l, r);
                    }
                    default:
                        throw std::runtime_error("Unkown binop");
                    };
                };
                auto [result, overflow] = op_fn(op, l, r);
                if (overflow) {
                    throw std::runtime_error(fmt::format("Overflow happend on {} and {}", l, r));
                }
                return Value(Scalar::from_int(result, result_type.size()), result_type);
            }
            const auto l = left.scalar().to_usize();
            const auto r = right.scalar().to_usize();
            const auto cmp_op = [](ir::BinOp op, uint64_t l, uint64_t r) -> std::optional<bool> {
                switch (op) {
                case ir::BinOp::Eq:
                    return some(ops::u64::eq(l, r));
                case ir::BinOp::Lt:
                    return some(ops::u64::lt(l, r));
                case ir::BinOp::Le:
                    return some(ops::u64::le(l, r));
                case ir::BinOp::Ne:
                    return some(ops::u64::ne(l, r));
                case ir::BinOp::Ge:
                    return some(ops::u64::ge(l, r));
                case ir::BinOp::Gt:
                    return some(ops::u64::gt);
                default:
                    return std::nullopt;
                }
            }(op, l, r);
            if (cmp_op) {
                return Value::from_bool(*cmp_op);
            }
            const auto op_fn = [](ir::BinOp op, uint64_t l, uint64_t r) {
                switch (op) {
                case ir::BinOp::Add:
                    return ops::i64::overflowing_add(l, r);
                case ir::BinOp::Sub:
                    return ops::i64::overflowing_sub(l, r);
                case ir::BinOp::Mul:
                    return ops::i64::overflowing_mul(l, r);
                case ir::BinOp::Div:
                    if (r == 0)
                        throw std::runtime_error("Division by zero");
                    return ops::i64::overflowing_div(l, r);
                default:
                    throw std::runtime_error("Unkown binop");
                };
            };
            auto [result, overflow] = op_fn(op, l, r);
            if (overflow) {
                throw std::runtime_error(fmt::format("Overflow happend on {} and {}", l, r));
            }
            return Value(Scalar::from_int(result, result_type.size()), result_type);
        }

        Value interp_un_op(ir::UnOp op, const Value &val) const {
            return std::visit(
                overloaded{
                    [&](const types::BoolTy &) -> Value {
                        const auto b_val = val.scalar().to_bool();
                        switch (op) {
                        case ir::UnOp::Not:
                            return Value::from_bool(!b_val);
                        default:
                            throw std::runtime_error("Invalid UnOp on bool");
                        }
                    },
                    [&](const types::IntTy &) -> Value {
                        const auto i_val = val.scalar().to_i64();
                        switch (op) {
                        case ir::UnOp::Not:
                            return Value(Scalar::from_int(~i_val, val.type.size()), val.type);
                        case ir::UnOp::Neg:
                            return Value(Scalar::from_int(-i_val, val.type.size()), val.type);
                        default:
                            throw std::runtime_error("Invalid UnOp on integer");
                        }
                    },
                    [&](const types::UIntTy &) -> Value {
                        const auto u_val = val.scalar().to_u64();
                        switch (op) {
                        case ir::UnOp::Not:
                            return Value(Scalar::from_uint(!u_val, val.type.size()), val.type);
                        default:
                            throw std::runtime_error("Invalid UnOp on integer");
                        }
                    },
                    [&](const auto &) -> Value {
                        throw std::runtime_error("Invalid type for unary op");
                    }
                },
                val.type
            );
        } // namespace middle_interpreter

        Value interp_operand(const ir::Operand &op) {
            return std::visit(
                overloaded{
                    [&](const ir::Const &v) { return Value(v.scalar, v.ty); },
                    [&](const ir::Move &m) { return std::move(interp_place(m.val)); },
                    [&](const ir::Copy &c) { return interp_place(c.val); }
                },
                op
            );
        }

        Value &interp_place(const ir::Place &place) {
            // do projections to get value, for now just get values
            auto val = &_stack.frame().values[place.local.id()];
            for (auto &proj : place.projections) {
                val = &val->project(proj);
            }
            return *val;
        }
        const Value &interp_place(const ir::Place &place) const {
            // do projections to get value, for now just get value
            // do projections to get value, for now just get values
            const Value *val = &_stack.frame().values[place.local.id()];
            for (auto &proj : place.projections) {
                val = &val->project(proj);
            }
            return *val;
        }

        Value local_to_uninit_value(const ir::Local &local) {
            // for now we just have scalars with size of type
            return uninit_val_of_type(local.ty);
        }

        Value uninit_val_of_type(const types::Ty &type) {
            return std::visit(
                overloaded{
                    [&](const types::TupleTy &tup) {
                        std::vector<Value> vals;
                        vals.reserve(tup.tys.size());
                        for (const auto &t : tup.tys) {
                            vals.emplace_back(uninit_val_of_type(t));
                        }
                        return Value(Aggregate{std::move(vals)}, type);
                    },
                    [&](const auto &) { return Value(Scalar{0, type.size()}, type); }
                },
                type
            );
        }

        // jumping and stuff

        void go_to_block(ir::BlockId target) {
            _stack.frame().loc = ir::Location{.basic_block = target, .stmt_idx = 0};
        }

        // ---- none interpreting stuff -----

        void print_stack_trace() const { fmt::println("TODO: Stack Trace"); }
    }; // namespace mr
}} // namespace mr::middle_interpreter
