#pragma once

#include "local.hpp"
#include "values.hpp"
#include <variant>
#include <vector>

namespace mr {
    namespace middle {
        namespace ir {
            // because we dont check any thing and because i like std::variant
            // we will be using std::variant
            // lets see if this is possible

            struct Assign {
                Place  place;
                RValue value;
            };
            using statement_variant_t = std::variant<Assign>;
            struct Statement : statement_variant_t {

                Statement(Assign as) : statement_variant_t(as) {}

                void print() const noexcept {
                    std::visit(overloaded{[](const Assign& as) {
                                              std::cout << '_' << as.place.local.id
                                                        << " = " << as.value << std::endl;
                                          },
                                          [](const auto& _skip) {
                                              std::cout << "UNKNOWN STATEMENT"
                                                        << std::endl;
                                          }},
                               *this);
                } // namespace ir
            }; // namespace middle
        } // namespace ir

    } // namespace middle

} // namespace mr