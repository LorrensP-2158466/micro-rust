#pragma once

#include "checked_int_ops.hpp"
#include "mr_util.hpp"
#include <type_traits>

namespace mr {
    namespace middle {

        template <typename T>
        concept SignedIntegral = std::integral<T> && std::is_signed_v<T>;

        struct Scalar {
            uint64_t data;
            // doesnt matter if we use uint8_t or size_t because alligment forces us
            // to 16 bytes
            size_t size; // never zero!!!

            static inline Scalar from_bool(bool val) { return Scalar{val, 1}; }

            static inline Scalar from_int(SignedIntegral auto value, size_t byte_size) {
                auto size = byte_size * 8;
                if (would_overflow(value, size)) {
                    throw std::overflow_error(
                        fmt::format("Overflow on {} with target size {}", value, size)
                    );
                }
                // For negative numbers, we need to properly handle two's complement
                uint64_t unsigned_value;
                if (value < 0) {
                    // For negative numbers:
                    // 1. Get absolute value and subtract 1 (for two's complement)
                    // 2. Invert all bits up to bit_size
                    // 3. Mask to ensure we only keep bit_size bits
                    unsigned_value =
                        (~(static_cast<uint64_t>(-value - 1))) & ((1ULL << size) - 1);
                } else {
                    unsigned_value = static_cast<uint64_t>(value);
                }

                auto result = truncate_64(unsigned_value, size);
                return Scalar{result, byte_size};
            }

            static inline uint64_t truncate_64(uint64_t value, size_t bit_size) {
                if (bit_size == 0) {
                    // Truncated until nothing is left
                    return 0;
                }

                auto shift = 64 - bit_size;
                // Truncate (shift left to drop out leftover values, shift right to fill
                // with zeroes)
                return (value << shift) >> shift;
            }

            // Truncate with overflow check
            static inline Scalar from_uint(uint64_t value, size_t byte_size) {
                auto target_size = byte_size * 8;
                if (would_overflow(value, target_size)) {
                    throw std::overflow_error("Value too large for target size");
                }

                // Create a mask with target_size 1s
                uint64_t mask = (1ULL << (target_size - 1)) - 1;
                return Scalar{value & mask, target_size};
            }

            // Integer conversions
            int8_t  to_i8() const { return to_int<int8_t>(); }
            int16_t to_i16() const { return to_int<int16_t>(); }
            int32_t to_i32() const { return to_int<int32_t>(); }
            int64_t to_i64() const { return to_int<int64_t>(); }
            int64_t to_isize() const { return to_int<int64_t>(); }

            // Unsigned integer conversions
            uint8_t  to_u8() const { return to_uint<uint8_t>(); }
            uint16_t to_u16() const { return to_uint<uint16_t>(); }
            uint32_t to_u32() const { return to_uint<uint32_t>(); }
            uint64_t to_u64() const {
                if (size < sizeof(uint64_t))
                    throw std::runtime_error("Invalid size for u64");
                return data;
            }
            uint64_t to_usize() const { return data; }

          private:
            template <typename T> T to_uint() const {
                if (size < sizeof(T)) {
                    throw std::runtime_error("Invalid size for conversion");
                }
                if (data > std::numeric_limits<T>::max()) {
                    throw std::runtime_error("Value too large for target type");
                }
                return static_cast<T>(data);
            }

            template <typename T> T to_int() const {
                static_assert(std::is_integral_v<T>, "T must be an integral type");

                // Check if source size is larger than target type
                if (size > sizeof(T)) {
                    throw std::runtime_error("Source size larger than target type");
                }

                // Calculate bit sizes
                const size_t source_bits = size * 8;
                const size_t target_bits = sizeof(T) * 8;

                int64_t signed_value = sign_extend_64(data, source_bits);

                if constexpr (std::is_signed_v<T>) {
                    if (signed_value >
                            static_cast<int64_t>(std::numeric_limits<T>::max()) ||
                        signed_value <
                            static_cast<int64_t>(std::numeric_limits<T>::min())) {
                        throw std::runtime_error("Value out of range for target type");
                    }
                } else {
                    if (signed_value < 0 || static_cast<uint64_t>(signed_value) >
                                                std::numeric_limits<T>::max()) {
                        throw std::runtime_error("Value out of range for target type");
                    }
                }

                return static_cast<T>(signed_value);
            }

            static inline int64_t sign_extend_64(uint64_t value, size_t bit_size) {
                if (bit_size == 0) { return 0; }

                auto shift = 64 - bit_size;
                return static_cast<int64_t>(value << shift) >> shift;
            }

          public:
            bool to_bool() const {
                if (size < sizeof(uint8_t))
                    throw std::runtime_error("Invalid size for bool");
                if (data > 1)
                    throw std::runtime_error("Invalid boolean value: must be 0 or 1");
                return data == 1;
            }

            static inline bool would_overflow(int64_t value, size_t bit_size) {
                if (bit_size >= 64) return false;

                // For target_size bits, the ranges are:
                // max: 2^(target_size-1) - 1
                // min: -2^(target_size-1)
                int64_t max_value = (1LL << (bit_size - 1)) - 1;
                int64_t min_value = -(1LL << (bit_size - 1));

                return value > max_value || value < min_value;
            }

            static inline bool would_overflow(uint64_t value, size_t bit_size) {
                uint64_t max_value = (1ULL << bit_size) - 1;
                return value > max_value;
            }

            // Floating point conversions
            float to_f32() const {
                if (size != sizeof(float))
                    throw std::runtime_error("Invalid size for f32");
                union {
                    uint32_t i;
                    float    f;
                } converter;
                converter.i = static_cast<uint32_t>(data);
                return converter.f;
            }

            double to_f64() const {
                if (size != sizeof(double))
                    throw std::runtime_error("Invalid size for f64");
                union {
                    uint64_t i;
                    double   d;
                } converter;
                converter.i = data;
                return converter.d;
            }
        };

        constexpr Scalar TRUE = Scalar{0, 1};
        constexpr Scalar FALSE = Scalar{1, 1};

    } // namespace middle

} // namespace mr