#pragma once

#include "../ir/module.hpp"
#include "../tast/module.hpp"
#include "../type.hpp"
#include "../type_inference.hpp"
#include "basic_blocks.hpp"
#include "mr_util.hpp"
#include <fmt/format.h>
#include <functional>
#include <spdlog/spdlog.h>
#include <unordered_map>

namespace mr {
    namespace middle {
        namespace build {
            using namespace types;
            using namespace tast;
            using namespace inference;
            using namespace ir;

            class IrBuilder {
              public:
                inference::TyInferer& _inferer; // context of types
                // name to local_id, symboltable is used, because we can shadow in rust
                SymbolTable<LocalId> _locals_table;
                LocalId              return_local;
                std::optional<Place> _unit_temp;
                std::vector<Local>   _locals;

                // TODO: create scopes Class to handle this when we introduce drops
                std::vector<Place> _break_places;
                // list of blocks that need a `GoTo` terminator to the enclosing breakable
                // scope
                // TODO: what to do with nested labled scopes
                // only do the top level of course
                std::vector<std::vector<BlockId>> _need_go_tos;

                BasicBlocks _blocks;

                IrBuilder(inference::TyInferer& i) : _inferer(i) {}

                Function build_function(const tast::TAst fn) {

                    return_local = create_local(
                        "0_RETURN", _inferer.resolve(fn.ret_type), Mutability::Mutable
                    );
                    for (const auto& param : fn.params) {
                        const auto ty = _inferer.resolve(param.type);
                        create_local(param.id, ty, param.mut);
                    }
                    auto block_id = _blocks.create_new_block();
                    for (const auto& stmt : fn.body._statements) {
                        block_id = build_statement(*stmt, block_id).into_block();
                    }
                    if (fn.body._tail) {
                        unpack(
                            block_id,
                            expr_into_place(Place(RETURN_LOCAL), *fn.body._tail, block_id)
                        );
                    }
                    _blocks.terminate(block_id, Terminator(Return{}));

                    return Function{
                        fn.name, std::move(_blocks), std::move(_locals), fn.params.size()
                    };
                }

              private:
                Scalar from_tast_literal(const tast::Literal lit) {
                    return Scalar{lit.raw_value(), lit.size()};
                }
                LocalId create_local(const std::string name, Ty ty, Mutability mut) {
                    spdlog::info("CREATING LOCAL `{}`", name);
                    const auto id = LocalId{_locals.size()};
                    _locals_table.insert(name, id);
                    _locals.emplace_back(std::move(name), std::move(ty), mut);
                    return id;
                }

                // helper which assures that going in a scope will always push a scope
                // and exitting will always pop a scope.
                template <typename R>
                BlockWith<R>
                build_in_scope(std::function<BlockWith<R>(IrBuilder& builder)> f) {
                    _locals_table.push_scope();
                    const auto result = f(*this);
                    _locals_table.pop_scope();
                    return result;
                }

                BlockWith<void> build_in_breakable_scope(
                    BlockId loop_block, Place break_place,
                    std::function<void(IrBuilder& builder)> f
                ) {
                    spdlog::info("BUILDING IN A BREAKABLE SCOPE");
                    _break_places.push_back(break_place);
                    _locals_table.push_scope();
                    _need_go_tos.emplace_back();
                    f(*this);
                    _locals_table.pop_scope();
                    _break_places.pop_back();

                    const auto exit_block = _blocks.create_new_block();
                    for (const auto block : _need_go_tos.back()) {
                        _blocks.go_to(block, exit_block);
                    }
                    _need_go_tos.pop_back();
                    spdlog::info("DONE BUILDING IN BREAKABLE SCOPE");
                    return exit_block.empty();
                }

                BlockWith<void> build_block_statements(
                    const Place place, const BlockExpr& tast_block, BlockId basic_block
                ) {
                    unpack(
                        basic_block,
                        build_in_scope<void>([&](IrBuilder& builder) -> BlockWith<void> {
                            for (const auto& stmt : tast_block._statements) {
                                unpack(basic_block, build_statement(*stmt, basic_block));
                            }
                            // check for tail expression
                            if (tast_block._tail)
                                unpack(
                                    basic_block,
                                    expr_into_place(place, *tast_block._tail, basic_block)
                                );
                            return basic_block.empty();
                        })
                    );
                    return basic_block.empty();
                }

                BlockWith<void> build_statement(const tast::Stmt& stmt, BlockId block) {
                    return std::visit(
                        overloaded{
                            [&](const ExprStmt& e) { return build_expr_stmt(e, block); },
                            [&](const LetStmt& e) { return build_let_stmt(e, block); },
                            [&](const PrintLn& e) { return build_print_stmt(e, block); }
                        },
                        stmt.inner
                    );
                }

                BlockWith<void> build_let_stmt(const LetStmt& let, BlockId block) {
                    const auto resolved_ty = _inferer.resolve(let.type_decl);
                    if (!resolved_ty.is_known()) { std::runtime_error("TYPE ERROR"); }
                    const auto local = create_local(let.id, resolved_ty, let.mut);
                    // no initalizer nothing to do
                    if (!let.initializer) return block.empty();
                    return expr_into_place(Place(local), *let.initializer, block);
                }
                BlockWith<void>
                build_expr_stmt(const ExprStmt& expr_stmt, BlockId block) {
                    const Expr& expr = expr_stmt.expr;
                    return std::visit(
                        overloaded{
                            [&](const AssignExpr&) {

                            },
                            [&](const AssignOpExpr&) {

                            },
                            [&](const Break& br) {
                                // set placeholder so that build_in_breakable_scope can
                                // fill this in when it's done building the breakable
                                // scope

                                // assign to break_place
                                block =
                                    expr_into_place(_break_places.back(), *br.val, block)
                                        .into_block();
                                // this block needs a go to to the exit of the breakable
                                // scope
                                _need_go_tos.back().push_back(block);
                                return block.empty();
                            },
                            [&](const auto& buh) {
                                const auto tmp = Place(
                                    create_local("", expr.type, Mutability::Immutable)
                                );
                                return expr_into_place(tmp, expr, block);
                            },
                        },
                        expr.kind
                    );
                }
                BlockWith<void> build_print_stmt(const PrintLn& print, BlockId block) {
                    // not every expr statement needs a tmp;
                    TODO("build let statement");
                }

                //------- Local/Operand stuff -------

                // introduces a temporary if expr is a place
                BlockWith<Operand> expr_as_operand(const Expr& expr, BlockId block) {
                    return std::visit(
                        overloaded{
                            [&](const BinOpExpr& bin_op) {
                                const auto temp_place = Place(create_local(
                                    "temp",
                                    _inferer.resolve(expr.type),
                                    Mutability::Mutable
                                ));
                                unpack(
                                    block, expr_into_place(Place(temp_place), expr, block)
                                );
                                return block.with(Operand::move(Place(temp_place)));
                            },
                            [&](const Literal& lit) {
                                return block.with(Operand::const_(
                                    from_tast_literal(lit), _inferer.resolve(expr.type)
                                ));
                            },
                            [&](const Identifier& id) {
                                const auto local = _locals_table.look_up(id.symbol);
                                if (!local)
                                    throw std::runtime_error(
                                        "LOCAL CANT BE FOUND IN BUILDER"
                                    );
                                const auto ty = _inferer.resolve(expr.type);
                                return block.with(Operand::copy(Place(*local)));
                            },
                            [](const auto& buh) {
                                spdlog::critical("Cant build expr: {} as operand", buh);
                                return mr::unreachable<BlockWith<Operand>>();
                            },
                        },
                        expr.kind
                    );
                } // namespace build

                BlockWith<void>
                expr_into_place(Place place, const Expr& expr, BlockId block) {
                    return std::visit(
                        overloaded{
                            [&](const BinOpExpr& bin_op) {
                                const auto lhs =
                                    unpack(block, expr_as_operand(*bin_op.left, block));
                                const auto rhs =
                                    unpack(block, expr_as_operand(*bin_op.right, block));
                                _blocks.push_assign(
                                    block, place, RValue(BinaryOp{bin_op.op, lhs, rhs})
                                );
                                return block.empty();
                            },
                            [&](const UnaryOpExpr& un_op) {
                                const auto operand =
                                    unpack(block, expr_as_operand(*un_op.expr, block));
                                _blocks.push_assign(
                                    block, place, RValue(ir::UnaryOp{un_op.op, operand})
                                );
                                return block.empty();
                            },
                            [&](const Literal& lit) {
                                const auto operand = Operand::const_(
                                    from_tast_literal(lit), _inferer.resolve(expr.type)
                                );
                                _blocks.push_assign(
                                    block, place, RValue(AsIs{std::move(operand)})
                                );
                                return block.empty();
                            },
                            [&](const Identifier& id) {
                                _locals_table.print();
                                const auto local = _locals_table.look_up(id.symbol);
                                if (!local) {
                                    std::cerr << id.symbol << std::endl;
                                    throw std::runtime_error(
                                        "LOCAL CANT BE FOUND IN BUILDER"
                                    );
                                }
                                _blocks.push_assign(
                                    block,
                                    place,
                                    RValue(AsIs{Operand::move(Place(*local))})
                                );
                                return block.empty();
                            },
                            [&](const CallExpr& call) {
                                // Using std::transform
                                std::vector<Operand> call_operands{};
                                call_operands.reserve(call.args.size());
                                std::transform(
                                    call.args.cbegin(),
                                    call.args.cend(),
                                    std::back_inserter(call_operands),
                                    [&](const auto& expr) {
                                        return unpack(
                                            block, expr_as_operand(*expr, block)
                                        );
                                    }
                                );
                                _blocks.push_assign(
                                    block,
                                    place,
                                    RValue(Call{call.id, std::move(call_operands)})
                                );
                                return block.empty();
                            },
                            [&](const BlockExpr& bl) {
                                return build_block_statements(place, bl, block);
                            },
                            [&](const IfElse& if_el) {
                                const auto cond_op = unpack(
                                    block, expr_as_operand(*if_el.conditional_expr, block)
                                );
                                // build the then branch
                                auto then_blk = _blocks.create_new_block();
                                unpack(
                                    then_blk,
                                    build_block_statements(
                                        place, if_el.then_block, then_blk
                                    )
                                );
                                // build the else branch
                                auto el_blk = _blocks.create_new_block();
                                if (if_el.else_block) {
                                    unpack(
                                        el_blk,
                                        expr_into_place(
                                            place, *(*if_el.else_block), el_blk
                                        )
                                    );
                                } else {
                                    // if no else is used, push assign just to keep the
                                    // CFG in a predictable shape
                                    _blocks.push_unit_assign(el_blk, unit_temp());
                                }

                                // goto then/else from conditinonal
                                _blocks.terminate(
                                    block, Terminator(CondGoTo{cond_op, then_blk, el_blk})
                                );

                                // we have build both branches, we now join them into a
                                // new block
                                const auto join_block = _blocks.create_new_block();
                                _blocks.go_to(then_blk, join_block);
                                _blocks.go_to(el_blk, join_block);
                                return join_block.empty();
                            },
                            [&](const Loop& loop) {
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
                                _blocks.go_to(block, loop_block);
                                return build_in_breakable_scope(
                                    loop_block,
                                    place,
                                    [&](IrBuilder& builder) {
                                        const auto body_block =
                                            _blocks.create_new_block();
                                        _blocks.go_to(loop_block, body_block);

                                        // return value of loop BODY should be unit
                                        const auto body_tmp = unit_temp();
                                        const auto body_end =
                                            expr_into_place(
                                                body_tmp, *loop.body, body_block
                                            )
                                                .into_block();
                                        spdlog::info(
                                            "BODY BLOCK {} <-> END BLOCK {}",
                                            body_block.id,
                                            body_end.id
                                        );
                                        _blocks.go_to(body_end, loop_block);
                                    }
                                );
                            },
                            [&](const Break& br) {
                                // set placeholder so that build_in_breakable_scope can
                                // fill this in when it's done building the breakable
                                // scope

                                // assign to break_place
                                block =
                                    expr_into_place(_break_places.back(), *br.val, block)
                                        .into_block();
                                // this block needs a go to to the exit of the breakable
                                // scope
                                _need_go_tos.back().push_back(block);
                                return block.empty();
                            },
                            [&](const Unit& unit) {
                                //_blocks.push_unit_assign(block, unit_temp());
                                return block.empty();
                            },
                            [&](const auto& buh) {
                                spdlog::critical(
                                    "Cant build expr: `{}` into place: `{}`",
                                    buh,
                                    place.local.id
                                );
                                throw std::runtime_error("COMPILER NOT YET IMPLEMENTED");
                                return mr::unreachable<BlockWith<void>>();
                            },
                        },
                        expr.kind
                    );
                }

                Place unit_temp() {
                    if (_unit_temp) return *_unit_temp;
                    else {
                        const auto unit_temp = Place(create_local(
                            "UNIT_TEMP", _inferer.unit(), Mutability::Mutable
                        ));
                        _unit_temp = unit_temp;
                        return unit_temp;
                    }
                }
            };
        } // namespace build
    } // namespace middle
} // namespace mr
