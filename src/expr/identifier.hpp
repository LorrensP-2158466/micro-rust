#pragma once

#include "module.hpp"
#include <string>


namespace mr
{
    namespace expr  
    {
        struct Identifier : public Expr{
            std::string _id;


            Identifier(std::string id) : Expr(), _id(id){}

            void print(const int depth) const override{
                const auto indent = std::string(depth, '\t');
                std::cout << indent <<  "Identifier: " << _id << '\n';
            }

        };
    } // namespace expr
    
} // namespace mr
