#pragma once

#include "../ast/module.hpp"
#include "../expr/module.hpp"
#include "symbol_table.hpp"
#include "tast/module.hpp"
#include "type.hpp"
#include "type_inference.hpp"

namespace mr {
    namespace middle {
        using namespace ::mr::middle::types;
        using namespace ::mr::middle::tast;
        using namespace ::mr::middle::inference;
        using namespace ::mr::middle::ir;

        class TAstBuilder
            : public ast::AstVisitor<Stmt, Unique<mr::middle::Expr>,
                                     Ty /* visiting an item results in a type*/> {
            using ExprU = Unique<mr::middle::Expr>;
            static const char* RETURN_NAME;
            SymbolTable<Ty>&   _scoped_types;
            TyInferer&         _inferer;

          public:
            TAstBuilder(SymbolTable<Ty>& scoped_types, TyInferer& inferer)
                : _scoped_types(scoped_types), _inferer(inferer) {};

            ~TAstBuilder() = default;

            TAst build(const ast::FunDecl& fun_decl) {
                std::vector<Param> args{};
                _scoped_types.push_scope();
                _inferer.push_scope();

                // insert arguments and return_type
                const auto return_type = _inferer.from_ast_type(fun_decl.return_type());
                _scoped_types.insert(RETURN_NAME, return_type);
                for (auto&& arg : fun_decl.args()) {
                    const auto type = _inferer.from_ast_type(arg.type);
                    _scoped_types.insert(arg.id, type);
                    args.emplace_back(arg.id, type, arg.mut);
                }
                auto block_expr =
                    dynamic_unique_cast<BlockExpr>(visit_block_expr(fun_decl.body()));
                // check implicit return of body to return type
                if (!_inferer.eq(return_type, block_expr->type)) {
                    type_error(block_expr->type, return_type);
                }

                _inferer.pop_scope();
                _scoped_types.pop_scope();
                return TAst{fun_decl.name(), std::move(args), std::move(block_expr),
                            return_type};
            }

            [[noreturn]] void type_error(Ty found, Ty expected) {
                std::cerr << "Mismatched Types found: " << _inferer.ty_to_string(found)
                          << " but expected: " << _inferer.ty_to_string(expected)
                          << std::endl;
                std::abort();
            }

            Stmt visit_fun_decl_stmt(const ast::FunDecl& fun_decl) override {
                TODO("Implement function declarations inside functions");
            }

            Stmt visit_let_stmt(const ast::LetStmt& let) override {
                const auto user_decl_type = let.type_decl()
                                                ? _inferer.from_ast_type(*let.type_decl())
                                                : _inferer.create_type_var();

                auto initializer =
                    let.initializer() ? visit_expr(*let.initializer()) : nullptr;

                if (!initializer) {
                    return Stmt::let(let.id(), user_decl_type, std::move(initializer),
                                     let.is_mutable());
                }
                // the initializer must match the user defined type
                // if there is no user defined type, this will create a
                // type variable which will point to the type of the
                // expression if there is one, the initalizer will be
                // inferred/checked against that
                const auto equated = _inferer.eq(user_decl_type, initializer->type);

                if (!equated) { type_error(initializer->type, user_decl_type); }

                _scoped_types.insert(let.id(), *equated);

                return Stmt::let(let.id(), user_decl_type, std::move(initializer),
                                 let.is_mutable());
            }

            Stmt visit_print_stmt(const ast::PrintLn& p) override {
                std::regex pattern(
                    "\\{([^}]+)\\}"); // Regex pattern to find text between {}
                auto words_begin = std::sregex_iterator(p._format_str.begin(),
                                                        p._format_str.end(), pattern);
                auto words_end = std::sregex_iterator();

                for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
                    const auto id = (*i)[1].str();
                    // "{{x}}" is printed as: {x}
                    // while "{x}" is printed as the value of x
                    if (id.starts_with('{')) continue;
                    if (!_scoped_types.look_up(id).has_value()) {
                        std::cerr << "In print Statement identifier `" << id
                                  << "` not found\n";
                        std::abort();
                    }
                }
                return PrintLn(p._format_str);
            }

            /*
            the return type of a block is for now the tail expression
            BUT:

            in the future we will support breaking a labled block, then we
            have to probe to find the first "return expr" of this block,
            this will be highly recursive so i guess we will punish people
            who nest their code with 30 block expressions...
            */
            Unique<BlockExpr> visit_block_expr_as_block(const expr::BlockExpr& block) {
                return dynamic_unique_cast<BlockExpr>(visit_block_expr(block));
            }
            ExprU visit_block_expr(const expr::BlockExpr& block) override {
                _scoped_types.push_scope();
                _inferer.push_scope();

                auto statements = std::vector<Stmt>();
                statements.reserve(block.statements().size());

                for (auto& stmt : block.statements()) {
                    statements.push_back(std::move(visit_statement(*stmt)));
                }
                auto tail_expr =
                    block.tail_expr() ? visit_expr(*block.tail_expr()) : nullptr;
                const auto ty = tail_expr ? tail_expr->type : Ty{UnitTy{}};
                _scoped_types.pop_scope();
                _inferer.pop_scope();
                return BlockExpr::unique(std::move(statements), std::move(tail_expr), ty);
            }

            ExprU visit_while_expr(const expr::WhileLoop& expr) override {
                TODO("Check while loops");
            }

            ExprU visit_unit_expr(const expr::Unit& lit) override {
                return std::make_unique<Unit>();
            }

            // if expression without else clauses resolve to `()` type
            // so we check this
            ExprU visit_if_else_expr(const expr::IfElse& expr) override {
                // check that condition is a boolean
                auto condition = visit_expr(*expr.conditional_expr);
                if (!_inferer.eq(condition->type, Ty{BoolTy{}})) {
                    type_error(condition->type, Ty{BoolTy{}});
                };

                auto then_block =
                    dynamic_unique_cast<BlockExpr>(visit_block_expr(*expr.then_block));

                if (!expr.else_block) {
                    if (_inferer.eq(Ty{UnitTy{}}, then_block->type)) {
                        DBG("here4");
                        return IfElse::unique(std::move(condition), std::move(then_block),
                                              {}, Ty{UnitTy{}});
                    }
                    type_error(Ty{UnitTy{}}, then_block->type);
                }
                auto       els = visit_expr(*(*expr.else_block));
                const auto ty = _inferer.eq(then_block->type, els->type);

                if (!ty) type_error(els->type, then_block->type);
                return IfElse::unique(std::move(condition), std::move(then_block),
                                      {std::move(els)}, *ty);
            }
            ExprU visit_binary_op_expr(const expr::BinOpExpr& bin_op) override {
                auto left = visit_expr(*bin_op.left);
                auto right = visit_expr(*bin_op.right);
                switch (bin_op.op) {
                case expr::BinOp::Mul:
                case expr::BinOp::Div:
                case expr::BinOp::Plus:
                case expr::BinOp::Min:
                    if (_inferer.is_integer_type(left->type) &&
                        _inferer.is_integer_type(right->type)) {
                        const auto ty = _inferer.eq(left->type, right->type);
                        if (ty)
                            return BinOpExpr::unique(std::move(left),
                                                     bin_op_from_ast(bin_op.op),
                                                     std::move(right), *ty);
                    }
                    std::cerr << "Can't perform binary operator "
                              << binop_to_str(bin_op.op) << "On left: " << left
                              << " and right: " << right << std::endl;
                    throw std::runtime_error("Type error on binary operator");
                case expr::BinOp::L_AND:
                case expr::BinOp::L_OR:
                    throw std::runtime_error("Logical operators not supported");
                case expr::BinOp::Eq:
                case expr::BinOp::NEq:
                case expr::BinOp::Gt:
                case expr::BinOp::Lt:
                case expr::BinOp::GtEq:
                case expr::BinOp::LtEq: {
                    auto eq_result = _inferer.eq(left->type, right->type);
                    if (!eq_result) {
                        std::cerr << "Can't perform binary operator "
                                  << binop_to_str(bin_op.op) << "On left: " << left
                                  << " and right: " << right << std::endl;
                        throw std::runtime_error("Type error on binary operator");
                    }
                    auto op = bin_op_from_ast(bin_op.op);
                    return BinOpExpr::unique(
                        std::move(left), op, std::move(right),
                        _inferer.bool_t()); // these always return boolean
                }
                }
            }

            BinOp bin_op_from_ast(const expr::BinOp& op) {
                switch (op) {
                case expr::BinOp::Mul:
                    return BinOp::Mul;
                case expr::BinOp::Div:
                    return BinOp::Div;
                case expr::BinOp::Plus:
                    return BinOp::Add;
                case expr::BinOp::Min:
                    return BinOp::Sub;
                case expr::BinOp::Eq:
                    return BinOp::Eq;
                case expr::BinOp::NEq:
                    return BinOp::Ne;
                case expr::BinOp::Gt:
                    return BinOp::Gt;
                case expr::BinOp::Lt:
                    return BinOp::Lt;
                case expr::BinOp::GtEq:
                    return BinOp::Ge;
                case expr::BinOp::LtEq:
                    return BinOp::Le;
                default: {
                    std::cerr << "Cant Create Binary Operator from "
                              << expr::BinOp_to_string(op) << std::endl;
                    std::abort();
                }
                }
            }

            ExprU visit_unary_op_expr(const expr::UnaryOpExpr& expr) override {
                auto operand = visit_expr(*expr._expr);
                switch (expr._op) {
                case expr::UnaryOp::Borrow:
                case expr::UnaryOp::MutBorrow:
                case expr::UnaryOp::Deref:
                    throw std::runtime_error("Borrowing/Dereferencing not supported yet");
                case expr::UnaryOp::Not:
                case expr::UnaryOp::Negate:
                    if (_inferer.is_integer_type(operand->type) ||
                        std::holds_alternative<BoolTy>(operand->type)) {
                        return UnaryOpExpr::unique(expr._op, std::move(operand),
                                                   operand->type);
                    }
                    throw std::runtime_error("Can't negate on type: TODO!!!");
                default:
                    throw std::runtime_error("Unknown Unary operator");
                }
            }

            ExprU visit_assign_expr(const expr::AssignExpr& assign) override {
                // the left type should match the right type;
                const auto assignee_type = _scoped_types.look_up(assign._id);
                if (!assignee_type.has_value()) {
                    std::cerr << "Identifier " << assign._id << "not found\n";
                }

                auto value = visit_expr(*assign._expr.get());

                const auto ty = _inferer.eq(*assignee_type, value->type);
                if (!ty) { type_error(value->type, *assignee_type); }
                _scoped_types.update(assign._id, *ty);
                return assign._op == expr::AssignOp::Eq
                           ? AssignExpr::unique(assign._id, std::move(value),
                                                _inferer.unit())
                           : AssignOpExpr::unique(assign._id,
                                                  *bin_op_from_assign_op(assign._op),
                                                  std::move(value), _inferer.unit());
            }

            std::optional<BinOp> bin_op_from_assign_op(const expr::AssignOp& op) {
                switch (op) {
                case expr::AssignOp::Eq:
                    return {};
                case expr::AssignOp::PlusEq:
                    return BinOp::Add;
                case expr::AssignOp::MinEq:
                    return BinOp::Sub;
                case expr::AssignOp::MulEq:
                    return BinOp::Mul;
                case expr::AssignOp::DivEq:
                    return BinOp::Div;
                }
            }

            ExprU visit_call_expr(const expr::CallExpr& expr) override {
                const auto type = _scoped_types.look_up(expr._id);
                if (!type.has_value()) {
                    std::cerr << "No function found with name " << expr._id << std::endl;
                    std::exit(1);
                }
                if (!has_variant<const FunctionType*>(*type)) {
                    std::cerr << "Cant call `" << expr._id
                              << "` which is not a function\n";
                    throw std::runtime_error("Cant call non callable");
                }
                const auto ft = std::get<const FunctionType*>(*type);
                if (ft->arg_types.size() != expr._args.size()) {
                    std::cerr << "Expected " << ft->arg_types.size()
                              << " amount of arguments, "
                              << "but got " << expr._args.size() << " instead\n";
                    std::abort();
                }
                auto call_operands = std::vector<Unique<Expr>>();
                call_operands.reserve(expr._args.size());
                for (size_t i = 0; i < ft->arg_types.size(); i++) {
                    const auto expected_type = ft->arg_types[i];
                    auto       call_op = visit_expr(*expr._args[i]);
                    if (!_inferer.eq(expected_type, call_op->type)) {
                        type_error(call_op->type, expected_type);
                    }
                    call_operands.push_back(std::move(call_op));
                }
                return std::make_unique<CallExpr>(expr._id, std::move(call_operands),
                                                  ft->ret_ty);
            }
            ExprU visit_litt_expr(const expr::Literal& lit) override {
                return std::make_unique<Literal>(Literal::from_ast_lit(lit, _inferer));
            }

            ExprU visit_identifier_expr(const expr::Identifier& id) override {
                return std::make_unique<Identifier>(id._id,
                                                    *_scoped_types.look_up(id._id));
            }
        }; // TAstBuilder class
        const char* TAstBuilder::RETURN_NAME = "0_return";

    } // namespace middle

} // namespace mr
