// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

// "%code top" blocks.
#line 39 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"

#include <string>
#include <variant>
#include <cstddef>
#include <memory>
#include <assert.h>
#include "lexer/lexer.hpp"
#include "driver/mr_driver.hpp"

    #define yylex lexer.yylex
    #define DEFAULT_ACTION(to, from) do { to = std::move(from);} while(0)

#line 52 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"




#include "parser.tab.hpp"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
namespace mr {
#line 152 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"

  /// Build a parser object.
  Parser::Parser (driver::MRDriver& driver_yyarg, Lexer &lexer_yyarg, const bool debug_yyarg, const char* input_file_name_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg),
      lexer (lexer_yyarg),
      debug (debug_yyarg),
      input_file_name (input_file_name_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_func_arg: // func_arg
        value.copy< FunArg > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
      case symbol_kind::S_STR_LITERAL: // STR_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_I8: // I8
      case symbol_kind::S_I16: // I16
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_I64: // I64
      case symbol_kind::S_ISIZE: // ISIZE
      case symbol_kind::S_U8: // U8
      case symbol_kind::S_U16: // U16
      case symbol_kind::S_U32: // U32
      case symbol_kind::S_U64: // U64
      case symbol_kind::S_USIZE: // USIZE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_LN: // PRINT_LN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_EQEQ: // EQEQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_BANG: // BANG
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_L_AND: // L_AND
      case symbol_kind::S_L_OR: // L_OR
      case symbol_kind::S_PLUS_EQ: // PLUS_EQ
      case symbol_kind::S_MIN_EQ: // MIN_EQ
      case symbol_kind::S_MUL_EQ: // MUL_EQ
      case symbol_kind::S_DIV_EQ: // DIV_EQ
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_AMPERSAND: // AMPERSAND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AMPERSAND_MUT: // AMPERSAND_MUT
        value.copy< Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.copy< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.copy< U<AssignExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.copy< U<Ast> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.copy< U<BinOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.copy< U<BlockExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.copy< U<CallExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_expr_w_block: // expr_w_block
      case symbol_kind::S_expr_wo_block: // expr_wo_block
        value.copy< U<Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.copy< U<FunDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.copy< U<IfElse> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item: // item
        value.copy< U<Item> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_let: // let
        value.copy< U<LetStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_literal: // literal
        value.copy< U<Literal> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_print_ln: // print_ln
        value.copy< U<PrintLn> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.copy< U<Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.copy< U<UnaryOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.copy< U<WhileLoop> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.copy< std::optional<Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.copy< std::vector<FunArg> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.copy< std::vector<U<Expr>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item_list: // item_list
        value.copy< std::vector<U<Item>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< std::vector<U<Stmt>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_func_arg: // func_arg
        value.move< FunArg > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
      case symbol_kind::S_STR_LITERAL: // STR_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_I8: // I8
      case symbol_kind::S_I16: // I16
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_I64: // I64
      case symbol_kind::S_ISIZE: // ISIZE
      case symbol_kind::S_U8: // U8
      case symbol_kind::S_U16: // U16
      case symbol_kind::S_U32: // U32
      case symbol_kind::S_U64: // U64
      case symbol_kind::S_USIZE: // USIZE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_LN: // PRINT_LN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_EQEQ: // EQEQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_BANG: // BANG
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_L_AND: // L_AND
      case symbol_kind::S_L_OR: // L_OR
      case symbol_kind::S_PLUS_EQ: // PLUS_EQ
      case symbol_kind::S_MIN_EQ: // MIN_EQ
      case symbol_kind::S_MUL_EQ: // MUL_EQ
      case symbol_kind::S_DIV_EQ: // DIV_EQ
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_AMPERSAND: // AMPERSAND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AMPERSAND_MUT: // AMPERSAND_MUT
        value.move< Token > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.move< Type > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< U<AssignExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_program: // program
        value.move< U<Ast> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.move< U<BinOpExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.move< U<BlockExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.move< U<CallExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_expr_w_block: // expr_w_block
      case symbol_kind::S_expr_wo_block: // expr_wo_block
        value.move< U<Expr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.move< U<FunDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.move< U<IfElse> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_item: // item
        value.move< U<Item> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_let: // let
        value.move< U<LetStmt> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_literal: // literal
        value.move< U<Literal> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_print_ln: // print_ln
        value.move< U<PrintLn> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< U<Stmt> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.move< U<UnaryOpExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.move< U<WhileLoop> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< std::optional<Type> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.move< std::vector<FunArg> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.move< std::vector<U<Expr>> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_item_list: // item_list
        value.move< std::vector<U<Item>> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<U<Stmt>> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_func_arg: // func_arg
        value.YY_MOVE_OR_COPY< FunArg > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
      case symbol_kind::S_STR_LITERAL: // STR_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_I8: // I8
      case symbol_kind::S_I16: // I16
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_I64: // I64
      case symbol_kind::S_ISIZE: // ISIZE
      case symbol_kind::S_U8: // U8
      case symbol_kind::S_U16: // U16
      case symbol_kind::S_U32: // U32
      case symbol_kind::S_U64: // U64
      case symbol_kind::S_USIZE: // USIZE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_LN: // PRINT_LN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_EQEQ: // EQEQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_BANG: // BANG
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_L_AND: // L_AND
      case symbol_kind::S_L_OR: // L_OR
      case symbol_kind::S_PLUS_EQ: // PLUS_EQ
      case symbol_kind::S_MIN_EQ: // MIN_EQ
      case symbol_kind::S_MUL_EQ: // MUL_EQ
      case symbol_kind::S_DIV_EQ: // DIV_EQ
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_AMPERSAND: // AMPERSAND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AMPERSAND_MUT: // AMPERSAND_MUT
        value.YY_MOVE_OR_COPY< Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.YY_MOVE_OR_COPY< U<AssignExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< U<Ast> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.YY_MOVE_OR_COPY< U<BinOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.YY_MOVE_OR_COPY< U<BlockExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.YY_MOVE_OR_COPY< U<CallExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_expr_w_block: // expr_w_block
      case symbol_kind::S_expr_wo_block: // expr_wo_block
        value.YY_MOVE_OR_COPY< U<Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.YY_MOVE_OR_COPY< U<FunDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.YY_MOVE_OR_COPY< U<IfElse> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item: // item
        value.YY_MOVE_OR_COPY< U<Item> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_let: // let
        value.YY_MOVE_OR_COPY< U<LetStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_literal: // literal
        value.YY_MOVE_OR_COPY< U<Literal> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_print_ln: // print_ln
        value.YY_MOVE_OR_COPY< U<PrintLn> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.YY_MOVE_OR_COPY< U<Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.YY_MOVE_OR_COPY< U<UnaryOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.YY_MOVE_OR_COPY< U<WhileLoop> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.YY_MOVE_OR_COPY< std::optional<Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.YY_MOVE_OR_COPY< std::vector<FunArg> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.YY_MOVE_OR_COPY< std::vector<U<Expr>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item_list: // item_list
        value.YY_MOVE_OR_COPY< std::vector<U<Item>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< std::vector<U<Stmt>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_func_arg: // func_arg
        value.move< FunArg > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
      case symbol_kind::S_STR_LITERAL: // STR_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_I8: // I8
      case symbol_kind::S_I16: // I16
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_I64: // I64
      case symbol_kind::S_ISIZE: // ISIZE
      case symbol_kind::S_U8: // U8
      case symbol_kind::S_U16: // U16
      case symbol_kind::S_U32: // U32
      case symbol_kind::S_U64: // U64
      case symbol_kind::S_USIZE: // USIZE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_LN: // PRINT_LN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_EQEQ: // EQEQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_BANG: // BANG
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_L_AND: // L_AND
      case symbol_kind::S_L_OR: // L_OR
      case symbol_kind::S_PLUS_EQ: // PLUS_EQ
      case symbol_kind::S_MIN_EQ: // MIN_EQ
      case symbol_kind::S_MUL_EQ: // MUL_EQ
      case symbol_kind::S_DIV_EQ: // DIV_EQ
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_AMPERSAND: // AMPERSAND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AMPERSAND_MUT: // AMPERSAND_MUT
        value.move< Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.move< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< U<AssignExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< U<Ast> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.move< U<BinOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.move< U<BlockExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.move< U<CallExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_expr_w_block: // expr_w_block
      case symbol_kind::S_expr_wo_block: // expr_wo_block
        value.move< U<Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.move< U<FunDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.move< U<IfElse> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item: // item
        value.move< U<Item> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_let: // let
        value.move< U<LetStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_literal: // literal
        value.move< U<Literal> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_print_ln: // print_ln
        value.move< U<PrintLn> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< U<Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.move< U<UnaryOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.move< U<WhileLoop> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< std::optional<Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.move< std::vector<FunArg> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.move< std::vector<U<Expr>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item_list: // item_list
        value.move< std::vector<U<Item>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<U<Stmt>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_func_arg: // func_arg
        value.copy< FunArg > (that.value);
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
      case symbol_kind::S_STR_LITERAL: // STR_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_I8: // I8
      case symbol_kind::S_I16: // I16
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_I64: // I64
      case symbol_kind::S_ISIZE: // ISIZE
      case symbol_kind::S_U8: // U8
      case symbol_kind::S_U16: // U16
      case symbol_kind::S_U32: // U32
      case symbol_kind::S_U64: // U64
      case symbol_kind::S_USIZE: // USIZE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_LN: // PRINT_LN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_EQEQ: // EQEQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_BANG: // BANG
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_L_AND: // L_AND
      case symbol_kind::S_L_OR: // L_OR
      case symbol_kind::S_PLUS_EQ: // PLUS_EQ
      case symbol_kind::S_MIN_EQ: // MIN_EQ
      case symbol_kind::S_MUL_EQ: // MUL_EQ
      case symbol_kind::S_DIV_EQ: // DIV_EQ
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_AMPERSAND: // AMPERSAND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AMPERSAND_MUT: // AMPERSAND_MUT
        value.copy< Token > (that.value);
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.copy< Type > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.copy< U<AssignExpr> > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< U<Ast> > (that.value);
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.copy< U<BinOpExpr> > (that.value);
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.copy< U<BlockExpr> > (that.value);
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.copy< U<CallExpr> > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_expr_w_block: // expr_w_block
      case symbol_kind::S_expr_wo_block: // expr_wo_block
        value.copy< U<Expr> > (that.value);
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.copy< U<FunDecl> > (that.value);
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.copy< U<IfElse> > (that.value);
        break;

      case symbol_kind::S_item: // item
        value.copy< U<Item> > (that.value);
        break;

      case symbol_kind::S_let: // let
        value.copy< U<LetStmt> > (that.value);
        break;

      case symbol_kind::S_literal: // literal
        value.copy< U<Literal> > (that.value);
        break;

      case symbol_kind::S_print_ln: // print_ln
        value.copy< U<PrintLn> > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.copy< U<Stmt> > (that.value);
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.copy< U<UnaryOpExpr> > (that.value);
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.copy< U<WhileLoop> > (that.value);
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.copy< std::optional<Type> > (that.value);
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.copy< std::vector<FunArg> > (that.value);
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.copy< std::vector<U<Expr>> > (that.value);
        break;

      case symbol_kind::S_item_list: // item_list
        value.copy< std::vector<U<Item>> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< std::vector<U<Stmt>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_func_arg: // func_arg
        value.move< FunArg > (that.value);
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
      case symbol_kind::S_STR_LITERAL: // STR_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_I8: // I8
      case symbol_kind::S_I16: // I16
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_I64: // I64
      case symbol_kind::S_ISIZE: // ISIZE
      case symbol_kind::S_U8: // U8
      case symbol_kind::S_U16: // U16
      case symbol_kind::S_U32: // U32
      case symbol_kind::S_U64: // U64
      case symbol_kind::S_USIZE: // USIZE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_LN: // PRINT_LN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_EQEQ: // EQEQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_BANG: // BANG
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_L_AND: // L_AND
      case symbol_kind::S_L_OR: // L_OR
      case symbol_kind::S_PLUS_EQ: // PLUS_EQ
      case symbol_kind::S_MIN_EQ: // MIN_EQ
      case symbol_kind::S_MUL_EQ: // MUL_EQ
      case symbol_kind::S_DIV_EQ: // DIV_EQ
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_AMPERSAND: // AMPERSAND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AMPERSAND_MUT: // AMPERSAND_MUT
        value.move< Token > (that.value);
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.move< Type > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< U<AssignExpr> > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< U<Ast> > (that.value);
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.move< U<BinOpExpr> > (that.value);
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.move< U<BlockExpr> > (that.value);
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.move< U<CallExpr> > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_expr_w_block: // expr_w_block
      case symbol_kind::S_expr_wo_block: // expr_wo_block
        value.move< U<Expr> > (that.value);
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.move< U<FunDecl> > (that.value);
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.move< U<IfElse> > (that.value);
        break;

      case symbol_kind::S_item: // item
        value.move< U<Item> > (that.value);
        break;

      case symbol_kind::S_let: // let
        value.move< U<LetStmt> > (that.value);
        break;

      case symbol_kind::S_literal: // literal
        value.move< U<Literal> > (that.value);
        break;

      case symbol_kind::S_print_ln: // print_ln
        value.move< U<PrintLn> > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< U<Stmt> > (that.value);
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.move< U<UnaryOpExpr> > (that.value);
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.move< U<WhileLoop> > (that.value);
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< std::optional<Type> > (that.value);
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.move< std::vector<FunArg> > (that.value);
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.move< std::vector<U<Expr>> > (that.value);
        break;

      case symbol_kind::S_item_list: // item_list
        value.move< std::vector<U<Item>> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<U<Stmt>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_func_arg: // func_arg
        yylhs.value.emplace< FunArg > ();
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
      case symbol_kind::S_STR_LITERAL: // STR_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_I8: // I8
      case symbol_kind::S_I16: // I16
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_I64: // I64
      case symbol_kind::S_ISIZE: // ISIZE
      case symbol_kind::S_U8: // U8
      case symbol_kind::S_U16: // U16
      case symbol_kind::S_U32: // U32
      case symbol_kind::S_U64: // U64
      case symbol_kind::S_USIZE: // USIZE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_LN: // PRINT_LN
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_EQEQ: // EQEQ
      case symbol_kind::S_NE: // NE
      case symbol_kind::S_BANG: // BANG
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_LE: // LE
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_GE: // GE
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_L_AND: // L_AND
      case symbol_kind::S_L_OR: // L_OR
      case symbol_kind::S_PLUS_EQ: // PLUS_EQ
      case symbol_kind::S_MIN_EQ: // MIN_EQ
      case symbol_kind::S_MUL_EQ: // MUL_EQ
      case symbol_kind::S_DIV_EQ: // DIV_EQ
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_AMPERSAND: // AMPERSAND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_AMPERSAND_MUT: // AMPERSAND_MUT
        yylhs.value.emplace< Token > ();
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        yylhs.value.emplace< Type > ();
        break;

      case symbol_kind::S_assignment: // assignment
        yylhs.value.emplace< U<AssignExpr> > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< U<Ast> > ();
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        yylhs.value.emplace< U<BinOpExpr> > ();
        break;

      case symbol_kind::S_block_expr: // block_expr
        yylhs.value.emplace< U<BlockExpr> > ();
        break;

      case symbol_kind::S_call_expr: // call_expr
        yylhs.value.emplace< U<CallExpr> > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_expr_w_block: // expr_w_block
      case symbol_kind::S_expr_wo_block: // expr_wo_block
        yylhs.value.emplace< U<Expr> > ();
        break;

      case symbol_kind::S_function_decl: // function_decl
        yylhs.value.emplace< U<FunDecl> > ();
        break;

      case symbol_kind::S_if_expr: // if_expr
        yylhs.value.emplace< U<IfElse> > ();
        break;

      case symbol_kind::S_item: // item
        yylhs.value.emplace< U<Item> > ();
        break;

      case symbol_kind::S_let: // let
        yylhs.value.emplace< U<LetStmt> > ();
        break;

      case symbol_kind::S_literal: // literal
        yylhs.value.emplace< U<Literal> > ();
        break;

      case symbol_kind::S_print_ln: // print_ln
        yylhs.value.emplace< U<PrintLn> > ();
        break;

      case symbol_kind::S_stmt: // stmt
        yylhs.value.emplace< U<Stmt> > ();
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        yylhs.value.emplace< U<UnaryOpExpr> > ();
        break;

      case symbol_kind::S_while_expr: // while_expr
        yylhs.value.emplace< U<WhileLoop> > ();
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_type_decl: // type_decl
        yylhs.value.emplace< std::optional<Type> > ();
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        yylhs.value.emplace< std::vector<FunArg> > ();
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        yylhs.value.emplace< std::vector<U<Expr>> > ();
        break;

      case symbol_kind::S_item_list: // item_list
        yylhs.value.emplace< std::vector<U<Item>> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< std::vector<U<Stmt>> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: item_list
#line 126 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                { driver.set_ast(std::make_unique<Ast>(std::move(yystack_[0].value.as < std::vector<U<Item>> > ()))); }
#line 1743 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 3: // item_list: item_list item
#line 130 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     {yystack_[1].value.as < std::vector<U<Item>> > ().push_back(std::move(yystack_[0].value.as < U<Item> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Item>> > (), yystack_[1].value.as < std::vector<U<Item>> > ());}
#line 1749 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 4: // item_list: item_list error item
#line 132 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                           {yystack_[2].value.as < std::vector<U<Item>> > ().push_back(std::move(yystack_[0].value.as < U<Item> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Item>> > (), yystack_[2].value.as < std::vector<U<Item>> > ());}
#line 1755 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 5: // item_list: item
#line 133 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           {
        auto vec = std::vector<U<Item>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Item> > ()));
        yylhs.value.as < std::vector<U<Item>> > () = std::move(vec) ;}
#line 1764 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 6: // item_list: error
#line 137 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
            { std::cerr << "Expected Item\n"; }
#line 1770 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 7: // item: function_decl
#line 141 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                  { DEFAULT_ACTION(yylhs.value.as < U<Item> > (), yystack_[0].value.as < U<FunDecl> > ()); }
#line 1776 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 8: // function_decl: FN IDENTIFIER func_decl_args func_ret_type block_expr
#line 147 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
    { 
        yylhs.value.as < U<FunDecl> > () = FunDecl::make_unique(yystack_[3].value.as < Token > ().string_value(), std::move(yystack_[2].value.as < std::vector<FunArg> > ()), std::move(yystack_[1].value.as < Type > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ()));
    }
#line 1784 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 9: // func_ret_type: ARROW type
#line 153 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < Type > (), yystack_[0].value.as < Type > ()); }
#line 1790 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 10: // func_ret_type: %empty
#line 154 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
      { yylhs.value.as < Type > () = Type(); }
#line 1796 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 11: // func_decl_args: LPAREN func_arg_list RPAREN
#line 159 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                  {yylhs.value.as < std::vector<FunArg> > () = std::move(yystack_[1].value.as < std::vector<FunArg> > ());}
#line 1802 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 12: // func_decl_args: LPAREN RPAREN
#line 160 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                    { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{};}
#line 1808 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 13: // func_decl_args: error
#line 161 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
            { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{};}
#line 1814 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 14: // func_arg_list: func_arg_list COMMA func_arg
#line 165 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                   { yystack_[2].value.as < std::vector<FunArg> > ().push_back(std::move(yystack_[0].value.as < FunArg > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<FunArg> > (), yystack_[2].value.as < std::vector<FunArg> > ());}
#line 1820 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 15: // func_arg_list: func_arg
#line 166 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
               { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{}; yylhs.value.as < std::vector<FunArg> > ().push_back(std::move(yystack_[0].value.as < FunArg > ())); }
#line 1826 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 16: // func_arg: opt_mut IDENTIFIER COLON type
#line 170 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                    { yylhs.value.as < FunArg > () = FunArg{yystack_[2].value.as < Token > ().string_value(), std::move(yystack_[0].value.as < Type > ()), yystack_[3].value.as < bool > ()}; }
#line 1832 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 17: // func_arg: opt_mut IDENTIFIER error
#line 171 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                               { std::cerr << "Expected type declaration\n";}
#line 1838 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 18: // stmt: SEMICOLON
#line 174 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                {yylhs.value.as < U<Stmt> > () = std::make_unique<EmptyStmt>();}
#line 1844 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 19: // stmt: let
#line 175 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
          { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[0].value.as < U<LetStmt> > ()); }
#line 1850 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 20: // stmt: RETURN SEMICOLON
#line 176 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                       {  yylhs.value.as < U<Stmt> > () = std::make_unique<Return>(std::make_unique<Unit>()); }
#line 1856 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 21: // stmt: BREAK SEMICOLON
#line 177 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                      {  yylhs.value.as < U<Stmt> > () = std::make_unique<Break>(std::make_unique<Unit>()); }
#line 1862 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 22: // stmt: CONTINUE SEMICOLON
#line 178 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                         {  yylhs.value.as < U<Stmt> > () = std::make_unique<Continue>(); }
#line 1868 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 23: // stmt: expr_stmt
#line 179 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[0].value.as < U<Expr> > ());}
#line 1874 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 24: // stmt: print_ln SEMICOLON
#line 180 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                         { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[1].value.as < U<PrintLn> > ());}
#line 1880 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 25: // stmt: item
#line 181 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[0].value.as < U<Item> > ()); }
#line 1886 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 26: // stmt: error SEMICOLON
#line 182 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                      {/* just keep going */}
#line 1892 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 27: // stmt_list: stmt_list stmt
#line 186 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yystack_[1].value.as < std::vector<U<Stmt>> > ().push_back(std::move(yystack_[0].value.as < U<Stmt> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Stmt>> > (), yystack_[1].value.as < std::vector<U<Stmt>> > ()); }
#line 1898 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 28: // stmt_list: stmt
#line 187 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           {
        auto vec = std::vector<U<Stmt>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Stmt> > ()));
        yylhs.value.as < std::vector<U<Stmt>> > () = std::move(vec); 
      }
#line 1908 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 29: // print_ln: PRINT_LN LPAREN STR_LITERAL RPAREN
#line 195 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                         { yylhs.value.as < U<PrintLn> > () = std::make_unique<PrintLn>(yystack_[1].value.as < Token > ().string_value()); }
#line 1914 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 30: // type_decl: COLON type
#line 199 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < std::optional<Type> > (), yystack_[0].value.as < Type > ()); }
#line 1920 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 31: // type_decl: %empty
#line 200 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
      { yylhs.value.as < std::optional<Type> > () = {}; }
#line 1926 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 32: // opt_mut: MUT
#line 204 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
         { yylhs.value.as < bool > () = true; }
#line 1932 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 33: // opt_mut: %empty
#line 205 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
         { yylhs.value.as < bool > () = false; }
#line 1938 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 34: // let: LET opt_mut IDENTIFIER type_decl EQ expr SEMICOLON
#line 210 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
      {yylhs.value.as < U<LetStmt> > () = LetStmt::make_unique_init(yystack_[4].value.as < Token > ().string_value(), std::move(yystack_[3].value.as < std::optional<Type> > ()), std::move(yystack_[1].value.as < U<Expr> > ()), yystack_[5].value.as < bool > ());}
#line 1944 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 35: // let: LET opt_mut IDENTIFIER type_decl error EQ SEMICOLON
#line 212 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
      {
        yylhs.value.as < U<LetStmt> > () = LetStmt::make_unique_init(yystack_[4].value.as < Token > ().string_value(), std::move(yystack_[3].value.as < std::optional<Type> > ()), std::unique_ptr<Expr>(nullptr), yystack_[5].value.as < bool > ()); 
      }
#line 1952 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 36: // let: LET opt_mut IDENTIFIER type_decl SEMICOLON
#line 215 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                                 {
        yylhs.value.as < U<LetStmt> > () = LetStmt::make_unique_decl(yystack_[2].value.as < Token > ().string_value(), std::move(yystack_[1].value.as < std::optional<Type> > ()), yystack_[3].value.as < bool > ());
    }
#line 1960 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 37: // if_expr: IF expr block_expr
#line 221 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                         { yylhs.value.as < U<IfElse> > () = std::make_unique<IfElse>(std::move(yystack_[1].value.as < U<Expr> > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ())); }
#line 1966 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 38: // if_expr: IF expr block_expr ELSE if_expr
#line 222 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                      {yylhs.value.as < U<IfElse> > () = std::make_unique<IfElse>(std::move(yystack_[3].value.as < U<Expr> > ()), std::move(yystack_[2].value.as < U<BlockExpr> > ()), std::move(yystack_[0].value.as < U<IfElse> > ())); }
#line 1972 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 39: // if_expr: IF expr block_expr ELSE block_expr
#line 223 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                         {yylhs.value.as < U<IfElse> > () = std::make_unique<IfElse>(std::move(yystack_[3].value.as < U<Expr> > ()), std::move(yystack_[2].value.as < U<BlockExpr> > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ())); }
#line 1978 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 40: // type: I8
#line 234 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::I8); }
#line 1984 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 41: // type: I16
#line 235 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           { yylhs.value.as < Type > () = Type(primitive_type::I16); }
#line 1990 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 42: // type: I32
#line 236 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::I32); }
#line 1996 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 43: // type: I64
#line 237 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           { yylhs.value.as < Type > () = Type(primitive_type::I64); }
#line 2002 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 44: // type: ISIZE
#line 238 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
             { yylhs.value.as < Type > () = Type(primitive_type::ISIZE); }
#line 2008 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 45: // type: U8
#line 239 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::U8); }
#line 2014 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 46: // type: U16
#line 240 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           { yylhs.value.as < Type > () = Type(primitive_type::U16); }
#line 2020 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 47: // type: U32
#line 241 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::U32); }
#line 2026 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 48: // type: U64
#line 242 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           { yylhs.value.as < Type > () = Type(primitive_type::U64); }
#line 2032 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 49: // type: USIZE
#line 243 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
             { yylhs.value.as < Type > () = Type(primitive_type::USIZE); }
#line 2038 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 50: // type: BOOL
#line 244 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
            { yylhs.value.as < Type > () = Type(primitive_type::BOOL); }
#line 2044 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 51: // type: LPAREN RPAREN
#line 245 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yylhs.value.as < Type > () = Type(); }
#line 2050 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 52: // block_expr: LBRACE stmt_list RBRACE
#line 251 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                              { yylhs.value.as < U<BlockExpr> > () = std::make_unique<BlockExpr>(std::move(yystack_[1].value.as < std::vector<U<Stmt>> > ()), std::make_unique<Unit>()); }
#line 2056 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 53: // block_expr: LBRACE stmt_list expr RBRACE
#line 252 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                    { yylhs.value.as < U<BlockExpr> > () = std::make_unique<BlockExpr>(std::move(yystack_[2].value.as < std::vector<U<Stmt>> > ()), std::move(yystack_[1].value.as < U<Expr> > ())); }
#line 2062 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 54: // block_expr: LBRACE expr RBRACE
#line 253 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                          { yylhs.value.as < U<BlockExpr> > () = std::make_unique<BlockExpr>(std::vector<U<Stmt>>{}, std::move(yystack_[1].value.as < U<Expr> > ())); }
#line 2068 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 55: // block_expr: LBRACE RBRACE
#line 254 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yylhs.value.as < U<BlockExpr> > () = std::make_unique<BlockExpr>(std::vector<U<Stmt>>{}, std::make_unique<Unit>()); }
#line 2074 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 56: // assignment: IDENTIFIER EQ expr
#line 258 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                         { yylhs.value.as < U<AssignExpr> > () = std::make_unique<AssignExpr>(yystack_[2].value.as < Token > ().string_value(), AssignOp::Eq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2080 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 57: // assignment: IDENTIFIER PLUS_EQ expr
#line 259 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                              { yylhs.value.as < U<AssignExpr> > () = std::make_unique<AssignExpr>(yystack_[2].value.as < Token > ().string_value(), AssignOp::PlusEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2086 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 58: // assignment: IDENTIFIER MIN_EQ expr
#line 260 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                             { yylhs.value.as < U<AssignExpr> > () = std::make_unique<AssignExpr>(yystack_[2].value.as < Token > ().string_value(), AssignOp::MinEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2092 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 59: // assignment: IDENTIFIER DIV_EQ expr
#line 261 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                             { yylhs.value.as < U<AssignExpr> > () = std::make_unique<AssignExpr>(yystack_[2].value.as < Token > ().string_value(), AssignOp::DivEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2098 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 60: // assignment: IDENTIFIER MUL_EQ expr
#line 262 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                             { yylhs.value.as < U<AssignExpr> > () = std::make_unique<AssignExpr>(yystack_[2].value.as < Token > ().string_value(), AssignOp::MulEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2104 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 61: // unary_op_expr: MINUS expr
#line 267 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                              { yylhs.value.as < U<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Negate, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2110 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 62: // unary_op_expr: STAR expr
#line 268 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                            { yylhs.value.as < U<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Deref, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2116 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 63: // unary_op_expr: BANG expr
#line 269 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                          { yylhs.value.as < U<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Not, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2122 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 64: // unary_op_expr: AMPERSAND expr
#line 270 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                               { yylhs.value.as < U<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Borrow, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2128 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 65: // unary_op_expr: AMPERSAND_MUT expr
#line 271 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                       { yylhs.value.as < U<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::MutBorrow, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2134 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 66: // bin_op_expr: expr PLUS expr
#line 275 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Plus, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2140 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 67: // bin_op_expr: expr MINUS expr
#line 276 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                      { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Min, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2146 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 68: // bin_op_expr: expr STAR expr
#line 277 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Mul, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2152 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 69: // bin_op_expr: expr SLASH expr
#line 278 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                      { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Div, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2158 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 70: // bin_op_expr: expr L_AND expr
#line 279 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                      { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::L_AND, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2164 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 71: // bin_op_expr: expr L_OR expr
#line 280 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::L_OR, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2170 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 72: // bin_op_expr: expr EQEQ expr
#line 281 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Eq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2176 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 73: // bin_op_expr: expr NE expr
#line 282 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::NEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2182 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 74: // bin_op_expr: expr LT expr
#line 283 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Lt, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2188 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 75: // bin_op_expr: expr GT expr
#line 284 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Gt, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2194 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 76: // bin_op_expr: expr GE expr
#line 285 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::GtEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2200 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 77: // bin_op_expr: expr LE expr
#line 286 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { yylhs.value.as < U<BinOpExpr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::LtEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2206 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 78: // literal: DEC_LITERAL
#line 290 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                  { yylhs.value.as < U<Literal> > () = Literal::make_int_lit(yystack_[0].value.as < Token > ().symbol);}
#line 2212 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 79: // literal: STR_LITERAL
#line 291 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                  { yylhs.value.as < U<Literal> > () = Literal::make_str_lit(yystack_[0].value.as < Token > ().symbol); }
#line 2218 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 80: // literal: FLOAT_LITERAL
#line 292 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                    { assert(1 && "How did we get here"); }
#line 2224 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 81: // literal: TRUE
#line 293 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           { yylhs.value.as < U<Literal> > () = Literal::make_bool_lit(yystack_[0].value.as < Token > ().symbol); }
#line 2230 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 82: // literal: FALSE
#line 294 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
            { yylhs.value.as < U<Literal> > () = Literal::make_bool_lit(yystack_[0].value.as < Token > ().symbol); }
#line 2236 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 83: // call_expr_args: call_expr_args COMMA expr
#line 299 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                { yystack_[2].value.as < std::vector<U<Expr>> > ().push_back(std::move(yystack_[0].value.as < U<Expr> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Expr>> > (), yystack_[2].value.as < std::vector<U<Expr>> > ()); }
#line 2242 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 84: // call_expr_args: expr
#line 300 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           { 
        auto vec = std::vector<U<Expr>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Expr> > ()));
        yylhs.value.as < std::vector<U<Expr>> > () = std::move(vec);
        }
#line 2252 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 85: // call_expr: IDENTIFIER LPAREN call_expr_args RPAREN
#line 308 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                              { yylhs.value.as < U<CallExpr> > () = std::make_unique<CallExpr>(yystack_[3].value.as < Token > ().string_value(), std::move(yystack_[1].value.as < std::vector<U<Expr>> > ())); }
#line 2258 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 86: // call_expr: IDENTIFIER LPAREN RPAREN
#line 309 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                               { yylhs.value.as < U<CallExpr> > () = std::make_unique<CallExpr>(yystack_[2].value.as < Token > ().string_value(), std::vector<U<Expr>>{}); }
#line 2264 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 87: // while_expr: WHILE expr block_expr
#line 312 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                            {yylhs.value.as < U<WhileLoop> > () = std::make_unique<WhileLoop>(std::move(yystack_[1].value.as < U<Expr> > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ())); }
#line 2270 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 88: // expr: expr_w_block
#line 316 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2276 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 89: // expr: expr_wo_block
#line 317 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                    { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2282 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 90: // expr_stmt: expr_w_block
#line 322 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                    { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2288 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 91: // expr_stmt: expr_wo_block SEMICOLON
#line 323 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[1].value.as < U<Expr> > ()); }
#line 2294 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 92: // expr_w_block: while_expr
#line 327 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<WhileLoop> > ()); }
#line 2300 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 93: // expr_w_block: if_expr
#line 328 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<IfElse> > ()); }
#line 2306 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 94: // expr_w_block: block_expr
#line 329 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<BlockExpr> > ()); }
#line 2312 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 95: // expr_wo_block: assignment
#line 333 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<AssignExpr> > ()); }
#line 2318 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 96: // expr_wo_block: bin_op_expr
#line 334 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<BinOpExpr> > ()); }
#line 2324 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 97: // expr_wo_block: IDENTIFIER
#line 335 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                  { yylhs.value.as < U<Expr> > () = std::make_unique<Identifier>(yystack_[0].value.as < Token > ().string_value()); }
#line 2330 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 98: // expr_wo_block: unary_op_expr
#line 336 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                {DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<UnaryOpExpr> > ()); }
#line 2336 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 99: // expr_wo_block: LPAREN expr RPAREN
#line 337 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                         { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[1].value.as < U<Expr> > ()); }
#line 2342 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 100: // expr_wo_block: LPAREN RPAREN
#line 338 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                    { yylhs.value.as < U<Expr> > () = std::make_unique<Unit>(); }
#line 2348 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 101: // expr_wo_block: call_expr
#line 339 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<CallExpr> > ()); }
#line 2354 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 102: // expr_wo_block: RETURN expr
#line 340 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                     { yylhs.value.as < U<Expr> > () = std::make_unique<Return>(std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2360 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 103: // expr_wo_block: BREAK expr
#line 341 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                    { yylhs.value.as < U<Expr> > () = std::make_unique<Break>(std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2366 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 104: // expr_wo_block: CONTINUE
#line 342 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                  { yylhs.value.as < U<Expr> > () = std::make_unique<Continue>(); }
#line 2372 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 105: // expr_wo_block: literal
#line 343 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Literal> > ()); }
#line 2378 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;


#line 2382 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -49;

  const signed char Parser::yytable_ninf_ = -89;

  const short
  Parser::yypact_[] =
  {
      72,   -49,    -3,     9,    26,   -49,   -49,     5,   -49,   -12,
     -49,   -49,    -9,   -24,   -49,   -49,   -49,   -30,   -49,    42,
      25,    11,    -4,   -49,     1,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,   -49,   -49,   -49,   -49,    13,   -49,   101,   -49,
     -49,   -49,    25,   -49,    39,   -49,   -49,   -49,   -49,   -49,
      22,    -4,   368,     7,   368,   368,   368,   368,   200,   242,
      41,   -49,   284,   -49,   368,   368,   -49,   -49,   158,    43,
     -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   426,
     -49,   449,    44,   -49,   -49,   368,   368,   368,   368,   368,
     326,    89,   368,   368,   -49,   495,   -49,   -49,    75,   -49,
     -49,   -49,   495,   -49,   -49,   -49,   -49,   -49,   -49,   401,
     -49,   -49,   -49,   -49,   472,   -49,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   -49,   -49,
     517,   517,   517,   517,   517,   -49,   -25,   517,    45,   -49,
      46,    62,   -49,   -49,    29,    29,    29,    29,    29,    29,
      40,    40,   -49,   -49,   553,   537,   368,   -49,    25,     6,
     -49,    28,   517,   -49,    84,   368,   -49,   -49,   -49,    56,
     140,   -49,   -49
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     6,     0,     0,     0,     5,     7,     0,     1,     0,
       3,    13,    33,    10,     4,    32,    12,     0,    15,     0,
       0,     0,    33,    11,     0,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,     0,     9,     0,     8,
      14,    17,     0,    51,     0,    78,    80,    79,    81,    82,
      97,    33,     0,     0,     0,     0,     0,     0,     0,     0,
     104,    55,     0,    18,     0,     0,    25,    28,     0,     0,
      19,    93,    94,    95,    98,    96,   105,   101,    92,     0,
      23,    90,    89,    16,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   104,     0,    88,    89,     0,    63,
      61,    62,     0,    20,   102,    21,   103,    22,   100,     0,
      64,    65,    52,    27,     0,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,    91,
      56,    57,    58,    60,    59,    86,     0,    84,    31,    87,
       0,    37,    99,    53,    72,    73,    74,    77,    75,    76,
      66,    67,    68,    69,    70,    71,     0,    85,     0,     0,
      29,     0,    83,    30,     0,     0,    36,    38,    39,     0,
       0,    35,    34
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -49,   -49,   -49,    10,   -49,   -49,   -49,   -49,    90,    47,
     -49,   -49,   -49,    63,   -49,   -48,   -41,   -21,   -49,   -49,
     -49,   -49,   -49,   -49,   -49,   -34,   -49,   -35,   -22
  };

  const unsigned char
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    66,     6,    21,    13,    17,    18,    67,
      68,    69,   159,    19,    70,    71,    37,    72,    73,    74,
      75,    76,   136,    77,    78,   104,    80,    96,    97
  };

  const short
  Parser::yytable_[] =
  {
      39,    83,    41,    81,    79,     7,    11,   164,    22,     8,
       5,     2,    15,   156,    10,    20,    82,    15,    95,    14,
      99,   100,   101,   102,    23,   106,    -2,     9,   109,   157,
     110,   111,   165,    81,   114,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    16,    82,    35,    85,     2,
      24,   130,   131,   132,   133,   134,   137,    42,    12,   106,
      98,   166,    38,   122,   123,   124,   125,    43,    57,    86,
      87,    88,    89,     1,   139,    90,   124,   125,    36,    38,
     140,   141,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,    84,     2,   107,   138,   115,   129,
     160,   158,    44,   161,    45,    46,    47,    48,    49,    50,
     169,   171,    40,   167,    91,   113,     0,   163,     0,     0,
       0,    51,   162,     0,     2,    52,    53,     0,     0,     0,
      54,   170,     0,     0,     0,     0,    55,    56,     0,     0,
     168,    57,     0,    58,    59,    60,     0,     0,     0,     0,
       0,     0,    38,    61,    62,     0,    63,     0,    64,    44,
      65,    45,    46,    47,    48,    49,    50,   116,   117,     0,
     118,   119,   120,   121,   122,   123,   124,   125,    51,     0,
       0,     2,    52,    53,     0,   126,   127,    54,     0,     0,
       0,     0,     0,    55,    56,   172,     0,     0,    57,     0,
      58,    59,    60,    45,    46,    47,    48,    49,    50,    38,
     112,    62,     0,    63,     0,    64,     0,    65,     0,     0,
       0,     0,     0,     0,    52,     0,     0,     0,     0,    54,
       0,     0,     0,     0,     0,    55,    56,     0,     0,     0,
      57,     0,    92,    93,    94,    45,    46,    47,    48,    49,
      50,    38,     0,    62,     0,   103,     0,    64,     0,    65,
       0,     0,     0,     0,     0,     0,    52,     0,     0,     0,
       0,    54,     0,     0,     0,     0,     0,    55,    56,     0,
       0,     0,    57,     0,    92,    93,    94,    45,    46,    47,
      48,    49,    50,    38,     0,    62,     0,   105,     0,    64,
       0,    65,     0,     0,     0,     0,     0,     0,    52,     0,
       0,     0,     0,    54,     0,     0,     0,     0,     0,    55,
      56,     0,     0,     0,    57,     0,    92,    93,    94,    45,
      46,    47,    48,    49,    50,    38,     0,    62,   108,     0,
       0,    64,     0,    65,     0,     0,     0,     0,     0,     0,
      52,     0,     0,     0,     0,    54,     0,     0,     0,     0,
       0,    55,    56,     0,     0,     0,    57,     0,    92,    93,
      94,    45,    46,    47,    48,    49,    50,    38,     0,    62,
     135,     0,     0,    64,     0,    65,     0,     0,     0,     0,
       0,     0,    52,     0,     0,     0,     0,    54,     0,     0,
       0,     0,     0,    55,    56,     0,     0,     0,    57,     0,
      92,    93,    94,     0,     0,     0,     0,     0,     0,    38,
       0,    62,     0,     0,     0,    64,     0,    65,   116,   117,
       0,   118,   119,   120,   121,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,   126,   127,     0,     0,
       0,     0,     0,   116,   117,   142,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     0,     0,     0,     0,     0,
       0,   126,   127,     0,     0,     0,   -88,   -88,   128,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,     0,     0,     0,
       0,     0,     0,     0,   -88,   -88,     0,     0,     0,   116,
     117,   -88,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,   126,   127,     0,
       0,     0,   116,   117,   143,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,     0,     0,     0,
     126,   127,     0,     0,   116,   117,    38,   118,   119,   120,
     121,   122,   123,   124,   125,     0,     0,     0,     0,     0,
       0,     0,   126,   127,   116,   117,     0,   118,   119,   120,
     121,   122,   123,   124,   125,     0,     0,     0,     0,     0,
     116,   117,   126,   118,   119,   120,   121,   122,   123,   124,
     125
  };

  const short
  Parser::yycheck_[] =
  {
      21,    42,     1,    38,    38,     8,     1,     1,    38,     0,
       0,    23,    21,    38,     4,    39,    38,    21,    52,     9,
      54,    55,    56,    57,    54,    59,     0,     1,    62,    54,
      64,    65,    26,    68,    68,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    54,    68,    22,    26,    23,
       8,    85,    86,    87,    88,    89,    90,    56,    53,    93,
      53,    55,    51,    34,    35,    36,    37,    54,    40,    47,
      48,    49,    50,     1,    95,    53,    36,    37,    53,    51,
       5,   102,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    55,    23,    55,     8,    55,    55,
      54,    56,     1,    41,     3,     4,     5,     6,     7,     8,
      26,    55,    22,   161,    51,    68,    -1,   158,    -1,    -1,
      -1,    20,   156,    -1,    23,    24,    25,    -1,    -1,    -1,
      29,   165,    -1,    -1,    -1,    -1,    35,    36,    -1,    -1,
     161,    40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    -1,    55,    -1,    57,     1,
      59,     3,     4,     5,     6,     7,     8,    27,    28,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    20,    -1,
      -1,    23,    24,    25,    -1,    45,    46,    29,    -1,    -1,
      -1,    -1,    -1,    35,    36,    55,    -1,    -1,    40,    -1,
      42,    43,    44,     3,     4,     5,     6,     7,     8,    51,
      52,    53,    -1,    55,    -1,    57,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,
      40,    -1,    42,    43,    44,     3,     4,     5,     6,     7,
       8,    51,    -1,    53,    -1,    55,    -1,    57,    -1,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    35,    36,    -1,
      -1,    -1,    40,    -1,    42,    43,    44,     3,     4,     5,
       6,     7,     8,    51,    -1,    53,    -1,    55,    -1,    57,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    35,
      36,    -1,    -1,    -1,    40,    -1,    42,    43,    44,     3,
       4,     5,     6,     7,     8,    51,    -1,    53,    54,    -1,
      -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    35,    36,    -1,    -1,    -1,    40,    -1,    42,    43,
      44,     3,     4,     5,     6,     7,     8,    51,    -1,    53,
      54,    -1,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    35,    36,    -1,    -1,    -1,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    53,    -1,    -1,    -1,    57,    -1,    59,    27,    28,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    -1,    -1,
      -1,    -1,    -1,    27,    28,    54,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    46,    -1,    -1,    -1,    27,    28,    52,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    -1,    -1,    -1,    27,
      28,    52,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    -1,
      -1,    -1,    27,    28,    52,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    -1,    -1,    27,    28,    51,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    46,    27,    28,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      27,    28,    45,    30,    31,    32,    33,    34,    35,    36,
      37
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     1,    23,    77,    78,    79,    80,     8,     0,     1,
      79,     1,    53,    82,    79,    21,    54,    83,    84,    89,
      39,    81,    38,    54,     8,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    22,    53,    92,    51,    93,
      84,     1,    56,    54,     1,     3,     4,     5,     6,     7,
       8,    20,    24,    25,    29,    35,    36,    40,    42,    43,
      44,    52,    53,    55,    57,    59,    79,    85,    86,    87,
      90,    91,    93,    94,    95,    96,    97,    99,   100,   101,
     102,   103,   104,    92,    55,    26,    47,    48,    49,    50,
      53,    89,    42,    43,    44,   101,   103,   104,    53,   101,
     101,   101,   101,    55,   101,    55,   101,    55,    54,   101,
     101,   101,    52,    85,   101,    55,    27,    28,    30,    31,
      32,    33,    34,    35,    36,    37,    45,    46,    52,    55,
     101,   101,   101,   101,   101,    54,    98,   101,     8,    93,
       5,    93,    54,    52,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,    38,    54,    56,    88,
      54,    41,   101,    92,     1,    26,    55,    91,    93,    26,
     101,    55,    55
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    76,    77,    78,    78,    78,    78,    79,    80,    81,
      81,    82,    82,    82,    83,    83,    84,    84,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    86,    86,    87,
      88,    88,    89,    89,    90,    90,    90,    91,    91,    91,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    93,    93,    93,    93,    94,    94,    94,    94,
      94,    95,    95,    95,    95,    95,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    97,    97,
      97,    97,    97,    98,    98,    99,    99,   100,   101,   101,
     102,   102,   103,   103,   103,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     1,     1,     1,     5,     2,
       0,     3,     2,     1,     3,     1,     4,     3,     1,     1,
       2,     2,     2,     1,     2,     1,     2,     2,     1,     4,
       2,     0,     1,     0,     7,     7,     5,     3,     5,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     4,     3,     2,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     3,     1,     4,     3,     3,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     1,     2,     2,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "DEC_LITERAL",
  "FLOAT_LITERAL", "STR_LITERAL", "TRUE", "FALSE", "IDENTIFIER",
  "UNDERSCORE", "I8", "I16", "I32", "I64", "ISIZE", "U8", "U16", "U32",
  "U64", "USIZE", "LET", "MUT", "BOOL", "FN", "WHILE", "PRINT_LN", "EQ",
  "EQEQ", "NE", "BANG", "LT", "LE", "GT", "GE", "PLUS", "MINUS", "STAR",
  "SLASH", "COMMA", "ARROW", "IF", "ELSE", "RETURN", "BREAK", "CONTINUE",
  "L_AND", "L_OR", "PLUS_EQ", "MIN_EQ", "MUL_EQ", "DIV_EQ", "LBRACE",
  "RBRACE", "LPAREN", "RPAREN", "SEMICOLON", "COLON", "AMPERSAND", "OR",
  "AMPERSAND_MUT", "MOD_EQ", "BIT_AND_EQ", "BIT_OR_EQ", "BIT_XOR_EQ",
  "SHL_EQ", "SHR_EQ", "MOD", "UMINUS", "DEREF", "NOT", "REF", "REF_MUT",
  "CALL_INDEX", "UNARY", "BIN_OP", "CONTROL_FLOW", "$accept", "program",
  "item_list", "item", "function_decl", "func_ret_type", "func_decl_args",
  "func_arg_list", "func_arg", "stmt", "stmt_list", "print_ln",
  "type_decl", "opt_mut", "let", "if_expr", "type", "block_expr",
  "assignment", "unary_op_expr", "bin_op_expr", "literal",
  "call_expr_args", "call_expr", "while_expr", "expr", "expr_stmt",
  "expr_w_block", "expr_wo_block", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   126,   126,   130,   132,   133,   137,   141,   146,   153,
     154,   159,   160,   161,   165,   166,   170,   171,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   186,   187,   195,
     199,   200,   204,   205,   209,   211,   215,   221,   222,   223,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   251,   252,   253,   254,   258,   259,   260,   261,
     262,   267,   268,   269,   270,   271,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   290,   291,
     292,   293,   294,   299,   300,   308,   309,   312,   316,   317,
     322,   323,   327,   328,   329,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
    };
    // Last valid token kind.
    const int code_max = 330;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
} // mr
#line 3114 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"

#line 346 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"


namespace mr
{
    
    void Parser::error(const Parser::location_type &loc, const std::string &message)
    {
        // i don't care about error's of bison
        std::cerr << "Error in " << this->input_file_name << ":" << loc.end.line << ":" << loc.end.column
            <<":\n"
            << message << std::endl;
    }
}
