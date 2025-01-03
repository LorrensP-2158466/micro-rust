#pragma once

#include "location.hh"
#include <fmt/format.h>
#include <string>
#include <vector>

namespace mr {
    namespace error {
        // every Error class should be able to create a Diagnostic, this is the same sort
        // of stuff rustc does but they do it much better. I just do it because i like the
        // architecture and the maintainablity

        enum class Level {
            Lint,    // don't have these but why not include it
            Warning, // don't have those but why not include it
            Error
        };
        struct Diagnostic {
            Level                                         level;
            std::string                                   message;
            location                                      source_loc;
            std::vector<std::pair<location, std::string>> info_labels;

            void emit_to_user(const std::vector<std::string>& source_in_lines) const {
                const int line_width = std::to_string(source_loc.begin.line).length();

                fmt::println(
                    "ERROR: {} at {}:{}",
                    message,
                    source_loc.begin.line,
                    source_loc.begin.column
                );

                fmt::println("{:>{}}", "|", line_width + 3);
                fmt::println(
                    "{:>{}}  | {}",
                    source_loc.begin.line,
                    line_width,
                    source_in_lines[source_loc.begin.line - 1]
                );

                for (const auto& [loc, label] : info_labels) {
                    const auto offset = loc.begin.column;
                    const auto length = loc.end.column - loc.begin.column;
                    fmt::println(
                        "{:>{}}{:<{}}{:<{}} {}",
                        "|",
                        line_width + 3,
                        ' ',
                        offset,
                        '^',
                        length,
                        label
                    );
                }
            }
        };
    } // namespace error

} // namespace mr
