#pragma once

/*
    This is the ast lowerer to a more defined middle represantation which will
   make type checking and borrow checking much more convenient. In rust, it
   doesn't matter where something is defined in a scope, it just is defined in
   that entire scope. These "things" are items:
        - function decl
        - struct
        - enum
        - mod and use
    They are defined in their entire scope, so not like c++ where something
   needs to be defined before their use in the program file. So in rust this is
   valid:
        // beginnin of file we can still use `Foo`
        fn foo() -> Foo{
            Foo{}
        }
        // ... some more stuff

        // decl of struct `Foo`
        struct Foo;

    So when we begin to lower the ast, we want to check everything first before
   we do any checking This is called the "scan" fase.

    Next we type check every function and their inner scopes, we will be using a
   symbol table which will simulate these "scopes". But ofcourse, before we
   check any scope, we have to scan that.

    So for example this program:

        fn foo(a: i32, b: i32) -> i32{
            a * b
        }

        fn main(){
            let x = bar();


            fn bar() -> i32 {
                foo(10, 20)
            }
        }

    We will first scan the items in the global scope, (these are always items
   since rust is declarative and non OOP) These will be declared and then we can
   check every scope in order [foo, main] but when we will check main we first
   HAVE to check it's declared items because we use the function `bar` before
    it's declared (remember how this is valid?)
*/
#include "build/ir_builder.hpp"
#include "high/ast/module.hpp"
#include "high/expr/module.hpp"
#include "ir/checker.hpp"
#include "mr_util.hpp"
#include "passes/passmanager.hpp"
#include "symbol_table.hpp"
#include "tast/tast_builder.hpp"
#include "traversal/postorder.hpp"
#include "type_inference.hpp"
#include "types/type.hpp"
#include <errors/ctx.hpp>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace mr {
    namespace middle {
        using namespace types;
        class MiddlePhase {
            error::ErrorCtx &ecx;
            SymbolTable<const ast::FunDecl *> _functions;
            SymbolTable<Ty> _scoped_types;
            inference::TyInferer _inferer;
            ir_pass::PassManager _pass_manager;
            ir::Ir generated_ir;

          public:
            MiddlePhase(error::ErrorCtx &_ecx)
                : ecx(_ecx) {}
            ir::Ir run(const U<ast::Ast> ast) {
                // first we collect every global item (fn, struct, enum, const)
                collect_global_items(*ast.get());

                // then for every executable block of code (fn body, const)
                // to collecting and checking
                check_executable_blocks();
                if (!ecx.has_errors() && !generated_ir.has_main()) {
                    throw std::runtime_error("\nMain function needed as entry point. "
                                             "Please provide:\nfn main(){...}");
                }
                return std::move(generated_ir);
            }

          private:
            [[noreturn]] void type_error(Ty found, Ty expected) {
                std::cerr << "Mismatched Types found: " << _inferer.ty_to_string(found)
                          << " but expected: " << _inferer.ty_to_string(expected) << std::endl;
                std::abort();
            }

            void check_executable_blocks() {
                /*
                When creating the symbol table for every function we inluce 2
                things:
                    - arguments | these are also values
                    - return value | very important!

                the arguments are very straightforward:
                    we insert every argument with their type into the scope

                the return value is not so straightforward:
                    we essentially create an entry in the scope of the function
                called "0_return" (cant be created by user) and everytime we
                want to refer to the return type of the current function we just
                    lookup "0_return" and tada

                */
                TAstBuilder tast_builder{_scoped_types, _inferer, ecx};
                build::IrBuilder ir_builder{ecx, _inferer};
                for (const auto &[fn_name, function] : _functions.get_current_scope()) {
                    auto [outer_tast, inners] = tast_builder.build_everything(*function);
                    if (!outer_tast.structure_invalid)
                        generated_ir.register_function(fn_name, ir_builder.build_function(std::move(outer_tast.tast)));

                    std::vector<std::pair<std::string, ir::Function>> ir_functions{};
                    ir_functions.reserve(inners.size());
                    for (auto &[name, tast, structure_failure] : inners) {
                        // we know errors occured, so we don't have to worry about not
                        // building this, bcs it will not be executed
                        if (structure_failure)
                            continue;
                        ir_functions.emplace_back(std::move(name), ir_builder.build_function(std::move(tast)));
                    }

                    generated_ir.register_functions(std::move(ir_functions));
                    _inferer.clear_tables();
                    generated_ir.dump();
                    spdlog::info("RUNNING CHECKER");
                    // check before opt passes?
                    check_ir(generated_ir, ecx);
                    // don't bother optimizing when 
                    if (ecx.has_errors()) {
                        spdlog::info("RUNNING PASSES");
                        _pass_manager.run_passes(generated_ir);
                    }

                    generated_ir.dump();
                }
            }
            // collects items from statements in a scope
            void collect_scope_items(const std::vector<U<ast::Stmt>> &scope_statements) {
                for (const auto &stmt : scope_statements) {
                    if (auto fn_item = dynamic_cast<const ast::FunDecl *>(stmt.get()))
                        std::runtime_error("Function Items in function scopes not supported yet");
                    // collect_function_item(fn_item);
                }
            }
            void collect_global_items(const ast::Ast &ast) {
                for (const auto &item : ast.items()) {
                    if (auto fn_item = dynamic_cast<const ast::FunDecl *>(item.get())) {
                        collect_function_item(fn_item);
                    }
                }
            }

            void collect_function_item(const ast::FunDecl *fn_item) {
                auto typ = _inferer.create_function_type(*fn_item);
                _scoped_types.insert(fn_item->name(), Ty{typ});
                if (_functions.get_current_scope().contains(fn_item->name())) {
                    std::cerr << "function definition for name: " << fn_item->name() << " already exits\n";
                    throw std::runtime_error("");
                }
                _functions.insert(fn_item->name(), fn_item);
            }
        };
    } // namespace middle

} // namespace mr
