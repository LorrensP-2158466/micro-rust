#include "type.hpp"

#include <unordered_map>

namespace mr { namespace middle { namespace types {
    // WORK IN PROGRESS
    // interner to get all the types
    // to seperate concerns of the inference
    class TyCtx {
        std::unordered_map<TyKind, TyKind> _types;
        struct Primitives {
            Ty unit;
            Ty bool_t;
            Ty isize;
            Ty i8;
            Ty i16;
            Ty i32;
            Ty i64;
            Ty usize;
            Ty u8;
            Ty u16;
            Ty u32;
            Ty u64;
            Ty f32;
            Ty f64;
            Ty never;
            Ty unknown;
        } commons;

      public:
        TyCtx()
            : commons{Primitives{
                  .unit = make_type(UnitTy{}),
                  .bool_t = make_type(BoolTy{}),
                  .isize = make_type(IntTy::isize),
                  .i8 = make_type(IntTy::i8),
                  .i16 = make_type(IntTy::i16),
                  .i32 = make_type(IntTy::i32),
                  .i64 = make_type(IntTy::i64),
                  .usize = make_type(UIntTy::usize),
                  .u8 = make_type(UIntTy::u8),
                  .u16 = make_type(UIntTy::u16),
                  .u32 = make_type(UIntTy::u32),
                  .u64 = make_type(UIntTy::u64),
                  .f32 = make_type(FloatTy::F32),
                  .f64 = make_type(FloatTy::F64),
                  .never = make_type(NeverTy{}),
                  .unknown = make_type(UnknownTy{})
              }} {}

        Ty make_type(TyKind kind) {
            // default construct to UnKnown
            //
            TyKind &ty = _types[kind];
            ty = kind;
            return Ty{kind};
        }

        Ty make_fn_ptr(std::vector<Ty> args, Ty ret_ty) {
            // default construct to UnKnown
            //
            // TyKind fn_ptr_kind = FnPointerTy{std::move(args), ret_ty};
            // TyKind &ty = _types[fn_ptr_kind];
            // ty = kind;
            // return Ty{&ty};
        }
        Ty make_fn_item(std::vector<Ty> args, Ty ret_ty, std::string name) {
            // // default construct to UnKnown
            // //
            // TyKind &ty = _types[kind];
            // ty = kind;
            // return Ty{&ty};
        }

        inline Ty i8() const noexcept { return commons.i8; }
        inline Ty i16() const noexcept { return commons.i16; }
        inline Ty i32() const noexcept { return commons.i32; }
        inline Ty i64() const noexcept { return commons.i64; }
        inline Ty isize() const noexcept { return commons.isize; }
        inline Ty u8() const noexcept { return commons.u8; }
        inline Ty u16() const noexcept { return commons.u16; }
        inline Ty u32() const noexcept { return commons.u32; }
        inline Ty u64() const noexcept { return commons.u64; }
        inline Ty f32() const noexcept { return commons.f32; }
        inline Ty f64() const noexcept { return commons.f64; }
        inline Ty usize() const noexcept { return commons.usize; }
        inline Ty bool_t() const noexcept { return commons.bool_t; }
        inline Ty unit() const noexcept { return commons.unit; }
        inline Ty never() const noexcept { return commons.never; }
        inline Ty unknown() const noexcept { return commons.unknown; }
    };
}}} // namespace mr::middle::types