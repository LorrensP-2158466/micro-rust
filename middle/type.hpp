#pragma once

#include "../ast/module.hpp"
#include "mr_util.hpp"
#include <assert.h>
#include <string>
#include <variant>
#include <vector>
#include <sstream>
#include <utility>
#include <type_traits>

#define STANDARD_TYPE_VARIANT(name)                                            \
    struct name {                                                              \
        friend bool operator==(const name& _l, const name& _r) {               \
            return true;                                                       \
        }                                                                      \
    };

#define TYPE_VARIABLE(name)\
struct name {\
    size_t      _id;\
    name(size_t i) : _id(i){};\
    inline size_t id() const { return _id;}\
    friend bool operator==(const name& l, const name& r) {\
        return l._id == r._id;\
    }\
};

namespace mr {
    namespace middle {
        namespace types {
            using namespace std::literals;
            // first forward-declare the types than create the variant type

            // a defined type like:
            // i32, bool
            // fn(i32) -> i32 !! with (mangled?) name because in rust no 2
            // functions are the same (function pointers are!) struct Foo{x:
            // i32} a type is anything with a name or something:

            // i32, i64, u32, ...
            // seperate because this makes it easier for checking operations
            ENUM_DEFINE(IntTy, I8, I16, I32, I64, ISIZE)
            ENUM_DEFINE(UIntTy, U8, U16, U32, U64, USIZE)
            ENUM_DEFINE(FloatTy, F32, F64)

            // we don't know, used with type variables
            STANDARD_TYPE_VARIANT(UnknownTy);

            // the '!' type, basically something that doesn't exist but has a represenation
            // easiest to explain is this:
            /*
             Say we have an if else initializer:
                let a = if some_condition { 10 } else {return 20;};
            The type of the `then` block will be an integer, so the `else` block needs to also match
            that type, but because of the return statement, there is not value of that block, so the type is
            `never` since it will never be executed.
            The nice thing about `never` is that it can be coerced into every type
            so when the 2 conditional blocks have to have an equal type, `never` can work here, since we can coerce it
            into the integer type, yayy
             */
            STANDARD_TYPE_VARIANT(NeverTy);
            STANDARD_TYPE_VARIANT(BoolTy);

            // type variables with id into inferer storage
            TYPE_VARIABLE(TypeVar);
            TYPE_VARIABLE(IntVar);
            TYPE_VARIABLE(FloatVar);
            
            struct IntVarValue : public std::variant<UnknownTy, IntTy, UIntTy> {
                friend std::ostream& operator<<(std::ostream&o, const IntVarValue& t){
                    o << std::visit(overloaded{
                        [](const UnknownTy& t) { return "{integer}";},
                        [](const IntTy& t) {return IntTy_to_string(t);},
                        [](const UIntTy& t){ return UIntTy_to_string(t);}
                    }, t);
                    return o;
                }
            };
            struct FloatVarValue : public std::variant<UnknownTy, FloatTy> {
                friend std::ostream& operator<<(std::ostream&o, const FloatVarValue& t){
                    o << std::visit(overloaded{
                        [](const UnknownTy& t) { return "{float}";},
                        [](const FloatTy& t) {return FloatTy_to_string(t);},
                    }, t);
                    return o;
                }
            };

            struct InferTy : public std::variant<TypeVar, IntVar, FloatVar> {
                inline const char* const infer_ty_to_string() const {
                    // yeah this is weird
                    switch (this->index()) {
                    case 0:
                        return "{unknown}"; 
                    case 1:
                        return "{integer}";
                    case 2:
                        return "{float}";
                    default:
                        mr::unreachable<const char*>();
                    }
                }

                bool is_int_var() const{
                    return std::holds_alternative<IntVar>(*this);
                }

                bool is_float_var() const{
                    return std::holds_alternative<FloatVar>(*this);
                }

                bool is_infer_var() const{
                    return std::holds_alternative<TypeVar>(*this);
                }
                friend std::ostream& operator<<(std::ostream& o,
                                                const InferTy ft) {
                    o << ft.infer_ty_to_string();
                    return o;
                }
            };
            STANDARD_TYPE_VARIANT(UnitTy);

            struct FunctionType;
            std::string function_type_to_string(const FunctionType* ft);

            using type_variant_t =
                std::variant<UnknownTy, NeverTy, InferTy, BoolTy, IntTy, UIntTy, UnitTy, FloatTy, const FunctionType*>;
            struct Ty : public type_variant_t {

                bool is_known() const noexcept {
                    return ! std::holds_alternative<InferTy>(*this);
                }

                friend std::ostream& operator<<(std::ostream& o, const Ty& ft) {
                    o << std::visit(
                        overloaded{
                            [](const FunctionType* const & t) { return function_type_to_string(t); },
                            [](const NeverTy& t)  { return "!"s; },
                            [](const UnitTy& t)  { return "()"s; },
                            [](const BoolTy& t) { return "bool"s; },
                            [](const UnknownTy& t)  { return "{unknown}"s;},
                            [](const InferTy& t) -> std::string {
                                return t.infer_ty_to_string();
                            },
                            [](const IntTy& t) -> std::string{ return IntTy_to_string(t); },
                            [](const UIntTy& t) -> std::string{ return UIntTy_to_string(t); },
                            [](const FloatTy& t) -> std::string{return FloatTy_to_string(t);},
                            [](const auto& t) {return "buhhhhh";}
                        },
                        ft);
                    return o;
                }
            };



            struct FunctionType {
                std::string id; // function types are also based on their name:
                                // fn() -> () {foo}
                // we remember the names for convenience
                // but these are not included into the "type"
                std::vector<Ty> arg_types;
                // the return type of the function: -> Ty
                Ty ret_ty;


                std::string to_string() const{
                    std::ostringstream o;
                    o << *this;
                    return o.str();
                }
                friend std::ostream& operator<<(std::ostream&       o,
                                                const FunctionType& ft) {
                    o << "fn(";
                    for (const auto& t : ft.arg_types) {
                        o << t << ", ";
                    }
                    o << ") -> " << ft.ret_ty << " {" << ft.id << '}';
                    return o;
                }

            };

            std::string function_type_to_string(const FunctionType* ft){
                return ft->to_string();
            }
        } // namespace types

    } // namespace tmir

} // namespace mr

namespace std{  

    template<>
    struct variant_size<mr::middle::types::Ty> : variant_size<mr::middle::types::type_variant_t> {
    };

    template<std::size_t I>
    struct variant_alternative<I,mr::middle::types::Ty> :  variant_alternative<I,mr::middle::types::type_variant_t> {
    };
 }
