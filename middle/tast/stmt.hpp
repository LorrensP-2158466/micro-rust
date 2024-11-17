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
                std::string  id;
                types::Ty    type_decl;
                Unique<Expr> initializer;
                bool         mut;

                LetStmt(std::string i, types::Ty td, Unique<Expr> init, bool m)
                    : id(i), type_decl(td), initializer(std::move(init)), mut(m) {}
            };

            // Exprs are simple types so we're defining them as structs
            // everything is public this way, but that doesn't really matter
            struct ExprStmt {
                Expr* expr;
                ExprStmt(Expr* e) : expr(e) {}
            };

            using stmt_variant_t = std::variant<ExprStmt, LetStmt, PrintLn>;
            struct Stmt : stmt_variant_t {

                // for implicit construction
                Stmt(Expr* e) : stmt_variant_t(e) {}
                Stmt(Unique<Expr> e) : stmt_variant_t(e.release()) {}
                Stmt(LetStmt l) : stmt_variant_t(std::move(l)) {}
                Stmt(PrintLn p) : stmt_variant_t(p) {}

                static Stmt expr(Expr* e) { return Stmt(e); }

                static Stmt let(std::string i, types::Ty td, Unique<Expr> init, bool m) {
                    return Stmt(LetStmt(i, td, std::move(init), m));
                }
                static Stmt print(std::string s) { return Stmt(PrintLn(std::move(s))); }
            };

        } // namespace tast

    } // namespace middle

} // namespace mr
