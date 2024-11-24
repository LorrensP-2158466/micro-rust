#pragma once
#include "statement.hpp"
#include "terminator.hpp"
#include <unordered_map>

namespace mr {
    namespace middle {
        namespace ir {
            // im taking some very big shortcuts compared to the rustc impl
            // but this is similar to their `BasicBlock` only still very highlevel
            // In the first implementation of this compiler, this is meant as the
            // representation on which the interpreter will work on, but in the future
            // this will work as an actual **Intermediate** representation of which
            // the byte code will be made
            //
            // A block consists of:
            //  a list of statements (empty or not)
            //  a terminator
            // The statement are not important here, they basicly are a more descriptive
            // verion of the AST statements. The terminator is very important, it acts as
            // a way to go the next block **OR** return from the current function. These
            // are the pointers in the CFG and will let us construct a simple borrow
            // checker and "variable is initalized" checker, together with some other
            // things. This can also be used to make optimizations based on CFG it
            // represents.
            //
            // NOTE: blocks are always inside of a function and ONLY reference blocks
            // inside that function,  going to another function requires a function call

            template <typename T> struct BlockWith;
            struct Terminator;
            struct Block {
                std::vector<Statement> statements;

                // yeah stupid fucking c++ with it's forward declaration bullshit
                // goddammmnnn
                // this is needed because i have to choose between forward
                // declaring a usize (BlockId), which is dumb  or Forward declaring
                // Terminator. so Terminator it is. Maybe there is a fix to this, but i
                // don't think so.
                // Also, this should always exist. (Simplifier may temorarly make this empty, but if it is done, it is not empty)
                Unique<Terminator> terminator;

            };

            struct BlockId {
                size_t                             id;
                template <typename T> BlockWith<T> with(T val);
                BlockWith<void>                    empty() const;

                auto operator<=>(const BlockId&) const = default;
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

            template <typename T> BlockWith<T> BlockId::with(T val) {
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
