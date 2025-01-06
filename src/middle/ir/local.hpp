#pragma once

#include "types/type.hpp"
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <iostream>
#include <string>

namespace mr {
    namespace middle {
        namespace ir {
            enum class MutabilityType {
                Mutable,
                Immutable,
            };

            using Mutability = Locusable<MutabilityType>;

            static inline std::ostream &operator<<(std::ostream &o, const MutabilityType m) {
                if (m == MutabilityType::Mutable)
                    o << "mut";
                return o;
            }
            struct Local {
                std::string id; // error reporting

                // for later when references are introduced, we have to remember the type
                types::Ty ty;

                MutabilityType mutablity; // used for borrow check, can't take mutable
                                          // reference to non mutable

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
        } // namespace ir

    } // namespace middle

} // namespace mr

OSTREAM_FORMATTER(mr::middle::ir::Local)
OSTREAM_FORMATTER(mr::middle::ir::MutabilityType)