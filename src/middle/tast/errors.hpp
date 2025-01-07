#pragma once

#include "errors/diagnostic.hpp"
#include "location.hh"
#include "types/type.hpp"
#include <fmt/format.h>

namespace mr { namespace middle { namespace tast { namespace errors {

    static inline error::Diagnostic mismatched_return_types(
        const types::Ty &found, location found_loc, const types::Ty &expected, location expected_loc
    ) {
        return error::Diagnostic{
            error::Level::Error,
            std::string("Return type mismatch"),
            found_loc,
            std::vector{
                error::DiagnosticLabel{
                    expected_loc,
                    fmt::format("Expected `{}` because of return type", expected),
                    error::Style::Primary
                },
                error::DiagnosticLabel{
                    found_loc,
                    fmt::format("Expected `{}` but found `{}`", expected, found),
                    error::Style::Primary
                },
            },
        };
    }

    static inline error::Diagnostic
    mismatched_types(const types::Ty &found, const types::Ty &expected, location loc) {
        return error::Diagnostic{
            error::Level::Error,
            std::string("Type mismatch"),
            loc,
            std::vector{error::DiagnosticLabel{
                loc,
                fmt::format("Expected `{}` but found `{}`", expected, found),
                error::Style::Primary
            }},
        };
    }

    static inline error::Diagnostic mismatched_if_else_types(
        const types::Ty &found, location else_t_loc, const types::Ty &expected, location if_t_loc,
        location if_loc, location else_loc
    ) {
        return error::Diagnostic{
            error::Level::Error,
            std::string("`if` and `else` have incompatible types"),
            else_t_loc,
            {error::DiagnosticLabel{if_loc, "", error::Style::Secondary},
             error::DiagnosticLabel{if_t_loc, "expected because of this", error::Style::Secondary},
             error::DiagnosticLabel{else_loc, "", error::Style::NoStyle},
             error::DiagnosticLabel{
                 else_t_loc,
                 fmt::format("Expected `{}` but found `{}`", expected, found),
                 error::Style::Primary
             }

            },
        };
    }
    class MisMatchedCallArgs {};

    static inline error::Diagnostic
    unknown_field(std::string field, const types::Ty &actual_type, location loc) {
        return error::Diagnostic{
            error::Level::Error,
            fmt::format("no field `{}` on type `{}`", field, actual_type),
            loc,
            std::vector{error::DiagnosticLabel{loc, "unkown field", error::Style::Primary}},
        };
    }

    static inline error::Diagnostic no_field_on_primitive(const types::Ty &prim, location loc) {
        return error::Diagnostic{
            error::Level::Error,
            fmt::format("`{}` is a primitive type and therefore doesn't have fields", prim),
            loc,
            std::vector{error::DiagnosticLabel{loc, "", error::Style::Primary}},
        };
    }
    class CallingUnCallable {};

    static inline error::Diagnostic un_assignable_expr(location loc) {
        return error::Diagnostic{
            error::Level::Error,
            "invalid left-hand side of assignment",
            loc,
            std::vector{error::DiagnosticLabel{
                loc, "cannot assign to this expression", error::Style::Primary
            }},
        };
    }

    static inline error::Diagnostic
    ident_not_found(const std::string &ident, location loc, std::string possible_help = "") {
        return error::Diagnostic{
            error::Level::Error,
            fmt::format("cannot find value `{}` in this scope", ident),
            loc,
            std::vector{error::DiagnosticLabel{
                loc,
                possible_help.empty() ? "not found in this scope"
                                      : fmt::format("help: {}", possible_help),
                error::Style::Primary
            }},
        };
    }
    class UnSupportedUnOp {};

    static inline error::Diagnostic continue_outside_loop(location loc) {
        return error::Diagnostic{
            error::Level::Error,
            "`continue` outside of a loop",
            loc,
            std::vector{error::DiagnosticLabel{
                loc, "cannot `continue` outside of a loop", error::Style::Primary
            }},
        };
    }
    static inline error::Diagnostic break_outside_loop(location loc) {
        return error::Diagnostic{
            error::Level::Error,
            "`break` outside of a loop",
            loc,
            std::vector{error::DiagnosticLabel{
                loc, "cannot `break` outside of a loop", error::Style::Primary
            }},
        };
    }

}}}} // namespace mr::middle::tast::errors
