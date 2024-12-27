#pragma once

#include "../expr/expr.hpp"
#include "mr_util.hpp"
#include "stmt.hpp"
#include "types.hpp"
#include <memory>
#include <optional>

namespace mr {
    namespace ast {
        /* let (mut)? ID(: TYPE)? ( = INIT)?;
           why type and init optional? Because this is valid rust code.
            let x;
            x = 5;
         */
        class LetStmt : public Stmt {
            std::string         _id;
            std::optional<Type> _type_decl;
            U<expr::Expr>       _initializer;
            bool                _mutable;

          public:
            // full constructor
            LetStmt(
                std::string id, std::optional<Type> type_decl, U<expr::Expr> init,
                bool mut
            )
                : Stmt(), _id(id), _type_decl(std::move(type_decl)),
                  _initializer(std::move(init)), _mutable(mut) {};

            ~LetStmt() = default;

            static U<LetStmt> make_unique_decl(
                std::string id, std::optional<Type> type_decl, bool mut
            ) noexcept {
                return std::make_unique<LetStmt>(
                    id, std::move(type_decl), std::unique_ptr<expr::Expr>{}, mut
                );
            }

            // it is possible that we declare a type but init is not that type
            // this is a job for typechecker
            static U<LetStmt> make_unique_init(
                std::string id, std::optional<Type> type_decl, U<expr::Expr> expr,
                bool mut
            ) noexcept {
                return std::make_unique<LetStmt>(
                    id, std::move(type_decl), std::move(expr), mut
                );
            }

            const std::string&         id() const { return _id; }
            const std::optional<Type>& type_decl() const { return _type_decl; }
            const expr::Expr*          initializer() const { return _initializer.get(); }
            bool                       is_mutable() const { return _mutable; }

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                const auto let = indent + "Let Statement:\n";
                const auto id = indent + "  identifier: " + _id + '\n';
                const auto mut = indent + "  mutable: " + bool_to_str(_mutable) + "\n";
                auto       type_decl = indent + "  type decl: ";
                if (_type_decl) {
                    type_decl += _type_decl->to_string() + "\n";
                } else {
                    type_decl += "NO TYPE DECL\n";
                }
                const auto init = indent + "  initializer:\n";
                std::cout << let << id << mut << type_decl << init;
                if (_initializer) { _initializer->print(depth + 1); }
            }
        };

    } // namespace ast

} // namespace mr
