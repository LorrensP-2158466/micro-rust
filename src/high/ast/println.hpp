#pragma once

#include "location.hh"
#include "module.hpp"
#include <regex>
#include <string>

namespace mr {
    namespace ast {
        class PrintLn : public Stmt {
          public:
            std::string _format_str;

            PrintLn(std::string s, location l) : Stmt(l), _format_str(s) {};
            ~PrintLn() = default;

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "Print Line: " << _format_str << std::endl;
            }
        };

    } // namespace ast

} // namespace mr
