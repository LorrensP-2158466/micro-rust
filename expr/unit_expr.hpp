#pragma once
#include "module.hpp"

namespace mr
{
    namespace expr
    {
        // will later be used to create tuple expressions
        struct Unit : public Expr
        {
            void print(const int depth) const override{
                std::cout << std::string(depth, '\t') << "UNIT: ()\n";
            }
        };
        
    } // namespace expr
    
} // namespace mr
