#pragma once

#include "ast.hpp"

namespace mr {
    namespace ast {
        /**
         * The same as a node i think?
         */
        class Stmt {
          public:
            location loc;
            Stmt(location l) : loc(l) {};
            virtual ~Stmt() = default;

            virtual void print(const int depth) const = 0;
        };

        struct EmptyStmt final : public Stmt {
            EmptyStmt(location l) : Stmt(l) {}
            void print(const int) const {}
        };

    } // namespace ast

} // namespace mr