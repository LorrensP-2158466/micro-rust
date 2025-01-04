#pragma once

#include "../expr/block_expr.hpp"
#include "item.hpp"
#include "let.hpp"
#include "mr_util.hpp"
#include "types.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace mr {
    namespace ast {
        struct FunArg {
            std::string id;
            ast::Type   type;
            Mut         mut;
        };

        class FunDecl : public Item {
            std::string         _id;
            std::vector<FunArg> _args;
            ast::Type           _ret_type;
            U<expr::BlockExpr>  _body;

          public:
            FunDecl(
                std::string id, std::vector<FunArg> args, ast::Type ret_type,
                U<expr::BlockExpr> body, location loc
            )
                : Item(loc), _id(id), _args(std::move(args)),
                  _ret_type(std::move(ret_type)), _body(std::move(body)) {}

            static U<FunDecl> make_unique(
                std::string id, std::vector<FunArg> args, ast::Type ret_type,
                U<expr::BlockExpr> body, location loc
            ) noexcept {
                std::cout << std::endl;
                return std::make_unique<FunDecl>(
                    id, std::move(args), std::move(ret_type), std::move(body), loc
                );
            }

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                const auto decl = indent + std::string("FunDecl:\n");
                const auto id = indent + std::string("  identifier: ") + _id + "\n";
                auto       args = indent + std::string("  args:\n");
                for (const auto& arg : _args) {
                    args += arg.id + ": " + arg.type.to_string();
                }
                std::string ret = indent + std::string("  return_type: ") +
                                  _ret_type.to_string() + "\n";
                const auto body = indent + std::string("  body:\n");
                std::cout << decl << id << args << body;
                _body->print(depth + 1);
            }

            const char* name() const { return _id.c_str(); }

            const auto& args() const { return _args; }

            const ast::Type& return_type() const { return _ret_type; }

            const expr::BlockExpr& body() const { return *_body; }
        };
    } // namespace ast

} // namespace mr
