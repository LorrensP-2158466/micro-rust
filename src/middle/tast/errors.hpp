#pragma once

#include "errors/diagnostic.hpp"
#include "location.hh"
#include "types/type.hpp"
#include <fmt/format.h>

namespace mr {
    namespace middle {
        namespace tast {
            namespace errors {

                class MisMatchedReturnTypes {};
                class MisMatchedTypes {};
                class MisMatchedIfElseType {};
                class MisMatchedCallArgs {};

                static inline error::Diagnostic
                unknown_field(std::string field, const types::Ty& actual_type, location loc) {
                    return error::Diagnostic{
                        error::Level::Error,
                        fmt::format("no field `{}` on type `{}`", field, actual_type),
                        loc,
                        std::vector<std::pair<location, std::string>>{
                            {loc, "unkown field"}
                        },
                    };
                }
                class NoFieldOnPrimitive {};
                class CallingUnCallable {};

                class UnAssignableExpr {};
                class IdentNotFound {};
                class UnSupportedUnOp {};

                class ContinueOutsideLoop {};

            } // namespace errors
        } // namespace tast

    } // namespace middle

} // namespace mr
