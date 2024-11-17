
#pragma once

#include "local.hpp"
#include <variant>
#include <vector>

namespace mr {
    namespace middle {
        namespace ir {

            ENUM_DEFINE(BinOp, Add, Sub, Mul, Div, BitXor, BitAnd, BitOr, Eq, Lt, Le, Ne,
                        Ge, Gt, Cmp, Offset, )
            ENUM_DEFINE(UnOp, Not, Neg)

            // a place is just a location in memory, this will be usefull when
            // doing stuff like: Struct/Tuple Field, slicess, index, deref, ...
            // because when constructing byte code/llvm IR/... this will tell us
            // where in "memory" this is
            // this is again from the rust compiler, but a little different
            // it uses a project list
            struct Place {
                LocalId local;
                // TODO: projections

                Place(LocalId l) : local(l) {}
            };

            // operands, used for borrow checking in the future
            // now everything is just copy because everything is copy
            struct Move {
                Place val;
            };
            struct Copy {
                Place val;
            };
            struct Operand : std::variant<Copy, Move> {

                static Operand move(Place val) { return Operand{Move{val}}; }
                static Operand copy(Place val) { return Operand{Copy{val}}; }
            };

            struct BinaryOp {
                BinOp   op;
                Operand left;
                Operand right;
            };
            // just the value of the local as it is
            struct AsIs {
                Local local;
            };

            using rvalue_variant_t = std::variant<AsIs, BinaryOp>;
            struct RValue : public rvalue_variant_t {};

        } // namespace ir

    } // namespace middle

} // namespace mr