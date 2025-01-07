#pragma once

#include "style.hpp"
#include <vector>

namespace mr { namespace error {

    struct StyledChar {

        char c;
        Style style;
    };
    const static inline StyledChar SPACE = StyledChar{' ', Style::NoStyle};

    struct StyledString {
        std::string s;
        Style style;
    };
    // used for creating a diagnostic window to show to the user
    class DiagnosticWindow {
        std::vector<std::vector<StyledChar>> buffer{};

        void extra_lines(size_t lines) {
            if (lines >= buffer.size()) {
                buffer.resize(lines);
            }
        }

      public:
        // collect lines into strings where each char has the same style
        std::vector<std::vector<StyledString>> render() const {
            std::vector<std::vector<StyledString>> rendered{};
            std::vector<StyledString> rendered_line;
            rendered.reserve(buffer.size());
            for (const auto &line : buffer) {
                auto curr_style = Style::NoStyle;
                std::string curr_str{};
                for (const auto c : line) {
                    if (c.style != curr_style) {
                        if (!curr_str.empty())
                            rendered_line.push_back(StyledString{std::move(curr_str), curr_style});
                        curr_style = c.style;
                        curr_str = std::string();
                    }
                    curr_str.push_back(c.c);
                }
                if (!curr_str.empty())
                    rendered_line.push_back(StyledString{std::move(curr_str), curr_style});
                rendered.push_back(std::move(rendered_line));
                rendered_line = std::vector<StyledString>();
            }
            return rendered;
        }
        void set_char(size_t line, size_t col, char c, Style style) {
            extra_lines(line);
            if (col >= buffer[line].size()) {
                buffer[line].resize(col + 1, SPACE);
            }
            buffer[line][col] = StyledChar{c, style};
        }

        void set_line(size_t line, size_t col, const std::string &s, Style style) {
            for (const auto c : s) {
                set_char(line, col, c, style);
                col += 1;
            }
        }

        void append_line(size_t line, const std::string &s, Style style) {
            if (line >= buffer.size()) {
                set_line(line, 0, s, style);
            } else {
                const auto col = buffer[line].size();
                set_line(line, col, s, style);
            }
        }
    };
}} // namespace mr::error
