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
#line 39 "src/parser/yaccfile.yy"

#include <string>
#include <variant>
#include <cstddef>
#include <memory>
#include <assert.h>
#include "lexer/lexer.hpp"
#include "driver/mr_driver.hpp"

    #define yylex lexer.yylex
    #define DEFAULT_ACTION(to, from) do { to = std::move(from);} while(0)

#line 52 "yaccfile.tab.cc"




#include "yaccfile.tab.hh"




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

#line 5 "src/parser/yaccfile.yy"
namespace mr {
#line 152 "yaccfile.tab.cc"

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
      case symbol_kind::S_DOT: // DOT
        value.copy< Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.copy< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.copy< U<Ast> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.copy< U<BlockExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.copy< U<CallExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
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

      case symbol_kind::S_tuple_index_expr: // tuple_index_expr
        value.copy< U<TupleIndexExpr> > (YY_MOVE (that.value));
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

      case symbol_kind::S_type_list: // type_list
        value.copy< std::vector<Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
      case symbol_kind::S_expr_list: // expr_list
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
      case symbol_kind::S_DOT: // DOT
        value.move< Token > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.move< Type > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_program: // program
        value.move< U<Ast> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.move< U<BlockExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.move< U<CallExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
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

      case symbol_kind::S_tuple_index_expr: // tuple_index_expr
        value.move< U<TupleIndexExpr> > (YY_MOVE (s.value));
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

      case symbol_kind::S_type_list: // type_list
        value.move< std::vector<Type> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
      case symbol_kind::S_expr_list: // expr_list
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
      case symbol_kind::S_DOT: // DOT
        value.YY_MOVE_OR_COPY< Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< U<Ast> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.YY_MOVE_OR_COPY< U<BlockExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.YY_MOVE_OR_COPY< U<CallExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
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

      case symbol_kind::S_tuple_index_expr: // tuple_index_expr
        value.YY_MOVE_OR_COPY< U<TupleIndexExpr> > (YY_MOVE (that.value));
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

      case symbol_kind::S_type_list: // type_list
        value.YY_MOVE_OR_COPY< std::vector<Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
      case symbol_kind::S_expr_list: // expr_list
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
      case symbol_kind::S_DOT: // DOT
        value.move< Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.move< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< U<Ast> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.move< U<BlockExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.move< U<CallExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
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

      case symbol_kind::S_tuple_index_expr: // tuple_index_expr
        value.move< U<TupleIndexExpr> > (YY_MOVE (that.value));
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

      case symbol_kind::S_type_list: // type_list
        value.move< std::vector<Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
      case symbol_kind::S_expr_list: // expr_list
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
      case symbol_kind::S_DOT: // DOT
        value.copy< Token > (that.value);
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.copy< Type > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< U<Ast> > (that.value);
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.copy< U<BlockExpr> > (that.value);
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.copy< U<CallExpr> > (that.value);
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
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

      case symbol_kind::S_tuple_index_expr: // tuple_index_expr
        value.copy< U<TupleIndexExpr> > (that.value);
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

      case symbol_kind::S_type_list: // type_list
        value.copy< std::vector<Type> > (that.value);
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
      case symbol_kind::S_expr_list: // expr_list
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
      case symbol_kind::S_DOT: // DOT
        value.move< Token > (that.value);
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.move< Type > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< U<Ast> > (that.value);
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.move< U<BlockExpr> > (that.value);
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.move< U<CallExpr> > (that.value);
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
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

      case symbol_kind::S_tuple_index_expr: // tuple_index_expr
        value.move< U<TupleIndexExpr> > (that.value);
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

      case symbol_kind::S_type_list: // type_list
        value.move< std::vector<Type> > (that.value);
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
      case symbol_kind::S_expr_list: // expr_list
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
      case symbol_kind::S_DOT: // DOT
        yylhs.value.emplace< Token > ();
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        yylhs.value.emplace< Type > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< U<Ast> > ();
        break;

      case symbol_kind::S_block_expr: // block_expr
        yylhs.value.emplace< U<BlockExpr> > ();
        break;

      case symbol_kind::S_call_expr: // call_expr
        yylhs.value.emplace< U<CallExpr> > ();
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
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

      case symbol_kind::S_tuple_index_expr: // tuple_index_expr
        yylhs.value.emplace< U<TupleIndexExpr> > ();
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

      case symbol_kind::S_type_list: // type_list
        yylhs.value.emplace< std::vector<Type> > ();
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
      case symbol_kind::S_expr_list: // expr_list
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
#line 130 "src/parser/yaccfile.yy"
                { driver.set_ast(std::make_unique<Ast>(std::move(yystack_[0].value.as < std::vector<U<Item>> > ()))); }
#line 1764 "yaccfile.tab.cc"
    break;

  case 3: // item_list: item_list item
#line 134 "src/parser/yaccfile.yy"
                     {yystack_[1].value.as < std::vector<U<Item>> > ().push_back(std::move(yystack_[0].value.as < U<Item> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Item>> > (), yystack_[1].value.as < std::vector<U<Item>> > ());}
#line 1770 "yaccfile.tab.cc"
    break;

  case 4: // item_list: item_list error item
#line 136 "src/parser/yaccfile.yy"
                           {yystack_[2].value.as < std::vector<U<Item>> > ().push_back(std::move(yystack_[0].value.as < U<Item> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Item>> > (), yystack_[2].value.as < std::vector<U<Item>> > ());}
#line 1776 "yaccfile.tab.cc"
    break;

  case 5: // item_list: item
#line 137 "src/parser/yaccfile.yy"
           {
        auto vec = std::vector<U<Item>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Item> > ()));
        yylhs.value.as < std::vector<U<Item>> > () = std::move(vec) ;}
#line 1785 "yaccfile.tab.cc"
    break;

  case 6: // item_list: error
#line 141 "src/parser/yaccfile.yy"
            { std::cerr << "Expected Item\n"; }
#line 1791 "yaccfile.tab.cc"
    break;

  case 7: // item: function_decl
#line 145 "src/parser/yaccfile.yy"
                  { DEFAULT_ACTION(yylhs.value.as < U<Item> > (), yystack_[0].value.as < U<FunDecl> > ()); }
#line 1797 "yaccfile.tab.cc"
    break;

  case 8: // function_decl: FN IDENTIFIER func_decl_args func_ret_type block_expr
#line 151 "src/parser/yaccfile.yy"
    { 
        yylhs.value.as < U<FunDecl> > () = FunDecl::make_unique(yystack_[3].value.as < Token > ().string_value(), std::move(yystack_[2].value.as < std::vector<FunArg> > ()), std::move(yystack_[1].value.as < Type > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ()));
    }
#line 1805 "yaccfile.tab.cc"
    break;

  case 9: // func_ret_type: ARROW type
#line 157 "src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < Type > (), yystack_[0].value.as < Type > ()); }
#line 1811 "yaccfile.tab.cc"
    break;

  case 10: // func_ret_type: %empty
#line 158 "src/parser/yaccfile.yy"
      { yylhs.value.as < Type > () = Type(); }
#line 1817 "yaccfile.tab.cc"
    break;

  case 11: // func_decl_args: LPAREN func_arg_list RPAREN
#line 163 "src/parser/yaccfile.yy"
                                  {yylhs.value.as < std::vector<FunArg> > () = std::move(yystack_[1].value.as < std::vector<FunArg> > ());}
#line 1823 "yaccfile.tab.cc"
    break;

  case 12: // func_decl_args: LPAREN RPAREN
#line 164 "src/parser/yaccfile.yy"
                    { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{};}
#line 1829 "yaccfile.tab.cc"
    break;

  case 13: // func_decl_args: error
#line 165 "src/parser/yaccfile.yy"
            { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{};}
#line 1835 "yaccfile.tab.cc"
    break;

  case 14: // func_arg_list: func_arg_list COMMA func_arg
#line 169 "src/parser/yaccfile.yy"
                                   { yystack_[2].value.as < std::vector<FunArg> > ().push_back(std::move(yystack_[0].value.as < FunArg > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<FunArg> > (), yystack_[2].value.as < std::vector<FunArg> > ());}
#line 1841 "yaccfile.tab.cc"
    break;

  case 15: // func_arg_list: func_arg
#line 170 "src/parser/yaccfile.yy"
               { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{}; yylhs.value.as < std::vector<FunArg> > ().push_back(std::move(yystack_[0].value.as < FunArg > ())); }
#line 1847 "yaccfile.tab.cc"
    break;

  case 16: // func_arg: opt_mut IDENTIFIER COLON type
#line 174 "src/parser/yaccfile.yy"
                                    { yylhs.value.as < FunArg > () = FunArg{yystack_[2].value.as < Token > ().string_value(), std::move(yystack_[0].value.as < Type > ()), yystack_[3].value.as < bool > ()}; }
#line 1853 "yaccfile.tab.cc"
    break;

  case 17: // func_arg: opt_mut IDENTIFIER error
#line 175 "src/parser/yaccfile.yy"
                               { std::cerr << "Expected type declaration\n";}
#line 1859 "yaccfile.tab.cc"
    break;

  case 18: // stmt: SEMICOLON
#line 178 "src/parser/yaccfile.yy"
                {yylhs.value.as < U<Stmt> > () = std::make_unique<EmptyStmt>();}
#line 1865 "yaccfile.tab.cc"
    break;

  case 19: // stmt: let
#line 179 "src/parser/yaccfile.yy"
          { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[0].value.as < U<LetStmt> > ()); }
#line 1871 "yaccfile.tab.cc"
    break;

  case 20: // stmt: RETURN SEMICOLON
#line 180 "src/parser/yaccfile.yy"
                       {  yylhs.value.as < U<Stmt> > () = std::make_unique<Return>(std::make_unique<Unit>()); }
#line 1877 "yaccfile.tab.cc"
    break;

  case 21: // stmt: BREAK SEMICOLON
#line 181 "src/parser/yaccfile.yy"
                      {  yylhs.value.as < U<Stmt> > () = std::make_unique<Break>(std::make_unique<Unit>()); }
#line 1883 "yaccfile.tab.cc"
    break;

  case 22: // stmt: CONTINUE SEMICOLON
#line 182 "src/parser/yaccfile.yy"
                         {  yylhs.value.as < U<Stmt> > () = std::make_unique<Continue>(); }
#line 1889 "yaccfile.tab.cc"
    break;

  case 23: // stmt: expr_stmt
#line 183 "src/parser/yaccfile.yy"
                { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[0].value.as < U<Expr> > ());}
#line 1895 "yaccfile.tab.cc"
    break;

  case 24: // stmt: print_ln SEMICOLON
#line 184 "src/parser/yaccfile.yy"
                         { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[1].value.as < U<PrintLn> > ());}
#line 1901 "yaccfile.tab.cc"
    break;

  case 25: // stmt: item
#line 185 "src/parser/yaccfile.yy"
           { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[0].value.as < U<Item> > ()); }
#line 1907 "yaccfile.tab.cc"
    break;

  case 26: // stmt_list: stmt_list stmt
#line 189 "src/parser/yaccfile.yy"
                     { yystack_[1].value.as < std::vector<U<Stmt>> > ().push_back(std::move(yystack_[0].value.as < U<Stmt> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Stmt>> > (), yystack_[1].value.as < std::vector<U<Stmt>> > ()); }
#line 1913 "yaccfile.tab.cc"
    break;

  case 27: // stmt_list: stmt
#line 190 "src/parser/yaccfile.yy"
           {
        auto vec = std::vector<U<Stmt>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Stmt> > ()));
        yylhs.value.as < std::vector<U<Stmt>> > () = std::move(vec); 
      }
#line 1923 "yaccfile.tab.cc"
    break;

  case 28: // print_ln: PRINT_LN LPAREN STR_LITERAL RPAREN
#line 198 "src/parser/yaccfile.yy"
                                         { yylhs.value.as < U<PrintLn> > () = std::make_unique<PrintLn>(yystack_[1].value.as < Token > ().string_value()); }
#line 1929 "yaccfile.tab.cc"
    break;

  case 29: // type_decl: COLON type
#line 202 "src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < std::optional<Type> > (), yystack_[0].value.as < Type > ()); }
#line 1935 "yaccfile.tab.cc"
    break;

  case 30: // type_decl: COLON error
#line 203 "src/parser/yaccfile.yy"
                  { yylhs.value.as < std::optional<Type> > () = Type(); printf("failure"); }
#line 1941 "yaccfile.tab.cc"
    break;

  case 31: // type_decl: %empty
#line 204 "src/parser/yaccfile.yy"
      { yylhs.value.as < std::optional<Type> > () = {}; }
#line 1947 "yaccfile.tab.cc"
    break;

  case 32: // opt_mut: MUT
#line 208 "src/parser/yaccfile.yy"
         { yylhs.value.as < bool > () = true; }
#line 1953 "yaccfile.tab.cc"
    break;

  case 33: // opt_mut: %empty
#line 209 "src/parser/yaccfile.yy"
         { yylhs.value.as < bool > () = false; }
#line 1959 "yaccfile.tab.cc"
    break;

  case 34: // let: LET opt_mut IDENTIFIER type_decl EQ expr SEMICOLON
#line 214 "src/parser/yaccfile.yy"
      {yylhs.value.as < U<LetStmt> > () = LetStmt::make_unique_init(yystack_[4].value.as < Token > ().string_value(), std::move(yystack_[3].value.as < std::optional<Type> > ()), std::move(yystack_[1].value.as < U<Expr> > ()), yystack_[5].value.as < bool > ());}
#line 1965 "yaccfile.tab.cc"
    break;

  case 35: // let: LET opt_mut IDENTIFIER type_decl error EQ SEMICOLON
#line 216 "src/parser/yaccfile.yy"
      {
        yylhs.value.as < U<LetStmt> > () = LetStmt::make_unique_init(yystack_[4].value.as < Token > ().string_value(), std::move(yystack_[3].value.as < std::optional<Type> > ()), std::unique_ptr<Expr>(nullptr), yystack_[5].value.as < bool > ()); 
      }
#line 1973 "yaccfile.tab.cc"
    break;

  case 36: // let: LET opt_mut IDENTIFIER type_decl SEMICOLON
#line 219 "src/parser/yaccfile.yy"
                                                 {
        yylhs.value.as < U<LetStmt> > () = LetStmt::make_unique_decl(yystack_[2].value.as < Token > ().string_value(), std::move(yystack_[1].value.as < std::optional<Type> > ()), yystack_[3].value.as < bool > ());
    }
#line 1981 "yaccfile.tab.cc"
    break;

  case 37: // if_expr: IF expr block_expr
#line 225 "src/parser/yaccfile.yy"
                         { yylhs.value.as < U<IfElse> > () = std::make_unique<IfElse>(std::move(yystack_[1].value.as < U<Expr> > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ())); }
#line 1987 "yaccfile.tab.cc"
    break;

  case 38: // if_expr: IF expr block_expr ELSE if_expr
#line 226 "src/parser/yaccfile.yy"
                                      {yylhs.value.as < U<IfElse> > () = std::make_unique<IfElse>(std::move(yystack_[3].value.as < U<Expr> > ()), std::move(yystack_[2].value.as < U<BlockExpr> > ()), std::move(yystack_[0].value.as < U<IfElse> > ())); }
#line 1993 "yaccfile.tab.cc"
    break;

  case 39: // if_expr: IF expr block_expr ELSE block_expr
#line 227 "src/parser/yaccfile.yy"
                                         {yylhs.value.as < U<IfElse> > () = std::make_unique<IfElse>(std::move(yystack_[3].value.as < U<Expr> > ()), std::move(yystack_[2].value.as < U<BlockExpr> > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ())); }
#line 1999 "yaccfile.tab.cc"
    break;

  case 40: // type_list: type_list COMMA type
#line 238 "src/parser/yaccfile.yy"
                           {yylhs.value.as < std::vector<Type> > () = std::move(yystack_[2].value.as < std::vector<Type> > ()); yylhs.value.as < std::vector<Type> > ().push_back(std::move(yystack_[0].value.as < Type > ()));}
#line 2005 "yaccfile.tab.cc"
    break;

  case 41: // type_list: type
#line 239 "src/parser/yaccfile.yy"
           {yylhs.value.as < std::vector<Type> > () = std::vector<Type>(); yylhs.value.as < std::vector<Type> > ().push_back(std::move(yystack_[0].value.as < Type > ()));}
#line 2011 "yaccfile.tab.cc"
    break;

  case 42: // type: I8
#line 243 "src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::I8); }
#line 2017 "yaccfile.tab.cc"
    break;

  case 43: // type: I16
#line 244 "src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::I16); }
#line 2023 "yaccfile.tab.cc"
    break;

  case 44: // type: I32
#line 245 "src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::I32); }
#line 2029 "yaccfile.tab.cc"
    break;

  case 45: // type: I64
#line 246 "src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::I64); }
#line 2035 "yaccfile.tab.cc"
    break;

  case 46: // type: ISIZE
#line 247 "src/parser/yaccfile.yy"
            { yylhs.value.as < Type > () = Type(primitive_type::ISIZE); }
#line 2041 "yaccfile.tab.cc"
    break;

  case 47: // type: U8
#line 248 "src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::U8); }
#line 2047 "yaccfile.tab.cc"
    break;

  case 48: // type: U16
#line 249 "src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::U16); }
#line 2053 "yaccfile.tab.cc"
    break;

  case 49: // type: U32
#line 250 "src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::U32); }
#line 2059 "yaccfile.tab.cc"
    break;

  case 50: // type: U64
#line 251 "src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::U64); }
#line 2065 "yaccfile.tab.cc"
    break;

  case 51: // type: USIZE
#line 252 "src/parser/yaccfile.yy"
            { yylhs.value.as < Type > () = Type(primitive_type::USIZE); }
#line 2071 "yaccfile.tab.cc"
    break;

  case 52: // type: BOOL
#line 253 "src/parser/yaccfile.yy"
           { yylhs.value.as < Type > () = Type(primitive_type::BOOL); }
#line 2077 "yaccfile.tab.cc"
    break;

  case 53: // type: LPAREN type_list RPAREN
#line 254 "src/parser/yaccfile.yy"
                              { yylhs.value.as < Type > () = Type(std::move(yystack_[1].value.as < std::vector<Type> > ()));}
#line 2083 "yaccfile.tab.cc"
    break;

  case 54: // type: LPAREN RPAREN
#line 255 "src/parser/yaccfile.yy"
                     { yylhs.value.as < Type > () = Type(); }
#line 2089 "yaccfile.tab.cc"
    break;

  case 55: // block_expr: LBRACE stmt_list RBRACE
#line 261 "src/parser/yaccfile.yy"
                              { yylhs.value.as < U<BlockExpr> > () = std::make_unique<BlockExpr>(std::move(yystack_[1].value.as < std::vector<U<Stmt>> > ()), std::make_unique<Unit>()); }
#line 2095 "yaccfile.tab.cc"
    break;

  case 56: // block_expr: LBRACE stmt_list expr RBRACE
#line 262 "src/parser/yaccfile.yy"
                                    { yylhs.value.as < U<BlockExpr> > () = std::make_unique<BlockExpr>(std::move(yystack_[2].value.as < std::vector<U<Stmt>> > ()), std::move(yystack_[1].value.as < U<Expr> > ())); }
#line 2101 "yaccfile.tab.cc"
    break;

  case 57: // block_expr: LBRACE expr RBRACE
#line 263 "src/parser/yaccfile.yy"
                          { yylhs.value.as < U<BlockExpr> > () = std::make_unique<BlockExpr>(std::vector<U<Stmt>>{}, std::move(yystack_[1].value.as < U<Expr> > ())); }
#line 2107 "yaccfile.tab.cc"
    break;

  case 58: // block_expr: LBRACE RBRACE
#line 264 "src/parser/yaccfile.yy"
                     { yylhs.value.as < U<BlockExpr> > () = std::make_unique<BlockExpr>(std::vector<U<Stmt>>{}, std::make_unique<Unit>()); }
#line 2113 "yaccfile.tab.cc"
    break;

  case 59: // unary_op_expr: MINUS expr
#line 268 "src/parser/yaccfile.yy"
                              { yylhs.value.as < U<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Negate, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2119 "yaccfile.tab.cc"
    break;

  case 60: // unary_op_expr: STAR expr
#line 269 "src/parser/yaccfile.yy"
                            { yylhs.value.as < U<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Deref, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2125 "yaccfile.tab.cc"
    break;

  case 61: // unary_op_expr: BANG expr
#line 270 "src/parser/yaccfile.yy"
                          { yylhs.value.as < U<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Not, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2131 "yaccfile.tab.cc"
    break;

  case 62: // unary_op_expr: AMPERSAND expr
#line 271 "src/parser/yaccfile.yy"
                               { yylhs.value.as < U<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Borrow, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2137 "yaccfile.tab.cc"
    break;

  case 63: // unary_op_expr: AMPERSAND_MUT expr
#line 272 "src/parser/yaccfile.yy"
                                       { yylhs.value.as < U<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::MutBorrow, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2143 "yaccfile.tab.cc"
    break;

  case 64: // bin_op_expr: expr PLUS expr
#line 276 "src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Plus, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2149 "yaccfile.tab.cc"
    break;

  case 65: // bin_op_expr: expr MINUS expr
#line 277 "src/parser/yaccfile.yy"
                      { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Min, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2155 "yaccfile.tab.cc"
    break;

  case 66: // bin_op_expr: expr STAR expr
#line 278 "src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Mul, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2161 "yaccfile.tab.cc"
    break;

  case 67: // bin_op_expr: expr SLASH expr
#line 279 "src/parser/yaccfile.yy"
                      { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Div, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2167 "yaccfile.tab.cc"
    break;

  case 68: // bin_op_expr: expr L_AND expr
#line 280 "src/parser/yaccfile.yy"
                      { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::L_AND, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2173 "yaccfile.tab.cc"
    break;

  case 69: // bin_op_expr: expr L_OR expr
#line 281 "src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::L_OR, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2179 "yaccfile.tab.cc"
    break;

  case 70: // bin_op_expr: expr EQEQ expr
#line 282 "src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Eq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2185 "yaccfile.tab.cc"
    break;

  case 71: // bin_op_expr: expr NE expr
#line 283 "src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::NEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2191 "yaccfile.tab.cc"
    break;

  case 72: // bin_op_expr: expr LT expr
#line 284 "src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Lt, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2197 "yaccfile.tab.cc"
    break;

  case 73: // bin_op_expr: expr GT expr
#line 285 "src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Gt, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2203 "yaccfile.tab.cc"
    break;

  case 74: // bin_op_expr: expr GE expr
#line 286 "src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::GtEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2209 "yaccfile.tab.cc"
    break;

  case 75: // bin_op_expr: expr LE expr
#line 287 "src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::LtEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2215 "yaccfile.tab.cc"
    break;

  case 76: // bin_op_expr: expr EQ expr
#line 289 "src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = std::make_unique<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::Eq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2221 "yaccfile.tab.cc"
    break;

  case 77: // bin_op_expr: expr PLUS_EQ expr
#line 290 "src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = std::make_unique<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::PlusEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2227 "yaccfile.tab.cc"
    break;

  case 78: // bin_op_expr: expr MIN_EQ expr
#line 291 "src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = std::make_unique<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::MinEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2233 "yaccfile.tab.cc"
    break;

  case 79: // bin_op_expr: expr DIV_EQ expr
#line 292 "src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = std::make_unique<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::DivEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2239 "yaccfile.tab.cc"
    break;

  case 80: // bin_op_expr: expr MUL_EQ expr
#line 293 "src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = std::make_unique<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::MulEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2245 "yaccfile.tab.cc"
    break;

  case 81: // literal: DEC_LITERAL
#line 297 "src/parser/yaccfile.yy"
                  { yylhs.value.as < U<Literal> > () = Literal::make_int_lit(yystack_[0].value.as < Token > ().symbol);}
#line 2251 "yaccfile.tab.cc"
    break;

  case 82: // literal: STR_LITERAL
#line 298 "src/parser/yaccfile.yy"
                  { yylhs.value.as < U<Literal> > () = Literal::make_str_lit(yystack_[0].value.as < Token > ().symbol); }
#line 2257 "yaccfile.tab.cc"
    break;

  case 83: // literal: FLOAT_LITERAL
#line 299 "src/parser/yaccfile.yy"
                    { assert(1 && "How did we get here"); }
#line 2263 "yaccfile.tab.cc"
    break;

  case 84: // literal: TRUE
#line 300 "src/parser/yaccfile.yy"
           { yylhs.value.as < U<Literal> > () = Literal::make_bool_lit(yystack_[0].value.as < Token > ().symbol); }
#line 2269 "yaccfile.tab.cc"
    break;

  case 85: // literal: FALSE
#line 301 "src/parser/yaccfile.yy"
            { yylhs.value.as < U<Literal> > () = Literal::make_bool_lit(yystack_[0].value.as < Token > ().symbol); }
#line 2275 "yaccfile.tab.cc"
    break;

  case 86: // call_expr_args: call_expr_args COMMA expr
#line 306 "src/parser/yaccfile.yy"
                                { yystack_[2].value.as < std::vector<U<Expr>> > ().push_back(std::move(yystack_[0].value.as < U<Expr> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Expr>> > (), yystack_[2].value.as < std::vector<U<Expr>> > ()); }
#line 2281 "yaccfile.tab.cc"
    break;

  case 87: // call_expr_args: expr
#line 307 "src/parser/yaccfile.yy"
           { 
        auto vec = std::vector<U<Expr>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Expr> > ()));
        yylhs.value.as < std::vector<U<Expr>> > () = std::move(vec);
        }
#line 2291 "yaccfile.tab.cc"
    break;

  case 88: // call_expr: IDENTIFIER LPAREN call_expr_args RPAREN
#line 315 "src/parser/yaccfile.yy"
                                              { yylhs.value.as < U<CallExpr> > () = std::make_unique<CallExpr>(yystack_[3].value.as < Token > ().string_value(), std::move(yystack_[1].value.as < std::vector<U<Expr>> > ())); }
#line 2297 "yaccfile.tab.cc"
    break;

  case 89: // call_expr: IDENTIFIER LPAREN RPAREN
#line 316 "src/parser/yaccfile.yy"
                               { yylhs.value.as < U<CallExpr> > () = std::make_unique<CallExpr>(yystack_[2].value.as < Token > ().string_value(), std::vector<U<Expr>>{}); }
#line 2303 "yaccfile.tab.cc"
    break;

  case 90: // while_expr: WHILE expr block_expr
#line 319 "src/parser/yaccfile.yy"
                            {yylhs.value.as < U<WhileLoop> > () = std::make_unique<WhileLoop>(std::move(yystack_[1].value.as < U<Expr> > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ())); }
#line 2309 "yaccfile.tab.cc"
    break;

  case 91: // tuple_index_expr: expr DOT literal
#line 323 "src/parser/yaccfile.yy"
                       { yylhs.value.as < U<TupleIndexExpr> > () = std::make_unique<TupleIndexExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), std::move(yystack_[0].value.as < U<Literal> > ()));}
#line 2315 "yaccfile.tab.cc"
    break;

  case 92: // expr: expr_w_block
#line 328 "src/parser/yaccfile.yy"
                   { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2321 "yaccfile.tab.cc"
    break;

  case 93: // expr: expr_wo_block
#line 329 "src/parser/yaccfile.yy"
                    { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2327 "yaccfile.tab.cc"
    break;

  case 94: // expr_list: expr_list COMMA expr
#line 333 "src/parser/yaccfile.yy"
                           { yystack_[2].value.as < std::vector<U<Expr>> > ().push_back(std::move(yystack_[0].value.as < U<Expr> > ())); yylhs.value.as < std::vector<U<Expr>> > () = std::move(yystack_[2].value.as < std::vector<U<Expr>> > ());}
#line 2333 "yaccfile.tab.cc"
    break;

  case 95: // expr_list: expr
#line 334 "src/parser/yaccfile.yy"
           {yylhs.value.as < std::vector<U<Expr>> > () = std::vector<U<Expr>>(); yylhs.value.as < std::vector<U<Expr>> > ().push_back(std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2339 "yaccfile.tab.cc"
    break;

  case 96: // expr_stmt: expr_w_block
#line 338 "src/parser/yaccfile.yy"
                    { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2345 "yaccfile.tab.cc"
    break;

  case 97: // expr_stmt: expr_wo_block SEMICOLON
#line 339 "src/parser/yaccfile.yy"
                              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[1].value.as < U<Expr> > ()); }
#line 2351 "yaccfile.tab.cc"
    break;

  case 98: // expr_w_block: while_expr
#line 343 "src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<WhileLoop> > ()); }
#line 2357 "yaccfile.tab.cc"
    break;

  case 99: // expr_w_block: if_expr
#line 344 "src/parser/yaccfile.yy"
              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<IfElse> > ()); }
#line 2363 "yaccfile.tab.cc"
    break;

  case 100: // expr_w_block: block_expr
#line 345 "src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<BlockExpr> > ()); }
#line 2369 "yaccfile.tab.cc"
    break;

  case 101: // expr_wo_block: LPAREN expr RPAREN
#line 348 "src/parser/yaccfile.yy"
                         { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[1].value.as < U<Expr> > ()); }
#line 2375 "yaccfile.tab.cc"
    break;

  case 102: // expr_wo_block: bin_op_expr
#line 349 "src/parser/yaccfile.yy"
                              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ()); }
#line 2381 "yaccfile.tab.cc"
    break;

  case 103: // expr_wo_block: tuple_index_expr
#line 350 "src/parser/yaccfile.yy"
                                          { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<TupleIndexExpr> > ()); }
#line 2387 "yaccfile.tab.cc"
    break;

  case 104: // expr_wo_block: IDENTIFIER
#line 351 "src/parser/yaccfile.yy"
                            { yylhs.value.as < U<Expr> > () = std::make_unique<Identifier>(yystack_[0].value.as < Token > ().string_value()); }
#line 2393 "yaccfile.tab.cc"
    break;

  case 105: // expr_wo_block: unary_op_expr
#line 352 "src/parser/yaccfile.yy"
                                {DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<UnaryOpExpr> > ()); }
#line 2399 "yaccfile.tab.cc"
    break;

  case 106: // expr_wo_block: LPAREN RPAREN
#line 353 "src/parser/yaccfile.yy"
                               { yylhs.value.as < U<Expr> > () = std::make_unique<Unit>(); }
#line 2405 "yaccfile.tab.cc"
    break;

  case 107: // expr_wo_block: call_expr
#line 354 "src/parser/yaccfile.yy"
                                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<CallExpr> > ()); }
#line 2411 "yaccfile.tab.cc"
    break;

  case 108: // expr_wo_block: RETURN expr
#line 355 "src/parser/yaccfile.yy"
                                     { yylhs.value.as < U<Expr> > () = std::make_unique<Return>(std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2417 "yaccfile.tab.cc"
    break;

  case 109: // expr_wo_block: BREAK expr
#line 356 "src/parser/yaccfile.yy"
                                    { yylhs.value.as < U<Expr> > () = std::make_unique<Break>(std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2423 "yaccfile.tab.cc"
    break;

  case 110: // expr_wo_block: CONTINUE
#line 357 "src/parser/yaccfile.yy"
                                  { yylhs.value.as < U<Expr> > () = std::make_unique<Continue>(); }
#line 2429 "yaccfile.tab.cc"
    break;

  case 111: // expr_wo_block: LPAREN expr_list opt_comma RPAREN
#line 358 "src/parser/yaccfile.yy"
                                         { yylhs.value.as < U<Expr> > () = std::make_unique<TupleExpr>(std::move(yystack_[2].value.as < std::vector<U<Expr>> > ())); }
#line 2435 "yaccfile.tab.cc"
    break;

  case 112: // expr_wo_block: literal
#line 359 "src/parser/yaccfile.yy"
              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Literal> > ()); }
#line 2441 "yaccfile.tab.cc"
    break;

  case 113: // opt_comma: COMMA
#line 364 "src/parser/yaccfile.yy"
            {}
#line 2447 "yaccfile.tab.cc"
    break;

  case 114: // opt_comma: %empty
#line 365 "src/parser/yaccfile.yy"
      {}
#line 2453 "yaccfile.tab.cc"
    break;


#line 2457 "yaccfile.tab.cc"

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


  const signed char Parser::yypact_ninf_ = -36;

  const signed char Parser::yytable_ninf_ = -93;

  const short
  Parser::yypact_[] =
  {
      25,   -36,    -1,    15,    13,   -36,   -36,     4,   -36,    -6,
     -36,   -36,   -15,   -12,   -36,   -36,   -36,   -22,   -36,    16,
     426,    22,    55,   -36,     0,   -36,   -36,   -36,   -36,   -36,
     -36,   -36,   -36,   -36,   -36,   -36,    50,   -36,   110,   -36,
     -36,   -36,   426,   -36,    -5,   -36,   -36,   -36,   -36,   -36,
     -36,    45,    55,   362,    46,   362,   362,   362,   362,   194,
     236,    47,   -36,   278,   -36,   362,   362,   -36,   -36,   152,
      54,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,
     423,   -36,   454,    57,   -36,   426,   -36,   320,    92,   362,
     362,   -36,   485,   -36,   -36,   105,    51,    51,    51,   485,
     -36,    51,   -36,    51,   -36,   -36,   516,    86,    51,    51,
     -36,   -36,   547,   -36,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   -36,   116,   -36,   -36,   -36,    21,   609,    69,   -36,
      72,    87,   -36,   362,    73,   -36,   609,   -25,   -25,   -25,
     -25,   -25,   -25,    17,    17,    51,    51,    10,   640,   609,
     609,   609,   609,   -36,   362,   -36,   413,     3,   -36,    56,
     609,   -36,   609,   -36,   -36,   111,   362,   -36,   -36,   -36,
      76,   578,   -36,   -36
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     6,     0,     0,     0,     5,     7,     0,     1,     0,
       3,    13,    33,    10,     4,    32,    12,     0,    15,     0,
       0,     0,    33,    11,     0,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,     0,     9,     0,     8,
      14,    17,     0,    54,     0,    41,    81,    83,    82,    84,
      85,   104,    33,     0,     0,     0,     0,     0,     0,     0,
       0,   110,    58,     0,    18,     0,     0,    25,    27,     0,
       0,    19,    99,   100,   105,   102,   112,   107,    98,   103,
       0,    23,    96,    93,    16,     0,    53,     0,     0,     0,
       0,   110,     0,    92,    93,     0,    61,    59,    60,     0,
      20,   108,    21,   109,    22,   106,    95,   114,    62,    63,
      55,    26,     0,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,     0,    97,    40,    89,     0,    87,    31,    90,
       0,    37,   101,   113,     0,    56,    76,    70,    71,    72,
      75,    73,    74,    64,    65,    66,    67,    68,    69,    77,
      78,    80,    79,    91,     0,    88,     0,     0,    28,     0,
      94,   111,    86,    30,    29,     0,     0,    36,    38,    39,
       0,     0,    35,    34
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -36,   -36,   -36,    97,   -36,   -36,   -36,   -36,   114,    71,
     -36,   -36,   -36,    90,   -36,   -31,   -36,   -34,   -21,   -36,
     -36,    11,   -36,   -36,   -36,   -36,   -35,   -36,   -36,   -19,
      36,   -36
  };

  const unsigned char
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    67,     6,    21,    13,    17,    18,    68,
      69,    70,   167,    19,    71,    72,    44,    37,    73,    74,
      75,    76,   136,    77,    78,    79,   101,   107,    81,    93,
      94,   144
  };

  const short
  Parser::yytable_[] =
  {
      39,    41,    45,    80,   175,    11,    15,     7,    84,   121,
     122,   123,   124,    -2,     9,     8,    22,     2,    92,    82,
      96,    97,    98,    99,    24,   103,     1,    20,   106,   176,
     108,   109,    23,    85,   112,   132,     2,   115,   116,    16,
     117,   118,   119,   120,   121,   122,   123,   124,     2,    86,
      82,   134,   137,   123,   124,   103,    42,    12,   177,   164,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
     132,   139,    35,    38,    83,   165,    15,   132,   141,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,    58,     5,    87,    95,
     138,    10,   104,    36,    43,    83,    14,    38,   170,   113,
     140,   132,   133,    46,    47,    48,    49,    50,    51,    46,
      47,    48,    49,    50,   143,   166,   168,   171,   169,   172,
      52,   182,   174,     2,    53,    54,    40,   180,   178,    55,
     111,   181,    88,   163,     0,    56,    57,     0,   179,     0,
      58,     0,    59,    60,    61,    46,    47,    48,    49,    50,
      51,    38,    62,    63,     0,    64,     0,    65,     0,    66,
       0,     0,    52,     0,     0,     2,    53,    54,     0,     0,
       0,    55,     0,     0,     0,     0,     0,    56,    57,     0,
       0,     0,    58,     0,    59,    60,    61,    46,    47,    48,
      49,    50,    51,    38,   110,    63,     0,    64,     0,    65,
       0,    66,     0,     0,     0,     0,     0,     0,    53,     0,
       0,     0,     0,    55,     0,     0,     0,     0,     0,    56,
      57,     0,     0,     0,    58,     0,    89,    90,    91,    46,
      47,    48,    49,    50,    51,    38,     0,    63,     0,   100,
       0,    65,     0,    66,     0,     0,     0,     0,     0,     0,
      53,     0,     0,     0,     0,    55,     0,     0,     0,     0,
       0,    56,    57,     0,     0,     0,    58,     0,    89,    90,
      91,    46,    47,    48,    49,    50,    51,    38,     0,    63,
       0,   102,     0,    65,     0,    66,     0,     0,     0,     0,
       0,     0,    53,     0,     0,     0,     0,    55,     0,     0,
       0,     0,     0,    56,    57,     0,     0,     0,    58,     0,
      89,    90,    91,    46,    47,    48,    49,    50,    51,    38,
       0,    63,   105,     0,     0,    65,     0,    66,     0,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,    55,
       0,     0,     0,     0,     0,    56,    57,     0,     0,     0,
      58,     0,    89,    90,    91,    46,    47,    48,    49,    50,
      51,    38,     0,    63,   135,     0,     0,    65,     0,    66,
       0,     0,     0,     0,     0,     0,    53,     0,     0,     0,
       0,    55,     0,     0,     0,     0,     0,    56,    57,     0,
       0,     0,    58,     0,    89,    90,    91,     0,     0,     0,
       0,     0,     0,    38,   173,    63,     0,     0,     0,    65,
       0,    66,     0,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,     0,     0,    35,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,     0,     0,    35,   114,
     115,   116,     0,   117,   118,   119,   120,   121,   122,   123,
     124,     0,     0,     0,     0,     0,    36,     0,   125,   126,
     127,   128,   129,   130,     0,   131,     0,     0,     0,    36,
     -92,   -92,   -92,   132,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,     0,     0,     0,     0,     0,     0,     0,   -92,
     -92,   -92,   -92,   -92,   -92,     0,   -92,     0,     0,     0,
       0,   114,   115,   116,   -92,   117,   118,   119,   120,   121,
     122,   123,   124,     0,     0,     0,     0,     0,     0,     0,
     125,   126,   127,   128,   129,   130,    38,     0,     0,     0,
       0,     0,   114,   115,   116,   132,   117,   118,   119,   120,
     121,   122,   123,   124,     0,     0,     0,     0,     0,     0,
       0,   125,   126,   127,   128,   129,   130,     0,     0,     0,
     142,     0,     0,   114,   115,   116,   132,   117,   118,   119,
     120,   121,   122,   123,   124,     0,     0,     0,     0,     0,
       0,     0,   125,   126,   127,   128,   129,   130,     0,   145,
       0,     0,     0,     0,   114,   115,   116,   132,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,     0,     0,   125,   126,   127,   128,   129,   130,     0,
       0,     0,     0,   183,     0,   114,   115,   116,   132,   117,
     118,   119,   120,   121,   122,   123,   124,     0,     0,     0,
       0,     0,     0,     0,   125,   126,   127,   128,   129,   130,
       0,     0,     0,     0,     0,     0,     0,   115,   116,   132,
     117,   118,   119,   120,   121,   122,   123,   124,     0,     0,
       0,     0,     0,     0,     0,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     132
  };

  const short
  Parser::yycheck_[] =
  {
      21,     1,    36,    38,     1,     1,    21,     8,    42,    34,
      35,    36,    37,     0,     1,     0,    38,    23,    53,    38,
      55,    56,    57,    58,     8,    60,     1,    39,    63,    26,
      65,    66,    54,    38,    69,    60,    23,    27,    28,    54,
      30,    31,    32,    33,    34,    35,    36,    37,    23,    54,
      69,    85,    87,    36,    37,    90,    56,    53,    55,    38,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      60,    92,    22,    51,    38,    54,    21,    60,    99,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,    40,     0,    53,    53,
       8,     4,    55,    53,    54,    69,     9,    51,   143,    55,
       5,    60,    55,     3,     4,     5,     6,     7,     8,     3,
       4,     5,     6,     7,    38,    56,    54,    54,    41,   164,
      20,    55,   166,    23,    24,    25,    22,    26,   169,    29,
      69,   176,    52,   132,    -1,    35,    36,    -1,   169,    -1,
      40,    -1,    42,    43,    44,     3,     4,     5,     6,     7,
       8,    51,    52,    53,    -1,    55,    -1,    57,    -1,    59,
      -1,    -1,    20,    -1,    -1,    23,    24,    25,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    35,    36,    -1,
      -1,    -1,    40,    -1,    42,    43,    44,     3,     4,     5,
       6,     7,     8,    51,    52,    53,    -1,    55,    -1,    57,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    35,
      36,    -1,    -1,    -1,    40,    -1,    42,    43,    44,     3,
       4,     5,     6,     7,     8,    51,    -1,    53,    -1,    55,
      -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    35,    36,    -1,    -1,    -1,    40,    -1,    42,    43,
      44,     3,     4,     5,     6,     7,     8,    51,    -1,    53,
      -1,    55,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    35,    36,    -1,    -1,    -1,    40,    -1,
      42,    43,    44,     3,     4,     5,     6,     7,     8,    51,
      -1,    53,    54,    -1,    -1,    57,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,
      40,    -1,    42,    43,    44,     3,     4,     5,     6,     7,
       8,    51,    -1,    53,    54,    -1,    -1,    57,    -1,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    35,    36,    -1,
      -1,    -1,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    51,     1,    53,    -1,    -1,    -1,    57,
      -1,    59,    -1,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    -1,    22,    26,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    53,    -1,    45,    46,
      47,    48,    49,    50,    -1,    52,    -1,    -1,    -1,    53,
      26,    27,    28,    60,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    -1,    52,    -1,    -1,    -1,
      -1,    26,    27,    28,    60,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    60,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      54,    -1,    -1,    26,    27,    28,    60,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    -1,    52,
      -1,    -1,    -1,    -1,    26,    27,    28,    60,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    -1,    55,    -1,    26,    27,    28,    60,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    60,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     1,    23,    82,    83,    84,    85,     8,     0,     1,
      84,     1,    53,    87,    84,    21,    54,    88,    89,    94,
      39,    86,    38,    54,     8,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    22,    53,    98,    51,    99,
      89,     1,    56,    54,    97,    98,     3,     4,     5,     6,
       7,     8,    20,    24,    25,    29,    35,    36,    40,    42,
      43,    44,    52,    53,    55,    57,    59,    84,    90,    91,
      92,    95,    96,    99,   100,   101,   102,   104,   105,   106,
     107,   109,   110,   111,    98,    38,    54,    53,    94,    42,
      43,    44,   107,   110,   111,    53,   107,   107,   107,   107,
      55,   107,    55,   107,    55,    54,   107,   108,   107,   107,
      52,    90,   107,    55,    26,    27,    28,    30,    31,    32,
      33,    34,    35,    36,    37,    45,    46,    47,    48,    49,
      50,    52,    60,    55,    98,    54,   103,   107,     8,    99,
       5,    99,    54,    38,   112,    52,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   102,    38,    54,    56,    93,    54,    41,
     107,    54,   107,     1,    98,     1,    26,    55,    96,    99,
      26,   107,    55,    55
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    81,    82,    83,    83,    83,    83,    84,    85,    86,
      86,    87,    87,    87,    88,    88,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90,    91,    91,    92,    93,
      93,    93,    94,    94,    95,    95,    95,    96,    96,    96,
      97,    97,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    99,    99,    99,    99,   100,
     100,   100,   100,   100,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   102,   102,   102,   102,   102,   103,   103,   104,   104,
     105,   106,   107,   107,   108,   108,   109,   109,   110,   110,
     110,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   112,   112
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     1,     1,     1,     5,     2,
       0,     3,     2,     1,     3,     1,     4,     3,     1,     1,
       2,     2,     2,     1,     2,     1,     2,     1,     4,     2,
       2,     0,     1,     0,     7,     7,     5,     3,     5,     5,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     3,     4,     3,     2,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     3,     1,     4,     3,
       3,     3,     1,     1,     3,     1,     1,     2,     1,     1,
       1,     3,     1,     1,     1,     1,     2,     1,     2,     2,
       1,     4,     1,     1,     0
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
  "AMPERSAND_MUT", "DOT", "MOD_EQ", "BIT_AND_EQ", "BIT_OR_EQ",
  "BIT_XOR_EQ", "SHL_EQ", "SHR_EQ", "MOD", "UMINUS", "DEREF", "NOT", "REF",
  "REF_MUT", "METHOD_CALL", "FIELD_ACCESS", "FUNC_CALL", "PATH",
  "CALL_INDEX", "UNARY", "BIN_OP", "CONTROL_FLOW", "$accept", "program",
  "item_list", "item", "function_decl", "func_ret_type", "func_decl_args",
  "func_arg_list", "func_arg", "stmt", "stmt_list", "print_ln",
  "type_decl", "opt_mut", "let", "if_expr", "type_list", "type",
  "block_expr", "unary_op_expr", "bin_op_expr", "literal",
  "call_expr_args", "call_expr", "while_expr", "tuple_index_expr", "expr",
  "expr_list", "expr_stmt", "expr_w_block", "expr_wo_block", "opt_comma", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   130,   130,   134,   136,   137,   141,   145,   150,   157,
     158,   163,   164,   165,   169,   170,   174,   175,   178,   179,
     180,   181,   182,   183,   184,   185,   189,   190,   198,   202,
     203,   204,   208,   209,   213,   215,   219,   225,   226,   227,
     238,   239,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   261,   262,   263,   264,   268,
     269,   270,   271,   272,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   289,   290,   291,   292,
     293,   297,   298,   299,   300,   301,   306,   307,   315,   316,
     319,   323,   328,   329,   333,   334,   338,   339,   343,   344,
     345,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   364,   365
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
      75,    76,    77,    78,    79,    80
    };
    // Last valid token kind.
    const int code_max = 335;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "src/parser/yaccfile.yy"
} // mr
#line 3220 "yaccfile.tab.cc"

#line 367 "src/parser/yaccfile.yy"


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
