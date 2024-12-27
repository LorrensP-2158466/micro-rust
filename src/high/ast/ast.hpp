#pragma once

#include "item.hpp"
#include "mr_util.hpp"
#include <vector>

namespace mr {
    namespace ast {
        class Ast {
            std::vector<U<Item>> _items;

          public:
            Ast(std::vector<U<Item>> items) : _items(std::move(items)) {};
            ~Ast() = default;

            void print() const {
                for (const auto& item : _items) {
                    item->print(0);
                }
            }

            const auto& items() const { return _items; }
        };
    } // namespace ast
} // namespace mr
