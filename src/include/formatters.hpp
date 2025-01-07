#pragma once

#include "location.hh"
#include <fmt/format.h>

// Formatter specialization for position class
template <> struct fmt::formatter<mr::position> {
    // Parse format specification
    constexpr auto parse(format_parse_context &ctx) {
        // Return iterator past the end of the parsed range
        return ctx.begin();
    }

    // Format the position
    template <typename FormatContext>
    auto format(const mr::position &pos, FormatContext &ctx) const {
        if (pos.filename) {
            return fmt::format_to(ctx.out(), "{}:{}:{}", *pos.filename, pos.line, pos.column);
        }
        return fmt::format_to(ctx.out(), "{}:{}", pos.line, pos.column);
    }
};

// Formatter specialization for location class
template <> struct fmt::formatter<mr::location> {
    // Parse format specification
    constexpr auto parse(format_parse_context &ctx) {
        // Return iterator past the end of the parsed range
        return ctx.begin();
    }

    // Format the location
    template <typename FormatContext>
    auto format(const mr::location &loc, FormatContext &ctx) const {
        if (loc.begin.filename) {
            // If begin and end are in same file
            if (loc.end.filename && *loc.begin.filename == *loc.end.filename) {
                // If begin and end are on same line
                if (loc.begin.line == loc.end.line) {
                    return fmt::format_to(
                        ctx.out(),
                        "{}:{}:{}-{}",
                        *loc.begin.filename,
                        loc.begin.line,
                        loc.begin.column,
                        loc.end.column
                    );
                }
                // Different lines
                return fmt::format_to(
                    ctx.out(),
                    "{}:{}:{}-{}:{}",
                    *loc.begin.filename,
                    loc.begin.line,
                    loc.begin.column,
                    loc.end.line,
                    loc.end.column
                );
            }
        }

        // If no filename or different files, format as two positions
        return fmt::format_to(ctx.out(), "{}-{}", loc.begin, loc.end);
    }
};