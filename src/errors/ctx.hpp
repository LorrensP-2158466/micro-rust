#pragma once

#include "error.hpp"
#include <mr_util.hpp>
#include <vector>
namespace mr {
    namespace error {

        class ErrorCtx {
            std::vector<U<Error>> _errors;

          public:
            // emit an error
            void emit_error(U<Error> err) { _errors.push_back(err); }

            // show errors to user
            void show_errors() const {}
        };

    } // namespace error

} // namespace mr
