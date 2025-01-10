#pragma once

/**
 *
 * Convenience structure for holding and updating a collection of basic blocks that all
 * point to eachother
 *
 * A CFG if you will
 */

#include <optional>
#include <ranges>
#include <vector>

#include "block_id.hpp"
#include "iterators.hpp"
#include "location.hh"
#include "module.hpp"
#include "mr_util.hpp"
#include "statement.hpp"
#include "terminator.hpp"
#include "types/type.hpp"

namespace mr { namespace middle { namespace ir {

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

    struct Block {
        std::vector<Statement> statements;
        std::optional<Terminator> _terminator;

        Terminator &terminator() {
            if (!_terminator)
                throw std::runtime_error("Invalid terminator state");
            return *_terminator;
        }

        const Terminator &terminator() const {
            if (!_terminator)
                throw std::runtime_error("Invalid terminator state");
            return *_terminator;
        }
    };

    class BasicBlocks {
        std::vector<Block> _blocks;

      public:
        BasicBlocks() = default;
        BasicBlocks(BasicBlocks &&other)
            : _blocks(std::move(other._blocks)) {}

        inline const Block &block(BlockId block) const { return _blocks.at(block.id()); }
        inline Block &block(BlockId block) { return _blocks.at(block.id()); }

        std::vector<Block> &raw_blocks() { return _blocks; }

        auto begin() { return _blocks.begin(); }
        auto end() { return _blocks.end(); }

        auto begin() const { return _blocks.begin(); }
        auto end() const { return _blocks.end(); }
        auto cbegin() const { return _blocks.cbegin(); }
        auto cend() const { return _blocks.cend(); }

        inline Block &operator[](const BlockId idx) { return block(idx); }
        inline const Block &operator[](const BlockId idx) const { return block(idx); }

        auto indices() const { return std::views::iota(BlockId(0), BlockId{_blocks.size()}); }

        auto bb_iter() const { return iterators::zip(indices(), _blocks); }

        // amount of blocks
        size_t size() const noexcept { return _blocks.size(); }
        bool empty() const noexcept { return _blocks.empty(); }

        BlockId create_new_block() {
            const auto id = BlockId{_blocks.size()};
            _blocks.emplace_back();
            return id;
        }

        void terminate(BlockId block, Terminator term) {
            _blocks.at(block.id())._terminator = term;
        }

        void return_(BlockId block, location loc) { terminate(block, Terminator{Return{}, loc}); }

        void go_to(BlockId from, BlockId target, location loc) {
            assert(target.id() < _blocks.size());
            terminate(from, Terminator(GoTo{target}, loc));
        }

        void push_stmt(BlockId bb, Statement stmt) {
            block(bb).statements.push_back(std::move(stmt));
        }

        void push_assign(BlockId block, Place lhs, RValue rhs, location loc) {
            return push_stmt(block, Statement(Assign{lhs, rhs}, loc));
        }

        void push_unit_assign(BlockId block, Place lhs, location loc) {
            return push_stmt(
                block,
                Statement(
                    Assign{lhs, RValue(AsIs(Operand::const_scalar(Scalar{0, 0}, types::Ty::unit())))}, loc
                )
            );
        }

        void dead_local(BlockId block, LocalId local) {
            return push_stmt(block, Statement(Dead{local}));
        }
    };
}}} // namespace mr::middle::ir
