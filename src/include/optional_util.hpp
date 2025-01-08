#pragma once
#include <fmt/format.h>
#include <fmt/std.h>
#include <optional>

namespace mr {

// this is taken from rust, but it is tedious to constantly do:
// - std::make_optional
// - std::null_opt;
// this makes it easier, espaccially in lambdas, which have limited
// typing support
template <typename T> constexpr inline std::optional<T> none() { return std::nullopt; }

template <typename T> constexpr inline std::optional<T> some(T t) {
    return std::make_optional(std::move(t));
}

template <typename T, typename MapF>
auto map_optional(std::optional<T> o, MapF f) -> std::optional<decltype(f(std::declval<T>()))> {
    return o ? some(f(*o)) : std::nullopt;
}
template <typename T, typename U, typename MapF>
U map_optional_or(std::optional<T> o, MapF &&f, U u) {
    return o ? f(std::move(*o)) : std::move(u);
}

template <typename T> std::optional<T> take(std::optional<T> &o) {

    std::optional<T> t = o;
    o = none<T>();
    return t;
}
} // namespace mr
