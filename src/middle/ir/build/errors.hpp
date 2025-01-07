
#include "errors/diagnostic.hpp"

namespace mr { namespace middle { namespace build { namespace errors {

    static inline error::Diagnostic unknown_type(location init_loc) {
        return error::Diagnostic{
            error::Level::Error,
            "type annotations needed",
            init_loc,
            std::vector{error::DiagnosticLabel{init_loc, ": TYPE", error::Style::Error}}
        };
    }
}}}} // namespace mr::middle::build::errors