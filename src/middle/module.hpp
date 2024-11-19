#pragma once

/**
 * Typed mid level intermediate representation
 *
 * combination of the HIR and MIR phase of the rust compiler
 */

#include "ast_lowering.hpp"
#include "build/module.hpp"
#include "ir/module.hpp"
#include "symbol_table.hpp"
#include "tast/module.hpp"
#include "tast_builder.hpp"
#include "type.hpp"
#include "unification_table.hpp"