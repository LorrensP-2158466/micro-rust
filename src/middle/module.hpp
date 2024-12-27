#pragma once

/**
 * Typed mid level intermediate representation
 *
 * combination of the HIR and MIR phase of the rust compiler
 */

#include "middle_phase.hpp"


#include "build/module.hpp"
#include "ir/module.hpp"
#include "symbol_table.hpp"
#include "tast/module.hpp"
#include "tast/tast_builder.hpp"
#include "types/type.hpp"
#include "unification_table.hpp"