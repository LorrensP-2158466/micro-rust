#pragma once

#include <memory>

#include "../ast/stmt.hpp"
#include "location.hh"

namespace mr {
    namespace expr {
        struct Expr : public ast::Stmt {
            Expr(location l) : ast::Stmt(l) {};
            virtual ~Expr() = default;

            virtual void print(const int depth) const override = 0;
        };

        // create pointer type
    } // namespace expr
} // namespace mr
