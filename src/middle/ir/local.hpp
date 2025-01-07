#pragma once

#include "types/type.hpp"
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <iostream>
#include <string>

namespace mr { namespace middle { namespace ir {
    enum class MutabilityType {
        Mutable,
        Immutable,
    };

    using Mutability = Locusable<MutabilityType>;
    // Temorary or User Defined?
    enum class LocalType { UserDef, Temp };

    static inline std::ostream &operator<<(std::ostream &o, const MutabilityType m) {
        if (m == MutabilityType::Mutable)
            o << "mut";
        return o;
    }
    struct Local {
        std::string id; // error reporting
        // for later when references are introduced, we have to remember the type
        types::Ty ty;
        MutabilityType mutablity;
        LocalType local_type;
        location loc;

        inline bool is_mutable() const noexcept { return mutablity == MutabilityType::Mutable; }
        friend std::ostream &operator<<(std::ostream &o, const Local &l) {
            if (l.mutablity == MutabilityType::Mutable)
                o << fmt::format("mut {}:{}", l.id, l.ty);
            else
                o << fmt::format("{}: {}", l.id, l.ty);
            return o;
        }
    };

    struct LocalId {
        size_t idx;
        INDEX_TYPE(LocalId, idx)
    };
    const LocalId RETURN_LOCAL = LocalId{0};
}}} // namespace mr::middle::ir

OSTREAM_FORMATTER(mr::middle::ir::Local)
OSTREAM_FORMATTER(mr::middle::ir::MutabilityType)