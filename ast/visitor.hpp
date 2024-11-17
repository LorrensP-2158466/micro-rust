
#pragma once

#include "../expr/module.hpp"
#include "fun_decl.hpp"
#include "let.hpp"
#include "mr_util.hpp"
#include "println.hpp"

namespace mr {
    namespace ast {
        template <typename StmtT = void, typename ExprT = void, typename ItemT = void>
        class AstVisitor {
          public:
            using Stmt_T = StmtT;
            using Expr_T = ExprT;
            using Item_T = ItemT;
            virtual void visit_ast(const ast::Ast& ast) {
                for (const auto& item : ast.items()) {
                    visit_item(*item);
                }
            }

            ItemT visit_item(const ast::Item& i) {
                if (auto fun_decl = dynamic_cast<const ast::FunDecl*>(&i))
                    return visit_fun_decl_item(*fun_decl);
                else {
                    std::cerr << "Unkown Item:\n";
                    i.print(0);
                    std::abort();
                }
            }

            virtual ItemT visit_fun_decl_item(const ast::FunDecl& p) {
                TODO("Implement visit_fun_decl_item");
            };

            StmtT visit_statement(const ast::Stmt& s) {
                if (auto fun_decl = dynamic_cast<const ast::FunDecl*>(&s))
                    return visit_fun_decl_stmt(*fun_decl);
                else if (auto print = dynamic_cast<const ast::PrintLn*>(&s))
                    return visit_print_stmt(*print);
                else if (auto let = dynamic_cast<const ast::LetStmt*>(&s))
                    return visit_let_stmt(*let);
                else if (auto expr = dynamic_cast<const expr::Expr*>(&s)) {
                    return visit_expr(*expr);
                } else {
                    s.print(0);
                    std::abort();
                }
            }

            virtual StmtT visit_print_stmt(const ast::PrintLn& p) = 0;
            virtual StmtT visit_let_stmt(const ast::LetStmt& p) = 0;
            virtual StmtT visit_fun_decl_stmt(const ast::FunDecl& p) = 0;

            ExprT visit_expr(const expr::Expr& expr) {
                if (auto block = dynamic_cast<const expr::BlockExpr*>(&expr))
                    return visit_block_expr(*block);
                else if (auto bin_op = dynamic_cast<const expr::BinOpExpr*>(&expr))
                    return visit_binary_op_expr(*bin_op);
                else if (auto un_op = dynamic_cast<const expr::UnaryOpExpr*>(&expr))
                    return visit_unary_op_expr(*un_op);
                else if (auto if_else = dynamic_cast<const expr::IfElse*>(&expr))
                    return visit_if_else_expr(*if_else);
                else if (auto call = dynamic_cast<const expr::CallExpr*>(&expr))
                    return visit_call_expr(*call);
                else if (auto lit = dynamic_cast<const expr::Literal*>(&expr))
                    return visit_litt_expr(*lit);
                else if (auto assign = dynamic_cast<const expr::AssignExpr*>(&expr))
                    return visit_assign_expr(*assign);
                else if (auto while_l = dynamic_cast<const expr::WhileLoop*>(&expr))
                    return visit_while_expr(*while_l);
                else if (auto id = dynamic_cast<const expr::Identifier*>(&expr))
                    return visit_identifier_expr(*id);
                else if (auto unit = dynamic_cast<const expr::Unit*>(&expr))
                    return visit_unit_expr(*unit);
                else {
                    expr.print(0);
                    std::abort();
                }
            }

            virtual ExprT visit_block_expr(const expr::BlockExpr& block) = 0;
            virtual ExprT visit_identifier_expr(const expr::Identifier& expr) = 0;
            virtual ExprT visit_while_expr(const expr::WhileLoop& expr) = 0;
            virtual ExprT visit_if_else_expr(const expr::IfElse& expr) = 0;
            virtual ExprT visit_binary_op_expr(const expr::BinOpExpr& bin_op) = 0;
            virtual ExprT visit_unary_op_expr(const expr::UnaryOpExpr& expr) = 0;
            virtual ExprT visit_assign_expr(const expr::AssignExpr& expr) = 0;
            virtual ExprT visit_call_expr(const expr::CallExpr& expr) = 0;
            virtual ExprT visit_litt_expr(const expr::Literal& lit) = 0;
            virtual ExprT visit_unit_expr(const expr::Unit& lit) = 0;
        };
    } // namespace ast

} // namespace mr
