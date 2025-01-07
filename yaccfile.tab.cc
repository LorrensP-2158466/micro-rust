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
#line 38 "src/parser/yaccfile.yy"

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

      case symbol_kind::S_ident: // ident
        value.copy< Identifier > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.copy< Mut > (YY_MOVE (that.value));
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

      case symbol_kind::S_ident: // ident
        value.move< Identifier > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.move< Mut > (YY_MOVE (s.value));
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

      case symbol_kind::S_ident: // ident
        value.YY_MOVE_OR_COPY< Identifier > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.YY_MOVE_OR_COPY< Mut > (YY_MOVE (that.value));
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

      case symbol_kind::S_ident: // ident
        value.move< Identifier > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.move< Mut > (YY_MOVE (that.value));
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

      case symbol_kind::S_ident: // ident
        value.copy< Identifier > (that.value);
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.copy< Mut > (that.value);
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

      case symbol_kind::S_ident: // ident
        value.move< Identifier > (that.value);
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.move< Mut > (that.value);
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

      case symbol_kind::S_ident: // ident
        yylhs.value.emplace< Identifier > ();
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        yylhs.value.emplace< Mut > ();
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
#line 118 "src/parser/yaccfile.yy"
                { driver.set_ast(m_u<Ast>(std::move(yystack_[0].value.as < std::vector<U<Item>> > ()))); }
#line 1785 "yaccfile.tab.cc"
    break;

  case 3: // item_list: item_list item
#line 122 "src/parser/yaccfile.yy"
                     {yystack_[1].value.as < std::vector<U<Item>> > ().push_back(std::move(yystack_[0].value.as < U<Item> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Item>> > (), yystack_[1].value.as < std::vector<U<Item>> > ());}
#line 1791 "yaccfile.tab.cc"
    break;

  case 4: // item_list: item
#line 123 "src/parser/yaccfile.yy"
           {
        auto vec = std::vector<U<Item>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Item> > ()));
        yylhs.value.as < std::vector<U<Item>> > () = std::move(vec) ;}
#line 1800 "yaccfile.tab.cc"
    break;

  case 5: // item: function_decl
#line 130 "src/parser/yaccfile.yy"
                  { DEFAULT_ACTION(yylhs.value.as < U<Item> > (), yystack_[0].value.as < U<FunDecl> > ()); }
#line 1806 "yaccfile.tab.cc"
    break;

  case 6: // function_decl: FN IDENTIFIER func_decl_args ARROW type block_expr
#line 136 "src/parser/yaccfile.yy"
    { 
        const auto loc = yystack_[5].location + yystack_[0].value.as < U<BlockExpr> > ()->loc;
        yylhs.value.as < U<FunDecl> > () = FunDecl::make_unique(yystack_[4].value.as < Token > ().string_value(), std::move(yystack_[3].value.as < std::vector<FunArg> > ()), std::move(yystack_[1].value.as < Type > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ()),loc);
    }
#line 1815 "yaccfile.tab.cc"
    break;

  case 7: // function_decl: FN IDENTIFIER func_decl_args block_expr
#line 141 "src/parser/yaccfile.yy"
    { 
        const auto loc = yystack_[3].location + yystack_[0].value.as < U<BlockExpr> > ()->loc;
        yylhs.value.as < U<FunDecl> > () = FunDecl::make_unique(yystack_[2].value.as < Token > ().string_value(), std::move(yystack_[1].value.as < std::vector<FunArg> > ()), Type(location(yystack_[0].value.as < U<BlockExpr> > ()->loc.begin, yystack_[0].value.as < U<BlockExpr> > ()->loc.begin + 1)), std::move(yystack_[0].value.as < U<BlockExpr> > ()), loc);
    }
#line 1824 "yaccfile.tab.cc"
    break;

  case 8: // func_decl_args: LPAREN func_arg_list RPAREN
#line 148 "src/parser/yaccfile.yy"
                                  {yylhs.value.as < std::vector<FunArg> > () = std::move(yystack_[1].value.as < std::vector<FunArg> > ());}
#line 1830 "yaccfile.tab.cc"
    break;

  case 9: // func_decl_args: LPAREN RPAREN
#line 149 "src/parser/yaccfile.yy"
                    { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{};}
#line 1836 "yaccfile.tab.cc"
    break;

  case 10: // func_decl_args: error
#line 150 "src/parser/yaccfile.yy"
            { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{};}
#line 1842 "yaccfile.tab.cc"
    break;

  case 11: // func_arg_list: func_arg_list COMMA func_arg
#line 154 "src/parser/yaccfile.yy"
                                   { yystack_[2].value.as < std::vector<FunArg> > ().push_back(std::move(yystack_[0].value.as < FunArg > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<FunArg> > (), yystack_[2].value.as < std::vector<FunArg> > ());}
#line 1848 "yaccfile.tab.cc"
    break;

  case 12: // func_arg_list: func_arg
#line 155 "src/parser/yaccfile.yy"
               { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{}; yylhs.value.as < std::vector<FunArg> > ().push_back(std::move(yystack_[0].value.as < FunArg > ())); }
#line 1854 "yaccfile.tab.cc"
    break;

  case 13: // func_arg: opt_mut IDENTIFIER COLON type
#line 159 "src/parser/yaccfile.yy"
                                    { yylhs.value.as < FunArg > () = FunArg{yystack_[2].value.as < Token > ().string_value(), std::move(yystack_[0].value.as < Type > ()), yystack_[3].value.as < Mut > ().loc + yystack_[0].value.as < Type > ().loc, yystack_[3].value.as < Mut > ()}; }
#line 1860 "yaccfile.tab.cc"
    break;

  case 14: // stmt: SEMICOLON
#line 162 "src/parser/yaccfile.yy"
                {yylhs.value.as < U<Stmt> > () = m_u<EmptyStmt>(yystack_[0].location);}
#line 1866 "yaccfile.tab.cc"
    break;

  case 15: // stmt: let
#line 163 "src/parser/yaccfile.yy"
          { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[0].value.as < U<LetStmt> > ()); }
#line 1872 "yaccfile.tab.cc"
    break;

  case 16: // stmt: expr_stmt SEMICOLON
#line 167 "src/parser/yaccfile.yy"
                          { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[1].value.as < U<Expr> > ());}
#line 1878 "yaccfile.tab.cc"
    break;

  case 17: // stmt: print_ln SEMICOLON
#line 168 "src/parser/yaccfile.yy"
                         { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[1].value.as < U<PrintLn> > ());}
#line 1884 "yaccfile.tab.cc"
    break;

  case 18: // stmt: item
#line 169 "src/parser/yaccfile.yy"
           { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[0].value.as < U<Item> > ()); }
#line 1890 "yaccfile.tab.cc"
    break;

  case 19: // stmt_list: stmt_list stmt
#line 173 "src/parser/yaccfile.yy"
                     { yystack_[1].value.as < std::vector<U<Stmt>> > ().push_back(std::move(yystack_[0].value.as < U<Stmt> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Stmt>> > (), yystack_[1].value.as < std::vector<U<Stmt>> > ()); }
#line 1896 "yaccfile.tab.cc"
    break;

  case 20: // stmt_list: stmt_list error
#line 175 "src/parser/yaccfile.yy"
                      { DEFAULT_ACTION(yylhs.value.as < std::vector<U<Stmt>> > (), yystack_[1].value.as < std::vector<U<Stmt>> > ());}
#line 1902 "yaccfile.tab.cc"
    break;

  case 21: // stmt_list: stmt
#line 176 "src/parser/yaccfile.yy"
           {
        auto vec = std::vector<U<Stmt>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Stmt> > ()));
        yylhs.value.as < std::vector<U<Stmt>> > () = std::move(vec); 
      }
#line 1912 "yaccfile.tab.cc"
    break;

  case 22: // print_ln: PRINT_LN LPAREN STR_LITERAL RPAREN
#line 185 "src/parser/yaccfile.yy"
                                         { yylhs.value.as < U<PrintLn> > () = m_u<PrintLn>(yystack_[1].value.as < Token > ().string_value(), yystack_[3].location + yystack_[0].location); }
#line 1918 "yaccfile.tab.cc"
    break;

  case 23: // type_decl: COLON type
#line 189 "src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < std::optional<Type> > (), yystack_[0].value.as < Type > ()); }
#line 1924 "yaccfile.tab.cc"
    break;

  case 24: // type_decl: COLON error
#line 190 "src/parser/yaccfile.yy"
                  { yylhs.value.as < std::optional<Type> > () = Type::infer(yystack_[1].location);  }
#line 1930 "yaccfile.tab.cc"
    break;

  case 25: // type_decl: %empty
#line 191 "src/parser/yaccfile.yy"
      { yylhs.value.as < std::optional<Type> > () = {}; }
#line 1936 "yaccfile.tab.cc"
    break;

  case 26: // opt_mut: MUT
#line 195 "src/parser/yaccfile.yy"
         { yylhs.value.as < Mut > () = Mut{true, yystack_[0].location}; }
#line 1942 "yaccfile.tab.cc"
    break;

  case 27: // opt_mut: %empty
#line 196 "src/parser/yaccfile.yy"
         { yylhs.value.as < Mut > () = Mut{false, location()}; }
#line 1948 "yaccfile.tab.cc"
    break;

  case 28: // ident: IDENTIFIER
#line 200 "src/parser/yaccfile.yy"
                 { yylhs.value.as < Identifier > () = Identifier{yystack_[0].value.as < Token > ().string_value(), yystack_[0].location};}
#line 1954 "yaccfile.tab.cc"
    break;

  case 29: // let: LET opt_mut ident type_decl EQ expr SEMICOLON
#line 205 "src/parser/yaccfile.yy"
      {yylhs.value.as < U<LetStmt> > () = LetStmt::make_unique_init(std::move(yystack_[4].value.as < Identifier > ()), std::move(yystack_[3].value.as < std::optional<Type> > ()), std::move(yystack_[1].value.as < U<Expr> > ()), yystack_[5].value.as < Mut > (), yystack_[6].location + yystack_[0].location);}
#line 1960 "yaccfile.tab.cc"
    break;

  case 30: // let: LET opt_mut ident type_decl SEMICOLON
#line 206 "src/parser/yaccfile.yy"
                                            {
        yylhs.value.as < U<LetStmt> > () = LetStmt::make_unique_decl(std::move(yystack_[2].value.as < Identifier > ()), std::move(yystack_[1].value.as < std::optional<Type> > ()), yystack_[3].value.as < Mut > (), yystack_[4].location + yystack_[0].location);
    }
#line 1968 "yaccfile.tab.cc"
    break;

  case 31: // if_expr: IF expr block_expr
#line 212 "src/parser/yaccfile.yy"
                         { yylhs.value.as < U<IfElse> > () = m_u<IfElse>(yystack_[2].location, std::move(yystack_[1].value.as < U<Expr> > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ()), location()); }
#line 1974 "yaccfile.tab.cc"
    break;

  case 32: // if_expr: IF expr block_expr ELSE if_expr
#line 213 "src/parser/yaccfile.yy"
                                      {yylhs.value.as < U<IfElse> > () = m_u<IfElse>(yystack_[4].location, std::move(yystack_[3].value.as < U<Expr> > ()), std::move(yystack_[2].value.as < U<BlockExpr> > ()), yystack_[1].location, std::move(yystack_[0].value.as < U<IfElse> > ())); }
#line 1980 "yaccfile.tab.cc"
    break;

  case 33: // if_expr: IF expr block_expr ELSE block_expr
#line 214 "src/parser/yaccfile.yy"
                                         {yylhs.value.as < U<IfElse> > () = m_u<IfElse>(yystack_[4].location, std::move(yystack_[3].value.as < U<Expr> > ()), std::move(yystack_[2].value.as < U<BlockExpr> > ()), yystack_[1].location, std::move(yystack_[0].value.as < U<BlockExpr> > ())); }
#line 1986 "yaccfile.tab.cc"
    break;

  case 34: // type_list: type_list COMMA type
#line 225 "src/parser/yaccfile.yy"
                           {yylhs.value.as < std::vector<Type> > () = std::move(yystack_[2].value.as < std::vector<Type> > ()); yylhs.value.as < std::vector<Type> > ().push_back(std::move(yystack_[0].value.as < Type > ()));}
#line 1992 "yaccfile.tab.cc"
    break;

  case 35: // type_list: type
#line 226 "src/parser/yaccfile.yy"
           {yylhs.value.as < std::vector<Type> > () = std::vector<Type>(); yylhs.value.as < std::vector<Type> > ().push_back(std::move(yystack_[0].value.as < Type > ()));}
#line 1998 "yaccfile.tab.cc"
    break;

  case 36: // type: I8
#line 230 "src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::I8, yystack_[0].location); }
#line 2004 "yaccfile.tab.cc"
    break;

  case 37: // type: I16
#line 231 "src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::I16, yystack_[0].location); }
#line 2010 "yaccfile.tab.cc"
    break;

  case 38: // type: I32
#line 232 "src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::I32, yystack_[0].location); }
#line 2016 "yaccfile.tab.cc"
    break;

  case 39: // type: I64
#line 233 "src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::I64, yystack_[0].location); }
#line 2022 "yaccfile.tab.cc"
    break;

  case 40: // type: ISIZE
#line 234 "src/parser/yaccfile.yy"
            { yylhs.value.as < Type > () = Type(primitive_type::ISIZE, yystack_[0].location); }
#line 2028 "yaccfile.tab.cc"
    break;

  case 41: // type: U8
#line 235 "src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::U8, yystack_[0].location); }
#line 2034 "yaccfile.tab.cc"
    break;

  case 42: // type: U16
#line 236 "src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::U16, yystack_[0].location); }
#line 2040 "yaccfile.tab.cc"
    break;

  case 43: // type: U32
#line 237 "src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::U32, yystack_[0].location); }
#line 2046 "yaccfile.tab.cc"
    break;

  case 44: // type: U64
#line 238 "src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::U64, yystack_[0].location); }
#line 2052 "yaccfile.tab.cc"
    break;

  case 45: // type: USIZE
#line 239 "src/parser/yaccfile.yy"
            { yylhs.value.as < Type > () = Type(primitive_type::USIZE, yystack_[0].location); }
#line 2058 "yaccfile.tab.cc"
    break;

  case 46: // type: BOOL
#line 240 "src/parser/yaccfile.yy"
           { yylhs.value.as < Type > () = Type(primitive_type::BOOL, yystack_[0].location); }
#line 2064 "yaccfile.tab.cc"
    break;

  case 47: // type: LPAREN type_list RPAREN
#line 241 "src/parser/yaccfile.yy"
                              { yylhs.value.as < Type > () = Type(std::move(yystack_[1].value.as < std::vector<Type> > ()), yystack_[2].location + yystack_[0].location);}
#line 2070 "yaccfile.tab.cc"
    break;

  case 48: // type: LPAREN RPAREN
#line 242 "src/parser/yaccfile.yy"
                    { yylhs.value.as < Type > () = Type(yystack_[1].location + yystack_[0].location); }
#line 2076 "yaccfile.tab.cc"
    break;

  case 49: // block_expr: LBRACE stmt_list RBRACE
#line 247 "src/parser/yaccfile.yy"
                              { yylhs.value.as < U<BlockExpr> > () = m_u<BlockExpr>(std::move(yystack_[1].value.as < std::vector<U<Stmt>> > ()), m_u<Unit>(yystack_[0].location), yystack_[2].location + yystack_[0].location); }
#line 2082 "yaccfile.tab.cc"
    break;

  case 50: // block_expr: LBRACE stmt_list expr RBRACE
#line 248 "src/parser/yaccfile.yy"
                                    { yylhs.value.as < U<BlockExpr> > () = m_u<BlockExpr>(std::move(yystack_[2].value.as < std::vector<U<Stmt>> > ()), std::move(yystack_[1].value.as < U<Expr> > ()), yystack_[3].location + yystack_[0].location); }
#line 2088 "yaccfile.tab.cc"
    break;

  case 51: // block_expr: LBRACE expr RBRACE
#line 249 "src/parser/yaccfile.yy"
                          { yylhs.value.as < U<BlockExpr> > () = m_u<BlockExpr>(std::vector<U<Stmt>>{}, std::move(yystack_[1].value.as < U<Expr> > ()), yystack_[2].location + yystack_[0].location); }
#line 2094 "yaccfile.tab.cc"
    break;

  case 52: // block_expr: LBRACE RBRACE
#line 250 "src/parser/yaccfile.yy"
                     { yylhs.value.as < U<BlockExpr> > () = m_u<BlockExpr>(std::vector<U<Stmt>>{}, m_u<Unit>(yystack_[1].location + yystack_[0].location), yystack_[1].location + yystack_[0].location); }
#line 2100 "yaccfile.tab.cc"
    break;

  case 53: // unary_op_expr: MINUS expr
#line 254 "src/parser/yaccfile.yy"
                              { yylhs.value.as < U<UnaryOpExpr> > () = m_u<UnaryOpExpr>(UnaryOp::Negate, yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2106 "yaccfile.tab.cc"
    break;

  case 54: // unary_op_expr: STAR expr
#line 255 "src/parser/yaccfile.yy"
                            { yylhs.value.as < U<UnaryOpExpr> > () = m_u<UnaryOpExpr>(UnaryOp::Deref, yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2112 "yaccfile.tab.cc"
    break;

  case 55: // unary_op_expr: BANG expr
#line 256 "src/parser/yaccfile.yy"
                          { yylhs.value.as < U<UnaryOpExpr> > () = m_u<UnaryOpExpr>(UnaryOp::Not, yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2118 "yaccfile.tab.cc"
    break;

  case 56: // unary_op_expr: AMPERSAND expr
#line 257 "src/parser/yaccfile.yy"
                               { yylhs.value.as < U<UnaryOpExpr> > () = m_u<UnaryOpExpr>(UnaryOp::Borrow, yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2124 "yaccfile.tab.cc"
    break;

  case 57: // unary_op_expr: AMPERSAND_MUT expr
#line 258 "src/parser/yaccfile.yy"
                                       { yylhs.value.as < U<UnaryOpExpr> > () = m_u<UnaryOpExpr>(UnaryOp::MutBorrow, yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2130 "yaccfile.tab.cc"
    break;

  case 58: // bin_op_expr: expr PLUS expr
#line 262 "src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Plus, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2136 "yaccfile.tab.cc"
    break;

  case 59: // bin_op_expr: expr MINUS expr
#line 263 "src/parser/yaccfile.yy"
                      { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Min, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2142 "yaccfile.tab.cc"
    break;

  case 60: // bin_op_expr: expr STAR expr
#line 264 "src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Mul, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2148 "yaccfile.tab.cc"
    break;

  case 61: // bin_op_expr: expr SLASH expr
#line 265 "src/parser/yaccfile.yy"
                      { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Div, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2154 "yaccfile.tab.cc"
    break;

  case 62: // bin_op_expr: expr L_AND expr
#line 266 "src/parser/yaccfile.yy"
                      { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::L_AND, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2160 "yaccfile.tab.cc"
    break;

  case 63: // bin_op_expr: expr L_OR expr
#line 267 "src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::L_OR, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2166 "yaccfile.tab.cc"
    break;

  case 64: // bin_op_expr: expr EQEQ expr
#line 268 "src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Eq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2172 "yaccfile.tab.cc"
    break;

  case 65: // bin_op_expr: expr NE expr
#line 269 "src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::NEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2178 "yaccfile.tab.cc"
    break;

  case 66: // bin_op_expr: expr LT expr
#line 270 "src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Lt, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2184 "yaccfile.tab.cc"
    break;

  case 67: // bin_op_expr: expr GT expr
#line 271 "src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Gt, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2190 "yaccfile.tab.cc"
    break;

  case 68: // bin_op_expr: expr GE expr
#line 272 "src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::GtEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2196 "yaccfile.tab.cc"
    break;

  case 69: // bin_op_expr: expr LE expr
#line 273 "src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::LtEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2202 "yaccfile.tab.cc"
    break;

  case 70: // bin_op_expr: expr EQ expr
#line 275 "src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = m_u<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::Eq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2208 "yaccfile.tab.cc"
    break;

  case 71: // bin_op_expr: expr PLUS_EQ expr
#line 276 "src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = m_u<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::PlusEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2214 "yaccfile.tab.cc"
    break;

  case 72: // bin_op_expr: expr MIN_EQ expr
#line 277 "src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = m_u<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::MinEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2220 "yaccfile.tab.cc"
    break;

  case 73: // bin_op_expr: expr DIV_EQ expr
#line 278 "src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = m_u<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::DivEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2226 "yaccfile.tab.cc"
    break;

  case 74: // bin_op_expr: expr MUL_EQ expr
#line 279 "src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = m_u<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::MulEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2232 "yaccfile.tab.cc"
    break;

  case 75: // literal: DEC_LITERAL
#line 283 "src/parser/yaccfile.yy"
                  { yylhs.value.as < U<Literal> > () = Literal::make_int_lit(yystack_[0].value.as < Token > ().symbol, yystack_[0].location);}
#line 2238 "yaccfile.tab.cc"
    break;

  case 76: // literal: STR_LITERAL
#line 284 "src/parser/yaccfile.yy"
                  { yylhs.value.as < U<Literal> > () = Literal::make_str_lit(yystack_[0].value.as < Token > ().symbol, yystack_[0].location); }
#line 2244 "yaccfile.tab.cc"
    break;

  case 77: // literal: FLOAT_LITERAL
#line 285 "src/parser/yaccfile.yy"
                    { assert(1 && "How did we get here"); }
#line 2250 "yaccfile.tab.cc"
    break;

  case 78: // literal: TRUE
#line 286 "src/parser/yaccfile.yy"
           { yylhs.value.as < U<Literal> > () = Literal::make_bool_lit(yystack_[0].value.as < Token > ().symbol, yystack_[0].location); }
#line 2256 "yaccfile.tab.cc"
    break;

  case 79: // literal: FALSE
#line 287 "src/parser/yaccfile.yy"
            { yylhs.value.as < U<Literal> > () = Literal::make_bool_lit(yystack_[0].value.as < Token > ().symbol, yystack_[0].location); }
#line 2262 "yaccfile.tab.cc"
    break;

  case 80: // call_expr_args: call_expr_args COMMA expr
#line 292 "src/parser/yaccfile.yy"
                                { yystack_[2].value.as < std::vector<U<Expr>> > ().push_back(std::move(yystack_[0].value.as < U<Expr> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Expr>> > (), yystack_[2].value.as < std::vector<U<Expr>> > ()); }
#line 2268 "yaccfile.tab.cc"
    break;

  case 81: // call_expr_args: expr
#line 293 "src/parser/yaccfile.yy"
           { 
        auto vec = std::vector<U<Expr>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Expr> > ()));
        yylhs.value.as < std::vector<U<Expr>> > () = std::move(vec);
        }
#line 2278 "yaccfile.tab.cc"
    break;

  case 82: // call_expr: IDENTIFIER LPAREN call_expr_args RPAREN
#line 301 "src/parser/yaccfile.yy"
                                              { yylhs.value.as < U<CallExpr> > () = m_u<CallExpr>(yystack_[3].location + yystack_[0].location, yystack_[3].value.as < Token > ().string_value(), std::move(yystack_[1].value.as < std::vector<U<Expr>> > ())); }
#line 2284 "yaccfile.tab.cc"
    break;

  case 83: // call_expr: IDENTIFIER LPAREN RPAREN
#line 302 "src/parser/yaccfile.yy"
                               { yylhs.value.as < U<CallExpr> > () = m_u<CallExpr>(yystack_[2].location + yystack_[0].location, yystack_[2].value.as < Token > ().string_value(), std::vector<U<Expr>>{}); }
#line 2290 "yaccfile.tab.cc"
    break;

  case 84: // while_expr: WHILE expr block_expr
#line 305 "src/parser/yaccfile.yy"
                            {yylhs.value.as < U<WhileLoop> > () = m_u<WhileLoop>(yystack_[2].location, std::move(yystack_[1].value.as < U<Expr> > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ())); }
#line 2296 "yaccfile.tab.cc"
    break;

  case 85: // tuple_index_expr: expr DOT DEC_LITERAL
#line 309 "src/parser/yaccfile.yy"
                           { yylhs.value.as < U<TupleIndexExpr> > () = m_u<TupleIndexExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), Literal::make_int_lit(yystack_[0].value.as < Token > ().symbol, yystack_[0].location));}
#line 2302 "yaccfile.tab.cc"
    break;

  case 86: // expr: expr_w_block
#line 314 "src/parser/yaccfile.yy"
                   { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2308 "yaccfile.tab.cc"
    break;

  case 87: // expr: expr_wo_block
#line 315 "src/parser/yaccfile.yy"
                    { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2314 "yaccfile.tab.cc"
    break;

  case 88: // expr_list: expr_list COMMA expr
#line 319 "src/parser/yaccfile.yy"
                           { yystack_[2].value.as < std::vector<U<Expr>> > ().push_back(std::move(yystack_[0].value.as < U<Expr> > ())); yylhs.value.as < std::vector<U<Expr>> > () = std::move(yystack_[2].value.as < std::vector<U<Expr>> > ());}
#line 2320 "yaccfile.tab.cc"
    break;

  case 89: // expr_list: expr
#line 320 "src/parser/yaccfile.yy"
           {yylhs.value.as < std::vector<U<Expr>> > () = std::vector<U<Expr>>(); yylhs.value.as < std::vector<U<Expr>> > ().push_back(std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2326 "yaccfile.tab.cc"
    break;

  case 90: // expr_stmt: expr_w_block
#line 324 "src/parser/yaccfile.yy"
                    { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2332 "yaccfile.tab.cc"
    break;

  case 91: // expr_stmt: expr_wo_block
#line 325 "src/parser/yaccfile.yy"
                    { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ()); }
#line 2338 "yaccfile.tab.cc"
    break;

  case 92: // expr_w_block: while_expr
#line 329 "src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<WhileLoop> > ()); }
#line 2344 "yaccfile.tab.cc"
    break;

  case 93: // expr_w_block: if_expr
#line 330 "src/parser/yaccfile.yy"
              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<IfElse> > ()); }
#line 2350 "yaccfile.tab.cc"
    break;

  case 94: // expr_w_block: block_expr
#line 331 "src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<BlockExpr> > ()); }
#line 2356 "yaccfile.tab.cc"
    break;

  case 95: // expr_wo_block: LPAREN expr RPAREN
#line 334 "src/parser/yaccfile.yy"
                         { yystack_[1].value.as < U<Expr> > ()->loc = yystack_[2].location + yystack_[0].location; DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[1].value.as < U<Expr> > ()); }
#line 2362 "yaccfile.tab.cc"
    break;

  case 96: // expr_wo_block: bin_op_expr
#line 335 "src/parser/yaccfile.yy"
                              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ()); }
#line 2368 "yaccfile.tab.cc"
    break;

  case 97: // expr_wo_block: tuple_index_expr
#line 336 "src/parser/yaccfile.yy"
                                          { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<TupleIndexExpr> > ()); }
#line 2374 "yaccfile.tab.cc"
    break;

  case 98: // expr_wo_block: IDENTIFIER
#line 337 "src/parser/yaccfile.yy"
                            { yylhs.value.as < U<Expr> > () = m_u<Identifier>(yystack_[0].value.as < Token > ().string_value(), yystack_[0].location); }
#line 2380 "yaccfile.tab.cc"
    break;

  case 99: // expr_wo_block: unary_op_expr
#line 338 "src/parser/yaccfile.yy"
                                {DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<UnaryOpExpr> > ()); }
#line 2386 "yaccfile.tab.cc"
    break;

  case 100: // expr_wo_block: LPAREN RPAREN
#line 339 "src/parser/yaccfile.yy"
                               { yylhs.value.as < U<Expr> > () = m_u<Unit>(yystack_[1].location + yystack_[0].location); }
#line 2392 "yaccfile.tab.cc"
    break;

  case 101: // expr_wo_block: call_expr
#line 340 "src/parser/yaccfile.yy"
                                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<CallExpr> > ()); }
#line 2398 "yaccfile.tab.cc"
    break;

  case 102: // expr_wo_block: RETURN expr
#line 341 "src/parser/yaccfile.yy"
                                     { yylhs.value.as < U<Expr> > () = m_u<Return>(yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2404 "yaccfile.tab.cc"
    break;

  case 103: // expr_wo_block: BREAK expr
#line 342 "src/parser/yaccfile.yy"
                                    { yylhs.value.as < U<Expr> > () = m_u<Break>(yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2410 "yaccfile.tab.cc"
    break;

  case 104: // expr_wo_block: CONTINUE
#line 343 "src/parser/yaccfile.yy"
                                  { yylhs.value.as < U<Expr> > () = m_u<Continue>(yystack_[0].location); }
#line 2416 "yaccfile.tab.cc"
    break;

  case 105: // expr_wo_block: LPAREN expr_list opt_comma RPAREN
#line 344 "src/parser/yaccfile.yy"
                                         { yylhs.value.as < U<Expr> > () = m_u<TupleExpr>(std::move(yystack_[2].value.as < std::vector<U<Expr>> > ()), yystack_[3].location + yystack_[0].location); }
#line 2422 "yaccfile.tab.cc"
    break;

  case 106: // expr_wo_block: literal
#line 345 "src/parser/yaccfile.yy"
              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Literal> > ()); }
#line 2428 "yaccfile.tab.cc"
    break;

  case 107: // opt_comma: COMMA
#line 350 "src/parser/yaccfile.yy"
            {}
#line 2434 "yaccfile.tab.cc"
    break;

  case 108: // opt_comma: %empty
#line 351 "src/parser/yaccfile.yy"
      {}
#line 2440 "yaccfile.tab.cc"
    break;


#line 2444 "yaccfile.tab.cc"

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

  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "DEC_LITERAL", "FLOAT_LITERAL",
  "STR_LITERAL", "TRUE", "FALSE", "IDENTIFIER", "UNDERSCORE", "I8", "I16",
  "I32", "I64", "ISIZE", "U8", "U16", "U32", "U64", "USIZE", "LET", "MUT",
  "BOOL", "FN", "WHILE", "PRINT_LN", "EQ", "EQEQ", "NE", "BANG", "LT",
  "LE", "GT", "GE", "PLUS", "MINUS", "STAR", "SLASH", "COMMA", "ARROW",
  "IF", "ELSE", "RETURN", "BREAK", "CONTINUE", "L_AND", "L_OR", "PLUS_EQ",
  "MIN_EQ", "MUL_EQ", "DIV_EQ", "LBRACE", "RBRACE", "LPAREN", "RPAREN",
  "SEMICOLON", "COLON", "AMPERSAND", "OR", "AMPERSAND_MUT", "DOT",
  "CONTROL_FLOW", "MOD_EQ", "BIT_AND_EQ", "BIT_OR_EQ", "BIT_XOR_EQ",
  "SHL_EQ", "SHR_EQ", "MOD", "BIN_OP", "UMINUS", "DEREF", "NOT", "REF",
  "REF_MUT", "UNARY", "METHOD_CALL", "FIELD_ACCESS", "FUNC_CALL",
  "CALL_INDEX", "PATH", "$accept", "program", "item_list", "item",
  "function_decl", "func_decl_args", "func_arg_list", "func_arg", "stmt",
  "stmt_list", "print_ln", "type_decl", "opt_mut", "ident", "let",
  "if_expr", "type_list", "type", "block_expr", "unary_op_expr",
  "bin_op_expr", "literal", "call_expr_args", "call_expr", "while_expr",
  "tuple_index_expr", "expr", "expr_list", "expr_stmt", "expr_w_block",
  "expr_wo_block", "opt_comma", YY_NULLPTR
    };
    return yy_sname[yysymbol];
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


  const signed char Parser::yypact_ninf_ = -45;

  const signed char Parser::yytable_ninf_ = -92;

  const short
  Parser::yypact_[] =
  {
      17,     4,    41,    17,   -45,   -45,     1,   -45,   -45,   -45,
     -16,   -38,   -45,   -45,   -23,   -45,    39,   320,   159,   -45,
      31,   -45,     3,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   307,    12,   -45,   -45,   -45,   -45,
     -45,    15,    31,   243,    16,   243,   243,   243,   243,   243,
     243,   -45,   -45,    13,   -45,   243,   243,   -45,   -45,   102,
      10,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     318,    18,    19,    20,   -45,   320,   -45,    -4,   -45,   -45,
     201,    71,   349,   -45,   -45,    75,    21,    21,    21,   349,
     473,   473,   -45,   380,    63,    21,    21,   -45,   -45,   -45,
     411,   -45,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   -45,
      99,   -45,   -45,   320,   -45,   -45,     8,   473,   -45,    48,
     -45,    57,    72,   -45,   243,    61,   -45,   473,   -28,   -28,
     -28,   -28,   -28,   -28,    40,    40,    21,    21,   520,   504,
     473,   473,   473,   473,   -45,   -45,   243,   -45,   294,   -12,
     -45,   -29,   473,   -45,   473,   -45,   -45,   243,   -45,   -45,
     -45,   442,   -45
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     2,     4,     5,     0,     1,     3,    10,
      27,     0,    26,     9,     0,    12,     0,     0,     0,     7,
      27,     8,     0,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,     0,     0,    75,    77,    76,    78,
      79,    98,    27,     0,     0,     0,     0,     0,     0,     0,
       0,   104,    52,     0,    14,     0,     0,    18,    21,     0,
       0,    15,    93,    94,    99,    96,   106,   101,    92,    97,
       0,     0,    86,    87,    11,     0,    48,     0,    35,     6,
       0,     0,     0,    86,    87,     0,    55,    53,    54,     0,
     102,   103,   100,    89,   108,    56,    57,    20,    49,    19,
       0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,    16,    13,     0,    47,    83,     0,    81,    28,    25,
      84,     0,    31,    95,   107,     0,    50,    70,    64,    65,
      66,    69,    67,    68,    58,    59,    60,    61,    62,    63,
      71,    72,    74,    73,    85,    34,     0,    82,     0,     0,
      22,     0,    88,   105,    80,    24,    23,     0,    30,    32,
      33,     0,    29
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -45,   -45,   -45,    58,   -45,   -45,   -45,    92,    59,   -45,
     -45,   -45,    74,   -45,   -45,   -44,   -45,   -24,   -11,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,   -20,   -45,   -45,   -15,
     -14,   -45
  };

  const unsigned char
  Parser::yydefgoto_[] =
  {
       0,     2,     3,    57,     5,    11,    14,    15,    58,    59,
      60,   159,    16,   129,    61,    62,    77,    35,    63,    64,
      65,    66,   126,    67,    68,    69,    70,    94,    71,    83,
      84,   135
  };

  const short
  Parser::yytable_[] =
  {
      19,    17,     9,    72,    73,    12,   109,   110,   111,   112,
      78,    48,     6,    18,   167,    20,    36,    37,    38,    39,
      40,    41,    18,    82,    79,    86,    87,    88,    89,    90,
      91,    21,   120,    93,   123,    95,    96,    43,    13,   100,
       1,     7,    45,   168,    72,    73,   156,    22,    46,    47,
     124,   122,    12,    48,    10,    49,    50,    51,     4,    75,
     127,     8,   157,    18,    18,   101,    53,    92,    80,    85,
      55,   130,    56,   121,   -90,   -91,   111,   112,   132,   128,
     131,   120,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   155,
     120,   134,   154,    97,   158,    36,    37,    38,    39,    40,
      41,   160,    74,   161,   162,   163,    81,   169,    99,     0,
       0,     0,    42,     0,     0,     1,    43,    44,     0,     0,
       0,    45,     0,     0,   166,     0,   164,    46,    47,     0,
       0,     0,    48,     0,    49,    50,    51,   171,     0,     0,
     170,     0,     0,    18,    98,    53,     0,    54,     0,    55,
       0,    56,    36,    37,    38,    39,    40,    41,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
       0,     0,     1,    43,    44,     0,     0,     0,    45,     0,
       0,     0,     0,     0,    46,    47,     0,     0,     0,    48,
       0,    49,    50,    51,    36,    37,    38,    39,    40,    41,
      18,    52,    53,     0,    54,     0,    55,     0,    56,     0,
       0,     0,     0,     0,     0,    43,     0,     0,     0,     0,
      45,     0,     0,     0,     0,     0,    46,    47,     0,     0,
       0,    48,     0,    49,    50,    51,    36,    37,    38,    39,
      40,    41,    18,     0,    53,   125,     0,     0,    55,     0,
      56,     0,     0,     0,     0,     0,     0,    43,     0,     0,
       0,     0,    45,     0,     0,     0,     0,     0,    46,    47,
       0,     0,     0,    48,     0,    49,    50,    51,     0,     0,
       0,     0,     0,     0,    18,   165,    53,     0,     0,     0,
      55,     0,    56,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     0,     0,    33,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     0,     0,    33,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       0,     0,    33,     0,   102,   103,   104,    34,   105,   106,
     107,   108,   109,   110,   111,   112,     0,     0,     0,     0,
      34,    76,     0,   113,   114,   115,   116,   117,   118,     0,
     119,     0,     0,    34,     0,   102,   103,   104,   120,   105,
     106,   107,   108,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,   113,   114,   115,   116,   117,   118,
      18,     0,     0,     0,     0,     0,   102,   103,   104,   120,
     105,   106,   107,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,   113,   114,   115,   116,   117,
     118,     0,     0,     0,   133,     0,     0,   102,   103,   104,
     120,   105,   106,   107,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,     0,   136,     0,     0,     0,     0,   102,   103,
     104,   120,   105,   106,   107,   108,   109,   110,   111,   112,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,     0,     0,     0,     0,   172,     0,   102,
     103,   104,   120,   105,   106,   107,   108,   109,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,   113,   114,
     115,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,   103,   104,   120,   105,   106,   107,   108,   109,   110,
     111,   112,     0,     0,     0,     0,     0,   103,   104,   113,
     105,   106,   107,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,   120,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     120
  };

  const short
  Parser::yycheck_[] =
  {
      11,    39,     1,    18,    18,    21,    34,    35,    36,    37,
      34,    40,     8,    51,    26,    38,     3,     4,     5,     6,
       7,     8,    51,    43,    35,    45,    46,    47,    48,    49,
      50,    54,    60,    53,    38,    55,    56,    24,    54,    59,
      23,     0,    29,    55,    59,    59,    38,     8,    35,    36,
      54,    75,    21,    40,    53,    42,    43,    44,     0,    56,
      80,     3,    54,    51,    51,    55,    53,    54,    53,    53,
      57,    82,    59,    55,    55,    55,    36,    37,    89,     8,
       5,    60,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   123,
      60,    38,     3,     1,    56,     3,     4,     5,     6,     7,
       8,    54,    20,    41,   134,    54,    42,   161,    59,    -1,
      -1,    -1,    20,    -1,    -1,    23,    24,    25,    -1,    -1,
      -1,    29,    -1,    -1,   158,    -1,   156,    35,    36,    -1,
      -1,    -1,    40,    -1,    42,    43,    44,   167,    -1,    -1,
     161,    -1,    -1,    51,    52,    53,    -1,    55,    -1,    57,
      -1,    59,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    23,    24,    25,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,    40,
      -1,    42,    43,    44,     3,     4,     5,     6,     7,     8,
      51,    52,    53,    -1,    55,    -1,    57,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    35,    36,    -1,    -1,
      -1,    40,    -1,    42,    43,    44,     3,     4,     5,     6,
       7,     8,    51,    -1,    53,    54,    -1,    -1,    57,    -1,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    35,    36,
      -1,    -1,    -1,    40,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    51,     1,    53,    -1,    -1,    -1,
      57,    -1,    59,    -1,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    -1,    22,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    22,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    22,    -1,    26,    27,    28,    53,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      53,    54,    -1,    45,    46,    47,    48,    49,    50,    -1,
      52,    -1,    -1,    53,    -1,    26,    27,    28,    60,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,    60,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    -1,    -1,    26,    27,    28,
      60,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    -1,    52,    -1,    -1,    -1,    -1,    26,    27,
      28,    60,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,    -1,    55,    -1,    26,
      27,    28,    60,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    28,    60,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    27,    28,    45,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    23,    82,    83,    84,    85,     8,     0,    84,     1,
      53,    86,    21,    54,    87,    88,    93,    39,    51,    99,
      38,    54,     8,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    22,    53,    98,     3,     4,     5,     6,
       7,     8,    20,    24,    25,    29,    35,    36,    40,    42,
      43,    44,    52,    53,    55,    57,    59,    84,    89,    90,
      91,    95,    96,    99,   100,   101,   102,   104,   105,   106,
     107,   109,   110,   111,    88,    56,    54,    97,    98,    99,
      53,    93,   107,   110,   111,    53,   107,   107,   107,   107,
     107,   107,    54,   107,   108,   107,   107,     1,    52,    89,
     107,    55,    26,    27,    28,    30,    31,    32,    33,    34,
      35,    36,    37,    45,    46,    47,    48,    49,    50,    52,
      60,    55,    98,    38,    54,    54,   103,   107,     8,    94,
      99,     5,    99,    54,    38,   112,    52,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,     3,    98,    38,    54,    56,    92,
      54,    41,   107,    54,   107,     1,    98,    26,    55,    96,
      99,   107,    55
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    81,    82,    83,    83,    84,    85,    85,    86,    86,
      86,    87,    87,    88,    89,    89,    89,    89,    89,    90,
      90,    90,    91,    92,    92,    92,    93,    93,    94,    95,
      95,    96,    96,    96,    97,    97,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    99,
      99,    99,    99,   100,   100,   100,   100,   100,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   102,   102,   102,   102,   102,
     103,   103,   104,   104,   105,   106,   107,   107,   108,   108,
     109,   109,   110,   110,   110,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   112,   112
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     1,     6,     4,     3,     2,
       1,     3,     1,     4,     1,     1,     2,     2,     1,     2,
       2,     1,     4,     2,     2,     0,     1,     0,     1,     7,
       5,     3,     5,     5,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     3,
       4,     3,     2,     2,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       3,     1,     4,     3,     3,     3,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       2,     1,     2,     2,     1,     4,     1,     1,     0
  };




#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   118,   118,   122,   123,   130,   135,   140,   148,   149,
     150,   154,   155,   159,   162,   163,   167,   168,   169,   173,
     175,   176,   185,   189,   190,   191,   195,   196,   200,   204,
     206,   212,   213,   214,   225,   226,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   247,
     248,   249,   250,   254,   255,   256,   257,   258,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     275,   276,   277,   278,   279,   283,   284,   285,   286,   287,
     292,   293,   301,   302,   305,   309,   314,   315,   319,   320,
     324,   325,   329,   330,   331,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   350,   351
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
#line 3132 "yaccfile.tab.cc"

#line 353 "src/parser/yaccfile.yy"


namespace mr
{
    
    void Parser::error(const Parser::location_type &loc, const std::string &message)
    {
        // i don't care about error's of bison
        std::cerr << "Error in " << this->input_file_name << ":" << loc.begin.line << ":" << loc.begin.column
            <<":\n"
            << message << std::endl;
    }
}
