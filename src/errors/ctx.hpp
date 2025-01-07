#pragma once

#include "diagnostic.hpp"
#include <mr_util.hpp>
#include <vector>

namespace mr { namespace error {

    class ErrorCtx {
        std::vector<Diagnostic> _diags;

      public:
        // emit an error
        void report_diag(Diagnostic diag) { _diags.emplace_back(std::move(diag)); }

        // show errors to user

        inline bool has_errors() const noexcept { return !_diags.empty(); }

        void show_errors(const char *file_name, const std::vector<std::string> &source_in_lines) const {
            for (const auto &diag : _diags)
                diag.emit_to_user(file_name, source_in_lines);
        }

        inline size_t error_amount() const noexcept { return _diags.size(); }
    };

}} // namespace mr::error
