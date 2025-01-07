#pragma once

#include "location.hh"
#include "stmt.hpp"
namespace mr { namespace ast {
    class Item : public Stmt {
      private:
        /* data */
      public:
        Item(location l)
            : Stmt(l) {}
        virtual ~Item() = default;

        virtual void print(const int depth) const = 0;
    };

}} // namespace mr::ast
