#pragma once

#include "module.hpp"
#include <string>

namespace mr {
    namespace expr {
        struct Return : public Expr {
            U<Expr> val;

            Return(U<Expr> val) : Expr(), val(std::move(val)) {}

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "Return Expr: \n";
                if (val) {
                    std::cout << indent << "  val:";
                    val->print(depth + 1);
                    std::cout << std::endl;
                }
            }
        };

        struct Break : public Expr {
            U<Expr> val;

            Break(U<Expr> val) : Expr(), val(std::move(val)) {}

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "Break Expr: \n";
                if (val) {
                    std::cout << indent << "  val:";
                    val->print(depth + 1);
                    std::cout << std::endl;
                }
            }
        };
        struct Continue : public Expr {

            void print(const int depth) const override {
                const auto indent = std::string(depth, '\t');
                std::cout << indent << "Continue Expr: \n";
            }
        };
    } // namespace expr

} // namespace mr