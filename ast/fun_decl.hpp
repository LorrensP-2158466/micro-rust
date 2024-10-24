#pragma once

#include "../expr/block_expr.hpp"
#include "item.hpp"
#include "mr_util.hpp"
#include "types.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace mr {
    namespace ast {
        struct FuncArg {
            std::string id;
            ast::Type   type;
        };

        class FunDecl : public Item {

            std::string              _id;
            std::vector<FuncArg>     _args;
            std::optional<ast::Type> _ret_type;
            Unique<expr::BlockExpr>  _body;

          public:
            FunDecl(std::string id, std::vector<FuncArg> args,
                    std::optional<ast::Type> ret_type,
                    Unique<expr::BlockExpr>  body)
                : _id(id), _args(args), _ret_type(ret_type),
                  _body(std::move(body)) {}
            

            static Unique<FunDecl>
            make_unique(std::string id, std::vector<FuncArg> args,
                        std::optional<ast::Type> ret_type,
                        Unique<expr::BlockExpr>  body) noexcept {
                std::cout << std::endl;
                return std::make_unique<FunDecl>(id, args, ret_type,
                                                 std::move(body));
            }

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                const auto decl = indent + std::string("FunDecl:\n");
                const auto id =
                    indent + std::string("  identifier: ") + _id + "\n";
                auto args = indent + std::string("  args:\n");
                for (const auto arg : _args) {
                    args += arg.id + ": " + arg.type.to_string();
                }
                std::string ret =
                    indent + std::string("  return_type: ") +
                    _ret_type.value_or(Type{primitive_type::Unit, 0}).to_string() +
                    "\n";
                const auto body = indent + std::string("  body:\n");
                std::cout << decl << id << args << body;
                _body->print(depth + 1);
            }
            
            const char*  name() const{
                return _id.c_str();
            }

            slice<FuncArg>  args()const{
                return slice(&_args[0], _args.size());
            }

            std::optional<ast::Type> return_type()const{
                return _ret_type;
            }
            
            const expr::BlockExpr&  body() const{
                return *_body;
            }
        };
    } // namespace ast

} // namespace mr
