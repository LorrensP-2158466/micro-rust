#pragma once

#include "./errors.hpp"
#include "errors/ctx.hpp"
#include "ir/module.hpp"
#include "mr_util.hpp"
#include "tast/module.hpp"
#include "type_inference.hpp"
#include "types/type.hpp"
#include <fmt/format.h>
#include <functional>
#include <spdlog/spdlog.h>
#include <unordered_map>

namespace mr { namespace middle { namespace build {
    using namespace types;
    using namespace inference;
    using namespace ir;

    class IrBuilder {
      public:
        error::ErrorCtx &ecx;
        inference::TyInferer &_inferer; // context of types
        // name to local_id, symboltable is used, because we can shadow in rust
        SymbolTable<LocalId> _locals_table;
        LocalId return_local;
        std::optional<Place> _unit_temp;
        std::vector<Local> _locals;

        // TODO: create scopes Class to handle this when we introduce drops
        std::vector<Place> _break_places;
        // list of blocks that need a `GoTo` terminator to the enclosing breakable
        // scope
        // TODO: what to do with nested labled scopes
        // only do the top level of course
        std::vector<std::vector<BlockId>> _need_go_tos;
        std::vector<std::vector<BlockId>> _need_continues;
        std::vector<std::vector<LocalId>> _decl_in_loop;
        size_t in_loop = 0;

        BasicBlocks _blocks;

        IrBuilder(error::ErrorCtx &ecx, inference::TyInferer &i)
            : ecx(ecx)
            , _inferer(i) {}

        Function build_function(const tast::TAst fn) {
            spdlog::info("BEGINNING IR BUILD OF FUNCTION {}", fn.name);
            return_local = create_local(
                "0_RETURN",
                _inferer.resolve(fn.ret_type),
                MutabilityType::Mutable,
                LocalType::Temp,
                location()
            );
            for (const auto &param : fn.params) {
                const auto ty = _inferer.resolve(param.type);
                create_local(
                    param.id, std::move(ty), param.mut.node, LocalType::UserDef, param.loc
                );
            }
            auto block_id = _blocks.create_new_block();
            for (const auto &stmt : fn.body._statements) {
                block_id = build_statement(*stmt, block_id).into_block();
            }
            if (fn.body._tail) {
                unpack(block_id, expr_into_place(Place(RETURN_LOCAL), *fn.body._tail, block_id));
            }
            _blocks.return_(block_id, fn.body._tail->loc);

            return Function{fn.name, std::move(_blocks), std::move(_locals), fn.params.size()};
        }

      private:
        Scalar from_tast_literal(const tast::Literal lit) {
            return Scalar{lit.raw_value(), lit.size()};
        }
        LocalId create_local(
            const std::string name, Ty ty, MutabilityType mut, LocalType type, location loc
        ) {
            spdlog::info("CREATING LOCAL `{}`", name);
            const auto id = LocalId{_locals.size()};
            _locals_table.insert(name, id);
            _locals.emplace_back(std::move(name), std::move(ty), mut, type, loc);
            if (in_loop) {
                DBG(in_loop);
                _decl_in_loop.back().push_back(id);
            }
            return id;
        }

        // helper which assures that going in a scope will always push a scope
        // and exitting will always pop a scope.
        template <typename R>
        BlockWith<R> build_in_scope(std::function<BlockWith<R>(IrBuilder &builder)> f) {
            _locals_table.push_scope();
            const auto result = f(*this);
            _locals_table.pop_scope();
            return result;
        }

        void enter_loop() {
            _need_go_tos.emplace_back();
            _need_continues.emplace_back();
            _decl_in_loop.emplace_back();
            in_loop += 1; // ughhh
        }

        void exit_loop() {
            _need_go_tos.pop_back();
            _need_continues.pop_back();
            _decl_in_loop.pop_back();
            in_loop -= 1;
        }

        void build_dead_locals(BlockId block) {
            for (const auto local : _decl_in_loop.back()) {
                _blocks.dead_local(block, local);
            }
        }

        BlockWith<void> build_in_breakable_scope(
            BlockId loop_block, Place break_place, std::function<void(IrBuilder &builder)> f
        ) {
            spdlog::info("BUILDING IN A BREAKABLE SCOPE");
            _break_places.push_back(break_place);
            _locals_table.push_scope();
            enter_loop();
            f(*this);
            _locals_table.pop_scope();
            _break_places.pop_back();

            const auto exit_block = _blocks.create_new_block();
            for (const auto block : _need_go_tos.back()) {
                build_dead_locals(block);
                _blocks.go_to(block, exit_block, location());
            }
            for (const auto block : _need_continues.back()) {
                build_dead_locals(block);
                _blocks.go_to(block, loop_block, location());
            }
            exit_loop();

            spdlog::info("DONE BUILDING IN BREAKABLE SCOPE");
            return exit_block.empty();
        }

        BlockWith<void> build_block_statements(
            const Place place, const tast::BlockExpr &tast_block, BlockId basic_block
        ) {
            unpack(basic_block, build_in_scope<void>([&](IrBuilder &builder) -> BlockWith<void> {
                       for (const auto &stmt : tast_block._statements) {
                           unpack(basic_block, builder.build_statement(*stmt, basic_block));
                       }
                       // check for tail expression
                       if (tast_block._tail)
                           unpack(
                               basic_block,
                               builder.expr_into_place(place, *tast_block._tail, basic_block)
                           );
                       return basic_block.empty();
                   }));
            return basic_block.empty();
        }

        BlockWith<void> build_statement(const tast::Stmt &stmt, BlockId block) {
            return std::visit(
                overloaded{
                    [&](const tast::ExprStmt &e) { return build_expr_stmt(e.expr, block); },
                    [&](const tast::LetStmt &e) { return build_let_stmt(e, block); },
                    [&](const tast::PrintLn &e) { return build_print_stmt(e, block); },
                    [&](const tast::EmptyStmt &) { return block.empty(); }
                },
                stmt.inner
            );
        }

        BlockWith<void> build_let_stmt(const tast::LetStmt &let, BlockId block) {
            const auto resolved_ty = _inferer.resolve(let.type_decl);
            fmt::println("let type: {}", resolved_ty);

            if (!resolved_ty.is_known()) {
                ecx.report_diag(errors::unknown_type(let.id.loc));
            }
            if (!let.initializer) {
                create_local(let.id._id, resolved_ty, let.mut.node, LocalType::UserDef, let.id.loc);
                return block.empty();
            }
            // because of shadowing in rust, we'll first build the assigment and than create the new
            // local, this is to prevent this:
            /*
                let bananas = 5;
                let bananas = bananas + 3; // if we build after local is created, bananas will point
               to the new uninit local and this is wrong
            */
            if (const auto fn_item = std::get_if<const FnItem *>(&resolved_ty)) {
                // we don't create a local
                /*
                    fn foo() {}
                    // ...
                    let x = foo;
                    // this just renames every x to foo...
                    // so we don't create a local
                */
                return block.empty();
            }
            const auto rvalue = unpack(block, expr_as_rvalue(*let.initializer, block));
            const auto local =
                create_local(let.id._id, resolved_ty, let.mut.node, LocalType::UserDef, let.id.loc);
            _blocks.push_assign(block, Place(local), std::move(rvalue), let.initializer->loc);
            return block.empty();
        }
        BlockWith<void> build_expr_stmt(const tast::Expr &expr, BlockId block) {
            return std::visit(
                overloaded{
                    [&](const tast::AssignExpr &assign) {
                        const auto rhs = unpack(block, expr_as_rvalue(*assign.rhs, block));
                        const auto lhs = unpack(block, expr_as_place(*assign.lhs, block));
                        spdlog::info("ASSIGN EXPR LOC: {}", expr.loc);
                        _blocks.push_assign(block, std::move(lhs), std::move(rhs), expr.loc);
                        return block.empty();
                    },
                    [&](const tast::AssignOpExpr &assign) {
                        const auto rhs = unpack(block, expr_as_operand(*assign.rhs, block));
                        const auto lhs = unpack(block, expr_as_place(*assign.lhs, block));
                        const auto result =
                            RValue(BinaryOp{assign.op, Operand::copy(Place(lhs)), rhs});
                        _blocks.push_assign(block, std::move(lhs), std::move(result), expr.loc);
                        return block.empty();
                    },
                    [&](const tast::Break &br) {
                        // set placeholder so that build_in_breakable_scope can
                        // fill this in when it's done building the breakable
                        // scope

                        // assign to break_place
                        block = expr_into_place(_break_places.back(), *br.val, block).into_block();
                        // this block needs a `go to` to the exit of the breakable
                        // scope
                        _need_go_tos.back().push_back(block);
                        return _blocks.create_new_block().empty();
                    },
                    [&](const tast::Return &ret) {
                        // we terminate the block and then we return a new block,
                        // but this one gets deleted
                        auto return_place = Place(LocalId{0});
                        block = expr_into_place(return_place, *ret.val, block).into_block();
                        _blocks.return_(block, expr.loc);
                        // terminate block, but we need a new block for the
                        // following statements these will be deleted because they
                        // are unreachable
                        return _blocks.create_new_block().empty();
                    },
                    [&](const tast::Continue &) {
                        // this needs a goto to the loop block
                        _need_continues.back().push_back(block);
                        return _blocks.create_new_block().empty();
                    },
                    [&](const auto &) {
                        const auto tmp = Place(create_local(
                            "", expr.type, MutabilityType::Immutable, LocalType::Temp, expr.loc
                        ));
                        return expr_into_place(tmp, expr, block);
                    },
                },
                expr.kind
            );
        }
        BlockWith<void> build_print_stmt(const tast::PrintLn &print, BlockId block) {
            auto end_str = print._end_str.value_or("");
            if (!print._start_fmt && print._fmt_structure.empty()) {
                _blocks.push_stmt(block, Statement{SPrintLn{std::move(end_str)}, print.loc});
                return block.empty();
            }
            auto first_operand = map_optional(print._start_fmt, [&](const std::string &s) {
                return Operand::copy(local_by_name(s));
            });
            std::vector<std::pair<std::string, Operand>> format_structure;
            format_structure.reserve(print._fmt_structure.size());
            for (const auto &[str, name] : print._fmt_structure) {
                format_structure.emplace_back(str, Operand::copy(local_by_name(name)));
            }
            _blocks.push_stmt(
                block,
                Statement{
                    FPrintLn{
                        std::move(first_operand), std::move(format_structure), std::move(end_str)
                    },
                    print.loc
                }
            );
            // we already checked the names inside the format, just take them
            // out
            return block.empty();
        }

        //------- Local/Operand stuff -------

        // introduces a temporary if expr is a place
        BlockWith<Operand> expr_as_operand(const tast::Expr &expr, BlockId block) {
            auto handle_temp_move = [&]() {
                auto resolved_type = _inferer.resolve(expr.type);
                if (!resolved_type.is_known()) {
                    ecx.report_diag(errors::unknown_type(expr.loc));
                }
                const auto temp_place = Place(create_local(
                    "temp",
                    std::move(resolved_type),
                    MutabilityType::Mutable,
                    LocalType::Temp,
                    expr.loc
                ));
                unpack(block, expr_into_place(Place(temp_place), expr, block));
                return block.with(Operand::move(Place(temp_place)));
            };
            return std::visit(
                overloaded{
                    [&](const tast::Literal &lit) {
                        auto resolved_type = _inferer.resolve(expr.type);
                        if (!resolved_type.is_known()) {
                            ecx.report_diag(errors::unknown_type(expr.loc));
                        }
                        return block.with(Operand::const_scalar(
                            from_tast_literal(lit), _inferer.resolve(expr.type)
                        ));
                    },
                    [&](const tast::FieldExpr &) {
                        auto place = unpack(block, expr_as_place(expr, block));
                        return block.with(Operand::copy(std::move(place)));
                    },
                    [&](const auto &) { return handle_temp_move(); },
                },
                expr.kind
            );
        } // namespace build

        BlockWith<RValue> expr_as_rvalue(const tast::Expr &expr, BlockId block) {
            return std::visit(
                overloaded{
                    [&](const tast::BinOpExpr &bin_op) {
                        const auto lhs = unpack(block, expr_as_operand(*bin_op.left, block));
                        const auto rhs = unpack(block, expr_as_operand(*bin_op.right, block));
                        return block.with(RValue(BinaryOp{bin_op.op, lhs, rhs}));
                    },
                    [&](const tast::UnaryOpExpr &un_op) {
                        const auto operand = unpack(block, expr_as_operand(*un_op.expr, block));
                        return block.with(RValue(ir::UnaryOp{un_op.op, operand}));
                    },
                    [&](const tast::Identifier &id) {
                        return std::visit(
                            overloaded{
                                [&](const types::FnItem *const &fi) {
                                    // yeah boyyyyy
                                    return block.with(RValue(Cast(
                                        CastKind::FnItemToPtr,
                                        Operand::const_item(fi->id, Ty{fi}),
                                        expr.type
                                    )));
                                },
                                [&](const auto &) {
                                    const auto local = local_by_name(id.symbol);
                                    return block.with(RValue(AsIs{Operand::move(Place(local))}));
                                }
                            },
                            expr.type
                        );
                    },
                    [&](const tast::TupleExpr &tup) {
                        std::vector<Operand> operands;
                        operands.reserve(tup.exprs.size());
                        for (const auto &expr : tup.exprs) {
                            operands.push_back(unpack(block, expr_as_operand(expr, block)));
                        }
                        return block.with(RValue(Aggregate{AggrKind::Tuple, std::move(operands)}));
                    },
                    [&](const tast::Literal &lit) {
                        auto resolved_type = _inferer.resolve(expr.type);
                        if (!resolved_type.is_known()) {
                            ecx.report_diag(errors::unknown_type(expr.loc));
                        }
                        const auto operand =
                            Operand::const_scalar(from_tast_literal(lit), std::move(resolved_type));
                        return block.with(RValue(AsIs{std::move(operand)}));
                    },
                    [&](const auto &) {
                        // these are not rvalues, rustc creates an operand and
                        // returns that as is guess that's the simplest way
                        const auto operand = unpack(block, expr_as_operand(expr, block));
                        return block.with(RValue(AsIs{std::move(operand)}));
                    }
                },
                expr.kind
            );
        }

        BlockWith<std::vector<Operand>>
        build_call_arguments(const tast::CallExpr &call, BlockId block) {
            std::vector<Operand> call_operands{};
            call_operands.reserve(call.args.size());
            std::transform(
                call.args.cbegin(),
                call.args.cend(),
                std::back_inserter(call_operands),
                [&](const tast::Expr &expr) { return unpack(block, expr_as_operand(expr, block)); }
            );
            return block.with(std::move(call_operands));
        }

        BlockWith<void> expr_into_place(Place place, const tast::Expr &expr, BlockId block) {
            return std::visit(
                overloaded{
                    [&](const tast::LogicalOpExpr &log_op) {
                        // the operand is very important to the generated
                        // structure with `&&` we want to go the exit path when
                        // the first operand is false and for `||` we want true
                        // the second operand dictates the result if it is needed
                        const auto cond_op = unpack(block, expr_as_operand(*log_op.left, block));
                        const auto then_blk = _blocks.create_new_block();
                        const auto else_blk = _blocks.create_new_block();
                        // goto then/else from conditinonal
                        _blocks.terminate(
                            block, Terminator(CondGoTo{cond_op, {else_blk, then_blk}}, expr.loc)
                        );

                        // we have to create the short-circuit structure:
                        // - if op is && and lhs fails, we short-circuit and
                        // assign false else we continue with rhs
                        // - if op is || and lhs succeeds, we short-circuit and
                        // assign true else we continue with lhs
                        BlockId short_circuit, continue_block;
                        bool const_bool;
                        switch (log_op.op) {
                        case tast::LogicalOp::Or: {
                            short_circuit = then_blk;
                            continue_block = else_blk;
                            const_bool = true;
                        } break;
                        case tast::LogicalOp::And: {
                            short_circuit = else_blk;
                            continue_block = then_blk;
                            const_bool = false;
                        } break;
                        };
                        // in short circuit, do the assignment and go to join
                        // block
                        _blocks.push_assign(
                            short_circuit,
                            place,
                            AsIs(Operand::const_scalar(
                                Scalar::from_bool(const_bool), _inferer.bool_t()
                            )),
                            expr.loc
                        );
                        const auto rhs =
                            expr_into_place(place, *log_op.right, continue_block).into_block();
                        const auto join = _blocks.create_new_block();
                        _blocks.go_to(short_circuit, join, expr.loc);
                        _blocks.go_to(rhs, join, expr.loc);
                        return join.empty();
                    },
                    [&](const tast::CallExpr &call) {
                        spdlog::info("CALL: fun_ty:{}", call.fun_ty);
                        if (const auto fn_item_p = std::get_if<const FnItem *>(&call.fun_ty)) {
                            const auto fn_item = *fn_item_p;
                            auto call_operands = unpack(block, build_call_arguments(call, block));
                            DBG("here");
                            auto new_block = _blocks.create_new_block();
                            _blocks.terminate(
                                block,
                                Terminator{
                                    Call{
                                        std::move(Operand::const_item(fn_item->id, Ty{fn_item})),
                                        std::move(call_operands),
                                        place,
                                        new_block
                                    },
                                    expr.loc
                                }
                            );
                            return new_block.empty();
                        }
                        auto fn = unpack(block, expr_as_operand(*call.fun, block));
                        auto call_operands = unpack(block, build_call_arguments(call, block));
                        auto new_block = _blocks.create_new_block();
                        _blocks.terminate(
                            block,
                            Terminator{
                                Call{std::move(fn), std::move(call_operands), place, new_block},
                                expr.loc
                            }
                        );
                        return new_block.empty();
                    },
                    [&](const tast::BlockExpr &bl) {
                        return build_block_statements(place, bl, block);
                    },
                    [&](const tast::IfElse &if_el) {
                        /*
                        this is some weird shit but stay with me

                        we need to convert a structure like this:
                            if ? { ... } else { ... }
                            ...
                        into something like this:
                            bb1{
                                _x = ?
                                CondGoTo(move _x) -> [true: then; false: else]
                            }
                            // then branch:
                            bb1{ ... }
                            ...
                            bbx{
                                ...
                                goto -> bbj
                            }

                            //else branch:
                            bbx+1{ ... }
                            ...
                            bbx+y{
                                ...
                                goto -> bbj
                            }

                            // join block
                            bbj { ... }

                        But there are some big caviats as you can see.
                        Building the branches can result in more than 1 block, so
                        the condition should branch into the beginning blocks of
                        either branches and these can result in different "end"
                        blocks. These end blocks should go to the join block. In
                        Code:
                        */
                        const auto cond_op =
                            unpack(block, expr_as_operand(*if_el.conditional_expr, block));
                        // build the then branch
                        auto begin_then_blk = _blocks.create_new_block();
                        auto end_then_blk =
                            build_block_statements(place, if_el.then_block, begin_then_blk)
                                .into_block();
                        // build the else branch
                        auto begin_else_blk = _blocks.create_new_block();
                        auto end_else_blk =
                            if_el.else_block
                                ? expr_into_place(place, *(*if_el.else_block), begin_else_blk)
                                      .into_block()
                                : begin_else_blk;

                        // goto then/else from conditinonal
                        _blocks.terminate(
                            block,
                            Terminator(
                                CondGoTo{cond_op, {begin_else_blk, begin_then_blk}},
                                if_el.conditional_expr->loc
                            )
                        );

                        // we have build both branches, we now join them into a
                        // new block
                        const auto join_block = _blocks.create_new_block();
                        _blocks.go_to(end_then_blk, join_block, expr.loc);
                        _blocks.go_to(end_else_blk, join_block, expr.loc);
                        return join_block.empty();
                    },
                    [&](const tast::Loop &loop) {
                        /*
                        we have to convert the following structure to a CFG:
                            // while loop
                            loop {
                                if <condition> { <body> } else { break }
                            }
                            // or infinite loop
                            loop{
                                <body>
                            }
                        */
                        // create the condition body, this mut be seperate because
                        // this is were everything starts so when we `goto` the
                        // start of the loop, we don't want to execute statements
                        // that have nothing to do with this loop
                        const auto loop_block = _blocks.create_new_block();

                        _blocks.go_to(block, loop_block, expr.loc);
                        return build_in_breakable_scope(loop_block, place, [&](IrBuilder &builder) {
                            const auto body_block = builder._blocks.create_new_block();
                            builder._blocks.go_to(loop_block, body_block, expr.loc);

                            // return value of loop BODY should be unit
                            const auto body_tmp = builder.unit_temp();
                            const auto body_end =
                                builder.expr_into_place(body_tmp, *loop.body, body_block)
                                    .into_block();
                            build_dead_locals(body_end);
                            builder._blocks.go_to(body_end, loop_block, expr.loc);
                        });
                    },
                    [&](const tast::Break &) {
                        // break can't assing to a place
                        block = build_expr_stmt(expr, block).into_block();
                        return block.empty();
                    },
                    [&](const tast::Return &) {
                        block = build_expr_stmt(expr, block).into_block();
                        return block.empty();
                    },
                    [&](const tast::Continue &) {
                        block = build_expr_stmt(expr, block).into_block();
                        return block.empty();
                    },
                    [&](const tast::Unit &) {
                        //_blocks.push_unit_assign(block, unit_temp());
                        return block.empty();
                    },
                    [&](const tast::AssignExpr &) {
                        block = build_expr_stmt(expr, block).into_block();
                        _blocks.push_unit_assign(block, place, expr.loc);
                        return block.empty();
                    },
                    [&](const tast::AssignOpExpr &) {
                        block = build_expr_stmt(expr, block).into_block();
                        _blocks.push_unit_assign(block, place, expr.loc);
                        return block.empty();
                    },
                    [&](const auto &) {
                        const auto rvalue = unpack(block, expr_as_rvalue(expr, block));
                        _blocks.push_assign(block, place, std::move(rvalue), expr.loc);
                        return block.empty();
                    },
                },
                expr.kind
            );
        }

        BlockWith<Place> expr_as_place(const tast::Expr &expr, BlockId block) {
            // currently onlly FieldExpr
            return std::visit(
                overloaded{
                    [&](const tast::FieldExpr &fe) {
                        auto place = unpack(block, expr_as_place(*fe.expr, block));
                        place.field(fe.idx);
                        return block.with(place);
                    },
                    [&](const tast::Identifier &ident) {
                        // so if we find pointer ty, we cast to that
                        // else we keep it,
                        // std::visit(
                        //     overloaded{
                        //         [&](const types::FnItem const *&) {},
                        //         [&](const auto &) {

                        //         }
                        //     },
                        //     expr.type
                        // );
                        return block.with(Place(local_by_name(ident.symbol)));
                    },

                    [&](const auto &e) {
                        fmt::println("OTHER EXPR: {} AS PLACE", e);
                        return unreachable<BlockWith<Place>>();
                    }
                },
                expr.kind
            );
        }

        LocalId local_by_name(const std::string &name) const {
            const auto local = _locals_table.look_up(name);
            spdlog::info("LOCAL `{}`", name);
            if (!local) {
                spdlog::critical("LOCAL `{}` CANT BE FOUND IN IR BUILDER", name);
                ICE(fmt::format("local: {} in IR builder not defined", name));
            }
            return *local;
        }

        Place unit_temp() {
            if (_unit_temp)
                return *_unit_temp;
            else {
                const auto unit_temp = Place(create_local(
                    "UNIT_TEMP",
                    _inferer.unit(),
                    MutabilityType::Mutable,
                    LocalType::Temp,
                    location()
                ));
                _unit_temp = unit_temp;
                return unit_temp;
            }
        }
    }; // namespace middle
}}} // namespace mr::middle::build
