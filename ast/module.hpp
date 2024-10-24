#pragma once
/**
 * Module for easier use to include the whole ast **module** ;)
 * 
 */

// the main ast class which includes all the items
#include "ast.hpp"

// an item in rust
/*
struct Foo{...}
fn foo(...) -> i32 {...}
use foo::Foo;
...
NOTE: an item is also a statement, this allows using these things
in function scopes
 */
#include "item.hpp"

// a function delcarion (item/statement)
#include "fun_decl.hpp"

// let statement, not the way rust does it ofcourse
// let (mut)? IDENT (: type)? = expr;
#include "let.hpp"

// base class for statements
#include "stmt.hpp"

// class for handling types in parsing stage
// this if effectively a "path" in rust
#include "types.hpp"

// simple println!() statement for debugging programs
#include "println.hpp"