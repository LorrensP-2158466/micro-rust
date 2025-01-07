# Mini-Rust Compiler/Interpreter

## What?

We have to create to implement a compiler/interpreter for a subset of the Rust language.

## Stages of compiler

### Lexing and Parsing

Im using Flex and Bison to tokenize and parse the input file and results into an ast.
Can be found in:

-   [lexer](lexer/lexfile.lex)
-   [parser](parser/yaccfile.yy)
-   [ast](ast/module.hpp)
-   [expr](expr/module.hpp)

this is the "simple" part of the compiler

### TAST

when the syntax is correct we will lower the AST to a more informative construct called HIR (this is from the rust compiler but not to that extend i just want to try this out).

We first find all defined types in the global scope (structs, enums, type defs, functions). and than for every function define the types in their scopes, etc. This is done when lowering. So when we have the TAST we can do the typechecking and lowering to IR

### IR

this is basicly the same thing as rust MIR (but again not to that extend). This is a control flow graph of initalisations, drops and borrows of every function in the input file. This is checked to be correct:

-   every used variable is initalised
-   borrowing rules are followed (see later)
-   some more?

this is then converted to the actual code the interpreter will run on.

#### Rust Borrowing

Rust borrowing is defined by 2 rules, which in turn create a whole lot of other rules. It creates the concept of Ownership and Borrowing.

Ownership is essentially an object who as an owner and that owner is in charge of destroying that object, i.e. dropping it. Only 1 "variable" can have ownership of an object, never more. Owners can be "moved", so for example:

```rust
let x = vec![1, 2, 3]; // x is owner of this vec object
let y = x; // ownership is transferred from x and y
// doing this will not work, since the value is moved
// x.push_back(4);
```

Borrowing is essentially having a reference (pointer but always valid, you'll see why) to an owned object. You can achieve borrowing through the operators:`&` and `&mut`.

-   `&` is an immutable borrow
-   `&mut` is a mutable borrow`

And the rules of borrowing are as follows:

A borrow can never live longer than the object being borrow, i.e. the lifetime of the owner is always longer or as long as the borrow. This says that every reference must be valid

You can either have multiple immutable borrows or 1 mutable borrow. This says that an object can't be updated when its borrowed immutably.
So for example this works:

```rust
let x = 10;
let y = &x; // immutable borrow 1 of x
let z = &x; // immutable borrow 2 of x
```

But this can't:

```rust
let mut x = 10;
let y = &mut x; // immutable borrow 1 of x
let z = &x;
*y = 20; // error can't immutable and mutable borrow at the same time

```

Note: the borrow is only "used" when using it you get me? if we didnt assign no error would be thrown.

You can circumvent this with scopes, which explicitly define lifetimes (we are not implementing lifetimes my god).

```rust
let x = 10;
// let z = &x; can't work because lifetime will be longer than `y`
{
    let y = &mut x;
    *y = 20;
}
let z = &x;
println!("{z}");
```

#### CFG

The official of MIR works by defining a Control Flow Graph of the program and checking it's soundness. It uses `Basic Blocks` for this which contain statements and a terminator.

For example the following code:

```rust
fn main(){
    let x = 10;
    let y = 20;

    let z = 10 + 20;
}
```

would look like this in human readable format:

```
fn main() -> () {
    let mut _0: ();
    let mut _2: (i32, bool);
    scope 1 {
        debug x => const 10_i32;
        scope 2 {
            debug y => const 20_i32;
            let _1: i32;
            scope 3 {
                debug z => _1;
            }
        }
    }

    bb0: {
        _2 = AddWithOverflow(const 10_i32, const 20_i32);
        assert(!move (_2.1: bool), "attempt to compute `{} + {}`, which would overflow", const 10_i32, const 20_i32) -> [success: bb1, unwind continue];
    }

    bb1: {
        _1 = move (_2.0: i32);
        return;
    }
}
```

This is very complex and not what i need to get the "same" effect. But you can find this all documented in the rustc-dev-guide

##### What will i do?

Well im keeping the structure but simplifying it a whole lot. Statements and Terminators still exist, but unwinding doesn't happen. The debugs i'll also wont use, because im not implementing a debugger.

And everything will be simplified to great extend, but still works.

##### What is a control flow?

Say you're programming, and one of the key features is conditional execution, `if ? then do this otherwise do this`. We can set this in a CFG like this:

```

                -------------
                | let mut y;|
                |   if x    |
                |           |
                -------------
               /             \
              / then          \ else
             /                 \
     -----------              -----------
     |         |              |         |
     |  y = 10 |              |  y = 20 |
     |         |              |         |
     –––––––––––              –––––––––––
             \                 /
              \               /
               \             /
                -------------
                |   y ?= 10 |
                |   y ?= 20 |
                |           |
                -------------
```

This is a flow graph of an if-else expression, as you see we don't know wether y is 10 or 20, what we do know is that y will be initialized. In the following graph we don't know that:

```

                -------------
                | let mut y;|
                |   if x    |
                |           |
                -------------
                   |          \
                   |           \ then
                   |            \
                   |           -----------
                   |           |         |
                   |           |  y = 20 |
                   |           |         |
                   |           –––––––––––
                   |            /
                   |           /
                   |         /
                -------------
                |   y = ? n |
                |           |
                |           |
                -------------
```

We can't know if y is every initialised, that's why you'll get errors in rust like: "ERROR value may not be initialized when used"

So when were checking the control flow, were basically performing Data Flow Analysis. The only ones i implemented were the ones that detect wether a variable is possibly initalized or possibly unintialized. Combining these can give a lot of information of our Mini-Rust program

### Interpreter

An interpreter that exectutes the IR, it follows the CFG and executes statements and changes blocks/functions on terminators.

When a function call happens, a new frame is pushed onto the frame stack, this frame includes the following information:

-   Current Locals (even temporaries, can't go around this)
-   Current Block and Statement Location in function executed
-   Reference to the current function (to get the block)
-   Mutable Reference to the return place in the caller, so when we encouter Return, we can write to it

This makes the interpreter not recursive, but causes for more locals per function and possibly more indirection. But it is "quite" "fast"
