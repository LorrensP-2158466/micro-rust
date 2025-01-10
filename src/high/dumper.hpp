
#include "ast/module.hpp"
#include "ast/visitor.hpp"
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <ranges>

// namespace mr { namespace ast {

//     class AstDumper : public AstVisitor<std::string, std::string, std::string> {
//         size_t indent = 0;
//         AstVisitor::Item_T visit_fun_decl_item(const ast::FunDecl &fun_decl) {
//             const auto format_arg = [](const FunArg &fa) { return std::string(); };
//             return fmt::format(
//                 "fn {}() {\n{}\n}",
//                 fun_decl.name(),
//                 fmt::join(fun_decl.args() | std::views::transform(format_arg), ", "),
//                 visit_block_expr(fun_decl.body())
//             );
//         }

//         AstVisitor::Stmt_T visit_print_stmt(const ast::PrintLn &p) = 0;
//         AstVisitor::Stmt_T visit_let_stmt(const ast::LetStmt &p) = 0;
//         AstVisitor::Stmt_T visit_empty_statement(const ast::EmptyStmt) { return ""; }

//         AstVisitor::Expr_T visit_block_expr(const expr::BlockExpr &block) {
//             indent += 1;
//             const auto stmts = fmt::format("{}", )
//             indent -= 1;
//             return "";
//         }
//         AstVisitor::Expr_T visit_identifier_expr(const expr::Identifier &expr) = 0;
//         AstVisitor::Expr_T visit_while_expr(const expr::WhileLoop &expr) = 0;
//         AstVisitor::Expr_T visit_if_else_expr(const expr::IfElse &expr) = 0;
//         AstVisitor::Expr_T visit_binary_op_expr(const expr::BinOpExpr &bin_op) = 0;
//         AstVisitor::Expr_T visit_unary_op_expr(const expr::UnaryOpExpr &expr) = 0;
//         AstVisitor::Expr_T visit_assign_expr(const expr::AssignExpr &expr) = 0;
//         AstVisitor::Expr_T visit_call_expr(const expr::CallExpr &expr) = 0;
//         AstVisitor::Expr_T visit_litt_expr(const expr::Literal &lit) = 0;
//         AstVisitor::Expr_T visit_unit_expr(const expr::Unit &lit) = 0;
//         AstVisitor::Expr_T visit_return_expr(const expr::Return &ret) = 0;
//         AstVisitor::Expr_T visit_break_expr(const expr::Break &brk) = 0;
//         AstVisitor::Expr_T visit_continue_expr(const expr::Continue &cont) = 0;
//         AstVisitor::Expr_T visit_tuple_expr(const expr::TupleExpr &cont) = 0;
//         AstVisitor::Expr_T visit_tuple_idx_expr(const expr::TupleIndexExpr &tup_index) = 0;

//       public:
//         void dump(const Ast &ast) {
//             for (const auto &item : ast.items()) {
//                 visit_item(*item);
//             }
//         }
//     };
// }} // namespace mr::ast