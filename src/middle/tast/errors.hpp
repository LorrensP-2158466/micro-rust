#pragma once

#include "errors/diagnostic.hpp"
#include "location.hh"
#include "types/type.hpp"
#include <fmt/format.h>

namespace mr { namespace middle { namespace errors {

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
    static inline error::Diagnostic called_uncallable(const types::Ty &found, location loc) {
        return error::Diagnostic{
            error::Level::Error,
            fmt::format("Expected function, found `{}`", found),
            loc,
            std::vector{error::DiagnosticLabel{
                loc, "Call expression required function", error::Style::Primary
            }},
        };
    }

    // expects the location of the function so we can primary it
    // than it expects the following list
    // [ found, expected, location of expr, argument number]
    static inline error::Diagnostic mis_matched_call_args(
        location fn_loc,
        std::vector<std::tuple<const types::Ty &, const types::Ty &, location, size_t>> mismatched
    ) {
        std::vector labels{error::DiagnosticLabel{fn_loc, "", error::Style::Primary}};
        labels.reserve(1 + mismatched.size());
        for (auto &&[found, expect, loc, pos] : std::move(mismatched)) {
            labels.emplace_back(
                loc,
                fmt::format("argument #{} expected `{}`, but got `{}` ", pos, expect, found),
                error::Style::Secondary
            );
        }

        return error::Diagnostic{
            error::Level::Error,
            "arguments to this function are incorrect",
            fn_loc,
            std::move(labels)
        };
    }

    // missing: [ expected_ty, arg_pos]
    static inline error::Diagnostic missing_args(
        location fn_loc, size_t found, size_t expected,
        std::vector<std::tuple<const types::Ty &, size_t>> missing
    ) {
        std::vector labels{error::DiagnosticLabel{fn_loc, "", error::Style::Primary}};
        labels.reserve(1 + missing.size());
        for (auto &&[expect, pos] : missing) {
            labels.emplace_back(
                fn_loc,
                fmt::format("missing argument #{} of `{}`", pos, expect, found),
                error::Style::Secondary
            );
        }

        return error::Diagnostic{
            error::Level::Error,
            fmt::format(
                "this function takes {} arguments but {} argument was supplied", expected, found
            ),
            fn_loc,
            std::move(labels)
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

}}} // namespace mr::middle::errors
