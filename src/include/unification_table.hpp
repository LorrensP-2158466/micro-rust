#pragma once

#include "datastructures.hpp"
#include <optional>
#include <type_traits>
#include <vector>

namespace mr { namespace middle {

    template <typename T>
    concept Value = requires(const T &lhs, const T &rhs) {
        { T::unify_values(lhs, rhs) } -> std::same_as<T>;
        requires std::is_same_v<decltype(&T::unify_values), T (*)(const T &, const T &)>;
    };

    template <Key K, Value V> class UnificationTable {
        struct Entry {
            V value;       // Holds a specific type or remains undefined
            size_t parent; // Points to the representative of the set or itself
        };
        std::vector<Entry> table;

      public:
        void clear() { table.clear(); }

        K new_var(V val) {
            size_t id = table.size();
            table.push_back({val, id});
            return K(id);
        }

        size_t find(K var) {
            auto root = var.id();
            while (table[root].parent != root) {
                root = table[root].parent;
            }

            // Path compression:
            auto current = var.id();
            while (current != root) {
                auto parent = table[current].parent;
                table[current].parent = root;
                current = parent;
            }

            return root;
        }

        void unionize(K var1, K var2) {
            const auto root1 = find(var1.id());
            const auto root2 = find(var2.id());

            if (root1 != root2) {
                const auto &value1 = table[root1].value;
                const auto &value2 = table[root2].value;
                if (value1 != value2) {
                    throw std::runtime_error("HELP ME IN UNIFICATION TABLE");
                }

                table[root2].parent = root1;
                table[root2].value = V::unify_values(value1, value2);
            }
        }

        // returns value on success
        inline bool unify_var_value(K var, V value) {
            size_t root = find(var.id());
            table[root].value = V::unify_values(table[root].value, value);
            return true;
        }

        void assign(K var, V value) {
            size_t root = find(var.id());
            table[root].value = value;
        }

        std::optional<V> get(K var) { return table.at(find(var.id())).value; }
    };

}} // namespace mr::middle
