#pragma once

#include "../ir/module.hpp"
#include "mr_util.hpp"
#include <algorithm>
#include <fmt/format.h>
#include <vector>
namespace mr {
    namespace middle {
        namespace traversal {
            using successor_iterator_t = std::span<const ir::BlockId>::reverse_iterator;
            class PostOrder {
                struct SuccessorIterator {
                    successor_iterator_t current;
                    successor_iterator_t end;
                };
                const ir::BasicBlocks &blocks;
                std::vector<bool> visited;

                std::vector<std::pair<ir::BlockId, SuccessorIterator>> to_visit;

              public:
                explicit PostOrder(const ir::BasicBlocks &blocks)
                    : blocks(blocks)
                    , visited(blocks.size())
                    , to_visit() {
                    visit_block(ir::BlockId{0});
                    traverse_successor();
                }

                void visit_block(ir::BlockId bb) {
                    if (visited[bb.id()])
                        return;
                    visited[bb.id()] = true;
                    const auto succs = blocks.block(bb).terminator().successors();
                    to_visit.emplace_back(bb, SuccessorIterator{succs.rbegin(), succs.rend()});
                }

                void traverse_successor() {
                    while (!to_visit.empty()) {
                        auto &[_, succs] = to_visit.back();
                        if (succs.current == succs.end)
                            break;
                        auto bb = *succs.current++;
                        visit_block(bb);
                    }
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

                    iterator(PostOrder *parent, ir::BlockId start)
                        : self(parent)
                        , current(start) {}

                    // Iterator operations
                    iterator &operator++() {
                        if (!self->to_visit.empty()) {
                            self->to_visit.pop_back();
                            self->traverse_successor();
                        }
                        if (self->to_visit.empty())
                            self = nullptr;
                        return *this;
                    }

                    iterator operator++(int) {
                        iterator tmp = *this;
                        ++(*this);
                        return tmp;
                    }

                    inline bool operator==(const iterator &other) const {
                        return (self == other.self) && (self == nullptr || current == other.current);
                    }

                    bool operator!=(const iterator &other) const { return !(*this == other); }

                    value_type operator*() {
                        current = self->to_visit.back().first;
                        return {current, self->blocks.block(current)};
                    }

                  private:
                    PostOrder *self = nullptr;
                    ir::BlockId current = ir::BlockId{0};
                };

                // Iterator accessors
                iterator begin() { return !blocks.empty() ? iterator(this, to_visit.back().first) : iterator(); }

                iterator end() { return iterator(); }
            };

            static inline auto postorder(const ir::BasicBlocks &blocks) { return PostOrder(blocks); }

            static inline auto reverse_postorder(const ir::BasicBlocks &blocks) {
                auto iterator = PostOrder(blocks);

                std::vector<std::pair<ir::BlockId, Ref<const ir::Block>>> order{};
                order.reserve(blocks.size());

                auto it = order.begin();
                for (auto &&bb : iterator)
                    it = order.emplace(it, bb);
                return order;
            }
        } // namespace traversal

    } // namespace middle

} // namespace mr
