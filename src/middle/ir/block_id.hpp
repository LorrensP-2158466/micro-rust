#pragma once
#include <fmt/ostream.h>

#include "mr_util.hpp"

namespace mr {
    namespace middle {
        namespace ir {

            template <typename T> struct BlockWith;

            struct BlockId {
                size_t idx;
                INDEX_TYPE(BlockId, idx)
                 template <typename T> inline BlockWith<T> with(T val);
                inline BlockWith<void> empty() const;
            };

            template <typename T> struct [[nodiscard]] BlockWith {
                BlockId block;
                T val;

                BlockWith(BlockId b, T v)
                    : block(b)
                    , val(v) {}
                BlockId into_block() && { return std::move(block); }
            };

            template <> struct [[nodiscard]] BlockWith<void> {
                BlockId block;

                BlockWith(BlockId b)
                    : block(b) {}
                BlockId into_block() && { return std::move(block); }
            };

            template <typename T> inline BlockWith<T> BlockId::with(T val) { return BlockWith(*this, std::move(val)); }
            BlockWith<void> BlockId::empty() const { return BlockWith<void>(*this); }

            template <typename T> inline T unpack(BlockId &id, BlockWith<T> block_with) noexcept {
                const auto [block, val] = block_with;
                id = block;
                return val;
            }
            template <> inline void unpack(BlockId &id, BlockWith<void> block_with) noexcept { id = block_with.block; }

            // location inside a body, if stmt_idx == len(statements), this is the terminator
            struct Location {
                ir::BlockId basic_block;
                size_t stmt_idx;
            };
            const static inline Location START_LOCATION = Location{0, 0};

        } // namespace ir

    } // namespace middle

} // namespace mr

OSTREAM_FORMATTER(mr::middle::ir::BlockId)