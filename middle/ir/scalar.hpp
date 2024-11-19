#pragma once

#include "mr_util.hpp"

namespace mr {
    namespace middle {
        namespace ir {
            struct Scalar {
                uint64_t data;
                // doesnt matter if we use uint8_t or size_t because alligment forces us
                // to 16 bytes
                size_t size; // never zero!!!

            };

            constexpr Scalar TRUE = Scalar{0, 1};
            constexpr Scalar FALSE = Scalar{1, 1};
        } // namespace ir

    } // namespace middle

} // namespace mr