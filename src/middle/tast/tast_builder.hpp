#pragma once

#include "high/ast/module.hpp"
#include "high/expr/module.hpp"
#include "mr_util.hpp"
#include "symbol_table.hpp"
#include "tast/module.hpp"
#include "type_inference.hpp"
#include "types/type.hpp"
#include <optional>
#include <spdlog/spdlog.h>
#include <variant>

namespace mr {
    namespace middle {
        using namespace ::mr::middle::types;
        using namespace ::mr::middle::tast;
        using namespace ::mr::middle::inference;
        using namespace ::mr::middle::ir;

        class FunctionNamer {
          private:
            size_t _scope_counter;

            std::string generate_mangled_name(
                const std::string& outer_name, const std::string& original_name,
                int block_id
            ) const {
                return fmt::format("{}::{}_{}", outer_name, block_id, original_name);
            }

          public:
            void push_scope() { _scope_counter += 1; }

            void pop_scope() {
                if (_scope_counter >= 1) _scope_counter -= 1;
            }

            // Generate a new unique name for a function in the current scope
            std::string get_unique_name(
                const std::string& outer_name, const std::string& original_name
            ) const {
                return generate_mangled_name(outer_name, original_name, _scope_counter);
            }
        };

        class TAstBuilder : public ast::AstVisitor<Stmt, Expr, void> {
            static inline const char* RETURN_NAME = "0_RETURN";
            SymbolTable<Ty>&          _scoped_types;
            TyInferer&                _inferer;

            FunctionNamer _fn_namer;

            std::optional<Ref<const ast::FunDecl>> _curr_build;
            // possible to have nested functions
            std::vector<std::pair<std::string, Ref<const ast::FunDecl>>>
                                                      _inner_functions_to_build;
            std::vector<std::pair<std::string, TAst>> _built_functions;

            // it is possible that a block contains a return/continue/break
            // these result in the ! type of that block, but we can't know when this
            // happend, this state variable keeps trakc of those exited control flows
            bool control_flow_exit = false;
            // used to check if "continue" is only called inside a loop
            // counter because we can have nested loops, but we only check on 0
            size_t in_loop = 0;

          public:
            TAstBuilder(SymbolTable<Ty>& scoped_types, TyInferer& inferer)
                : _scoped_types(scoped_types), _inferer(inferer), _fn_namer() {};

            ~TAstBuilder() = default;

            std::pair<TAst, std::vector<std::pair<std::string, TAst>>>
            build_everything(const ast::FunDecl& fun_decl) {
                _curr_build = fun_decl;

                auto outer = build_function(fun_decl);
                while (!_inner_functions_to_build.empty()) {
                    const auto& [mangled_name, fn_decl] =
                        _inner_functions_to_build.back();
                    _curr_build = fn_decl;
                    _inner_functions_to_build.pop_back();
                    _built_functions.emplace_back(
                        std::move(mangled_name), build_function(fn_decl)
                    );
                }
                return std::make_pair(std::move(outer), std::move(_built_functions));
            }

            // build function and every nested item of that function
            TAst build_function(const ast::FunDecl& fun_decl) {
                spdlog::info("Beginning TAST build of function {}", fun_decl.name());
                std::vector<Param> args{};
                _fn_namer.push_scope();
                _scoped_types.push_scope();
                _inferer.push_scope();

                // insert arguments and return_type
                const auto return_type = _inferer.from_ast_type(fun_decl.return_type());
                _scoped_types.insert(RETURN_NAME, return_type);
                for (auto&& arg : fun_decl.args()) {
                    const auto type = _inferer.from_ast_type(arg.type);
                    _scoped_types.insert(arg.id, type);
                    args.emplace_back(
                        arg.id,
                        type,
                        arg.mut ? Mutability::Mutable : Mutability::Immutable
                    );
                }
                spdlog::info("visiting block expr");
                auto block_expr = visit_block_expr(fun_decl.body());
                // check implicit return of body to return type
                spdlog::info("Equating types in build");
                if (!_inferer.eq(return_type, block_expr.type)) {
                    type_error(block_expr.type, return_type);
                }
                spdlog::info("Done equating");

                // we have the outer function, now build all the inner ones also
                _inferer.pop_scope();
                _scoped_types.pop_scope();
                _fn_namer.pop_scope();
                return TAst{
                    fun_decl.name(),
                    std::move(args),
                    std::move(std::get<BlockExpr>(block_expr.kind)),
                    return_type
                };
            }

          private:
            [[noreturn]] void type_error(Ty found, Ty expected) {
                std::cerr << "Mismatched Types found: " << _inferer.ty_to_string(found)
                          << " but expected: " << _inferer.ty_to_string(expected)
                          << std::endl;
                std::abort();
            }
            void visit_fun_decl_item(const ast::FunDecl& p) override {
                // so this is a nested function, we have to mangle and change the name
                auto typ = _inferer.create_function_type(p);
                if (_scoped_types.get_current_scope().contains(p.name())) { return; }
                // mangle name
                auto mangled_name =
                    _fn_namer.get_unique_name(_curr_build->get().name(), typ->id);

                typ->id = mangled_name;

                // but still keep the name of the decl in the scope
                _scoped_types.insert(p.name(), Ty{typ});

                _inner_functions_to_build.emplace_back(mangled_name, p);
            }

            Stmt visit_let_stmt(const ast::LetStmt& let) override {
                spdlog::info("Building Ast Let to TAst Let of `{}`", let.id());
                const auto user_decl_type = let.type_decl()
                                                ? _inferer.from_ast_type(*let.type_decl())
                                                : _inferer.create_type_var();

                auto initializer =
                    let.initializer()
                        ? std::make_optional(std::move(visit_expr(*let.initializer())))
                        : std::nullopt;
                if (!initializer) {
                    _scoped_types.insert(let.id(), user_decl_type);
                    return Stmt::let(
                        let.id(),
                        user_decl_type,
                        nullptr,
                        let.is_mutable() ? Mutability::Mutable : Mutability::Immutable
                    );
                }

                // the initializer must match the user defined type
                const auto equated = _inferer.eq(user_decl_type, (*initializer).type);
                if (!equated) { type_error(initializer->type, user_decl_type); }

                _scoped_types.insert(let.id(), *equated);
                auto init = std::make_unique<Expr>(std::move(initializer.value()));
                return Stmt::let(
                    let.id(),
                    *equated,
                    std::move(init),
                    let.is_mutable() ? Mutability::Mutable : Mutability::Immutable
                );
            }

            Stmt visit_print_stmt(const ast::PrintLn& p) override {
                auto print_stmt = PrintLn::from_str(p._format_str);
                auto error = false;
                auto check_name = [&](const std::string& name) {
                    if (!_scoped_types.look_up(name).has_value()) {
                        std::cerr << "In print Statement identifier `" << name
                                  << "` not found\n";
                        error = true;
                    }
                };
                if (print_stmt._start_fmt) check_name(*print_stmt._start_fmt);
                for (const auto [_s, var] : print_stmt._fmt_structure) {
                    fmt::println("{} : {}", _s, var);
                    check_name(var);
                }
                if (error) { std::abort(); }
                return print_stmt;
            }

            /*
            the return type of a block is for now the tail expression
            BUT:

            in the future we will support breaking a labled block, then we
            have to probe to find the first "return expr" of this block,
            this will be highly recursive so i guess we will punish people
            who nest their code with 30 block expressions...
            */
            BlockExpr visit_block_expr_as_block(const expr::BlockExpr& block) {
                return std::get<BlockExpr>(visit_block_expr(block).kind);
            }
            Expr visit_block_expr(const expr::BlockExpr& block) override {
                spdlog::info("Building Block Expr");
                _scoped_types.push_scope();
                _inferer.push_scope();
                _fn_namer.push_scope();

                control_flow_exit = false;
                auto statements = std::vector<U<Stmt>>();
                statements.reserve(block.statements().size());
                for (auto& stmt : block.statements())
                    if (auto item = dynamic_cast<ast::Item*>(stmt.get()))
                        visit_item(*item);

                for (auto& stmt : block.statements()) {
                    // if item, skip we already checked those...
                    if (dynamic_cast<ast::Item*>(stmt.get())) continue;
                    statements.push_back(
                        std::make_unique<Stmt>(std::move(visit_statement(*stmt)))
                    );
                }
                auto tail_expr = block.tail_expr()
                                     ? std::make_optional<Expr>(
                                           std::move(visit_expr(*block.tail_expr()))
                                       )
                                     : std::nullopt;

                auto ty = control_flow_exit
                              ? _inferer.never()
                              : (tail_expr ? tail_expr->type : _inferer.unit());
                _scoped_types.pop_scope();
                _inferer.pop_scope();
                _fn_namer.pop_scope();
                auto tail_p = map_optional_or(
                    std::move(tail_expr),
                    std::make_unique<Expr, Expr>,
                    std::unique_ptr<Expr>(nullptr)
                );
                return Expr(
                    BlockExpr(std::move(statements), std::move(tail_p)), std::move(ty)
                );
            }

            Expr visit_while_expr(const expr::WhileLoop& expr) override {
                spdlog::info("Building Ast `while` to TAst Loop");
                /*
                 so lowering a while expression to a loop expression

                 a while expression looks like this:
                    while `condition` {
                        `body`
                    }
                We have to create a loop expression, with the first statement a branch
                checking wether we can enter the loop body, something like this:
                    loop{
                        if `condition` { `body` } else { break (); }
                    }
                where `condition` is the original while condition
                and `body` is the body of the while expression
                and the break value is unit because of a loop always has unit type
                this can then easely be converted to IR
                */
                auto condition = visit_expr(*expr._cond);
                // condition is always of boolean type
                if (!_inferer.eq(condition.type, _inferer.bool_t())) {
                    type_error(condition.type, _inferer.bool_t());
                };

                auto cond_p = std::make_unique<Expr>(std::move(condition));
                in_loop += 1;
                auto block_expr = visit_block_expr(*expr._body);
                // body is always of unit type
                if (!_inferer.eq(block_expr.type, _inferer.unit())) {
                    type_error(block_expr.type, _inferer.unit());
                }
                auto body = std::get<BlockExpr>(std::move(block_expr.kind));
                in_loop -= 1;
                auto break_branch = std::make_unique<Expr>(
                    BlockExpr(std::make_unique<Expr>(
                        Break(std::make_unique<Expr>(Unit(), _inferer.unit())),
                        _inferer.unit()
                    )),
                    _inferer.unit()
                );

                auto loop_body = std::make_unique<Expr>(
                    ExprKind(IfElse(
                        std::move(cond_p), std::move(body), some(std::move(break_branch))
                    )),
                    _inferer.unit()
                );
                return Expr(ExprKind(Loop(std::move(loop_body))), _inferer.unit());
            }

            Expr visit_unit_expr(const expr::Unit& lit) override {
                return Expr(Unit{}, _inferer.unit());
            }

            // if expression without else clauses resolve to `()` type
            // so we check this
            Expr visit_if_else_expr(const expr::IfElse& expr) override {
                spdlog::info("Building IfElse Expr in to TAST");
                // check that condition is a boolean
                auto condition = visit_expr(*expr.conditional_expr);
                if (!_inferer.eq(condition.type, Ty{BoolTy{}})) {
                    type_error(condition.type, Ty{BoolTy{}});
                };
                auto cond_p = std::make_unique<Expr>(std::move(condition));

                auto then_expr = visit_block_expr(*expr.then_block);
                auto then_block = std::get<BlockExpr>(std::move(then_expr.kind));

                if (!expr.else_block) {
                    if (_inferer.eq(_inferer.unit(), then_expr.type)) {
                        return Expr(
                            ExprKind(std::move(IfElse(
                                std::move(cond_p), std::move(then_block), std::nullopt
                            ))),
                            _inferer.unit()
                        );
                    }
                    type_error(_inferer.unit(), then_expr.type);
                }
                auto       els = visit_expr(*(*expr.else_block));
                const auto ty = _inferer.eq(then_expr.type, els.type);

                if (!ty) type_error(els.type, then_expr.type);
                auto else_p = std::make_unique<Expr>(std::move(els));
                auto kind = ExprKind(std::move(
                    IfElse(std::move(cond_p), std::move(then_block), std::move(else_p))
                ));
                return Expr(std::move(kind), *ty);
            }
            Expr visit_binary_op_expr(const expr::BinOpExpr& bin_op) override {
                spdlog::info("Building Binary Op Expr in to TAST");

                auto left = std::make_unique<Expr>(std::move(visit_expr(*bin_op.left)));
                auto right = std::make_unique<Expr>(std::move(visit_expr(*bin_op.right)));
                auto left_type = left->type;
                auto right_type = right->type;
                Ty   result_type;
                switch (bin_op.op) {
                case expr::BinOp::Mul:
                case expr::BinOp::Div:
                case expr::BinOp::Plus:
                case expr::BinOp::Min: {
                    const auto ty = _inferer.eq(left->type, right->type);
                    if (ty) {
                        if (_inferer.is_integer_type(*ty)) {
                            result_type = *ty;
                            break;
                        }
                    }
                    std::cerr << "Can't perform binary operator "
                              << binop_to_str(bin_op.op) << "On left: " << left
                              << " and right: " << right << std::endl;
                    throw std::runtime_error("Type error on binary operator");
                }
                case expr::BinOp::L_AND:
                case expr::BinOp::L_OR: {
                    auto bool_type = _inferer.bool_t();
                    // if both left and right are boolean, than they are equal
                    if (!_inferer.eq(left_type, bool_type))
                        type_error(left_type, bool_type);
                    if (!_inferer.eq(right_type, bool_type))
                        type_error(right_type, bool_type);
                    return Expr(
                        LogicalOpExpr(
                            std::move(left),
                            log_op_from_bin_op(bin_op.op),
                            std::move(right)
                        ),
                        std::move(bool_type)
                    );
                    break;
                }
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
                    result_type = _inferer.bool_t();
                    break;
                }
                }
                auto op = bin_op_from_ast(bin_op.op);
                return Expr(
                    BinOpExpr(std::move(left), op, std::move(right)),
                    std::move(result_type)
                );
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
                case expr::BinOp::L_AND:
                    return BinOp::And;
                case expr::BinOp::L_OR:
                    return BinOp::Or;
                default: {
                    std::cerr << "Cant Create Binary Operator from "
                              << expr::BinOp_to_string(op) << std::endl;
                    std::abort();
                }
                }
            }

            Expr visit_unary_op_expr(const expr::UnaryOpExpr& expr) override {
                spdlog::info("Building UnaryOp Expr in to TAST");

                auto operand = visit_expr(*expr._expr);
                switch (expr._op) {
                case expr::UnaryOp::Borrow:
                case expr::UnaryOp::MutBorrow:
                case expr::UnaryOp::Deref:
                    throw std::runtime_error("Borrowing/Dereferencing not supported yet");
                case expr::UnaryOp::Not:
                case expr::UnaryOp::Negate:
                    if (_inferer.is_integer_type(operand.type) ||
                        std::holds_alternative<BoolTy>(operand.type)) {
                        // capture ty because of move;
                        const auto ty = operand.type;
                        auto       operand_p = std::make_unique<Expr>(std::move(operand));
                        return Expr(
                            std::move(UnaryOpExpr(expr._op, std::move(operand_p))), ty
                        );
                    }
                    throw std::runtime_error("Can't negate on type: TODO!!!");
                default:
                    throw std::runtime_error("Unknown Unary operator");
                }
            }

            Expr visit_assign_expr(const expr::AssignExpr& assign) override {
                spdlog::info("Building Assign Expr in to TAST");
                // the left type should match the right type;
                const auto assignee_type = _scoped_types.look_up(assign._id);
                if (!assignee_type.has_value()) {
                    std::cerr << "Identifier " << assign._id << "not found\n";
                }

                auto value = visit_expr(*assign._expr.get());
                fmt::println("{} == {}", *assignee_type, value.type);
                const auto ty = _inferer.eq(*assignee_type, value.type);
                if (!ty) { type_error(value.type, *assignee_type); }
                _scoped_types.update(assign._id, *ty);
                auto value_p = std::make_unique<Expr>(std::move(value));
                auto kind = assign._op == expr::AssignOp::Eq
                                ? ExprKind(AssignExpr(assign._id, std::move(value_p)))
                                : ExprKind(AssignOpExpr(
                                      assign._id,
                                      *bin_op_from_assign_op(assign._op),
                                      std::move(value_p)
                                  ));
                return Expr(std::move(kind), _inferer.unit());
            }

            std::optional<BinOp> bin_op_from_assign_op(const expr::AssignOp op) {
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

            Expr visit_return_expr(const expr::Return& ret) override {
                auto value = visit_expr(*ret.val);
                auto return_type = *_scoped_types.look_up(RETURN_NAME);
                auto eq_result = _inferer.eq(value.type, return_type);
                if (!eq_result) { type_error(value.type, return_type); }
                // type of return expr is ! so we set the state
                control_flow_exit = true;
                return Expr(
                    tast::Return{std::make_unique<Expr>(std::move(value))},
                    _inferer.never()
                );
            }
            Expr visit_break_expr(const expr::Break& brk) override {
                auto value = visit_expr(*brk.val);
                auto return_type = *_scoped_types.look_up(RETURN_NAME);
                auto eq_result = _inferer.eq(value.type, return_type);
                if (!eq_result) { type_error(value.type, return_type); }
                // type of break expr is !
                control_flow_exit = true;
                return Expr(
                    tast::Break{std::make_unique<Expr>(std::move(value))},
                    _inferer.never()
                );
            }
            Expr visit_continue_expr(const expr::Continue& cont) override {
                if (!in_loop) {
                    std::runtime_error("CAPTURE ERROR: continue not in loop body");
                }
                control_flow_exit = true;
                return Expr(tast::Continue{}, _inferer.never());
            }

            Expr visit_call_expr(const expr::CallExpr& expr) override {
                spdlog::info("Building Call Expr in to TAST");
                // we search by expr_id but the call will be of the name of the function
                // this way we can call nested same named functions
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
                auto call_operands = std::vector<U<Expr>>();
                call_operands.reserve(expr._args.size());
                for (size_t i = 0; i < ft->arg_types.size(); i++) {
                    const auto& expected_type = ft->arg_types[i];
                    auto        call_op = visit_expr(*expr._args[i]);
                    if (!_inferer.eq(expected_type, call_op.type)) {
                        type_error(call_op.type, expected_type);
                    }
                    call_operands.push_back(std::make_unique<Expr>(std::move(call_op)));
                }
                return Expr(
                    std::move(CallExpr(ft->id, std::move(call_operands))), ft->ret_ty
                );
            }
            Expr visit_litt_expr(const expr::Literal& lit) override {
                spdlog::info("Building Litt Expr in to TAST: `{}`", lit.symbol);
                const auto [l, ty] = Literal::from_ast_lit(lit, _inferer);
                return Expr(std::move(l), ty);
            }

            Expr visit_tuple_expr(const expr::TupleExpr& tup) override {
                std::vector<Expr> exprs;
                std::vector<Ty>   tys;
                exprs.reserve(tup.values.size());
                tys.reserve(tup.values.size());
                // Transform and append results
                for (const auto& e : tup.values) {
                    auto tast_expr = visit_expr(*e);
                    tys.push_back(tast_expr.type);
                    exprs.push_back(std::move(tast_expr));
                }
                return Expr(TupleExpr{std::move(exprs)}, Ty{TupleTy{std::move(tys)}});
            }

            Expr visit_identifier_expr(const expr::Identifier& id) override {
                spdlog::info("Building Identifier Expr in to TAST");

                return Expr(
                    std::move(Identifier(id._id)), *_scoped_types.look_up(id._id)
                );
            }
        }; // TAstBuilder class

    } // namespace middle

} // namespace mr
