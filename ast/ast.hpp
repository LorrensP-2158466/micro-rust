#pragma once

#include <vector>
#include "mr_util.hpp"
#include "item.hpp"


namespace mr {
    namespace ast {
        class Ast {
            std::vector<Unique<Item>> _items;

          public:
            Ast(std::vector<Unique<Item>> items)
               :  _items(std::move(items)) {};
            ~Ast() = default;

            void print() const{
                for (const auto &item: _items){
                    item->print(0);
                }
            }

            const auto& items() const {
                return _items;
            }


        };
    } // namespace ast

} // namespace mr
