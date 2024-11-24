#pragma once

#include "../type.hpp"
#include "./expr/module.hpp"
#include "mr_util.hpp"
#include <string>

namespace mr {
    namespace middle {
        namespace tast {

            // TODO enbed instructions to create format str
            struct PrintLn {
                std::string _format_str;

                PrintLn(std::string s) : _format_str(s) {}
            };

            /* let (mut)? ID(: TYPE)? ( = INIT)?;
             * why type and init optional? Because this is valid rust code.
             * let x;
             * x = 5;
             */
            struct LetStmt {
                std::string    id;
                types::Ty      type_decl;
                Unique<Expr>   initializer;
                ir::Mutability mut;

                LetStmt(std::string i, types::Ty td, Unique<Expr> init, ir::Mutability m)
                    : id(i), type_decl(td), initializer(std::move(init)), mut(m) {}
            };

            // Exprs are simple types so we're defining them as structs
            // everything is public this way, but that doesn't really matter
            struct ExprStmt {
                Expr expr;
                ExprStmt(Expr e) : expr(std::move(e)) {}
            };

            using StmtKind = std::variant<ExprStmt, LetStmt, PrintLn>;
            struct Stmt {
                StmtKind inner;
                // for implicit construction
                Stmt(Expr e) : inner(std::move(e)) {}
                Stmt(LetStmt l) : inner(std::move(l)) {}
                Stmt(PrintLn p) : inner(p) {}

                static Stmt expr(Expr e) { return Stmt(std::move(e)); }

                static Stmt
                let(std::string i, types::Ty td, Unique<Expr> init, ir::Mutability m) {
                    return Stmt(LetStmt(i, td, std::move(init), m));
                }
                static Stmt print(std::string s) { return Stmt(PrintLn(std::move(s))); }
            };

        } // namespace tast

    } // namespace middle

} // namespace mr
