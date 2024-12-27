#pragma once
#include <limits>
#include <optional>
#include <stdexcept>
#include <type_traits>
namespace mr {
    namespace middle {
        // TODO: CheckedResult instead of optional

        template <std::integral T> inline std::optional<T> checked_add(T a, T b) {
            if ((b > 0 && a > std::numeric_limits<T>::max() - b) ||
                (b < 0 && a < std::numeric_limits<T>::min() - b)) {
                return {};
            }
            return a + b;
        }

        template <std::integral T> inline std::optional<T> checked_sub(T a, T b) {
            if ((b > 0 && a < std::numeric_limits<T>::min() + b) ||
                (b < 0 && a > std::numeric_limits<T>::max() + b)) {
                return {};
            }
            return a - b;
        }

        template <std::integral T> inline std::optional<T> checked_mul(T a, T b) {
            if (a > 0) { // Handle positive a
                if (b > 0 && a > std::numeric_limits<T>::max() / b) return {};
                if (b < 0 && b < std::numeric_limits<T>::min() / a) return {};
            } else if (a < 0) { // Handle negative a
                if (b > 0 && a < std::numeric_limits<T>::min() / b) return {};
                if (b < 0 && b < std::numeric_limits<T>::max() / a) return {};
            }
            return a * b;
        }

        template <std::integral T> inline std::optional<T> checked_div(T a, T b) {
            if (b == 0 || (a == std::numeric_limits<T>::min() && b == -1)) { return {}; }
            return a / b;
        }
    } // namespace middle
} // namespace mr