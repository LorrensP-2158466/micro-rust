#pragma once

#include "consts/scalar.hpp"
#include "middle/ir/local.hpp"
#include "types/type.hpp"
#include <optional>
#include <variant>

namespace mr {
    namespace middle_interpreter {
        using namespace middle;

        struct Value : std::variant<Scalar> {
            types::Ty type;
            Value(Scalar s, types::Ty t) : std::variant<Scalar>(s), type(std::move(t)) {}
            Value(const ir::Local& l)
                : std::variant<Scalar>(Scalar{0, l.ty.size()}), type(l.ty) {}

            static inline Value from_bool(bool b) {
                return {
                    Scalar{b, 1},
                    types::Ty{types::BoolTy{}}
                };
            }

            // for output of the program
            std::string as_program_str() const {
                const auto self = std::get<Scalar>(*this);
                return std::visit(
                    overloaded{
                        [&](const types::BoolTy& t) {
                            return std::string(bool_to_str(self.to_bool()));
                        },
                        [&](const types::IntTy& t) {
                            return fmt::format("{}", self.to_isize());
                        },
                        [&](const types::UIntTy& t) {
                            return fmt::format("{}", self.to_usize());
                        },
                        [&](const types::UnitTy& t) { return std::string("()"); },
                        [&](const types::FloatTy& t) {
                            switch (t) {
                            case types::FloatTy::F32:
                                return fmt::format("{}", self.to_f32());
                            case types::FloatTy::F64:
                                return fmt::format("{}", self.to_f64());
                            }
                        },
                        [](const auto& _cantbe) {
                            throw std::runtime_error(
                                "This cant be, formatting these types is prohibbted"
                            );
                            return std::string();
                        }
                    },
                    type
                );
            }

            friend std::ostream& operator<<(std::ostream& o, const Value& v) {
                o << v.as_program_str();
                return o;
            }

            constexpr inline Scalar scalar() const { return std::get<Scalar>(*this); }
        };
    } // namespace middle_interpreter
} // namespace mr
