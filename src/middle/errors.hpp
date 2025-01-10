#pragma once

#include "errors/diagnostic.hpp"

namespace mr { namespace middle { namespace errors {

    static inline error::Diagnostic
    multiple_decls(location first_decl, location loc, const std::string &decl_name) {
        return error::Diagnostic{
            error::Level::Error,
            fmt::format("the name `{}` is defined multiple times", decl_name),
            loc,
            std::vector{
                error::DiagnosticLabel{
                    first_decl,
                    fmt::format("previous declaration of the value `{}` here", decl_name),
                    error::Style::Secondary
                },
                error::DiagnosticLabel{
                    loc, fmt::format("`{}` redefined here", decl_name), error::Style::Primary
                },
            }
        };
    }
}}} // namespace mr::middle::errors