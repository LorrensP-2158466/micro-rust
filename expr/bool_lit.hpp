#pragma once

#include "expr.hpp"
#include <iostream>
#include "mr_util.hpp"

namespace mr
{
    namespace expr
    {
        struct BoolLit : public Expr{
            bool _value;

            BoolLit(bool v): Expr(), _value(v){};

            void print(const int depth) const override{
                std::cout << std::string(depth, '\t') << "Boolean Literal: " <<bool_to_str(_value) << std::endl;
            }
        };
    } // namespace expr
    
} // namespace mr
