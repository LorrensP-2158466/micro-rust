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
#line 38 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"

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
#line 118 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                { driver.set_ast(m_u<Ast>(std::move(yystack_[0].value.as < std::vector<U<Item>> > ()))); }
#line 1785 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 3: // item_list: item_list item
#line 122 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     {yystack_[1].value.as < std::vector<U<Item>> > ().push_back(std::move(yystack_[0].value.as < U<Item> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Item>> > (), yystack_[1].value.as < std::vector<U<Item>> > ());}
#line 1791 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 4: // item_list: item
#line 123 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           {
        auto vec = std::vector<U<Item>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Item> > ()));
        yylhs.value.as < std::vector<U<Item>> > () = std::move(vec) ;}
#line 1800 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 5: // item: function_decl
#line 130 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                  { DEFAULT_ACTION(yylhs.value.as < U<Item> > (), yystack_[0].value.as < U<FunDecl> > ()); }
#line 1806 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 6: // function_decl: FN IDENTIFIER func_decl_args ARROW type block_expr
#line 136 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
    { 
        const auto loc = yystack_[5].location + yystack_[0].value.as < U<BlockExpr> > ()->loc;
        const auto decl_loc = yystack_[5].location + yystack_[1].location;
        yylhs.value.as < U<FunDecl> > () = FunDecl::make_unique(
            yystack_[4].value.as < Token > ().string_value(),
            std::move(yystack_[3].value.as < std::vector<FunArg> > ()),
            std::move(yystack_[1].value.as < Type > ()),
            std::move(yystack_[0].value.as < U<BlockExpr> > ()),
            loc,
            decl_loc
        );
    }
#line 1823 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 7: // function_decl: FN IDENTIFIER func_decl_args block_expr
#line 149 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
    { 
        const auto loc = yystack_[3].location + yystack_[0].value.as < U<BlockExpr> > ()->loc;
        const auto decl_loc = yystack_[3].location + yystack_[1].location;
        yylhs.value.as < U<FunDecl> > () = FunDecl::make_unique(
            yystack_[2].value.as < Token > ().string_value(),
            std::move(yystack_[1].value.as < std::vector<FunArg> > ()),
            Type(location(yystack_[0].value.as < U<BlockExpr> > ()->loc.begin, yystack_[0].value.as < U<BlockExpr> > ()->loc.begin + 1)),
            std::move(yystack_[0].value.as < U<BlockExpr> > ()), 
            loc, 
            decl_loc
        );
    }
#line 1840 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 8: // func_decl_args: LPAREN func_arg_list RPAREN
#line 164 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                  {yylhs.value.as < std::vector<FunArg> > () = std::move(yystack_[1].value.as < std::vector<FunArg> > ());}
#line 1846 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 9: // func_decl_args: LPAREN RPAREN
#line 165 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                    { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{};}
#line 1852 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 10: // func_decl_args: error
#line 166 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
            { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{};}
#line 1858 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 11: // func_arg_list: func_arg_list COMMA func_arg
#line 170 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                   { yystack_[2].value.as < std::vector<FunArg> > ().push_back(std::move(yystack_[0].value.as < FunArg > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<FunArg> > (), yystack_[2].value.as < std::vector<FunArg> > ());}
#line 1864 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 12: // func_arg_list: func_arg
#line 171 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
               { yylhs.value.as < std::vector<FunArg> > () = std::vector<FunArg>{}; yylhs.value.as < std::vector<FunArg> > ().push_back(std::move(yystack_[0].value.as < FunArg > ())); }
#line 1870 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 13: // func_arg: opt_mut IDENTIFIER COLON type
#line 175 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                    { yylhs.value.as < FunArg > () = FunArg{yystack_[2].value.as < Token > ().string_value(), std::move(yystack_[0].value.as < Type > ()), yystack_[3].value.as < Mut > ().loc + yystack_[0].value.as < Type > ().loc, yystack_[3].value.as < Mut > ()}; }
#line 1876 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 14: // stmt: SEMICOLON
#line 178 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                {yylhs.value.as < U<Stmt> > () = m_u<EmptyStmt>(yystack_[0].location);}
#line 1882 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 15: // stmt: let
#line 179 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
          { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[0].value.as < U<LetStmt> > ()); }
#line 1888 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 16: // stmt: RETURN SEMICOLON
#line 180 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                       {  yylhs.value.as < U<Stmt> > () = m_u<Return>(yystack_[1].location + yystack_[0].location, m_u<Unit>(yystack_[0].location) ); }
#line 1894 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 17: // stmt: BREAK SEMICOLON
#line 181 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                      {  yylhs.value.as < U<Stmt> > () = m_u<Break>(yystack_[1].location + yystack_[0].location, m_u<Unit>(yystack_[0].location)); }
#line 1900 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 18: // stmt: CONTINUE SEMICOLON
#line 182 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                         {  yylhs.value.as < U<Stmt> > () = m_u<Continue>(yystack_[1].location + yystack_[0].location); }
#line 1906 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 19: // stmt: expr_stmt SEMICOLON
#line 183 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                          { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[1].value.as < U<Expr> > ());}
#line 1912 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 20: // stmt: print_ln SEMICOLON
#line 185 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                         { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[1].value.as < U<PrintLn> > ());}
#line 1918 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 21: // stmt: item
#line 186 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           { DEFAULT_ACTION(yylhs.value.as < U<Stmt> > (), yystack_[0].value.as < U<Item> > ()); }
#line 1924 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 22: // stmt_list: stmt_list stmt
#line 190 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yystack_[1].value.as < std::vector<U<Stmt>> > ().push_back(std::move(yystack_[0].value.as < U<Stmt> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Stmt>> > (), yystack_[1].value.as < std::vector<U<Stmt>> > ()); }
#line 1930 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 23: // stmt_list: stmt_list error
#line 192 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                      { DEFAULT_ACTION(yylhs.value.as < std::vector<U<Stmt>> > (), yystack_[1].value.as < std::vector<U<Stmt>> > ());}
#line 1936 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 24: // stmt_list: stmt
#line 193 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           {
        auto vec = std::vector<U<Stmt>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Stmt> > ()));
        yylhs.value.as < std::vector<U<Stmt>> > () = std::move(vec); 
      }
#line 1946 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 25: // print_ln: PRINT_LN LPAREN STR_LITERAL RPAREN
#line 202 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                         { yylhs.value.as < U<PrintLn> > () = m_u<PrintLn>(yystack_[1].value.as < Token > ().string_value(), yystack_[3].location + yystack_[0].location); }
#line 1952 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 26: // type_decl: COLON type
#line 206 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < std::optional<Type> > (), yystack_[0].value.as < Type > ()); }
#line 1958 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 27: // type_decl: COLON error
#line 207 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                  { yylhs.value.as < std::optional<Type> > () = Type::infer(yystack_[1].location);  }
#line 1964 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 28: // type_decl: %empty
#line 208 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
      { yylhs.value.as < std::optional<Type> > () = {}; }
#line 1970 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 29: // opt_mut: MUT
#line 212 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
         { yylhs.value.as < Mut > () = Mut{true, yystack_[0].location}; }
#line 1976 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 30: // opt_mut: %empty
#line 213 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
         { yylhs.value.as < Mut > () = Mut{false, location()}; }
#line 1982 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 31: // ident: IDENTIFIER
#line 217 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                 { yylhs.value.as < Identifier > () = Identifier{yystack_[0].value.as < Token > ().string_value(), yystack_[0].location};}
#line 1988 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 32: // let: LET opt_mut ident type_decl EQ expr SEMICOLON
#line 222 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
      {yylhs.value.as < U<LetStmt> > () = LetStmt::make_unique_init(std::move(yystack_[4].value.as < Identifier > ()), std::move(yystack_[3].value.as < std::optional<Type> > ()), std::move(yystack_[1].value.as < U<Expr> > ()), yystack_[5].value.as < Mut > (), yystack_[6].location + yystack_[0].location);}
#line 1994 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 33: // let: LET opt_mut ident type_decl SEMICOLON
#line 223 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                            {
        yylhs.value.as < U<LetStmt> > () = LetStmt::make_unique_decl(std::move(yystack_[2].value.as < Identifier > ()), std::move(yystack_[1].value.as < std::optional<Type> > ()), yystack_[3].value.as < Mut > (), yystack_[4].location + yystack_[0].location);
    }
#line 2002 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 34: // if_expr: IF expr block_expr
#line 229 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                         { yylhs.value.as < U<IfElse> > () = m_u<IfElse>(yystack_[2].location, std::move(yystack_[1].value.as < U<Expr> > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ()), location()); }
#line 2008 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 35: // if_expr: IF expr block_expr ELSE if_expr
#line 230 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                      {yylhs.value.as < U<IfElse> > () = m_u<IfElse>(yystack_[4].location, std::move(yystack_[3].value.as < U<Expr> > ()), std::move(yystack_[2].value.as < U<BlockExpr> > ()), yystack_[1].location, std::move(yystack_[0].value.as < U<IfElse> > ())); }
#line 2014 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 36: // if_expr: IF expr block_expr ELSE block_expr
#line 231 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                         {yylhs.value.as < U<IfElse> > () = m_u<IfElse>(yystack_[4].location, std::move(yystack_[3].value.as < U<Expr> > ()), std::move(yystack_[2].value.as < U<BlockExpr> > ()), yystack_[1].location, std::move(yystack_[0].value.as < U<BlockExpr> > ())); }
#line 2020 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 37: // type_list: type_list COMMA type
#line 242 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                           {yylhs.value.as < std::vector<Type> > () = std::move(yystack_[2].value.as < std::vector<Type> > ()); yylhs.value.as < std::vector<Type> > ().push_back(std::move(yystack_[0].value.as < Type > ()));}
#line 2026 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 38: // type_list: type
#line 243 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           {yylhs.value.as < std::vector<Type> > () = std::vector<Type>(); yylhs.value.as < std::vector<Type> > ().push_back(std::move(yystack_[0].value.as < Type > ()));}
#line 2032 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 39: // type: I8
#line 248 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::I8, yystack_[0].location); }
#line 2038 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 40: // type: I16
#line 249 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::I16, yystack_[0].location); }
#line 2044 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 41: // type: I32
#line 250 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::I32, yystack_[0].location); }
#line 2050 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 42: // type: I64
#line 251 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::I64, yystack_[0].location); }
#line 2056 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 43: // type: ISIZE
#line 252 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
            { yylhs.value.as < Type > () = Type(primitive_type::ISIZE, yystack_[0].location); }
#line 2062 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 44: // type: U8
#line 253 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::U8, yystack_[0].location); }
#line 2068 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 45: // type: U16
#line 254 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::U16, yystack_[0].location); }
#line 2074 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 46: // type: U32
#line 255 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
         { yylhs.value.as < Type > () = Type(primitive_type::U32, yystack_[0].location); }
#line 2080 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 47: // type: U64
#line 256 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
          { yylhs.value.as < Type > () = Type(primitive_type::U64, yystack_[0].location); }
#line 2086 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 48: // type: USIZE
#line 257 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
            { yylhs.value.as < Type > () = Type(primitive_type::USIZE, yystack_[0].location); }
#line 2092 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 49: // type: BOOL
#line 258 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           { yylhs.value.as < Type > () = Type(primitive_type::BOOL, yystack_[0].location); }
#line 2098 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 50: // type: UNDERSCORE
#line 259 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                 { yylhs.value.as < Type > () = Type(Type::Infer{}, yystack_[0].location); }
#line 2104 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 51: // type: LPAREN type_list RPAREN
#line 260 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                              { yylhs.value.as < Type > () = Type(std::move(yystack_[1].value.as < std::vector<Type> > ()), yystack_[2].location + yystack_[0].location);}
#line 2110 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 52: // type: LPAREN RPAREN
#line 261 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                    { yylhs.value.as < Type > () = Type(yystack_[1].location + yystack_[0].location); }
#line 2116 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 53: // type: FN LPAREN type_list RPAREN ARROW type
#line 262 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                            { 
        auto ret_loc = yystack_[0].value.as < Type > ().loc;
        yylhs.value.as < Type > () = Type{Type::FnPointer{std::move(yystack_[3].value.as < std::vector<Type> > ()), m_u<Type>(std::move(yystack_[0].value.as < Type > ()))}, yystack_[5].location + ret_loc};
    }
#line 2125 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 54: // type: FN LPAREN type_list RPAREN
#line 266 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                  { 
        yylhs.value.as < Type > () = Type{Type::FnPointer{std::move(yystack_[1].value.as < std::vector<Type> > ()), m_u<Type>(Type(yystack_[0].location))}, yystack_[3].location + yystack_[0].location};
    }
#line 2133 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 55: // type: FN LPAREN RPAREN ARROW type
#line 269 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                  { 
        auto ret_loc = yystack_[0].value.as < Type > ().loc;
        yylhs.value.as < Type > () = Type{Type::FnPointer{std::vector<Type>(), m_u<Type>(std::move(yystack_[0].value.as < Type > ()))}, yystack_[4].location + ret_loc};
    }
#line 2142 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 56: // type: FN LPAREN RPAREN
#line 273 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                        { 
        yylhs.value.as < Type > () = Type{Type::FnPointer{std::vector<Type>(), m_u<Type>(Type(yystack_[0].location))}, yystack_[2].location + yystack_[0].location};
    }
#line 2150 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 57: // block_expr: LBRACE stmt_list RBRACE
#line 279 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                              { yylhs.value.as < U<BlockExpr> > () = m_u<BlockExpr>(std::move(yystack_[1].value.as < std::vector<U<Stmt>> > ()), m_u<Unit>(yystack_[0].location), yystack_[2].location + yystack_[0].location); }
#line 2156 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 58: // block_expr: LBRACE stmt_list expr RBRACE
#line 280 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                    { yylhs.value.as < U<BlockExpr> > () = m_u<BlockExpr>(std::move(yystack_[2].value.as < std::vector<U<Stmt>> > ()), std::move(yystack_[1].value.as < U<Expr> > ()), yystack_[3].location + yystack_[0].location); }
#line 2162 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 59: // block_expr: LBRACE expr RBRACE
#line 281 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                          { yylhs.value.as < U<BlockExpr> > () = m_u<BlockExpr>(std::vector<U<Stmt>>{}, std::move(yystack_[1].value.as < U<Expr> > ()), yystack_[2].location + yystack_[0].location); }
#line 2168 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 60: // block_expr: LBRACE RBRACE
#line 282 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yylhs.value.as < U<BlockExpr> > () = m_u<BlockExpr>(std::vector<U<Stmt>>{}, m_u<Unit>(yystack_[1].location + yystack_[0].location), yystack_[1].location + yystack_[0].location); }
#line 2174 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 61: // unary_op_expr: MINUS expr
#line 286 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                              { yylhs.value.as < U<UnaryOpExpr> > () = m_u<UnaryOpExpr>(UnaryOp::Negate, yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2180 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 62: // unary_op_expr: STAR expr
#line 287 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                            { yylhs.value.as < U<UnaryOpExpr> > () = m_u<UnaryOpExpr>(UnaryOp::Deref, yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2186 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 63: // unary_op_expr: BANG expr
#line 288 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                          { yylhs.value.as < U<UnaryOpExpr> > () = m_u<UnaryOpExpr>(UnaryOp::Not, yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2192 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 64: // unary_op_expr: AMPERSAND expr
#line 289 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                               { yylhs.value.as < U<UnaryOpExpr> > () = m_u<UnaryOpExpr>(UnaryOp::Borrow, yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2198 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 65: // unary_op_expr: AMPERSAND_MUT expr
#line 290 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                       { yylhs.value.as < U<UnaryOpExpr> > () = m_u<UnaryOpExpr>(UnaryOp::MutBorrow, yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2204 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 66: // bin_op_expr: expr PLUS expr
#line 294 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Plus, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2210 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 67: // bin_op_expr: expr MINUS expr
#line 295 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                      { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Min, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2216 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 68: // bin_op_expr: expr STAR expr
#line 296 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Mul, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2222 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 69: // bin_op_expr: expr SLASH expr
#line 297 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                      { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Div, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2228 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 70: // bin_op_expr: expr L_AND expr
#line 298 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                      { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::L_AND, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2234 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 71: // bin_op_expr: expr L_OR expr
#line 299 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::L_OR, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2240 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 72: // bin_op_expr: expr EQEQ expr
#line 300 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                     { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Eq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2246 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 73: // bin_op_expr: expr NE expr
#line 301 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::NEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2252 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 74: // bin_op_expr: expr LT expr
#line 302 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Lt, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2258 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 75: // bin_op_expr: expr GT expr
#line 303 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::Gt, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2264 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 76: // bin_op_expr: expr GE expr
#line 304 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::GtEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2270 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 77: // bin_op_expr: expr LE expr
#line 305 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { yylhs.value.as < U<Expr> > () = m_u<BinOpExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), BinOp::LtEq, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2276 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 78: // bin_op_expr: expr EQ expr
#line 307 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = m_u<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::Eq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2282 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 79: // bin_op_expr: expr PLUS_EQ expr
#line 308 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = m_u<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::PlusEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2288 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 80: // bin_op_expr: expr MIN_EQ expr
#line 309 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = m_u<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::MinEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2294 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 81: // bin_op_expr: expr DIV_EQ expr
#line 310 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = m_u<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::DivEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2300 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 82: // bin_op_expr: expr MUL_EQ expr
#line 311 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                        { yylhs.value.as < U<Expr> > () = m_u<AssignExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), AssignOp::MulEq, std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2306 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 83: // literal: DEC_LITERAL
#line 315 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                  { yylhs.value.as < U<Literal> > () = Literal::make_int_lit(yystack_[0].value.as < Token > ().symbol, yystack_[0].location);}
#line 2312 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 84: // literal: STR_LITERAL
#line 316 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                  { yylhs.value.as < U<Literal> > () = Literal::make_str_lit(yystack_[0].value.as < Token > ().symbol, yystack_[0].location); }
#line 2318 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 85: // literal: FLOAT_LITERAL
#line 317 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                    { assert(1 && "How did we get here"); }
#line 2324 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 86: // literal: TRUE
#line 318 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           { yylhs.value.as < U<Literal> > () = Literal::make_bool_lit(yystack_[0].value.as < Token > ().symbol, yystack_[0].location); }
#line 2330 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 87: // literal: FALSE
#line 319 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
            { yylhs.value.as < U<Literal> > () = Literal::make_bool_lit(yystack_[0].value.as < Token > ().symbol, yystack_[0].location); }
#line 2336 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 88: // call_expr_args: call_expr_args COMMA expr
#line 324 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                { yystack_[2].value.as < std::vector<U<Expr>> > ().push_back(std::move(yystack_[0].value.as < U<Expr> > ())); DEFAULT_ACTION(yylhs.value.as < std::vector<U<Expr>> > (), yystack_[2].value.as < std::vector<U<Expr>> > ()); }
#line 2342 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 89: // call_expr_args: expr
#line 325 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           { 
        auto vec = std::vector<U<Expr>>();
        vec.push_back(std::move(yystack_[0].value.as < U<Expr> > ()));
        yylhs.value.as < std::vector<U<Expr>> > () = std::move(vec);
        }
#line 2352 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 90: // call_expr: expr LPAREN call_expr_args RPAREN
#line 333 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                        { yylhs.value.as < U<CallExpr> > () = m_u<CallExpr>(yystack_[3].location + yystack_[0].location, std::move(yystack_[3].value.as < U<Expr> > ()), std::move(yystack_[1].value.as < std::vector<U<Expr>> > ())); }
#line 2358 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 91: // call_expr: expr LPAREN RPAREN
#line 334 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                         { yylhs.value.as < U<CallExpr> > () = m_u<CallExpr>(yystack_[2].location + yystack_[0].location, std::move(yystack_[2].value.as < U<Expr> > ()), std::vector<U<Expr>>{}); }
#line 2364 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 92: // while_expr: WHILE expr block_expr
#line 338 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                            {yylhs.value.as < U<WhileLoop> > () = m_u<WhileLoop>(yystack_[2].location, std::move(yystack_[1].value.as < U<Expr> > ()), std::move(yystack_[0].value.as < U<BlockExpr> > ())); }
#line 2370 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 93: // tuple_index_expr: expr DOT DEC_LITERAL
#line 342 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                           { yylhs.value.as < U<TupleIndexExpr> > () = m_u<TupleIndexExpr>(std::move(yystack_[2].value.as < U<Expr> > ()), Literal::make_int_lit(yystack_[0].value.as < Token > ().symbol, yystack_[0].location));}
#line 2376 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 94: // expr: expr_w_block
#line 347 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                   { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2382 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 95: // expr: expr_wo_block
#line 348 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                    { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2388 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 96: // expr_list: expr_list COMMA expr
#line 352 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                           { yystack_[2].value.as < std::vector<U<Expr>> > ().push_back(std::move(yystack_[0].value.as < U<Expr> > ())); yylhs.value.as < std::vector<U<Expr>> > () = std::move(yystack_[2].value.as < std::vector<U<Expr>> > ());}
#line 2394 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 97: // expr_list: expr
#line 353 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
           {yylhs.value.as < std::vector<U<Expr>> > () = std::vector<U<Expr>>(); yylhs.value.as < std::vector<U<Expr>> > ().push_back(std::move(yystack_[0].value.as < U<Expr> > ()));}
#line 2400 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 98: // expr_stmt: expr_w_block
#line 357 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                    { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ());}
#line 2406 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 99: // expr_stmt: expr_wo_block
#line 358 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                    { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ()); }
#line 2412 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 100: // expr_w_block: while_expr
#line 362 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<WhileLoop> > ()); }
#line 2418 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 101: // expr_w_block: if_expr
#line 363 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<IfElse> > ()); }
#line 2424 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 102: // expr_w_block: block_expr
#line 364 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<BlockExpr> > ()); }
#line 2430 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 103: // expr_wo_block: LPAREN expr RPAREN
#line 367 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                         { yystack_[1].value.as < U<Expr> > ()->loc = yystack_[2].location + yystack_[0].location; DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[1].value.as < U<Expr> > ()); }
#line 2436 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 104: // expr_wo_block: bin_op_expr
#line 368 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Expr> > ()); }
#line 2442 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 105: // expr_wo_block: tuple_index_expr
#line 369 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                          { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<TupleIndexExpr> > ()); }
#line 2448 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 106: // expr_wo_block: IDENTIFIER
#line 370 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                            { yylhs.value.as < U<Expr> > () = m_u<Identifier>(yystack_[0].value.as < Token > ().string_value(), yystack_[0].location); }
#line 2454 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 107: // expr_wo_block: unary_op_expr
#line 371 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                {DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<UnaryOpExpr> > ()); }
#line 2460 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 108: // expr_wo_block: LPAREN RPAREN
#line 372 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                               { yylhs.value.as < U<Expr> > () = m_u<Unit>(yystack_[1].location + yystack_[0].location); }
#line 2466 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 109: // expr_wo_block: call_expr
#line 373 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                 { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<CallExpr> > ()); }
#line 2472 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 110: // expr_wo_block: RETURN expr
#line 374 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                     { yylhs.value.as < U<Expr> > () = m_u<Return>(yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2478 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 111: // expr_wo_block: BREAK expr
#line 375 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                    { yylhs.value.as < U<Expr> > () = m_u<Break>(yystack_[1].location, std::move(yystack_[0].value.as < U<Expr> > ())); }
#line 2484 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 112: // expr_wo_block: CONTINUE
#line 376 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                  { yylhs.value.as < U<Expr> > () = m_u<Continue>(yystack_[0].location); }
#line 2490 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 113: // expr_wo_block: LPAREN expr_list opt_comma RPAREN
#line 377 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
                                         { yylhs.value.as < U<Expr> > () = m_u<TupleExpr>(std::move(yystack_[2].value.as < std::vector<U<Expr>> > ()), yystack_[3].location + yystack_[0].location); }
#line 2496 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 114: // expr_wo_block: literal
#line 378 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
              { DEFAULT_ACTION(yylhs.value.as < U<Expr> > (), yystack_[0].value.as < U<Literal> > ()); }
#line 2502 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 115: // opt_comma: COMMA
#line 383 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
            {}
#line 2508 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;

  case 116: // opt_comma: %empty
#line 384 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
      {}
#line 2514 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"
    break;


#line 2518 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"

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


  const signed char Parser::yypact_ninf_ = -53;

  const signed char Parser::yytable_ninf_ = -100;

  const short
  Parser::yypact_[] =
  {
     -10,    15,    25,   -10,   -53,   -53,     4,   -53,   -53,   -53,
     -19,    11,   -53,   -53,   -30,   -53,    43,   425,   173,   -53,
      32,   -53,   -52,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,     5,   392,     8,   -53,   -53,
     -53,   -53,   -53,   -53,    32,   341,    17,   341,   341,   341,
     341,   215,   257,    13,   -53,    12,   -53,   341,   341,   -53,
     -53,   131,    29,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   436,    33,    34,    36,   -53,   425,   407,   -53,
     -28,   -53,   -53,    79,   341,   341,   -53,   467,   -53,   -53,
     104,   -39,   -39,   -39,   467,   -53,   591,   -53,   591,   -53,
     -53,   498,    73,   -39,   -39,   -53,   -53,   -53,   529,   -53,
     341,   341,   341,   341,   341,   341,   341,   341,   341,   341,
     341,   341,   341,   341,   341,   341,   341,   -53,   299,   109,
     -53,   -53,    74,   -26,   425,   -53,   -53,    58,   -53,    61,
      76,   -53,   341,    65,   -53,   591,    92,    92,    92,    92,
      92,    92,   105,   105,   -39,   -39,   653,   622,   591,   591,
     591,   591,   -53,     6,   591,   -53,   425,    81,   -53,    63,
     -17,   -53,   -29,   591,   -53,   341,   -53,   -53,   425,   -53,
     -53,   341,   -53,   -53,   -53,   591,   -53,   560,   -53
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     2,     4,     5,     0,     1,     3,    10,
      30,     0,    29,     9,     0,    12,     0,     0,     0,     7,
      30,     8,     0,    50,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,     0,     0,     0,    83,    85,
      84,    86,    87,   106,    30,     0,     0,     0,     0,     0,
       0,     0,     0,   112,    60,     0,    14,     0,     0,    21,
      24,     0,     0,    15,   101,   102,   107,   104,   114,   109,
     100,   105,     0,     0,    94,    95,    11,     0,     0,    52,
       0,    38,     6,     0,     0,     0,   112,     0,    94,    95,
       0,    63,    61,    62,     0,    16,   110,    17,   111,    18,
     108,    97,   116,    64,    65,    23,    57,    22,     0,    20,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,     0,     0,
      19,    13,    56,     0,     0,    51,    31,    28,    92,     0,
      34,   103,   115,     0,    58,    78,    72,    73,    74,    77,
      75,    76,    66,    67,    68,    69,    70,    71,    79,    80,
      82,    81,    91,     0,    89,    93,     0,    54,    37,     0,
       0,    25,     0,    96,   113,     0,    90,    55,     0,    27,
      26,     0,    33,    35,    36,    88,    53,     0,    32
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -53,   -53,   -53,    42,   -53,   -53,   -53,   101,    62,   -53,
     -53,   -53,    78,   -53,   -53,   -47,    52,   -16,    -4,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -18,   -53,   -53,   -15,
     -12,   -53
  };

  const unsigned char
  Parser::yydefgoto_[] =
  {
       0,     2,     3,    59,     5,    11,    14,    15,    60,    61,
      62,   170,    16,   137,    63,    64,    80,    81,    65,    66,
      67,    68,   163,    69,    70,    71,    96,   102,    73,    88,
      89,   143
  };

  const short
  Parser::yytable_[] =
  {
      72,    37,    12,    74,    77,     9,    75,    19,    20,   181,
     134,    50,   134,     1,   128,    38,    39,    40,    41,    42,
      43,   129,    18,     6,    21,     7,   135,    87,   167,    91,
      92,    93,    94,    82,    98,    13,    45,   101,   182,   103,
     104,    47,     4,   108,   175,     8,    74,    48,    49,    75,
      17,    22,    50,    12,    84,    85,    86,    10,    78,    18,
     176,   131,    18,    18,   179,    55,   100,    98,    99,    57,
      90,    58,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,   138,   109,    34,    35,   136,   130,   -98,
     140,   -99,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   139,
     164,   142,   165,   166,   169,   171,    36,   172,   168,   174,
     178,    76,    83,   107,   173,   183,   117,   118,   119,   120,
     133,     0,   105,     0,    38,    39,    40,    41,    42,    43,
       0,   119,   120,     0,     0,   128,     0,     0,     0,     0,
     177,    44,   129,   180,     1,    45,    46,   185,   128,     0,
      47,     0,   186,   187,     0,   129,    48,    49,   184,     0,
       0,    50,     0,    51,    52,    53,    38,    39,    40,    41,
      42,    43,    18,   106,    55,     0,    56,     0,    57,     0,
      58,     0,     0,    44,     0,     0,     1,    45,    46,     0,
       0,     0,    47,     0,     0,     0,     0,     0,    48,    49,
       0,     0,     0,    50,     0,    51,    52,    53,    38,    39,
      40,    41,    42,    43,    18,    54,    55,     0,    56,     0,
      57,     0,    58,     0,     0,     0,     0,     0,     0,    45,
       0,     0,     0,     0,    47,     0,     0,     0,     0,     0,
      48,    49,     0,     0,     0,    50,     0,    84,    85,    86,
      38,    39,    40,    41,    42,    43,    18,     0,    55,     0,
      95,     0,    57,     0,    58,     0,     0,     0,     0,     0,
       0,    45,     0,     0,     0,     0,    47,     0,     0,     0,
       0,     0,    48,    49,     0,     0,     0,    50,     0,    84,
      85,    86,    38,    39,    40,    41,    42,    43,    18,     0,
      55,     0,    97,     0,    57,     0,    58,     0,     0,     0,
       0,     0,     0,    45,     0,     0,     0,     0,    47,     0,
       0,     0,     0,     0,    48,    49,     0,     0,     0,    50,
       0,    84,    85,    86,    38,    39,    40,    41,    42,    43,
      18,     0,    55,   162,     0,     0,    57,     0,    58,     0,
       0,     0,     0,     0,     0,    45,     0,     0,     0,     0,
      47,     0,     0,     0,     0,     0,    48,    49,     0,     0,
       0,    50,     0,    84,    85,    86,     0,     0,     0,     0,
       0,     0,    18,     0,    55,     0,     0,     0,    57,     0,
      58,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     0,     0,    34,    35,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,     0,    34,
      35,     0,     0,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    36,    79,    34,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,   132,   110,   111,   112,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,     0,     0,     0,    36,     0,
       0,   121,   122,   123,   124,   125,   126,     0,   127,   128,
       0,     0,     0,   110,   111,   112,   129,   113,   114,   115,
     116,   117,   118,   119,   120,     0,     0,     0,     0,     0,
       0,     0,   121,   122,   123,   124,   125,   126,    18,     0,
     128,     0,     0,     0,   110,   111,   112,   129,   113,   114,
     115,   116,   117,   118,   119,   120,     0,     0,     0,     0,
       0,     0,     0,   121,   122,   123,   124,   125,   126,     0,
       0,   128,   141,     0,     0,   110,   111,   112,   129,   113,
     114,   115,   116,   117,   118,   119,   120,     0,     0,     0,
       0,     0,     0,     0,   121,   122,   123,   124,   125,   126,
       0,   144,   128,     0,     0,     0,   110,   111,   112,   129,
     113,   114,   115,   116,   117,   118,   119,   120,     0,     0,
       0,     0,     0,     0,     0,   121,   122,   123,   124,   125,
     126,     0,     0,   128,     0,   188,     0,   110,   111,   112,
     129,   113,   114,   115,   116,   117,   118,   119,   120,     0,
       0,     0,     0,     0,     0,     0,   121,   122,   123,   124,
     125,   126,     0,     0,   128,     0,     0,     0,     0,   111,
     112,   129,   113,   114,   115,   116,   117,   118,   119,   120,
       0,     0,     0,     0,     0,     0,     0,   121,     0,     0,
       0,     0,     0,     0,     0,   128,     0,     0,     0,     0,
     111,   112,   129,   113,   114,   115,   116,   117,   118,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   128,     0,     0,     0,
       0,     0,     0,   129
  };

  const short
  Parser::yycheck_[] =
  {
      18,    17,    21,    18,    56,     1,    18,    11,    38,    26,
      38,    40,    38,    23,    53,     3,     4,     5,     6,     7,
       8,    60,    51,     8,    54,     0,    54,    45,    54,    47,
      48,    49,    50,    37,    52,    54,    24,    55,    55,    57,
      58,    29,     0,    61,    38,     3,    61,    35,    36,    61,
      39,     8,    40,    21,    42,    43,    44,    53,    53,    51,
      54,    77,    51,    51,     1,    53,    54,    85,    55,    57,
      53,    59,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    87,    55,    22,    23,     8,    55,    55,
      94,    55,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,     5,
     128,    38,     3,    39,    56,    54,    53,    41,   134,    54,
      39,    20,    44,    61,   142,   172,    34,    35,    36,    37,
      78,    -1,     1,    -1,     3,     4,     5,     6,     7,     8,
      -1,    36,    37,    -1,    -1,    53,    -1,    -1,    -1,    -1,
     166,    20,    60,   169,    23,    24,    25,   175,    53,    -1,
      29,    -1,   178,   181,    -1,    60,    35,    36,   172,    -1,
      -1,    40,    -1,    42,    43,    44,     3,     4,     5,     6,
       7,     8,    51,    52,    53,    -1,    55,    -1,    57,    -1,
      59,    -1,    -1,    20,    -1,    -1,    23,    24,    25,    -1,
      -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    35,    36,
      -1,    -1,    -1,    40,    -1,    42,    43,    44,     3,     4,
       5,     6,     7,     8,    51,    52,    53,    -1,    55,    -1,
      57,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,
      35,    36,    -1,    -1,    -1,    40,    -1,    42,    43,    44,
       3,     4,     5,     6,     7,     8,    51,    -1,    53,    -1,
      55,    -1,    57,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    35,    36,    -1,    -1,    -1,    40,    -1,    42,
      43,    44,     3,     4,     5,     6,     7,     8,    51,    -1,
      53,    -1,    55,    -1,    57,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,    40,
      -1,    42,    43,    44,     3,     4,     5,     6,     7,     8,
      51,    -1,    53,    54,    -1,    -1,    57,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    35,    36,    -1,    -1,
      -1,    40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    57,    -1,
      59,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    -1,    22,    23,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    22,
      23,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    53,    54,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    26,    27,    28,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    45,    46,    47,    48,    49,    50,    -1,    52,    53,
      -1,    -1,    -1,    26,    27,    28,    60,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    -1,    -1,    -1,    26,    27,    28,    60,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    -1,
      -1,    53,    54,    -1,    -1,    26,    27,    28,    60,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      -1,    52,    53,    -1,    -1,    -1,    26,    27,    28,    60,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    -1,    -1,    53,    -1,    55,    -1,    26,    27,    28,
      60,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    -1,    -1,    53,    -1,    -1,    -1,    -1,    27,
      28,    60,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      27,    28,    60,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    60
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    23,    82,    83,    84,    85,     8,     0,    84,     1,
      53,    86,    21,    54,    87,    88,    93,    39,    51,    99,
      38,    54,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    22,    23,    53,    98,     3,     4,
       5,     6,     7,     8,    20,    24,    25,    29,    35,    36,
      40,    42,    43,    44,    52,    53,    55,    57,    59,    84,
      89,    90,    91,    95,    96,    99,   100,   101,   102,   104,
     105,   106,   107,   109,   110,   111,    88,    56,    53,    54,
      97,    98,    99,    93,    42,    43,    44,   107,   110,   111,
      53,   107,   107,   107,   107,    55,   107,    55,   107,    55,
      54,   107,   108,   107,   107,     1,    52,    89,   107,    55,
      26,    27,    28,    30,    31,    32,    33,    34,    35,    36,
      37,    45,    46,    47,    48,    49,    50,    52,    53,    60,
      55,    98,    54,    97,    38,    54,     8,    94,    99,     5,
      99,    54,    38,   112,    52,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,    54,   103,   107,     3,    39,    54,    98,    56,
      92,    54,    41,   107,    54,    38,    54,    98,    39,     1,
      98,    26,    55,    96,    99,   107,    98,   107,    55
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    81,    82,    83,    83,    84,    85,    85,    86,    86,
      86,    87,    87,    88,    89,    89,    89,    89,    89,    89,
      89,    89,    90,    90,    90,    91,    92,    92,    92,    93,
      93,    94,    95,    95,    96,    96,    96,    97,    97,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    99,    99,    99,
      99,   100,   100,   100,   100,   100,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   102,   102,   102,   102,   102,   103,   103,
     104,   104,   105,   106,   107,   107,   108,   108,   109,   109,
     110,   110,   110,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   112,   112
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     1,     6,     4,     3,     2,
       1,     3,     1,     4,     1,     1,     2,     2,     2,     2,
       2,     1,     2,     2,     1,     4,     2,     2,     0,     1,
       0,     1,     7,     5,     3,     5,     5,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     6,     4,     5,     3,     3,     4,     3,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     3,     1,
       4,     3,     3,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     2,     1,
       2,     2,     1,     4,     1,     1,     0
  };




#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   118,   118,   122,   123,   130,   135,   148,   164,   165,
     166,   170,   171,   175,   178,   179,   180,   181,   182,   183,
     185,   186,   190,   192,   193,   202,   206,   207,   208,   212,
     213,   217,   221,   223,   229,   230,   231,   242,   243,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   266,   269,   273,   279,   280,   281,
     282,   286,   287,   288,   289,   290,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   307,   308,
     309,   310,   311,   315,   316,   317,   318,   319,   324,   325,
     333,   334,   338,   342,   347,   348,   352,   353,   357,   358,
     362,   363,   364,   367,   368,   369,   370,   371,   372,   373,
     374,   375,   376,   377,   378,   383,   384
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

#line 5 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"
} // mr
#line 3238 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/parser.tab.cpp"

#line 386 "/Users/lorrens/Informatica/Master1/Compilers/mini-rust/src/parser/yaccfile.yy"


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
