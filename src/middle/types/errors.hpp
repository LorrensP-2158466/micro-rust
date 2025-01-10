#pragma once

#include "mr_util.hpp"
#include "type.hpp"
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <ranges>
#include <string>

namespace mr { namespace middle {
    using namespace std::literals;

    static inline std::string default_value_for_ty(const types::Ty &ty) {
        return std::visit(
            overloaded{

                [](const types::BoolTy &) { return "false"s; },
                [](const types::IntTy &) { return "69"s; },
                [](const types::UIntTy &) { return "420"s; },
                [](const types::UnitTy &) { return "()"s; },
                [](const types::FloatTy &) { return "69.420"s; },
                [](const types::TupleTy &t) {
                    return fmt::format(
                        "({})",
                        fmt::join(
                            t.tys | std::views::transform([](const types::Ty &ty) -> std::string {
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
}} // namespace mr::middle