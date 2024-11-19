#pragma once

#include <optional>
#include <vector>

namespace mr {
    namespace middle {
        template <typename K>
        concept Key = requires(K k) {
            { k.id() } -> std::same_as<size_t>;
        } && std::is_constructible_v<K, size_t>;

        template <typename T>
        concept Value = std::equality_comparable<T>;

        template <Key K, Value T> class UnificationTable {
            struct Entry {
                T      value;  // Holds a specific type or remains undefined
                size_t parent; // Points to the representative of the set or itself
            };
            std::vector<Entry> table;

          public:
            void clear() { table.clear(); }

            K new_var(T val) {
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
                auto root1 = find(var1.id());
                auto root2 = find(var2.id());

                if (root1 != root2) {
                    const auto value1 = table[root1].value;
                    const auto value2 = table[root2].value;
                    if (value1 != value2) {
                        throw std::runtime_error("HELP ME IN UNIFICATION TABLE");
                    }

                    table[root2].parent = root1;
                    table[root2].value = value1;
                }
            }

            void assign(K var, T value) {
                size_t root = find(var.id());
                table[root].value = value;
            }

            std::optional<T> get(K var) { return table.at(find(var.id())).value; }
        };

    } // namespace middle

} // namespace mr
