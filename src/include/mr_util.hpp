#pragma once

#include <fmt/format.h>
#include <fmt/std.h>
#include <spdlog/spdlog.h>

#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <source_location>
#include <variant>

#include "formatters.hpp"
#include "location.hh"
#include "ops.hpp"
#include "optional_util.hpp"

namespace mr {

template <typename T> struct Locusable {
    T node;
    location loc;
};
template <typename T> using Ref = std::reference_wrapper<T>;

inline void todo(
    std::string message = "", const std::source_location location = std::source_location::current()
) {
    std::cerr << "TODO: " << message << " in " << location.file_name() << ':' << location.line()
              << ':' << location.column() << std::endl;
    abort();
}

inline void
ICE(std::string message = "",
    const std::source_location location = std::source_location::current()) {
    throw std::runtime_error(fmt::format("ICE: {} at: {}", message, location));
}

inline void unimplemented(const std::source_location location = std::source_location::current()) {
    std::cerr << "Function: " << location.function_name()
              << " is not implemented:" << location.file_name() << ':' << location.line() << ':'
              << location.column() << std::endl;
    abort();
}

template <typename T>
inline T debug_print(
    std::string expr, T t, const std::source_location location = std::source_location::current()
) {
    std::cerr << "DEBUG:  in " << location.file_name() << ':' << location.line() << ':'
              << location.column() << ": " << expr << " = " << t << std::endl;
    return t;
}
template <typename T = void> [[noreturn]] inline T unreachable() {
// Uses compiler specific extensions if possible.
// Even if no extension is used, undefined behavior is still raised by
// an empty function body and the noreturn attribute.
#if defined(_MSC_VER) && !defined(__clang__) // MSVC
    __assume(false);
#else // GCC, Clang
    __builtin_unreachable();
#endif
}

template <typename Variant, typename... Variants>
bool has_variant(const std::variant<Variants...> &v) {
    return std::holds_alternative<Variant>(v);
}

// convenience to check if variants of the same type hold some combination of variants
template <typename V1, typename V2, typename VariantT>
bool both_hold_variant(const VariantT &vt1, const VariantT &vt2) {
    return has_variant<V1>(vt1) && has_variant<V2>(vt2);
}

// thanks:
// https://stackoverflow.com/questions/46893056/how-do-i-write-operator-for-stdvariant
template <typename T, typename... Ts>
std::ostream &operator<<(std::ostream &os, const std::variant<T, Ts...> &v) {
    std::visit([&os](const auto &arg) { os << arg; }, v);
    return os;
}

// i hate typing "std::unique_ptr" constantly
template <typename T> using U = std::unique_ptr<T>;

template <typename T> using OptUnique = std::optional<U<T>>;

template <class T, class... Args> U<T> m_u(Args &&...args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

inline const char *bool_to_str(const bool b) { return b ? "true" : "false"; }

// this is very unsafe, this just checks if str == "true" else it returns false
// only use this when you are absolutely certain str can only have "true" or "false"
inline bool str_to_bool(const char *str) { return std::strcmp(str, "true") == 0; }

// to create multiple lambdas for std::visit
template <class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};

// dont know if this will work
template <typename U, typename... Ts>
auto variant_apply(std::variant<Ts...> &var, std::function<U(std::variant<Ts...> &)> f) {
    std::visit([&](const Ts var) { return f(var); }..., var);
}
// dynamic_pointer_cast overload for std::unique_ptr
template <class T, class U>
std::unique_ptr<T> dynamic_unique_cast(std::unique_ptr<U> &&r) noexcept {
    (void)dynamic_cast<T *>(static_cast<U *>(0));

    static_assert(
        std::has_virtual_destructor_v<T>,
        "The target of dynamic_pointer_cast must have a virtual destructor."
    );

    T *p = dynamic_cast<T *>(r.get());
    if (p)
        r.release();
    return std::unique_ptr<T>(p);
}

} // namespace mr

// MACROS:

#define TODO(msg)                                                                                  \
    do {                                                                                           \
        todo(msg);                                                                                 \
    } while (false)
#define DBG(t) debug_print(#t, t)

// Credits to someone on stackoverflow, i lost the source....

#define MAP(macro, ...) IDENTITY(APPLY(CHOOSE_MAP_START, COUNT(__VA_ARGS__))(macro, __VA_ARGS__))

#define CHOOSE_MAP_START(count) MAP##count

#define APPLY(macro, ...) IDENTITY(macro(__VA_ARGS__))

#define IDENTITY(x) x

#define MAP1(m, x) m(x)
#define MAP2(m, x, ...) m(x) IDENTITY(MAP1(m, __VA_ARGS__))
#define MAP3(m, x, ...) m(x) IDENTITY(MAP2(m, __VA_ARGS__))
#define MAP4(m, x, ...) m(x) IDENTITY(MAP3(m, __VA_ARGS__))
#define MAP5(m, x, ...) m(x) IDENTITY(MAP4(m, __VA_ARGS__))
#define MAP6(m, x, ...) m(x) IDENTITY(MAP5(m, __VA_ARGS__))
#define MAP7(m, x, ...) m(x) IDENTITY(MAP6(m, __VA_ARGS__))
#define MAP8(m, x, ...) m(x) IDENTITY(MAP7(m, __VA_ARGS__))
#define MAP9(m, x, ...) m(x) IDENTITY(MAP8(m, __VA_ARGS__))
#define MAP10(m, x, ...) m(x) IDENTITY(MAP9(m, __VA_ARGS__))
#define MAP11(m, x, ...) m(x) IDENTITY(MAP10(m, __VA_ARGS__))
#define MAP12(m, x, ...) m(x) IDENTITY(MAP11(m, __VA_ARGS__))
#define MAP13(m, x, ...) m(x) IDENTITY(MAP12(m, __VA_ARGS__))
#define MAP14(m, x, ...) m(x) IDENTITY(MAP13(m, __VA_ARGS__))
#define MAP15(m, x, ...) m(x) IDENTITY(MAP14(m, __VA_ARGS__))
#define MAP16(m, x, ...) m(x) IDENTITY(MAP15(m, __VA_ARGS__))

#define EVALUATE_COUNT(                                                                            \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, count, ...              \
)                                                                                                  \
    count

#define COUNT(...)                                                                                 \
    IDENTITY(EVALUATE_COUNT(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

// Stringizes each argument.
#define STRINGIZE_SINGLE(e) #e,
#define STRINGIZE(...) IDENTITY(MAP(STRINGIZE_SINGLE, __VA_ARGS__))

#define ENUM_DEFINE(enumName, ...)                                                                 \
    enum class enumName { __VA_ARGS__ };                                                           \
    static constexpr std::array enumName##_strings = {IDENTITY(STRINGIZE(__VA_ARGS__))};           \
    static constexpr const char *enumName##_to_string(enumName value) {                            \
        return enumName##_strings[static_cast<size_t>(value)];                                     \
    }                                                                                              \
    static std::ostream &operator<<(std::ostream &o, enumName value) {                             \
        o << enumName##_to_string(value);                                                          \
        return o;                                                                                  \
    }

// ty: Type Struct
// v: Variant Type
// v_t: the acutal std::variant<...>
#define VARIANT_CONSTR(ty, v, v_t)                                                                 \
    ty(v _value)                                                                                   \
        : v_t(_value) {}

#define OSTREAM_FORMATTER(t)                                                                       \
    template <> struct fmt::formatter<t> : ostream_formatter {};

#define INDEX_TYPE(TYPE, idx_val)                                                                  \
    TYPE() = default;                                                                              \
    TYPE(size_t id)                                                                                \
        : idx_val(id) {}                                                                           \
                                                                                                   \
    inline size_t id() const noexcept { return idx_val; }                                          \
                                                                                                   \
    auto operator<=>(const TYPE &) const = default;                                                \
    friend ptrdiff_t operator-(const TYPE &a, const TYPE &b) {                                     \
        return static_cast<ptrdiff_t>(a.idx_val) - static_cast<ptrdiff_t>(b.idx_val);              \
    }                                                                                              \
                                                                                                   \
    TYPE &operator+=(ptrdiff_t n) {                                                                \
        idx_val += static_cast<size_t>(n);                                                         \
        return *this;                                                                              \
    }                                                                                              \
                                                                                                   \
    friend TYPE operator+(TYPE a, ptrdiff_t n) { return a += n; }                                  \
                                                                                                   \
    friend TYPE operator+(ptrdiff_t n, TYPE a) { return a += n; }                                  \
    TYPE &operator++() {                                                                           \
        ++idx_val;                                                                                 \
        return *this;                                                                              \
    }                                                                                              \
                                                                                                   \
    TYPE operator++(int) {                                                                         \
        TYPE temp = *this;                                                                         \
        ++(*this);                                                                                 \
        return temp;                                                                               \
    }                                                                                              \
    friend std::ostream &operator<<(std::ostream &o, const TYPE b) {                               \
        o << b.idx_val;                                                                            \
        return o;                                                                                  \
    }

#define BUG(fmt_str, ...)                                                                          \
    do {                                                                                           \
        ICE(fmt::format(fmt_str, __VA_ARGS__));                                                    \
    } while (false)