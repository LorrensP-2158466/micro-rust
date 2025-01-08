#pragma once

#include "diagnostic_window.hpp"
#include "location.hh"
#include "style.hpp"
#include <fmt/color.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

namespace mr { namespace error {

    enum class Level {
        Lint,    // don't have these but why not include it
        Warning, // don't have those but why not include it
        Error
    };

    struct DiagnosticLabel {
        location loc;
        std::string message;
        Style style;
    };

    struct Suggestion {
        std::string message;
    };

    struct Diagnostic {
        Level level;
        std::string message;
        location source_loc;
        std::vector<DiagnosticLabel> info_labels;
        std::optional<Suggestion> code_suggestion = std::nullopt;

        void
        emit_to_user(const char *file_name, const std::vector<std::string> &source_in_lines) const {
            // DiagnosticWindow window{};
            const int line_width = std::to_string(source_loc.begin.line).length();

            // window.set_line(0, 0, "error", Style::Error);
            // window.append_line(0, ": ", Style::NoStyle);
            // window.append_line(0, message, Style::NoStyle);
            fmt::println(
                "{}: {}",
                fmt::styled("error", fmt::fg(fmt::color::red) | fmt::emphasis::bold),
                fmt::styled(message, fmt::emphasis::bold)
            );

            // window.set_line(
            //     1,
            //     0,
            //     fmt::format(
            //         " --> {}:{}:{}",

            //         file_name,
            //         source_loc.begin.line,
            //         source_loc.begin.column
            //     ),
            //     Style::NoStyle
            // );
            fmt::println(
                " {} {}:{}:{}",
                fmt::styled("-->", fmt::fg(fmt::color::sky_blue)),
                file_name,
                source_loc.begin.line,
                source_loc.begin.column
            );

            print_border(0, line_width);
            fmt::println("");
            auto prev_line = 1;
            bool first_info = true;

            for (const auto &[loc, label, style] : info_labels) {
                const auto curr_line = loc.begin.line;
                const auto prev_line_diff = loc.begin.line - prev_line;
                if (!first_info && prev_line_diff >= 3) {
                    fmt::print(fmt::fg(fmt::color::sky_blue), "...\n");
                } else if (prev_line_diff == 2) {
                    // rust prints the line between 2 lines ass well
                    print_border(curr_line, line_width);
                    fmt::println(" {}", source_in_lines[curr_line - 2]);
                }
                first_info = false;
                print_border(curr_line, line_width);
                fmt::println(" {}", source_in_lines[curr_line - 1]);
                print_diagnostic_label(loc, label, style, line_width);
                prev_line = curr_line;
            }
            print_border(0, line_width);
            print_suggestions();
            fmt::println("");
        }

        void print_diagnostic_label(
            location loc, const std::string &label, Style style, size_t line_width
        ) const {
            const auto offset = loc.begin.column;
            const auto length = loc.end.column - loc.begin.column;
            fmt::text_style print_style{};
            char indicator = '^';
            switch (style) {
            case Style::Secondary: {
                print_style = fmt::fg(fmt::color::sky_blue);
                indicator = '-';
            } break;
            case Style::Primary: {
                print_style = fmt::fg(fmt::color::red);
            } break;
            case Style::NoStyle: {
                if (label.empty()) {
                    return;
                };
            } break;
            default:
                break;
            }
            print_border(0, line_width);
            fmt::print(
                print_style | fmt::emphasis::bold,
                "{:<{}}{} {}\n",
                ' ',
                offset,
                std::string(length, indicator),
                label
            );
        }

        void print_suggestions() const {
            if (code_suggestion)
                fmt::println(
                    "\n{}: {}\n",
                    fmt::styled("help", fmt::fg(fmt::color::yellow_green)),
                    code_suggestion->message
                );
        }

        void print_border(size_t line_nr, size_t line_width) const {
            if (line_nr)
                fmt::print(
                    fg(fmt::color::sky_blue) | fmt::emphasis::bold, "{:>{}} |", line_nr, line_width
                );
            else
                fmt::print(
                    fg(fmt::color::sky_blue) | fmt::emphasis::bold, "{:>{}} |", "", line_width
                );
        }
    };
}} // namespace mr::error
