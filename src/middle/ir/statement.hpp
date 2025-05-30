#pragma once

#include "local.hpp"
#include "location.hh"
#include "values.hpp"
#include <utility>
#include <variant>
#include <vector>

namespace mr { namespace middle { namespace ir {
    // because we dont check any thing and because i like std::variant
    // we will be using std::variant
    // lets see if this is possible

    // simple assignment of an rvalue
    // x = 10
    // ...
    struct Assign {
        Place place;
        RValue value;
    };

    // formatted print line
    struct FPrintLn {
        // say we have a format string like this:
        // "Hello {name}, How are you {day}?"
        // this will be encoded in this structure like this:
        // start: None
        // format_structure: [
        //  ("Hello ", Operand(name)),
        //  (", How are you ", Operand(day))
        // ]
        // end: "?"

        // it is possible to direclty start with a format
        // println!("{var} == {var}")
        std::optional<Operand> start;
        // explained above
        std::vector<std::pair<std::string, Operand>> _format_structure;
        // the last string, optional as well
        std::optional<std::string> end;
    };

    // no formatting, just a plain string to print
    struct SPrintLn {
        std::string _string;
    };

    struct Dead {
        LocalId local;
    };

    using statement_variant_t = std::variant<Assign, Dead, FPrintLn, SPrintLn>;
    struct Statement : statement_variant_t {
        location loc;
        Statement(Dead d)
            : statement_variant_t(d)
            , loc(location()) {} // don't care about location of this
        Statement(Assign as, location l)
            : statement_variant_t(as)
            , loc(l) {}
        Statement(FPrintLn format, location l)
            : statement_variant_t(std::move(format))
            , loc(l) {}
        Statement(SPrintLn print, location l)
            : statement_variant_t(std::move(print))
            , loc(l) {}

        friend std::ostream &operator<<(std::ostream &o, const Statement &s) {
            std::visit(
                overloaded{
                    [&](const Assign &as) {
                        o << '_' << as.place.local.id() << " = " << as.value << std::endl;
                    },
                    [&](const FPrintLn &fmt) {
                        o << "PRINT(\"";
                        if (fmt.start) {
                            o << '{' << *fmt.start << '}';
                        }
                        for (const auto &[str, var] : fmt._format_structure) {
                            o << str << '{' << var << '}';
                        }
                        if (fmt.end)
                            o << *fmt.end;
                        o << "\")" << std::endl;
                    },
                    [&](const SPrintLn &print) {
                        o << "PRINT(\"" << print._string << "\")" << std::endl;
                    },
                    [&](const Dead d) { o << fmt::format("LocalDead(_{})\n", d.local.id()); },
                    [&](const auto &) { o << "UNKNOWN STATEMENT" << std::endl; }
                },
                s
            );
            return o;
        }
    };
}}} // namespace mr::middle::ir