#pragma once

#include "module.hpp"
#include <string>

namespace mr { namespace expr {
    struct Return : public Expr {
        U<Expr> val;

        Return(location ret_loc, U<Expr> val)
            : Expr(ret_loc + val->loc)
            , val(std::move(val)) {}

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

        Break(location brk_loc, U<Expr> val)
            : Expr(brk_loc + val->loc)
            , val(std::move(val)) {}

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
        Continue(location loc)
            : Expr(loc) {}
        void print(const int depth) const override {
            const auto indent = std::string(depth, '\t');
            std::cout << indent << "Continue Expr: \n";
        }
    };
}} // namespace mr::expr