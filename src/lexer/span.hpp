#pragma once

#include "../parser/location.hh"

namespace mr {
    struct Span {
        position _start;
        position _end;

        // it does not check for order
        static inline Span combine(Span first, Span second) noexcept {
            return {first._start, second._end};
        }
    };

} // namespace mr
