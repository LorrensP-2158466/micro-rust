#pragma once

#include "../ir/module.hpp"
#include "../tast/module.hpp"
#include "../type.hpp"
#include "../type_inference.hpp"
#include "basic_blocks.hpp"
#include "mr_util.hpp"
#include "spdlog/spdlog.h"
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
                std::vector<Local>   _locals;

                BasicBlocks _blocks;

                IrBuilder(inference::TyInferer& i) : _inferer(i) {}

                Function build_function(const tast::TAst fn) {

                    return_local =
                        create_local("0_RETURN", _inferer.resolve(fn.ret_type), true);
                    for (const auto& param : fn.params) {
                        const auto ty = _inferer.resolve(param.type);
                        create_local(param.id, ty, param.mut); // idk about mutable args
                    }
                    auto block_id = _blocks.create_new_block();
                    for (const auto& stmt : fn.body._statements) {
                        block_id = build_statement(*stmt, block_id).into_block();
                    }

                    return Function{std::move(_blocks), std::move(_locals)};
                }

              private:
                Scalar from_tast_literal(const tast::Literal lit) {
                    return Scalar{lit.raw_value(), lit.size()};
                }
                LocalId create_local(const std::string name, Ty ty, bool mut) {
                    const auto id = LocalId{_locals.size()};
                    _locals_table.insert(name, id);
                    _locals.emplace_back(std::move(name), std::move(ty), mut);
                    return id;
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
                BlockWith<void> build_expr_stmt(const ExprStmt& expr, BlockId block) {
                    TODO("build expr statement");
                }
                BlockWith<void> build_print_stmt(const PrintLn& print, BlockId block) {
                    TODO("build let statement");
                }

                //------- Local/Operand stuff -------

                // introduces a temporary if expr is a place
                BlockWith<Operand> expr_as_operand(const Expr& expr, BlockId block) {

                    return std::visit(
                        overloaded{
                            [&](const BinOpExpr& bin_op) {
                                const auto temp_place = Place(create_local(
                                    "temp", _inferer.resolve(expr.type), true
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
                                // spdlog::critical("Cant build expr: {} as operand",
                                // buh);
                                return mr::unreachable<BlockWith<Operand>>();
                            },
                        },
                        expr.kind
                    );
                } // namespace build

                BlockWith<void>
                expr_into_place(Place place, const Expr& expr, BlockId block) {
                    const auto val = std::visit(
                        overloaded{
                            [&](const BinOpExpr& bin_op) {
                                const auto lhs =
                                    unpack(block, expr_as_operand(*bin_op.left, block));
                                const auto rhs =
                                    unpack(block, expr_as_operand(*bin_op.right, block));
                                return RValue(BinaryOp{bin_op.op, lhs, rhs});
                            },
                            [&](const UnaryOpExpr& un_op) {
                                const auto operand =
                                    unpack(block, expr_as_operand(*un_op.expr, block));
                                return RValue(ir::UnaryOp{un_op.op, operand});
                            },
                            [&](const Literal& lit) {
                                const auto operand = Operand::const_(
                                    from_tast_literal(lit), _inferer.resolve(expr.type)
                                );
                                return RValue(AsIs{std::move(operand)});
                            },
                            [&](const Identifier& id) {
                                const auto local = _locals_table.look_up(id.symbol);
                                if (!local)
                                    throw std::runtime_error(
                                        "LOCAL CANT BE FOUND IN BUILDER"
                                    );
                                return RValue(AsIs{Operand::move(Place(*local))});
                            },
                            [&](const auto& buh) {
                                // spdlog::critical(
                                //     "Cant build expr: {} into place: {}", buh, place
                                // );
                                return mr::unreachable<RValue>();
                            },
                        },
                        expr.kind
                    );
                    _blocks.push_assign(block, place, val);
                    return block.empty();
                } // namespace build

                // -------- Expr Building
            }; // namespace middle
        }; // namespace build
    } // namespace middle

} // namespace mr
