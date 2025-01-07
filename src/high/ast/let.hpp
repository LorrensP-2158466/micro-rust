#pragma once

#include "../expr/expr.hpp"
#include "mr_util.hpp"
#include "stmt.hpp"
#include "types.hpp"
#include <memory>
#include <optional>

namespace mr { namespace ast {
    using Mut = Locusable<bool>;
    /* let (mut)? ID(: TYPE)? ( = INIT)?;
       why type and init optional? Because this is valid rust code.
        let x;
        x = 5;
     */
    class LetStmt : public Stmt {
        expr::Identifier _ident;
        std::optional<Type> _type_decl;
        U<expr::Expr> _initializer;
        Mut _mutable;

      public:
        // full constructor
        LetStmt(expr::Identifier id, std::optional<Type> type_decl, U<expr::Expr> init, Mut mut, location l)
            : Stmt(l)
            , _ident(std::move(id))
            , _type_decl(std::move(type_decl))
            , _initializer(std::move(init))
            , _mutable(mut) {};

        ~LetStmt() = default;

        static U<LetStmt>
        make_unique_decl(expr::Identifier id, std::optional<Type> type_decl, Mut mut, location l) noexcept {
            return std::make_unique<LetStmt>(
                std::move(id), std::move(type_decl), std::unique_ptr<expr::Expr>{}, mut, l
            );
        }

        // it is possible that we declare a type but init is not that type
        // this is a job for typechecker
        static U<LetStmt> make_unique_init(
            expr::Identifier id, std::optional<Type> type_decl, U<expr::Expr> expr, Mut mut, location l
        ) noexcept {
            return std::make_unique<LetStmt>(std::move(id), std::move(type_decl), std::move(expr), mut, l);
        }

        const expr::Identifier &id() const { return _ident; }
        const std::optional<Type> &type_decl() const { return _type_decl; }
        const expr::Expr *initializer() const { return _initializer.get(); }
        const Mut &mut() const { return _mutable; }

        void print(const int depth) const override {
            const auto indent = std::string(depth, '\t');
            const auto let = indent + "Let Statement:\n";
            const auto id = indent + "  identifier: " + _ident._id + '\n';
            const auto mut = indent + "  mutable: " + bool_to_str(_mutable.node) + "\n";
            auto type_decl = indent + "  type decl: ";
            if (_type_decl) {
                type_decl += _type_decl->to_string() + "\n";
            } else {
                type_decl += "NO TYPE DECL\n";
            }
            const auto init = indent + "  initializer:\n";
            std::cout << let << id << mut << type_decl << init;
            if (_initializer) {
                _initializer->print(depth + 1);
            }
        }
    };

}} // namespace mr::ast
