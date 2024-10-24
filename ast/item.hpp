#pragma once

#include "stmt.hpp"
namespace mr
{
    namespace ast
    {
        class Item : public Stmt
        {
        private:
            /* data */
        public:
            Item(/* args */) = default;
            virtual ~Item() = default;

            virtual void print(const int depth) const = 0;
        };
    
        
    } // namespace ast
    
} // namespace mr
