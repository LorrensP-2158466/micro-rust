# Mini-Rust Compiler/Interpreter

## Main Part and Flow of the Compiler

The Rust language is very complex and provides a lot of features that are very modern and thus require more complex implementation strategies. All components of the compiler are driven by the [`driver`](/src/driver/mr_driver.hpp) which orchestrates the flow of the compiler. There are a lot of subcomponents which work together to get the final output of the program the user expected. I'll list them shortly before explaining them in detail.

-   Lexer and Parser
-   ErrorCtx
-   TyInferencer
-   TAst Builder
-   IR Builder
-   Interpreter

These are the `"sub-drivers"` that are directed by the main driver to make the above statement come to live. These are thus divided into 3 steps, I call these `high`, `middle`, "`low`". The [`ErrorCtx`](/src/errors/ctx.hpp) is shared by all parts to collect and diagnose errors if they occur.

-   High: Lexer -> Parsing -> AST
-   Middle: Build TAst | TypeCheck -> Build IR -> Check -> Optimize
-   Low: Interpreter that evaluates the IR

I'll now explain each of them in detail that is sufficient to understand what is happening and why, some may be explained more than others.

#### Relevant source files

-   [`Driver`](src/driver/mr_driver.hpp)
-   [`Diagnostics`](src/errors/ctx.hpp)

### High and Parsing

We build an AST in the tradiotional way, the `Lexer` takes the source code and transforms these into `Tokens`, individual "language" constructs. The `Parser` works together with the `Lexer` and consumes these tokens to construct an AST that represents the the source code in a tree like structure.

Parsing and Lexing are done with [`GNU Flex`](https://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_mono/flex.html) and [`GNU Bison`](https://www.gnu.org/software/bison/manual/), and by providing actions on top of it's rules we can create an AST.

The AST consists of a list of `items` (think of functions, structs, ...) and each of them contain statements/expressions. Want to know more? -> rust reference is a great resource which I used a lot to reason about my parsing.

#### Relevant source files

-   [lexer](src/lexer/lexfile.lex)
-   [parser](src/parser/yaccfile.yy)
-   [ast](src/high/ast/ast.hpp)
-   [expr](src/high/expr/expr.hpp)

### Middle

Rust is a very flexible language, based on the context of the program, it can `infer` a many things you don't have to explicitly state (think types, borrows, lifetimes, owners, ...). Because of this, we have to use extension of the `AST` called the Typed AST (`TAst`) which has sort of the same construct as the AST (I'll explain this) but with the types encoded inside of it.

The main thing about the compiler is thus inferencing the types (and other things) and placing these types inside of the AST which we can later resolve when we know the full context. Among other things it also resolves complex structure such as while loops to their more simpler structures.

So we transform the `AST` into a list of `TASt`s (every function is a TAst) using the `TyInferer` to infer types based on their relations between other types. So when we have an expression of the form `expr on expr`, we use unification to create a constraint on these to be equal. This will result in equivalance classes of different types and expressions, so when we have constrained every expresssion/type inside of a `Tast`, we can resolve them to their real type. This makes use of several CS concepts such as the [`Hindley-Milner type system`](https://en.wikipedia.org/wiki/Hindley%E2%80%93Milner_type_system) and `UnificationTables` also called [`Disjoint sets`](https://en.wikipedia.org/wiki/Disjoint-set_data_structure).

When the `TAst` is built and the structure is sound (for example continue outside of a loop is unsound) we can start building the `IR`. We transform the structure of the `TAst` into a [`CFG`](https://en.wikipedia.org/wiki/Control-flow_graph), which is a collection of Basic Blocks, which consist of a list of `statements` (`assign` or `print`) and a `terminator`, this terminator acts like a edge to the next Basic Blocks it can `jump` to, be this condiontional or not.

But before we can evaluate the `IR` (remember, this is our final "step"), we have to check that some invariants are still uphold, mainly: initialisation and immutable variables. In Rust, every variable must be initialised before being used and we can only do mutliple `assignments` to a mutable variable. This (together with borrowing) was the main reason I wanted to use/create this Intermediate Representation (we also learned about this in the course, so why not).

The checker performs 3 dataflow-analyses, which return a list of states, corresponding with each basic block. The state of the current block tell us about everthing that happened before this block. This can't track the state of `B1` using it's statements/terminators, because we don't know when this state came to be in this block. This has to be handled separately.

-   MaybeInit: state for a block tells us which variable is maybe initialised
-   MaybeUninit: state for a block tells us which variable is maybe uninitialised
-   EverInit: state for a block tells us which variable was at some point before this block initialised.

The first 2 are used to determine if a variable is initialised when used. The second is used to determine if a variable may be initialised when it is immutable.

When these variants are upheld, we can optimize (1 pass at [`SimpliFy`](/src/middle/ir/passes/simplify.hpp)) and then evaluate the program.

#### Relevant source files

-   [`MiddlePhase`](/src/middle/middle_phase.hpp)
-   [`TAstBuilder`](/src/middle/tast/tast_builder.hpp)
-   [`TyInferer`](src/middle/type_inference.hpp)
-   [`IrBuilder`](src/middle/ir/build/ir_builder.hpp)
-   [`Checker`](src/middle/ir/checker/checker.hpp)
-   [`Analyser`](src/middle/ir/analysis/analysis.hpp)

(Drawings to understand the analyses if needed)

```
Maybe Init & UnInit

                -------------
                | let mut y;|   init: { }   uninit: { y }
                |   if x    |
                |           |
                -------------
                   |          \
                   |           \ then
                   |            \
                   |           -----------
                   |           |         | init: { y }   uninit: {  }
                   |           |  y = 20 |
                   |           |         |
                   |           –––––––––––
                   |            /
                   |           /
                   |         /
                -------------
                | c = y     |
                |           | init: { y }   uninit: { y }
                |           |
                -------------
variable y is potentially uninitialized.
```

```
Ever Init:
                -------------
                | let y;    |  ever : {}
                |   if x    |
                |           |
                -------------
               /             \
              / then          \ else
             /                 \
     -----------              -----------
     |         | ever : {y }  |         | ever : {}
     |  y = 10 |              |         |
     |         |              |         |
     –––––––––––              –––––––––––
             \                 /
              \               /
               \             /
                -------------
                |   y = 20  | ever : { y }
                |           |
                -------------
variable y is potentially already initialized.
(this also depends on dead local trees, too much detail, see: EverInit inside ./src/middle/ir/checker/analyzers.hpp
```

### Low and Interpreting

Interpreting is relatively simple, we act as if the `CFG` we get as input is checked and valid in every instruction used. We then evaluate the `CFG` as if we were an actual machine (with caveats). Every variable has it's own register and the return register is a pointer to the register of the callee which want's to assign the result to a register. Some things are taken over from rust, most notably overflowing operations, when an integer (unsigned/signed) is used in a binary operation, we crash at runtime if an over/under flow occured. That is basically it, because we did all the complex stuff at "compile time". So continue, breaks, returns, ... are all compiled away to simple `gotos`.

#### Relevant source files

-   [`Interpeter`](/src/interpreter/interpreter.hpp)
-   [`Frame Stack`](/src/interpreter/stack.hpp)
-   [`Value`](/src/interpreter/value.hpp) this is very hacky

## Extras

These things are not to be considered, because i should have talked about them during the examination or they are not relevant. But I might as well include them, because why not.

### What is there really?

-   i support the common types of rust: signed/unsigned integers, bools and floats
-   i support function types
-   i support writing rust without declaring any specific types (outside of arguments)
-   i have nice error handling (and displaying it :) )
-   i support

### Possible extensions that can be (easily) built upon the current system

-   Borrowing (Using Dataflow analysis this is much more elegant)
-   closure (we talked about this)
-   SSA optimization (we have "infinite" registers)
-   Compile Time Evaluation (using Dataflow and abstract Interpreter)
-   many more which i loved to implement but this document is getting quite long
