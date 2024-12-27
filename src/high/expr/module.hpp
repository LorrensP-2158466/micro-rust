
#pragma once
/**
 * Module for easier use to include the whole expr **module** ;)
 *
 */

// main expressions class
#include "expr.hpp"
// binary operation expressions
// ex.: 10 + foo
#include "bin_op_expr.hpp"

// block expressions:
/*
{
    statement;
    statement;
    ...
    expr | implicit return of block
}
*/
#include "block_expr.hpp"

// assign expressions
// foo += 10
// foo = 300
#include "assign_expr.hpp"

// identifier expressions
// foo, bar, bazz...
#include "identifier.hpp"

// if else expressions
#include "if_else_expr.hpp"

// unit or ()
#include "unit_expr.hpp"

// unary expressions:
/*
    &foo
    &mut foo
    !foo
    -foo
    *foo
*/
#include "unary_op_expr.hpp"

// function call expr
#include "call_expr.hpp"

// while loop expression
// yes while loops are expressions with return type UNIT
#include "while_loop.hpp"

// control flow expressions like: break, return, continue
#include "control_flow_exprs.hpp"

// literals with optional suffix
// true, false,
// 10, 10.0, 30usize, 30.f32
// 'h'
// "hello world"
#include "literal.hpp"

#include "tuple_expr.hpp"