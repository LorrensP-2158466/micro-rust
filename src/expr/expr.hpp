# pragma once

#include <memory>

#include "../ast/stmt.hpp"
#include "../ast/types.hpp"

namespace mr
{
    namespace expr
    {
        // Exprs are simple types so we're defining them as structs
        // everything is public this way, but that doesn't really matter
        struct Expr: public ast::Stmt{

            Expr() : ast::Stmt() {};
            virtual ~Expr() = default;
        
            virtual void print(const int depth)const override = 0;
        } ;

        // create pointer type
    } // namespace expr
} // namespace mr
