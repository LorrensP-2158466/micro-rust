#include <utility>

namespace mr { namespace ops {
    namespace i64 {
        // Helper functions that return result and overflow flag
        static inline std::pair<int64_t, bool> overflowing_div(int64_t l, int64_t r) {
            // Check for overflow (only happens with INT_MIN / -1)
            if (l == std::numeric_limits<int64_t>::min() && r == -1)
                return {l, true};
            return {l / r, false};
        }

        static inline std::pair<int64_t, bool> overflowing_rem(int64_t l, int64_t r) {
            // Remainder can't overflow in two's complement
            return {l % r, false};
        }

        static inline std::pair<int64_t, bool> overflowing_add(int64_t l, int64_t r) {
            int64_t result = l + r;
            // Overflow occurred if signs of operands are the same and sign of result
            // differs
            bool overflow = ((l >= 0) == (r >= 0)) && ((l >= 0) != (result >= 0));
            return {result, overflow};
        }

        static inline std::pair<int64_t, bool> overflowing_sub(int64_t l, int64_t r) {
            int64_t result = l - r;
            // Overflow occurred if signs of operands differ and sign of result
            // differs from l
            bool overflow = ((l >= 0) != (r >= 0)) && ((l >= 0) != (result >= 0));
            return {result, overflow};
        }

        static inline std::pair<int64_t, bool> overflowing_mul(int64_t l, int64_t r) {
            // Use wider type to detect overflow
            __int128_t wide_result = static_cast<__int128_t>(l) * static_cast<__int128_t>(r);
            bool overflow =
                wide_result > std::numeric_limits<int64_t>::max() || wide_result < std::numeric_limits<int64_t>::min();
            return {static_cast<int64_t>(wide_result), overflow};
        }

        static inline bool eq(int64_t l, int64_t r) { return l == r; }
        static inline bool ne(int64_t l, int64_t r) { return l != r; }
        static inline bool lt(int64_t l, int64_t r) { return l < r; }
        static inline bool gt(int64_t l, int64_t r) { return l > r; }
        static inline bool le(int64_t l, int64_t r) { return l <= r; }
        static inline bool ge(int64_t l, int64_t r) { return l >= r; }
    } // namespace i64
    namespace u64 {

        // Unsigned operations
        static inline std::pair<uint64_t, bool> overflowing_div(uint64_t l, uint64_t r) {
            return {l / r, false}; // Unsigned division cannot overflow
        }

        static inline std::pair<uint64_t, bool> overflowing_rem(uint64_t l, uint64_t r) {
            return {l % r, false}; // Unsigned remainder cannot overflow
        }

        static inline std::pair<uint64_t, bool> overflowing_add(uint64_t l, uint64_t r) {
            uint64_t result = l + r;
            bool overflow = result < l; // If result wrapped around, it's smaller than input
            return {result, overflow};
        }

        static inline std::pair<uint64_t, bool> overflowing_sub(uint64_t l, uint64_t r) {
            uint64_t result = l - r;
            bool overflow = result > l; // If result wrapped around, it's larger than input
            return {result, overflow};
        }

        static inline std::pair<uint64_t, bool> overflowing_mul(uint64_t l, uint64_t r) {
            unsigned __int128 wide_result = static_cast<unsigned __int128>(l) * static_cast<unsigned __int128>(r);
            bool overflow = wide_result > std::numeric_limits<uint64_t>::max();
            return {static_cast<uint64_t>(wide_result), overflow};
        }
        static inline bool eq(uint64_t l, uint64_t r) { return l == r; }
        static inline bool ne(uint64_t l, uint64_t r) { return l != r; }
        static inline bool lt(uint64_t l, uint64_t r) { return l < r; }
        static inline bool gt(uint64_t l, uint64_t r) { return l > r; }
        static inline bool le(uint64_t l, uint64_t r) { return l <= r; }
        static inline bool ge(uint64_t l, uint64_t r) { return l >= r; }
    } // namespace u64

}} // namespace mr::ops
