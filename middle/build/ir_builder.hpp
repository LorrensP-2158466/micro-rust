#pragma once

#include "../ir/module.hpp"
#include "../tast/module.hpp"
#include "../type.hpp"
#include "basic_blocks.hpp"
#include "mr_util.hpp"
#include <unordered_map>

namespace mr {
    namespace middle {
        namespace build {
            using namespace ::mr::middle::types;
            using namespace ::mr::middle::tast;
            using namespace ::mr::middle::inference;
            using namespace ::mr::middle::ir;

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
                    for (const auto& stmt : fn.body->_statements) {
                        block_id = build_statement(stmt, block_id).into_block();
                    }

                    return Function{std::move(_blocks), std::move(_locals)};
                }

              private:
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
                            [&](const PrintLn& e) { return build_print_stmt(e, block); }},
                        stmt);
                }

                BlockWith<void> build_let_stmt(const LetStmt& let, BlockId block) {
                    const auto resolved_ty = _inferer.resolve(let.type_decl);
                    if (!resolved_ty.is_known()) { std::runtime_error("TYPE ERROR"); }
                    const auto local = create_local(let.id, resolved_ty, let.mut);
                    // no initalizer nothing to do
                    if (!let.initializer) return block.empty();
                    return expr_into_place(Place(local), *let.initializer, block)
                        .into_block();
                }
                BlockWith<void> build_expr_stmt(const ExprStmt& expr, BlockId block) {
                    TODO("build expr statement");
                }
                BlockWith<void> build_print_stmt(const PrintLn& print, BlockId block) {
                    TODO("build let statement");
                }


                //------- Local/Operand stuff -------

                // introduces a temporary if expr is a place
                BlockWith<Operand> expr_as_operand(const Expr& expr, BlockId block) {}

                BlockWith<void> expr_into_place(Place place, const Expr& expr,
                                                BlockId block) {
                    RValue val;
                    if (auto block = dynamic_cast<const expr::BlockExpr*>(&expr))
                        TODO("Build Block Expr");
                    else if (auto bin_op = dynamic_cast<const expr::BinOpExpr*>(&expr)) {

                    } else if (auto un_op = dynamic_cast<const expr::UnaryOpExpr*>(&expr))
                        TODO("Build Unary Op Expr");
                    else if (auto if_else = dynamic_cast<const expr::IfElse*>(&expr))
                        TODO("Build If Else Expr");
                    else if (auto call = dynamic_cast<const expr::CallExpr*>(&expr))
                        TODO("Build Call Expr");
                    else if (auto lit = dynamic_cast<const expr::Literal*>(&expr))
                        TODO("Build Lit Expr");
                    else if (auto assign = dynamic_cast<const expr::AssignExpr*>(&expr))
                        TODO("Build Assign Expr");
                    else if (auto while_l = dynamic_cast<const expr::WhileLoop*>(&expr))
                        TODO("Build While Expr");
                    else if (auto id = dynamic_cast<const expr::Identifier*>(&expr))
                        TODO("Build Id Expr");
                    else if (auto unit = dynamic_cast<const expr::Unit*>(&expr))
                        TODO("Build Unit Expr");
                    else {
                        expr.print(0);
                        std::abort();
                    }
                    _blocks.push_assign()
                }

                // -------- Expr Building


            };
        }; // namespace build
    } // namespace middle

} // namespace mr
