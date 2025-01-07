#pragma once

#include "type.hpp"
#include <string>

namespace mr { namespace middle { namespace types {
    static inline std::string default_value_for_ty(const Ty &ty) { return " = ?"; }

}}} // namespace mr::middle::types