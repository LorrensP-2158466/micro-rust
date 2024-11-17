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
#include "../ast/module.hpp"
#include "../expr/module.hpp"
#include "build/ir_builder.hpp"
#include "mr_util.hpp"
#include "symbol_table.hpp"
#include "tast_builder.hpp"
#include "type.hpp"
#include "type_inference.hpp"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace mr {
    namespace middle {
        using namespace types;
        class AstLowerer {
            SymbolTable<const ast::FunDecl*> _functions;
            SymbolTable<Ty>                  _scoped_types;
            inference::TyInferer             _inferer;

          public:
            void lower(const Unique<ast::Ast> ast) {
                // first we collect every global item (fn, struct, enum, const)
                collect_global_items(*ast.get());

                // then for every executable block of code (fn body, const)
                // to collecting and checking
                check_executable_blocks();
            }

          private:
            [[noreturn]] void type_error(Ty found, Ty expected) {
                std::cerr << "Mismatched Types found: " << _inferer.ty_to_string(found)
                          << " but expected: " << _inferer.ty_to_string(expected)
                          << std::endl;
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
                TAstBuilder      tast_builder{_scoped_types, _inferer};
                build::IrBuilder ir_builder{_inferer};
                for (const auto& [fn_name, function] : _functions.get_current_scope()) {
                    // collect_scope_items(function->body().statements());
                    auto       fn_tast = tast_builder.build(*function);
                    const auto ir = ir_builder.build_function(std::move(fn_tast));
                    _inferer.clear_tables();
                }
            }

            // collects items from statements in a scope
            void
            collect_scope_items(const std::vector<Unique<ast::Stmt>>& scope_statements) {
                for (const auto& stmt : scope_statements) {
                    if (auto fn_item = dynamic_cast<const ast::FunDecl*>(stmt.get()))
                        std::runtime_error(
                            "Function Items in function scopes not supported yet");
                    // collect_function_item(fn_item);
                }
            }
            void collect_global_items(const ast::Ast& ast) {
                for (const auto& item : ast.items()) {
                    if (auto fn_item = dynamic_cast<const ast::FunDecl*>(item.get())) {
                        collect_function_item(fn_item);
                    }
                }
            }

            void collect_function_item(const ast::FunDecl* fn_item) {
                auto typ = _inferer.create_function_type(*fn_item);
                auto body = &fn_item->body();
                _scoped_types.insert(fn_item->name(), Ty{typ});
                const auto insertion_result = _functions.insert(fn_item->name(), fn_item);
                // if name already exists in global we don't like this
                if (!insertion_result.second) {
                    // TODO: Collect errors
                    // TODO: report spans/locations
                    std::cerr << "function definition for name: " << fn_item->name()
                              << " already exits\n";
                }
            }
        };
    } // namespace middle

} // namespace mr
