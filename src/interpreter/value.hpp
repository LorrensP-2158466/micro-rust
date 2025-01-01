#pragma once

#include "consts/scalar.hpp"
#include "middle/ir/local.hpp"
#include "types/type.hpp"
#include <optional>
#include <variant>

namespace mr {
    namespace middle_interpreter {
        struct Value;
        using namespace middle;

        struct Aggregate {
            std::vector<Value> vals;
        };

        using value_variant_t = std::variant<Scalar, Aggregate>;
        struct Value : value_variant_t {
            types::Ty type;
            Value(Scalar s, types::Ty t) : value_variant_t(s), type(std::move(t)) {}
            Value(Aggregate a, types::Ty t)
                : value_variant_t(std::move(a)), type(std::move(t)) {}

            static inline Value from_bool(bool b) {
                return {
                    Scalar{b, 1},
                    types::Ty{types::BoolTy{}}
                };
            }

            // crashes on non aggregate
            Value& project(const ir::Projection& proj) {
                auto& aggr = std::get<Aggregate>(*this);
                return std::visit(
                    overloaded{[&](ir::Field f) -> Value& { return aggr.vals[f.field]; }},
                    proj
                );
            }
            // crashes on non aggregate
            const Value& project(const ir::Projection& proj) const {
                const auto& aggr = std::get<Aggregate>(*this);
                return std::visit(
                    overloaded{[&](ir::Field f) -> const Value& {
                        return aggr.vals[f.field];
                    }},
                    proj
                );
            }

            // for output of the program
            std::string as_program_str() const {
                return std::visit(
                    overloaded{
                        [&](const Scalar self, const types::BoolTy&) {
                            return std::string(bool_to_str(self.to_bool()));
                        },
                        [&](const Scalar self, const types::IntTy&) {
                            return fmt::format("{}", self.to_isize());
                        },
                        [&](const Scalar self, const types::UIntTy&) {
                            return fmt::format("{}", self.to_usize());
                        },
                        [&](const Scalar self, const types::UnitTy&) {
                            return std::string("()");
                        },
                        [&](const Scalar self, const types::FloatTy& t) {
                            switch (t) {
                            case types::FloatTy::F32:
                                return fmt::format("{}", self.to_f32());
                            case types::FloatTy::F64:
                                return fmt::format("{}", self.to_f64());
                            }
                        },
                        [&](const Aggregate& self, const types::TupleTy&) {
                            std::string output = "(";
                            for (size_t i = 0; i < self.vals.size(); ++i) {
                                output += self.vals[i].as_program_str();
                                if (i < self.vals.size() - 1) { output += ", "; }
                            }
                            output += ")";
                            return output;
                        },
                        [](const auto&, const auto&) {
                            throw std::runtime_error("This cant be, formatting these "
                                                     "types and values is prohibbted");
                            return std::string();
                        }
                    },
                    *this,
                    type
                );
            } // namespace middle_interpreter

            friend std::ostream& operator<<(std::ostream& o, const Value& v) {
                o << v.as_program_str();
                return o;
            }

            constexpr inline Scalar scalar() const { return std::get<Scalar>(*this); }
        }; // namespace mr
    } // namespace middle_interpreter
} // namespace mr
