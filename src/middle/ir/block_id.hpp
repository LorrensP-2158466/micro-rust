#pragma once
#include "mr_util.hpp"
#include <fmt/ostream.h>

namespace mr {
    namespace middle {
        namespace ir {

            template <typename T> struct BlockWith;

            struct BlockId {
                size_t id;

                BlockId() = default;
                BlockId(size_t id) : id(id) {}
                template <typename T> inline BlockWith<T> with(T val);
                inline BlockWith<void>                    empty() const;

                auto operator<=>(const BlockId&) const = default;
                // Add difference operators
                friend ptrdiff_t operator-(const BlockId& a, const BlockId& b) {
                    return static_cast<ptrdiff_t>(a.id) - static_cast<ptrdiff_t>(b.id);
                }

                BlockId& operator+=(ptrdiff_t n) {
                    id += static_cast<size_t>(n);
                    return *this;
                }

                friend BlockId operator+(BlockId a, ptrdiff_t n) { return a += n; }

                friend BlockId operator+(ptrdiff_t n, BlockId a) { return a += n; }
                // Pre-increment
                BlockId& operator++() {
                    ++id;
                    return *this;
                }

                // Post-increment
                BlockId operator++(int) {
                    BlockId temp = *this;
                    ++(*this);
                    return temp;
                }
                friend std::ostream& operator<<(std::ostream& o, const BlockId b) {
                    o << "bb" << b.id;
                    return o;
                }
            };

            template <typename T> struct [[nodiscard]] BlockWith {
                BlockId block;
                T       val;

                BlockWith(BlockId b, T v) : block(b), val(v) {}
                BlockId into_block() && { return std::move(block); }
            };

            template <> struct [[nodiscard]] BlockWith<void> {
                BlockId block;

                BlockWith(BlockId b) : block(b) {}
                BlockId into_block() && { return std::move(block); }
            };

            template <typename T> inline BlockWith<T> BlockId::with(T val) {
                return BlockWith(*this, std::move(val));
            }
            BlockWith<void> BlockId::empty() const {
                return BlockWith<void>(*this);
            }

            template <typename T>
            inline T unpack(BlockId& id, BlockWith<T> block_with) noexcept {
                const auto [block, val] = block_with;
                id = block;
                return val;
            }
            template <>
            inline void unpack(BlockId& id, BlockWith<void> block_with) noexcept {
                id = block_with.block;
            }
        } // namespace ir

    } // namespace middle

} // namespace mr

OSTREAM_FORMATTER(mr::middle::ir::BlockId)