#pragma once

#include "ast.hpp"

namespace mr {
    namespace ast {
        /**
         * The same as a node i think?
         */
        class Stmt {
          private:
            /* data */
          public:
            Stmt(/* args */) {};
            virtual ~Stmt() = default;

            virtual void print(const int depth) const = 0;
        };

        class EmptyStmt final : public Stmt {
            void print(const int) const {}
        };

    } // namespace ast

} // namespace mr