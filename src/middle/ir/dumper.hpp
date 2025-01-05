
#include <variant>

#include "block_id.hpp"
#include "ir.hpp"
#include "statement.hpp"
#include "terminator.hpp"
#include "visitor.hpp"

namespace mr {
    namespace middle {
        namespace ir {

            class IrDumper : public Visitor {};
        } // namespace ir
    } // namespace middle
} // namespace mr