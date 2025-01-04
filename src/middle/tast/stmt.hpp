#pragma once

#include "high/expr/module.hpp"
#include "mr_util.hpp"
#include "types/type.hpp"
#include <string>

namespace mr {
    namespace middle {
        namespace tast {

            struct PrintLn {
                // first is possible {var}
                std::optional<std::string> _start_fmt;
                // (str, {var})
                std::vector<std::pair<std::string, std::string>> _fmt_structure;
                // str
                std::optional<std::string> _end_str;

                static PrintLn from_str(const std::string& format_str) {
                    std::regex  pattern(R"(\{([^}]+)\})"); // Regex to match {placeholder}
                    std::smatch matches;

                    PrintLn                     result;
                    std::string::const_iterator searchStart = format_str.cbegin();
                    std::string::const_iterator searchEnd = format_str.cend();

                    // First, check for the start_fmt (first placeholder before any other
                    // content)
                    if (format_str[0] == '{' &&
                        std::regex_search(searchStart, searchEnd, matches, pattern)) {
                        result._start_fmt = matches[1]; // The first matched placeholder
                        searchStart =
                            matches[0]
                                .second; // Move the search start past the first match
                    }

                    // Now parse the remaining content into fmt_structure
                    while (std::regex_search(searchStart, searchEnd, matches, pattern)) {
                        // Add the content before the next placeholder as an actual string
                        result._fmt_structure.push_back(
                            {std::string(searchStart, matches[0].first), matches[1]}
                        );
                        searchStart =
                            matches[0].second; // Move past the matched placeholder
                    }

                    // Add any remaining content after the last placeholder to end_str
                    if (searchStart != searchEnd) {
                        result._end_str = std::string(searchStart, searchEnd);
                    } else {
                        result._end_str =
                            std::nullopt; // No content after the last placeholder
                    }
                    fmt::println("start: {}", result._start_fmt);
                    fmt::println("middle: {}", result._fmt_structure);
                    fmt::println("end: {}", result._end_str);
                    return result;
                }
            };

            /* let (mut)? ID(: TYPE)? ( = INIT)?;
             * why type and init optional? Because this is valid rust code.
             * let x;
             * x = 5;
             */
            struct LetStmt {
                expr::Identifier id;
                types::Ty        type_decl;
                U<Expr>          initializer;
                ir::Mutability   mut;

                LetStmt(expr::Identifier i, types::Ty td, U<Expr> init, ir::Mutability m)
                    : id(std::move(i)), type_decl(td), initializer(std::move(init)),
                      mut(m) {}
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
                let(expr::Identifier i, types::Ty td, U<Expr> init, ir::Mutability m) {
                    return Stmt(LetStmt(std::move(i), td, std::move(init), m));
                }
                static Stmt print(std::string s) { return Stmt(PrintLn(std::move(s))); }
            };

        } // namespace tast

    } // namespace middle

} // namespace mr
