#pragma once

#include "ir/module.hpp"
#include "mr_util.hpp"
#include <fmt/format.h>
#include <vector>

namespace mr { namespace middle { namespace ir { namespace traversal {

    class PreOrder {
        const ir::BasicBlocks &blocks;
        std::vector<bool> visited;
        std::vector<ir::BlockId> to_visit;

      public:
        explicit PreOrder(const ir::BasicBlocks &blocks)
            : blocks(blocks)
            , visited{std::vector<bool>(blocks.size())}
            , to_visit(blocks.block(ir::BlockId{0}).terminator().successors().begin(),
                       blocks.block(ir::BlockId{0}).terminator().successors().end()) {
            // current is the start block, so we already visited it
            visited[0] = true;
        }

        std::vector<bool> get_visited() const { return visited; }
        class iterator {
          public:
            using iterator_category = std::input_iterator_tag;
            using value_type = std::pair<ir::BlockId, const ir::Block &>;
            using difference_type = std::ptrdiff_t;
            using pointer = const value_type *;
            using reference = const value_type &;

            iterator() = default; // End iterator constructor

            iterator(PreOrder *parent, ir::BlockId start)
                : self(parent)
                , current(start) {}

            // Iterator operations
            iterator &operator++() {
                while (!self->to_visit.empty()) {
                    current = self->to_visit.back();
                    self->to_visit.pop_back();
                    if (self->visited[current.id()]) {
                        continue;
                    }
                    // fmt::println("visited: {}", self->visited);
                    self->visited[current.id()] = true;
                    addSuccessors();
                    return *this;
                }
                self = nullptr;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            bool operator==(const iterator &other) const {
                return (self == other.self) && (self == nullptr || current == other.current);
            }

            bool operator!=(const iterator &other) const { return !(*this == other); }

            value_type operator*() { return {current, self->blocks.block(current)}; }

          private:
            PreOrder *self = nullptr;
            ir::BlockId current = ir::BlockId{0};

            void addSuccessors() {
                const auto &terminator = self->blocks.block(current).terminator();
                // it is possible that a pass steals the iterator, so in that
                // case, skip
                const auto succs = terminator.successors();
                self->to_visit.insert(self->to_visit.end(), succs.begin(), succs.end());
            }
        };

        // Iterator accessors
        iterator begin() { return !blocks.empty() ? iterator(this, ir::BlockId{0}) : iterator(); }

        iterator end() { return iterator(); }
    };

    static std::vector<bool> reachable_bitset(const ir::BasicBlocks &blocks) {
        auto preorder = PreOrder(blocks);
        for ([[maybe_unused]] const auto &_ : preorder) {
        }
        return preorder.get_visited();
    }
}}}} // namespace mr::middle::ir::traversal
