#pragma once

#include "mr_util.hpp"
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace mr { namespace middle {

    // From a symbol/id (a.k.a. std::string) to a value
    // But with scopes
    template <typename T> // t is the value
    class SymbolTable {
        struct ScopeEntry {
            std::unordered_map<std::string, T> symbols;
            // raw pointer is valid because this scope can only exist because of it's
            // parent scope Parent scope is NULl so then we know we are at the end
            // when searching
            ScopeEntry() {
                symbols.reserve(8); // 8 symbols per scope? why not
            }

            void clear() { symbols.clear(); }

            auto begin() { return symbols.begin(); }

            auto end() { return symbols.end(); }
            auto begin() const { return symbols.cbegin(); }

            auto end() const { return symbols.cend(); }

            auto cbegin() const { return symbols.cbegin(); }

            auto cend() const { return symbols.cend(); }

            auto insert(const std::string &symbol, T value) {
                return update(symbol, std::move(value));
            }

            auto update(const std::string &symbol, T value) { symbols[symbol] = std::move(value); }

            bool contains(const std::string &symbol) const { return symbols.contains(symbol); }

            T &get_value(const std::string &symbol) { return symbols.at(symbol); }

            const T &get_value(const std::string &symbol) const { return symbols.at(symbol); }
        };
        // current_scope -> parent_scope -> ... -> global_scope
        // so we only delete the parent_scopes if they exist
        std::vector<ScopeEntry> _scopes;
        size_t scopes{0};

      public:
        SymbolTable()
            : _scopes(std::vector<ScopeEntry>(1)) {}

        void print() {
            std::cout << "printing symbol table" << std::endl;
            size_t indent = 0;
            for (auto &scope : _scopes) {
                const auto indent_str = std::string(indent++, '\t');
                for (auto &[name, value] : scope) {
                    std::cout << indent_str << name << " => " << value << std::endl;
                }
            }
        }

        std::optional<T> look_up(const std::string &symbol) const {
            size_t curr_p = _scopes.size();
            while (curr_p > 0) {
                auto &curr = _scopes[curr_p - 1];
                if (curr.contains(symbol)) {
                    return curr.get_value(symbol);
                }
                curr_p--;
            }
            return {};
        }

        auto insert(const std::string &symbol, T value) {
            return get_current_scope().insert(symbol, std::move(value));
        }

        void update(const std::string &symbol, T value) {
            get_current_scope().update(symbol, std::move(value));
        }

        const auto &get_current_scope() const { return _scopes.back(); }

        auto &get_current_scope() { return _scopes.back(); }

        void push_scope() { _scopes.push_back(ScopeEntry()); }

        void pop_scope() {
            if (scopes > 1) {
                _scopes.pop_back();
            } else {
                get_current_scope().clear();
            }
        }

        inline auto begin() { return _scopes.rbegin(); }
        inline auto end() { return _scopes.rend(); }
        inline auto cbegin() const { return _scopes.crbegin(); }
        inline auto cend() const { return _scopes.crend(); }
    };
}} // namespace mr::middle
