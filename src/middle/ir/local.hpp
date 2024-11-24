#pragma once

#include "../type.hpp"
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <iostream>
#include <string>

namespace mr {
    namespace middle {
        namespace ir {
            enum class Mutability {
                Mutable,
                Immutable,
            };
            std::ostream& operator<<(std::ostream& o, const Mutability m) {
                switch (m) {
                case Mutability::Mutable:
                    o << "mut";
                    break;
                default: {
                }
                }
                return o;
            }
            struct Local {
                std::string id; // error reporting

                // for later when references are introduced, we have to remember the type
                types::Ty ty;

                Mutability mutablity; // used for borrow check, can't take mutable
                                      // reference to non mutable

                friend std::ostream& operator<<(std::ostream& o, const Local& l) {
                    if (l.mutablity == Mutability::Mutable)
                        o << fmt::format("mut {}:{}", l.id, l.ty);
                    else o << fmt::format("{}: {}", l.id, l.ty);
                    return o;
                }
            };

            struct LocalId {
                size_t id;

                friend std::ostream& operator<<(std::ostream& o, const LocalId id) {
                    o << '_' << id.id;
                    return o;
                }
            };
            const LocalId RETURN_LOCAL = LocalId{0};
        } // namespace ir

    } // namespace middle

} // namespace mr

OSTREAM_FORMATTER(mr::middle::ir::Local)
OSTREAM_FORMATTER(mr::middle::ir::Mutability)