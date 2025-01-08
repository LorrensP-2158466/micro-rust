#include "type.hpp"

using namespace mr::middle;

bool types::FnPointerTy::operator==(const types::FnPointerTy &other) const {
    return *ret_ty == *other.ret_ty && arg_tys == other.arg_tys;
}