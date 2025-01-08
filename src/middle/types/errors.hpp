#pragma once

#include "mr_util.hpp"
#include "type.hpp"
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <ranges>
#include <string>

namespace mr { namespace middle { namespace types {
    using namespace std::literals;

    static inline std::string default_value_for_ty(const Ty &ty) {
        return std::visit(
            overloaded{

                [](const BoolTy &) { return "false"s; },
                [](const IntTy &) { return "69"s; },
                [](const UIntTy &) { return "420"s; },
                [](const UnitTy &) { return "()"s; },
                [](const FloatTy &) { return "69.420"s; },
                [](const TupleTy &t) {
                    return fmt::format(
                        "({})",
                        fmt::join(
                            t.tys | std::views::transform([](const Ty &ty) -> std::string {
                                return default_value_for_ty(ty);
                            }),
                            ", "
                        )
                    );
                },
                [](const auto &) { return "?"s; }
            },
            ty
        );
    }
}}} // namespace mr::middle::types