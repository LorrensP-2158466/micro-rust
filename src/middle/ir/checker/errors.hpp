#include "errors/diagnostic.hpp"
#include "location.hh"
#include "middle/types/errors.hpp"
#include "mr_util.hpp"
#include <fmt/format.h>

namespace mr { namespace middle { namespace ir { namespace checker { namespace errors {
    using namespace error;
    static inline Diagnostic uninitialized_use(
        location decl_loc, location use_loc, const std::string &name, const types::Ty &ty
    ) {
        return Diagnostic{
            Level::Error,
            fmt::format("used variable `{}` isn't initialized", name),
            use_loc,
            std::vector{
                DiagnosticLabel{
                    decl_loc, "variable declared here but left uninitialized", Style::Secondary
                },
                DiagnosticLabel{
                    use_loc,
                    fmt::format("`{}` used here but it isn't initialized", name),
                    Style::Primary
                }
            },
            Suggestion{
                fmt::format("consider assigning a value: `{}`", types::default_value_for_ty(ty))
            }
        };
    }

    static inline Diagnostic assign_immutable(
        std::optional<location> first_ass_loc, location use_loc, const std::string &name,
        const types::Ty &ty
    ) {
        std::vector<DiagnosticLabel> labels{};
        if (first_ass_loc) {
            labels.emplace_back(
                *first_ass_loc, fmt::format("first assignment to `{}`", name), Style::Secondary
            );
        }
        labels.emplace_back(
            use_loc, fmt::format("cannot assign twice to immutable variable", name), Style::Primary
        );

        return Diagnostic{
            Level::Error,
            fmt::format("cannot assign twice to immutable variable `{}`", name),
            use_loc,
            std::move(labels),
            Suggestion{fmt::format("consider making this variable `mut`")}
        };
    }

}}}}} // namespace mr::middle::ir::checker::error