#pragma once

#include "../expr/module.hpp"
#include "symbol_table.hpp"
#include "type.hpp"
#include "unification_table.hpp"
#include <algorithm>
#include <fmt/format.h>
#include <optional>
#include <set>
#include <type_traits>
#include <variant>
#include <vector>

namespace mr {
    namespace middle {
        namespace inference {
            using namespace types;
            class TyInferer {
                // maps for type vars, int vars and float vars
                UnificationTable<TypeVar, Ty>             _type_vars;
                UnificationTable<IntVar, IntVarValue>     _int_vars;
                UnificationTable<FloatVar, FloatVarValue> _float_vars;
                SymbolTable<Ty>                           _types;

              public:
                void push_scope() { _types.push_scope(); }
                void pop_scope() { _types.pop_scope(); }
                void clear_tables() {
                    _type_vars.clear();
                    _int_vars.clear();
                    _float_vars.clear();
                }

                void insert_type(std::string name, Ty ty) { _types.insert(name, ty); }
                Ty   look_up_type(std::string name) { return *_types.look_up(name); }

                std::string ty_to_string(const Ty& t) {
                    return std::visit(
                        overloaded{
                            [&](const InferTy& ti) {
                                std::ostringstream o;
                                std::visit(
                                    overloaded{
                                        [&](const TypeVar& ttv) {
                                            o << ty_of_type_var(ttv);
                                        },
                                        [&](const IntVar& tiv) {
                                            o << ty_of_int_var(tiv);
                                        },
                                        [&](const FloatVar& tfv) {
                                            o << ty_of_float_var(tfv);
                                        },
                                    },
                                    ti
                                );
                                return o.str();
                            },
                            [&](const auto& _) {
                                std::ostringstream o;
                                o << t;
                                return o.str();
                            },
                        },
                        t
                    );
                }

                Ty i8() const noexcept { return Ty{IntTy::i8}; }
                Ty i16() const noexcept { return Ty{IntTy::i16}; }
                Ty i32() const noexcept { return Ty{IntTy::i32}; }
                Ty i64() const noexcept { return Ty{IntTy::i64}; }
                Ty isize() const noexcept { return Ty{IntTy::isize}; }
                Ty u8() const noexcept { return Ty{UIntTy::u8}; }
                Ty u16() const noexcept { return Ty{UIntTy::u16}; }
                Ty u32() const noexcept { return Ty{UIntTy::u32}; }
                Ty u64() const noexcept { return Ty{UIntTy::u64}; }
                Ty f32() const noexcept { return Ty{FloatTy::F32}; }
                Ty f64() const noexcept { return Ty{FloatTy::F64}; }
                Ty usize() const noexcept { return Ty{UIntTy::usize}; }
                Ty bool_t() const noexcept { return Ty{BoolTy{}}; }
                Ty unit() const noexcept { return Ty{UnitTy{}}; }

                // it is possible that a type cannot be inferred so then we return
                // optional it is up to the caller to deal with this
                Ty resolve(const Ty ty) {
                    if (!has_variant<InferTy>(ty)) return ty;
                    const auto infer = std::get<InferTy>(ty);
                    return std::visit(
                        overloaded{
                            [&](const TypeVar& tv) {
                                const auto t = _type_vars.get(tv);
                                if (!t)
                                    throw std::runtime_error("TypeVariable does not exist"
                                    );
                                return std::visit(
                                    overloaded{
                                        [&](const UnknownTy& _) {
                                            throw std::runtime_error(
                                                "Cant resolve type variable"
                                            );
                                            return ty;
                                        },
                                        [&](const InferTy& _) { return resolve(*t); },
                                        [&](const auto& ty) { return Ty{ty}; }
                                    },
                                    *t
                                );
                            },
                            [&](const IntVar& tv) {
                                const auto ty = _int_vars.get(tv);
                                if (!ty)
                                    throw std::runtime_error("IntVar does not exist");
                                if (auto i = std::get_if<IntTy>(&*ty)) { return Ty{*i}; }
                                if (auto u = std::get_if<UIntTy>(&*ty)) { return Ty{*u}; }
                                // default of int is I32
                                _int_vars.assign(tv, IntVarValue{IntTy::i32});
                                return Ty{IntTy::i32};
                            },
                            [&](const FloatVar& tv) {
                                const auto ty = _float_vars.get(tv);
                                if (!ty)
                                    throw std::runtime_error("FloatVar does not exist");
                                if (auto ft = std::get_if<FloatTy>(&*ty)) {
                                    return Ty{*ft};
                                }
                                // default of float is f64
                                _float_vars.assign(tv, FloatVarValue{FloatTy::F64});
                                return Ty{FloatTy::F64};
                            },
                        },
                        infer
                    );
                }

                Ty shallow_resolve(const Ty ty) {
                    if (!has_variant<InferTy>(ty)) return ty;
                    const auto infer = std::get<InferTy>(ty);
                    return std::visit(
                        overloaded{
                            [&](const TypeVar& tv) {
                                const auto t = _type_vars.get(tv);
                                if (!t)
                                    throw std::runtime_error("TypeVariable does not exist"
                                    );
                                return std::visit(
                                    overloaded{
                                        [&](const InferTy& _) { return resolve(*t); },
                                        [&](const auto& _) { return ty; }
                                    },
                                    *t
                                );
                            },
                            [&](const IntVar& tv) {
                                const auto t = _int_vars.get(tv);
                                if (!t) throw std::runtime_error("IntVar does not exist");
                                if (auto i = std::get_if<IntTy>(&*t)) { return Ty{*i}; }
                                if (auto u = std::get_if<UIntTy>(&*t)) { return Ty{*u}; }
                                return ty;
                            },
                            [&](const FloatVar& tv) {
                                const auto t = _float_vars.get(tv);
                                if (!t)
                                    throw std::runtime_error("FloatVar does not exist");
                                if (auto ft = std::get_if<FloatTy>(&*t)) {
                                    return Ty{*ft};
                                }
                                return ty;
                            },
                        },
                        infer
                    );
                }

                Ty create_type_var() {
                    // when the type var changes for this id
                    // everything that uses this TypeVar will have been updated
                    // you know?
                    TypeVar var = _type_vars.new_var(Ty{UnknownTy{}});
                    return Ty{InferTy{var}};
                }

                Ty ty_of_type_var(TypeVar var) { return *_type_vars.get(var); }

                Ty create_int_var() {
                    auto var = _int_vars.new_var(IntVarValue{UnknownTy{}});
                    return Ty{InferTy{var}};
                }

                IntVarValue ty_of_int_var(IntVar var) { return *_int_vars.get(var); }

                Ty create_float_var() {
                    auto var = _float_vars.new_var(FloatVarValue{UnknownTy{}});
                    return Ty{InferTy{var}};
                }

                FloatVarValue ty_of_float_var(FloatVar var) {
                    return *_float_vars.get(var);
                }

                types::Ty from_ast_type(const ast::Type& ast_type) {
                    using a_pt = ast::primitive_type;
                    return std::visit(
                        overloaded{
                            [](const a_pt& pt) {
                                switch (pt) {
                                case a_pt::Unit:
                                    return Ty{UnitTy{}};
                                case a_pt::I8:
                                    return Ty{IntTy::i8};
                                case a_pt::I16:
                                    return Ty{IntTy::i16};
                                case a_pt::I32:
                                    return Ty{IntTy::i32};
                                case a_pt::I64:
                                    return Ty{IntTy::i64};
                                case a_pt::ISIZE:
                                    return Ty{IntTy::isize};
                                case a_pt::U8:
                                    return Ty{UIntTy::u8};
                                case a_pt::U16:
                                    return Ty{UIntTy::u16};
                                case a_pt::U32:
                                    return Ty{UIntTy::u32};
                                case a_pt::U64:
                                    return Ty{UIntTy::u64};
                                case a_pt::USIZE:
                                    return Ty{UIntTy::usize};
                                case a_pt::Char:
                                    throw std::runtime_error("Char type not supported");
                                case a_pt::Bool:
                                    return Ty{BoolTy{}};
                                default:
                                    TODO(
                                        std::string("UNSUPPORTED TYPE ") +
                                        primitive_type_to_string(pt)
                                    );
                                    return Ty{NeverTy{}};
                                }
                            },
                            [&](const std::string& s) -> Ty {
                                TODO("USER DEFINED TYPES NOT SUPPORTED");
                            },
                        },
                        ast_type
                    );
                }
                /**
                 * sets a type `t` to be equal to a type `u`, if this can't
                 * If eq can't happen, nothing is returned
                 */
                std::optional<Ty> eq(Ty t, Ty u) {
                    t = shallow_resolve(t);
                    u = shallow_resolve(u);
                    if (t == u) { return {t}; }
                    return std::visit(
                        overloaded{
                            [&](const InferTy& ti, const InferTy& ui) {
                                return std::visit(
                                    overloaded{
                                        [&](const TypeVar& ttv, const TypeVar& uv) {
                                            TODO("EQUATE TWO TYPE VARIABLES");
                                            return no_type();
                                        },
                                        [&](const TypeVar& ttv, const IntVar& uiv) {
                                            return eq_intvar_type_var(uiv, ttv);
                                        },
                                        [&](const IntVar& tiv, const TypeVar& utv) {
                                            return eq_intvar_type_var(tiv, utv);
                                        },
                                        [&](const FloatVar& tfv, const TypeVar& utv) {
                                            return eq_floatvar_type_var(tfv, utv);
                                        },
                                        [&](const TypeVar& tfv, const FloatVar& ufv) {
                                            return eq_floatvar_type_var(ufv, tfv);
                                        },
                                        [&](const IntVar& tiv, const IntVar& uiv) {
                                            eq_int_vars(tiv, uiv);
                                            return some(t);
                                        },
                                        [&](const FloatVar& tfv, const FloatVar& utf) {
                                            return eq_float_vars(tfv, utf);
                                        },
                                        [](const auto& _t, const auto& _u) {
                                            return no_type();
                                        }
                                    },
                                    ti,
                                    ui
                                );
                            },
                            [&](const InferTy& it, const IntTy& iu) {
                                if (auto intvar = std::get_if<IntVar>(&it)) {
                                    _int_vars.assign(*intvar, IntVarValue{iu});
                                    return some(u); // return the correct type
                                }
                                if (auto var = std::get_if<TypeVar>(&it)) {
                                    _type_vars.assign(*var, u);
                                    return some(u);
                                }
                                return no_type();
                            },
                            [&](const IntTy& it, const InferTy& iu) {
                                if (auto intvar = std::get_if<IntVar>(&iu)) {
                                    _int_vars.assign(*intvar, IntVarValue{it});
                                    return some(t); // return the correct type
                                }
                                if (auto var = std::get_if<TypeVar>(&iu)) {
                                    _type_vars.assign(*var, t);
                                    return some(t);
                                }
                                return no_type();
                            },
                            [&](const InferTy& it, const UIntTy& uiu) {
                                if (auto uintvar = std::get_if<IntVar>(&it)) {
                                    _int_vars.assign(*uintvar, IntVarValue{uiu});
                                    return some(u); // return the correct type
                                }
                                if (auto var = std::get_if<TypeVar>(&it)) {
                                    _type_vars.assign(*var, t);
                                    return some(u);
                                }
                                return no_type();
                            },
                            [&](const UIntTy& uit, const InferTy& itu) {
                                if (auto uintvar = std::get_if<IntVar>(&itu)) {
                                    _int_vars.assign(*uintvar, IntVarValue{uit});
                                    return some(t); // return the correct type
                                }
                                if (auto var = std::get_if<TypeVar>(&itu)) {
                                    _type_vars.assign(*var, t);
                                    return some(t);
                                }
                                return no_type();
                            },
                            [&](const InferTy& it, const FloatTy& fu) {
                                if (!it.is_float_var()) return no_type();
                                return eq_infer_and_ty(it, u);
                            },
                            [&](const InferTy& it, const BoolTy& _u) {
                                if (auto type_var = std::get_if<TypeVar>(&it)) {
                                    _type_vars.assign(*type_var, u);
                                    return some(u);
                                }
                                return no_type();
                            },
                            [&](const BoolTy& _t, const InferTy& ut) {
                                if (auto type_var = std::get_if<TypeVar>(&ut)) {
                                    _type_vars.assign(*type_var, t);
                                    return some(t);
                                }
                                return no_type();
                            },
                            [&](const InferTy& it, const auto& _u) {
                                if (!it.is_infer_var()) return no_type();
                                return some(u);
                            },
                            [&](const auto& _i, const InferTy& ut) {
                                if (!ut.is_infer_var()) return no_type();
                                return some(u);
                            },
                            [&](const auto& _t, const auto& _u) { return no_type(); }
                        },
                        t,
                        u
                    );
                }

                std::optional<Ty> eq_infer_and_ty(const InferTy& it, const Ty& u) {
                    TODO("Cant infer from InferTy and auto _u");
                }

                std::optional<Ty> eq_float_vars(const FloatVar& tf, const FloatVar& uf) {
                    TODO("EQ FLOAT VARS NOT SUPPORTED");
                }
                std::optional<Ty> eq_int_vars(const IntVar& ti, const IntVar& ui) {
                    // an example of why we need to do this (same applies to floats)
                    // valid rust (but not valid in types):
                    /*
                        let x = 10; // 1: {integer}
                        let y = 20; // 2: {integer}
                        // this says that 1 and 2 must be equal to eachother
                        let cond = x == y;

                        // here `x` is inferred to be usize, so y also must be a usize
                        let z: usize = x;
                        let u: isize = y; // `y` is inferred to be usize
                       but we want isize **error**
                    */
                    // i don't know how to do this yet so im going of intuition
                    // like we cant just let `y` point to `x` in the _int_vars
                    // because switch the let statements of `z` and `u`, `x` won't know
                    // so we unionize these 2
                    _int_vars.unionize(ti, ui);
                }

                std::optional<Ty> eq_intvar_type_var(const IntVar& iv, const TypeVar tv) {
                    _type_vars.assign(tv, Ty{InferTy{iv}});
                    return Ty{InferTy{iv}};
                }

                std::optional<Ty>
                eq_floatvar_type_var(const FloatVar& iv, const TypeVar tv) {
                    TODO("EQ FLOAT VAR WITH TYPE VAR NOT SUPPORTED YET");
                }

                // returns NULL if error occured
                // error will be included later on
                const FunctionType* create_function_type(const ast::FunDecl& decl) {
                    std::vector<Ty> arg_types{};
                    arg_types.reserve(decl.args().size());
                    // just "insert" middle types into above vector with
                    // transform
                    std::unordered_map<std::string, int> seen_args; // for names
                    std::transform(
                        decl.args().cbegin(),
                        decl.args().cend(),
                        std::back_inserter(arg_types),
                        [&](const ast::FunArg& arg) {
                            seen_args[arg.id] += 1;
                            return from_ast_type(arg.type);
                        }
                    );
                    // we can iterate over this map and collect every arg
                    // but we don't care about that right now.
                    if (const auto val = std::find_if(
                            seen_args.cbegin(),
                            seen_args.cend(),
                            [](const auto& v) { return v.second > 1; }
                        );
                        val != seen_args.cend()) {
                        spdlog::critical(
                            "Argument `{}` in function `{}`, is declared more than once",
                            val->first,
                            decl.name()
                        );
                        TODO("COLLECT `ARGUMENT DECLARED MORE THAN ONCE` ERROR");
                    }

                    Ty ret_ty = from_ast_type(decl.return_type());

                    const auto ty = new FunctionType{
                        std::string(decl.name()), std::move(arg_types), std::move(ret_ty)
                    };
                    _types.insert(decl.name(), Ty{ty});
                    return ty;
                }
                bool is_integer_type(const Ty& ty) {
                    return std::visit(
                        overloaded{
                            [](const NeverTy& t) { return true; }, // can be
                            [&](const InferTy& t) {
                                return std::visit(
                                    overloaded{
                                        [](const IntVar& t) { return true; },
                                        [](const FloatVar& t) { return false; },
                                        [&](const TypeVar& t) {
                                            return is_integer_type(ty_of_type_var(t));
                                        }
                                    },
                                    t
                                );
                            },
                            [](const IntTy& t) { return true; },
                            [](const UIntTy& t) { return true; },
                            [](const auto& t) { return false; }
                        },
                        ty
                    );
                }

                static inline std::optional<Ty> no_type() { return none<Ty>(); }
            };
        } // namespace inference

    } // namespace middle

} // namespace mr
