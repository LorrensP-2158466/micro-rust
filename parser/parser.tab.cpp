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
#line 26 "parser/yaccfile.yy"


    #include <iostream>
    #include "../lexer/lexer.hpp"
    #include "parser.tab.hpp"
    #include "location.hh"
namespace mr {
  class Lexer; // Forward declaration
}

    extern mr::Unique<Ast> root;  

#line 52 "parser/parser.tab.cpp"




#include "parser.tab.hpp"


// Unqualified %code blocks.
#line 59 "parser/yaccfile.yy"

    #define yylex lexer.yylex

#line 65 "parser/parser.tab.cpp"


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

#line 38 "parser/yaccfile.yy"
namespace mr {
#line 158 "parser/parser.tab.cpp"

  /// Build a parser object.
  Parser::Parser (Lexer &lexer_yyarg, const bool debug_yyarg, const char* input_file_name_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
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
        value.copy< FuncArg > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_VAR: // PRINT_VAR
      case symbol_kind::S_PRINT_STRING: // PRINT_STRING
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

      case symbol_kind::S_type: // type
        value.copy< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.copy< Unique<AssignExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.copy< Unique<Ast> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.copy< Unique<BinOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.copy< Unique<BlockExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.copy< Unique<CallExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.copy< Unique<Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.copy< Unique<FunDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.copy< Unique<IfElse> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item: // item
        value.copy< Unique<Item> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_let: // let
        value.copy< Unique<LetStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.copy< Unique<Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.copy< Unique<UnaryOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.copy< Unique<WhileLoop> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type_decl: // type_decl
        value.copy< std::optional<Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.copy< std::vector<FuncArg> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.copy< std::vector<Unique<Expr>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item_list: // item_list
        value.copy< std::vector<Unique<Item>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< std::vector<Unique<Stmt>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_add: // ref_add
        value.copy< uint8_t > (YY_MOVE (that.value));
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
        value.move< FuncArg > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_VAR: // PRINT_VAR
      case symbol_kind::S_PRINT_STRING: // PRINT_STRING
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

      case symbol_kind::S_type: // type
        value.move< Type > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< Unique<AssignExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_program: // program
        value.move< Unique<Ast> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.move< Unique<BinOpExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.move< Unique<BlockExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.move< Unique<CallExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< Unique<Expr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.move< Unique<FunDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.move< Unique<IfElse> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_item: // item
        value.move< Unique<Item> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_let: // let
        value.move< Unique<LetStmt> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< Unique<Stmt> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.move< Unique<UnaryOpExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.move< Unique<WhileLoop> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type_decl: // type_decl
        value.move< std::optional<Type> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.move< std::vector<FuncArg> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.move< std::vector<Unique<Expr>> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_item_list: // item_list
        value.move< std::vector<Unique<Item>> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<Unique<Stmt>> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ref_add: // ref_add
        value.move< uint8_t > (YY_MOVE (s.value));
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
        value.YY_MOVE_OR_COPY< FuncArg > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_VAR: // PRINT_VAR
      case symbol_kind::S_PRINT_STRING: // PRINT_STRING
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

      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.YY_MOVE_OR_COPY< Unique<AssignExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< Unique<Ast> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.YY_MOVE_OR_COPY< Unique<BinOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.YY_MOVE_OR_COPY< Unique<BlockExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.YY_MOVE_OR_COPY< Unique<CallExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< Unique<Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.YY_MOVE_OR_COPY< Unique<FunDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.YY_MOVE_OR_COPY< Unique<IfElse> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item: // item
        value.YY_MOVE_OR_COPY< Unique<Item> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_let: // let
        value.YY_MOVE_OR_COPY< Unique<LetStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.YY_MOVE_OR_COPY< Unique<Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.YY_MOVE_OR_COPY< Unique<UnaryOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.YY_MOVE_OR_COPY< Unique<WhileLoop> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type_decl: // type_decl
        value.YY_MOVE_OR_COPY< std::optional<Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.YY_MOVE_OR_COPY< std::vector<FuncArg> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.YY_MOVE_OR_COPY< std::vector<Unique<Expr>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item_list: // item_list
        value.YY_MOVE_OR_COPY< std::vector<Unique<Item>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< std::vector<Unique<Stmt>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_add: // ref_add
        value.YY_MOVE_OR_COPY< uint8_t > (YY_MOVE (that.value));
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
        value.move< FuncArg > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_VAR: // PRINT_VAR
      case symbol_kind::S_PRINT_STRING: // PRINT_STRING
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

      case symbol_kind::S_type: // type
        value.move< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< Unique<AssignExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< Unique<Ast> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.move< Unique<BinOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.move< Unique<BlockExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.move< Unique<CallExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< Unique<Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.move< Unique<FunDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.move< Unique<IfElse> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item: // item
        value.move< Unique<Item> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_let: // let
        value.move< Unique<LetStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< Unique<Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.move< Unique<UnaryOpExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.move< Unique<WhileLoop> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type_decl: // type_decl
        value.move< std::optional<Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.move< std::vector<FuncArg> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.move< std::vector<Unique<Expr>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_item_list: // item_list
        value.move< std::vector<Unique<Item>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<Unique<Stmt>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_add: // ref_add
        value.move< uint8_t > (YY_MOVE (that.value));
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
        value.copy< FuncArg > (that.value);
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_VAR: // PRINT_VAR
      case symbol_kind::S_PRINT_STRING: // PRINT_STRING
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

      case symbol_kind::S_type: // type
        value.copy< Type > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.copy< Unique<AssignExpr> > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< Unique<Ast> > (that.value);
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.copy< Unique<BinOpExpr> > (that.value);
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.copy< Unique<BlockExpr> > (that.value);
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.copy< Unique<CallExpr> > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.copy< Unique<Expr> > (that.value);
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.copy< Unique<FunDecl> > (that.value);
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.copy< Unique<IfElse> > (that.value);
        break;

      case symbol_kind::S_item: // item
        value.copy< Unique<Item> > (that.value);
        break;

      case symbol_kind::S_let: // let
        value.copy< Unique<LetStmt> > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.copy< Unique<Stmt> > (that.value);
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.copy< Unique<UnaryOpExpr> > (that.value);
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.copy< Unique<WhileLoop> > (that.value);
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type_decl: // type_decl
        value.copy< std::optional<Type> > (that.value);
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.copy< std::vector<FuncArg> > (that.value);
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.copy< std::vector<Unique<Expr>> > (that.value);
        break;

      case symbol_kind::S_item_list: // item_list
        value.copy< std::vector<Unique<Item>> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< std::vector<Unique<Stmt>> > (that.value);
        break;

      case symbol_kind::S_ref_add: // ref_add
        value.copy< uint8_t > (that.value);
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
        value.move< FuncArg > (that.value);
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_VAR: // PRINT_VAR
      case symbol_kind::S_PRINT_STRING: // PRINT_STRING
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

      case symbol_kind::S_type: // type
        value.move< Type > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< Unique<AssignExpr> > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< Unique<Ast> > (that.value);
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.move< Unique<BinOpExpr> > (that.value);
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.move< Unique<BlockExpr> > (that.value);
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.move< Unique<CallExpr> > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.move< Unique<Expr> > (that.value);
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.move< Unique<FunDecl> > (that.value);
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.move< Unique<IfElse> > (that.value);
        break;

      case symbol_kind::S_item: // item
        value.move< Unique<Item> > (that.value);
        break;

      case symbol_kind::S_let: // let
        value.move< Unique<LetStmt> > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< Unique<Stmt> > (that.value);
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.move< Unique<UnaryOpExpr> > (that.value);
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.move< Unique<WhileLoop> > (that.value);
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type_decl: // type_decl
        value.move< std::optional<Type> > (that.value);
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.move< std::vector<FuncArg> > (that.value);
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.move< std::vector<Unique<Expr>> > (that.value);
        break;

      case symbol_kind::S_item_list: // item_list
        value.move< std::vector<Unique<Item>> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<Unique<Stmt>> > (that.value);
        break;

      case symbol_kind::S_ref_add: // ref_add
        value.move< uint8_t > (that.value);
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


    // User initialization code.
#line 53 "parser/yaccfile.yy"
{
    #if YYDEBUG != 0
        set_debug_level(debug);
    #endif
}

#line 1351 "parser/parser.tab.cpp"


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
        yylhs.value.emplace< FuncArg > ();
        break;

      case symbol_kind::S_DEC_LITERAL: // DEC_LITERAL
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_UNDERSCORE: // UNDERSCORE
      case symbol_kind::S_LET: // LET
      case symbol_kind::S_MUT: // MUT
      case symbol_kind::S_I32: // I32
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_FN: // FN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT_VAR: // PRINT_VAR
      case symbol_kind::S_PRINT_STRING: // PRINT_STRING
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

      case symbol_kind::S_type: // type
        yylhs.value.emplace< Type > ();
        break;

      case symbol_kind::S_assignment: // assignment
        yylhs.value.emplace< Unique<AssignExpr> > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< Unique<Ast> > ();
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        yylhs.value.emplace< Unique<BinOpExpr> > ();
        break;

      case symbol_kind::S_block_expr: // block_expr
        yylhs.value.emplace< Unique<BlockExpr> > ();
        break;

      case symbol_kind::S_call_expr: // call_expr
        yylhs.value.emplace< Unique<CallExpr> > ();
        break;

      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< Unique<Expr> > ();
        break;

      case symbol_kind::S_function_decl: // function_decl
        yylhs.value.emplace< Unique<FunDecl> > ();
        break;

      case symbol_kind::S_if_expr: // if_expr
        yylhs.value.emplace< Unique<IfElse> > ();
        break;

      case symbol_kind::S_item: // item
        yylhs.value.emplace< Unique<Item> > ();
        break;

      case symbol_kind::S_let: // let
        yylhs.value.emplace< Unique<LetStmt> > ();
        break;

      case symbol_kind::S_stmt: // stmt
        yylhs.value.emplace< Unique<Stmt> > ();
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        yylhs.value.emplace< Unique<UnaryOpExpr> > ();
        break;

      case symbol_kind::S_while_expr: // while_expr
        yylhs.value.emplace< Unique<WhileLoop> > ();
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type_decl: // type_decl
        yylhs.value.emplace< std::optional<Type> > ();
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        yylhs.value.emplace< std::vector<FuncArg> > ();
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        yylhs.value.emplace< std::vector<Unique<Expr>> > ();
        break;

      case symbol_kind::S_item_list: // item_list
        yylhs.value.emplace< std::vector<Unique<Item>> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< std::vector<Unique<Stmt>> > ();
        break;

      case symbol_kind::S_ref_add: // ref_add
        yylhs.value.emplace< uint8_t > ();
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
#line 118 "parser/yaccfile.yy"
                { root = std::make_unique<Ast>(std::move(yystack_[0].value.as < std::vector<Unique<Item>> > ())); }
#line 1626 "parser/parser.tab.cpp"
    break;

  case 3: // item_list: item_list item
#line 122 "parser/yaccfile.yy"
                     {yystack_[1].value.as < std::vector<Unique<Item>> > ().push_back(std::move(yystack_[0].value.as < Unique<Item> > ())); yylhs.value.as < std::vector<Unique<Item>> > () = std::move(yystack_[1].value.as < std::vector<Unique<Item>> > ());}
#line 1632 "parser/parser.tab.cpp"
    break;

  case 4: // item_list: item_list error item
#line 124 "parser/yaccfile.yy"
                           {yystack_[2].value.as < std::vector<Unique<Item>> > ().push_back(std::move(yystack_[0].value.as < Unique<Item> > ())); yylhs.value.as < std::vector<Unique<Item>> > () = std::move(yystack_[2].value.as < std::vector<Unique<Item>> > ());}
#line 1638 "parser/parser.tab.cpp"
    break;

  case 5: // item_list: item
#line 125 "parser/yaccfile.yy"
           {
        auto vec = std::vector<Unique<Item>>();
        vec.push_back(std::move(yystack_[0].value.as < Unique<Item> > ()));
         yylhs.value.as < std::vector<Unique<Item>> > () = std::move(vec) ;}
#line 1647 "parser/parser.tab.cpp"
    break;

  case 6: // item: function_decl
#line 132 "parser/yaccfile.yy"
                  { yylhs.value.as < Unique<Item> > () = std::move(yystack_[0].value.as < Unique<FunDecl> > ()); }
#line 1653 "parser/parser.tab.cpp"
    break;

  case 7: // function_decl: FN IDENTIFIER func_decl_args func_ret_type block_expr
#line 138 "parser/yaccfile.yy"
    { 
        yylhs.value.as < Unique<FunDecl> > () = FunDecl::make_unique(yystack_[3].value.as < Token > ().string_value(), yystack_[2].value.as < std::vector<FuncArg> > (), yystack_[1].value.as < std::optional<Type> > (), std::move(yystack_[0].value.as < Unique<BlockExpr> > ()));
    }
#line 1661 "parser/parser.tab.cpp"
    break;

  case 8: // func_ret_type: ARROW type
#line 144 "parser/yaccfile.yy"
                 { yylhs.value.as < std::optional<Type> > () = {yystack_[0].value.as < Type > ()}; }
#line 1667 "parser/parser.tab.cpp"
    break;

  case 9: // func_ret_type: %empty
#line 145 "parser/yaccfile.yy"
      { yylhs.value.as < std::optional<Type> > () = {primitive_type::Unit, 0}; }
#line 1673 "parser/parser.tab.cpp"
    break;

  case 10: // func_decl_args: LPAREN func_arg_list RPAREN
#line 150 "parser/yaccfile.yy"
                                  {yylhs.value.as < std::vector<FuncArg> > () = std::move(yystack_[1].value.as < std::vector<FuncArg> > ());}
#line 1679 "parser/parser.tab.cpp"
    break;

  case 11: // func_decl_args: LPAREN RPAREN
#line 151 "parser/yaccfile.yy"
                    { yylhs.value.as < std::vector<FuncArg> > () = std::vector<FuncArg>{};}
#line 1685 "parser/parser.tab.cpp"
    break;

  case 12: // func_decl_args: error
#line 152 "parser/yaccfile.yy"
            { yylhs.value.as < std::vector<FuncArg> > () = std::vector<FuncArg>{};}
#line 1691 "parser/parser.tab.cpp"
    break;

  case 13: // func_arg_list: func_arg_list COMMA func_arg
#line 156 "parser/yaccfile.yy"
                                   { yystack_[2].value.as < std::vector<FuncArg> > ().push_back(yystack_[0].value.as < FuncArg > ()); yylhs.value.as < std::vector<FuncArg> > () = yystack_[2].value.as < std::vector<FuncArg> > ();}
#line 1697 "parser/parser.tab.cpp"
    break;

  case 14: // func_arg_list: func_arg
#line 157 "parser/yaccfile.yy"
               { yylhs.value.as < std::vector<FuncArg> > () = std::vector<FuncArg>{ yystack_[0].value.as < FuncArg > () }; }
#line 1703 "parser/parser.tab.cpp"
    break;

  case 15: // func_arg: IDENTIFIER type_decl
#line 161 "parser/yaccfile.yy"
                           { yylhs.value.as < FuncArg > () = FuncArg{yystack_[1].value.as < Token > ().string_value(), *yystack_[0].value.as < std::optional<Type> > ()}; }
#line 1709 "parser/parser.tab.cpp"
    break;

  case 16: // stmt: SEMICOLON
#line 164 "parser/yaccfile.yy"
                {/* An empty statement */}
#line 1715 "parser/parser.tab.cpp"
    break;

  case 17: // stmt: let
#line 165 "parser/yaccfile.yy"
          { yylhs.value.as < Unique<Stmt> > () = std::move(yystack_[0].value.as < Unique<LetStmt> > ()); }
#line 1721 "parser/parser.tab.cpp"
    break;

  case 18: // stmt: expr SEMICOLON
#line 166 "parser/yaccfile.yy"
                     { yylhs.value.as < Unique<Stmt> > () = std::move(yystack_[1].value.as < Unique<Expr> > ()); }
#line 1727 "parser/parser.tab.cpp"
    break;

  case 19: // stmt: PRINT_LN SEMICOLON
#line 167 "parser/yaccfile.yy"
                         { yylhs.value.as < Unique<Stmt> > () = std::make_unique<PrintLn>(yystack_[1].value.as < Token > ().string_value()); }
#line 1733 "parser/parser.tab.cpp"
    break;

  case 20: // stmt: item
#line 168 "parser/yaccfile.yy"
           { yylhs.value.as < Unique<Stmt> > () = std::move(yystack_[0].value.as < Unique<Item> > ()); }
#line 1739 "parser/parser.tab.cpp"
    break;

  case 21: // stmt: error SEMICOLON
#line 169 "parser/yaccfile.yy"
                      {/* just keep going */}
#line 1745 "parser/parser.tab.cpp"
    break;

  case 22: // stmt_list: stmt_list stmt
#line 173 "parser/yaccfile.yy"
                     { yystack_[1].value.as < std::vector<Unique<Stmt>> > ().push_back(std::move(yystack_[0].value.as < Unique<Stmt> > ())); yylhs.value.as < std::vector<Unique<Stmt>> > () = std::move(yystack_[1].value.as < std::vector<Unique<Stmt>> > ()); }
#line 1751 "parser/parser.tab.cpp"
    break;

  case 23: // stmt_list: stmt
#line 174 "parser/yaccfile.yy"
           {
        auto vec = std::vector<Unique<Stmt>>();
        vec.push_back(std::move(yystack_[0].value.as < Unique<Stmt> > ()));
        yylhs.value.as < std::vector<Unique<Stmt>> > () = std::move(vec); 
      }
#line 1761 "parser/parser.tab.cpp"
    break;

  case 24: // type_decl: COLON type
#line 183 "parser/yaccfile.yy"
                 { yylhs.value.as < std::optional<Type> > () = yystack_[0].value.as < Type > (); }
#line 1767 "parser/parser.tab.cpp"
    break;

  case 25: // type_decl: %empty
#line 184 "parser/yaccfile.yy"
      { yylhs.value.as < std::optional<Type> > () = {}; }
#line 1773 "parser/parser.tab.cpp"
    break;

  case 26: // opt_mut: MUT
#line 188 "parser/yaccfile.yy"
         { yylhs.value.as < bool > () = true; }
#line 1779 "parser/parser.tab.cpp"
    break;

  case 27: // opt_mut: %empty
#line 189 "parser/yaccfile.yy"
         { yylhs.value.as < bool > () = false; }
#line 1785 "parser/parser.tab.cpp"
    break;

  case 28: // let: LET opt_mut IDENTIFIER type_decl EQ expr SEMICOLON
#line 194 "parser/yaccfile.yy"
      {yylhs.value.as < Unique<LetStmt> > () = LetStmt::make_unique_init(yystack_[4].value.as < Token > ().string_value(), yystack_[3].value.as < std::optional<Type> > (), std::move(yystack_[1].value.as < Unique<Expr> > ()), yystack_[5].value.as < bool > ());}
#line 1791 "parser/parser.tab.cpp"
    break;

  case 29: // let: LET opt_mut IDENTIFIER type_decl error EQ SEMICOLON
#line 196 "parser/yaccfile.yy"
      {
        yylhs.value.as < Unique<LetStmt> > () = LetStmt::make_unique_init(yystack_[4].value.as < Token > ().string_value(), yystack_[3].value.as < std::optional<Type> > (), std::unique_ptr<Expr>(nullptr), yystack_[5].value.as < bool > ()); 
      }
#line 1799 "parser/parser.tab.cpp"
    break;

  case 30: // let: LET opt_mut IDENTIFIER COLON type SEMICOLON
#line 199 "parser/yaccfile.yy"
                                                  { yylhs.value.as < Unique<LetStmt> > () = LetStmt::make_unique_decl(yystack_[3].value.as < Token > ().string_value(), yystack_[1].value.as < Type > (), yystack_[4].value.as < bool > ()); }
#line 1805 "parser/parser.tab.cpp"
    break;

  case 31: // let: LET UNDERSCORE COLON type EQ expr SEMICOLON
#line 200 "parser/yaccfile.yy"
                                                  { printf("INIT no named\n"); }
#line 1811 "parser/parser.tab.cpp"
    break;

  case 32: // if_expr: IF expr block_expr
#line 204 "parser/yaccfile.yy"
                         { yylhs.value.as < Unique<IfElse> > () = std::make_unique<IfElse>(std::move(yystack_[1].value.as < Unique<Expr> > ()), std::move(yystack_[0].value.as < Unique<BlockExpr> > ())); }
#line 1817 "parser/parser.tab.cpp"
    break;

  case 33: // if_expr: IF expr block_expr ELSE if_expr
#line 205 "parser/yaccfile.yy"
                                      {yylhs.value.as < Unique<IfElse> > () = std::make_unique<IfElse>(std::move(yystack_[3].value.as < Unique<Expr> > ()), std::move(yystack_[2].value.as < Unique<BlockExpr> > ()), std::move(yystack_[0].value.as < Unique<IfElse> > ())); }
#line 1823 "parser/parser.tab.cpp"
    break;

  case 34: // if_expr: IF expr block_expr ELSE block_expr
#line 206 "parser/yaccfile.yy"
                                         {yylhs.value.as < Unique<IfElse> > () = std::make_unique<IfElse>(std::move(yystack_[3].value.as < Unique<Expr> > ()), std::move(yystack_[2].value.as < Unique<BlockExpr> > ()), std::move(yystack_[0].value.as < Unique<BlockExpr> > ())); }
#line 1829 "parser/parser.tab.cpp"
    break;

  case 35: // ref_add: AMPERSAND
#line 211 "parser/yaccfile.yy"
                {yylhs.value.as < uint8_t > () = Type::ref_flag; }
#line 1835 "parser/parser.tab.cpp"
    break;

  case 36: // ref_add: AMPERSAND_MUT
#line 212 "parser/yaccfile.yy"
                    {yylhs.value.as < uint8_t > () = Type::ref_mut_flag; }
#line 1841 "parser/parser.tab.cpp"
    break;

  case 37: // ref_add: %empty
#line 213 "parser/yaccfile.yy"
      { yylhs.value.as < uint8_t > () = 0; }
#line 1847 "parser/parser.tab.cpp"
    break;

  case 38: // type: ref_add I32
#line 216 "parser/yaccfile.yy"
                  { yylhs.value.as < Type > () = Type{primitive_type::I32, yystack_[1].value.as < uint8_t > ()}; }
#line 1853 "parser/parser.tab.cpp"
    break;

  case 39: // type: ref_add BOOL
#line 217 "parser/yaccfile.yy"
                   { yylhs.value.as < Type > () = {primitive_type::Bool, yystack_[1].value.as < uint8_t > ()}; }
#line 1859 "parser/parser.tab.cpp"
    break;

  case 40: // type: ref_add LPAREN RPAREN
#line 218 "parser/yaccfile.yy"
                            { yylhs.value.as < Type > () = {primitive_type::Unit, yystack_[2].value.as < uint8_t > ()}; }
#line 1865 "parser/parser.tab.cpp"
    break;

  case 41: // type: ref_add IDENTIFIER
#line 219 "parser/yaccfile.yy"
                         { yylhs.value.as < Type > () = Type{yystack_[0].value.as < Token > ().string_value(), yystack_[1].value.as < uint8_t > ()}; }
#line 1871 "parser/parser.tab.cpp"
    break;

  case 42: // block_expr: LBRACE stmt_list RBRACE
#line 224 "parser/yaccfile.yy"
                              { yylhs.value.as < Unique<BlockExpr> > () = std::make_unique<BlockExpr>(std::move(yystack_[1].value.as < std::vector<Unique<Stmt>> > ()), std::make_unique<Unit>()); }
#line 1877 "parser/parser.tab.cpp"
    break;

  case 43: // block_expr: LBRACE stmt_list expr RBRACE
#line 225 "parser/yaccfile.yy"
                                    { yylhs.value.as < Unique<BlockExpr> > () = std::make_unique<BlockExpr>(std::move(yystack_[2].value.as < std::vector<Unique<Stmt>> > ()), std::move(yystack_[1].value.as < Unique<Expr> > ())); }
#line 1883 "parser/parser.tab.cpp"
    break;

  case 44: // block_expr: LBRACE expr RBRACE
#line 226 "parser/yaccfile.yy"
                          { yylhs.value.as < Unique<BlockExpr> > () = std::make_unique<BlockExpr>(std::vector<Unique<Stmt>>{}, std::move(yystack_[1].value.as < Unique<Expr> > ())); }
#line 1889 "parser/parser.tab.cpp"
    break;

  case 45: // block_expr: LBRACE RBRACE
#line 227 "parser/yaccfile.yy"
                     { yylhs.value.as < Unique<BlockExpr> > () = std::make_unique<BlockExpr>(std::vector<Unique<Stmt>>{}, std::make_unique<Unit>()); }
#line 1895 "parser/parser.tab.cpp"
    break;

  case 46: // assignment: IDENTIFIER EQ expr
#line 231 "parser/yaccfile.yy"
                         { yylhs.value.as < Unique<AssignExpr> > () = std::make_unique<AssignExpr>(yystack_[2].value.as < Token > ().string_value(), AssignOp::Eq, std::move(yystack_[0].value.as < Unique<Expr> > ()));}
#line 1901 "parser/parser.tab.cpp"
    break;

  case 47: // assignment: IDENTIFIER PLUS_EQ expr
#line 232 "parser/yaccfile.yy"
                              { yylhs.value.as < Unique<AssignExpr> > () = std::make_unique<AssignExpr>(yystack_[2].value.as < Token > ().string_value(), AssignOp::PlusEq, std::move(yystack_[0].value.as < Unique<Expr> > ()));}
#line 1907 "parser/parser.tab.cpp"
    break;

  case 48: // assignment: IDENTIFIER MIN_EQ expr
#line 233 "parser/yaccfile.yy"
                             { yylhs.value.as < Unique<AssignExpr> > () = std::make_unique<AssignExpr>(yystack_[2].value.as < Token > ().string_value(), AssignOp::MinEq, std::move(yystack_[0].value.as < Unique<Expr> > ()));}
#line 1913 "parser/parser.tab.cpp"
    break;

  case 49: // assignment: IDENTIFIER DIV_EQ expr
#line 234 "parser/yaccfile.yy"
                             { yylhs.value.as < Unique<AssignExpr> > () = std::make_unique<AssignExpr>(yystack_[2].value.as < Token > ().string_value(), AssignOp::DivEq, std::move(yystack_[0].value.as < Unique<Expr> > ()));}
#line 1919 "parser/parser.tab.cpp"
    break;

  case 50: // assignment: IDENTIFIER MUL_EQ expr
#line 235 "parser/yaccfile.yy"
                             { yylhs.value.as < Unique<AssignExpr> > () = std::make_unique<AssignExpr>(yystack_[2].value.as < Token > ().string_value(), AssignOp::MulEq, std::move(yystack_[0].value.as < Unique<Expr> > ()));}
#line 1925 "parser/parser.tab.cpp"
    break;

  case 51: // unary_op_expr: MINUS expr
#line 240 "parser/yaccfile.yy"
                              { yylhs.value.as < Unique<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Negate, std::move(yystack_[0].value.as < Unique<Expr> > ()));}
#line 1931 "parser/parser.tab.cpp"
    break;

  case 52: // unary_op_expr: STAR expr
#line 241 "parser/yaccfile.yy"
                            { yylhs.value.as < Unique<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Deref, std::move(yystack_[0].value.as < Unique<Expr> > ()));}
#line 1937 "parser/parser.tab.cpp"
    break;

  case 53: // unary_op_expr: BANG expr
#line 242 "parser/yaccfile.yy"
                          { yylhs.value.as < Unique<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Not, std::move(yystack_[0].value.as < Unique<Expr> > ()));}
#line 1943 "parser/parser.tab.cpp"
    break;

  case 54: // unary_op_expr: AMPERSAND expr
#line 243 "parser/yaccfile.yy"
                               { yylhs.value.as < Unique<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::Borrow, std::move(yystack_[0].value.as < Unique<Expr> > ()));}
#line 1949 "parser/parser.tab.cpp"
    break;

  case 55: // unary_op_expr: AMPERSAND_MUT expr
#line 244 "parser/yaccfile.yy"
                                       { yylhs.value.as < Unique<UnaryOpExpr> > () = std::make_unique<UnaryOpExpr>(UnaryOp::MutBorrow, std::move(yystack_[0].value.as < Unique<Expr> > ()));}
#line 1955 "parser/parser.tab.cpp"
    break;

  case 56: // bin_op_expr: expr PLUS expr
#line 248 "parser/yaccfile.yy"
                     { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::Plus, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 1961 "parser/parser.tab.cpp"
    break;

  case 57: // bin_op_expr: expr MINUS expr
#line 249 "parser/yaccfile.yy"
                      { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::Min, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 1967 "parser/parser.tab.cpp"
    break;

  case 58: // bin_op_expr: expr STAR expr
#line 250 "parser/yaccfile.yy"
                     { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::Mul, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 1973 "parser/parser.tab.cpp"
    break;

  case 59: // bin_op_expr: expr SLASH expr
#line 251 "parser/yaccfile.yy"
                      { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::Div, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 1979 "parser/parser.tab.cpp"
    break;

  case 60: // bin_op_expr: expr L_AND expr
#line 252 "parser/yaccfile.yy"
                      { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::L_AND, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 1985 "parser/parser.tab.cpp"
    break;

  case 61: // bin_op_expr: expr L_OR expr
#line 253 "parser/yaccfile.yy"
                     { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::L_OR, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 1991 "parser/parser.tab.cpp"
    break;

  case 62: // bin_op_expr: expr EQEQ expr
#line 254 "parser/yaccfile.yy"
                     { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::Eq, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 1997 "parser/parser.tab.cpp"
    break;

  case 63: // bin_op_expr: expr NE expr
#line 255 "parser/yaccfile.yy"
                   { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::NEq, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 2003 "parser/parser.tab.cpp"
    break;

  case 64: // bin_op_expr: expr LT expr
#line 256 "parser/yaccfile.yy"
                   { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::Lt, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 2009 "parser/parser.tab.cpp"
    break;

  case 65: // bin_op_expr: expr GT expr
#line 257 "parser/yaccfile.yy"
                   { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::Gt, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 2015 "parser/parser.tab.cpp"
    break;

  case 66: // bin_op_expr: expr GE expr
#line 258 "parser/yaccfile.yy"
                   { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::GtEq, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 2021 "parser/parser.tab.cpp"
    break;

  case 67: // bin_op_expr: expr LE expr
#line 259 "parser/yaccfile.yy"
                   { yylhs.value.as < Unique<BinOpExpr> > () =std::make_unique<BinOpExpr>(std::move(yystack_[2].value.as < Unique<Expr> > ()), BinOp::LtEq, std::move(yystack_[0].value.as < Unique<Expr> > ())); }
#line 2027 "parser/parser.tab.cpp"
    break;

  case 68: // call_expr_args: call_expr_args COMMA expr
#line 264 "parser/yaccfile.yy"
                                {yystack_[2].value.as < std::vector<Unique<Expr>> > ().push_back(std::move(yystack_[0].value.as < Unique<Expr> > ())); yylhs.value.as < std::vector<Unique<Expr>> > () = std::move(yystack_[2].value.as < std::vector<Unique<Expr>> > ()); }
#line 2033 "parser/parser.tab.cpp"
    break;

  case 69: // call_expr_args: expr
#line 265 "parser/yaccfile.yy"
           { 
        auto vec = std::vector<Unique<Expr>>();
        vec.push_back(std::move(yystack_[0].value.as < Unique<Expr> > ()));
        yylhs.value.as < std::vector<Unique<Expr>> > () = std::move(vec);
        }
#line 2043 "parser/parser.tab.cpp"
    break;

  case 70: // call_expr: IDENTIFIER LPAREN call_expr_args RPAREN
#line 273 "parser/yaccfile.yy"
                                              { yylhs.value.as < Unique<CallExpr> > () = std::make_unique<CallExpr>(yystack_[3].value.as < Token > ().string_value(), std::move(yystack_[1].value.as < std::vector<Unique<Expr>> > ())); }
#line 2049 "parser/parser.tab.cpp"
    break;

  case 71: // call_expr: IDENTIFIER LPAREN RPAREN
#line 274 "parser/yaccfile.yy"
                               { yylhs.value.as < Unique<CallExpr> > () = std::make_unique<CallExpr>(yystack_[2].value.as < Token > ().string_value(), std::vector<Unique<Expr>>{}); }
#line 2055 "parser/parser.tab.cpp"
    break;

  case 72: // while_expr: WHILE expr block_expr
#line 277 "parser/yaccfile.yy"
                            {yylhs.value.as < Unique<WhileLoop> > () = std::make_unique<WhileLoop>(std::move(yystack_[1].value.as < Unique<Expr> > ()), std::move(yystack_[0].value.as < Unique<BlockExpr> > ())); }
#line 2061 "parser/parser.tab.cpp"
    break;

  case 73: // expr: assignment
#line 281 "parser/yaccfile.yy"
                 { yylhs.value.as < Unique<Expr> > () = std::move(yystack_[0].value.as < Unique<AssignExpr> > ()); }
#line 2067 "parser/parser.tab.cpp"
    break;

  case 74: // expr: bin_op_expr
#line 282 "parser/yaccfile.yy"
                  { yylhs.value.as < Unique<Expr> > () = std::move(yystack_[0].value.as < Unique<BinOpExpr> > ()); }
#line 2073 "parser/parser.tab.cpp"
    break;

  case 75: // expr: block_expr
#line 283 "parser/yaccfile.yy"
                 { yylhs.value.as < Unique<Expr> > () = std::move(yystack_[0].value.as < Unique<BlockExpr> > ()); }
#line 2079 "parser/parser.tab.cpp"
    break;

  case 76: // expr: if_expr
#line 284 "parser/yaccfile.yy"
              { yylhs.value.as < Unique<Expr> > () = std::move(yystack_[0].value.as < Unique<IfElse> > ()); }
#line 2085 "parser/parser.tab.cpp"
    break;

  case 77: // expr: DEC_LITERAL
#line 285 "parser/yaccfile.yy"
                  { yylhs.value.as < Unique<Expr> > () = std::make_unique<DecLiteral>(yystack_[0].value.as < Token > ().size_t_value()); }
#line 2091 "parser/parser.tab.cpp"
    break;

  case 78: // expr: TRUE
#line 286 "parser/yaccfile.yy"
           { yylhs.value.as < Unique<Expr> > () = std::make_unique<BoolLit>(yystack_[0].value.as < Token > ().bool_value()); }
#line 2097 "parser/parser.tab.cpp"
    break;

  case 79: // expr: FALSE
#line 287 "parser/yaccfile.yy"
            { yylhs.value.as < Unique<Expr> > () = std::make_unique<BoolLit>(yystack_[0].value.as < Token > ().bool_value()); }
#line 2103 "parser/parser.tab.cpp"
    break;

  case 80: // expr: IDENTIFIER
#line 288 "parser/yaccfile.yy"
                 { yylhs.value.as < Unique<Expr> > () = std::make_unique<Identifier>(yystack_[0].value.as < Token > ().string_value()); }
#line 2109 "parser/parser.tab.cpp"
    break;

  case 81: // expr: unary_op_expr
#line 289 "parser/yaccfile.yy"
                     {yylhs.value.as < Unique<Expr> > () = std::move(yystack_[0].value.as < Unique<UnaryOpExpr> > ()); }
#line 2115 "parser/parser.tab.cpp"
    break;

  case 82: // expr: LPAREN expr RPAREN
#line 290 "parser/yaccfile.yy"
                         { yylhs.value.as < Unique<Expr> > () = std::move(yystack_[1].value.as < Unique<Expr> > ()); }
#line 2121 "parser/parser.tab.cpp"
    break;

  case 83: // expr: LPAREN RPAREN
#line 291 "parser/yaccfile.yy"
                    { yylhs.value.as < Unique<Expr> > () = std::make_unique<Unit>(); }
#line 2127 "parser/parser.tab.cpp"
    break;

  case 84: // expr: call_expr
#line 292 "parser/yaccfile.yy"
                { yylhs.value.as < Unique<Expr> > () = std::move(yystack_[0].value.as < Unique<CallExpr> > ()); }
#line 2133 "parser/parser.tab.cpp"
    break;

  case 85: // expr: while_expr
#line 293 "parser/yaccfile.yy"
                 { yylhs.value.as < Unique<Expr> > () = std::move(yystack_[0].value.as < Unique<WhileLoop> > ()); }
#line 2139 "parser/parser.tab.cpp"
    break;


#line 2143 "parser/parser.tab.cpp"

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


  const signed char Parser::yypact_ninf_ = -29;

  const signed char Parser::yytable_ninf_ = -3;

  const short
  Parser::yypact_[] =
  {
      -7,     4,    27,    12,   -29,   -29,     6,   -29,    -7,   -29,
     -29,    -5,     1,   -29,    -8,   -29,   -14,   -29,    14,    19,
      14,   -29,    34,   -29,   -29,   -29,    -2,   -29,    78,   -29,
     -29,   -29,   -29,   -29,   -29,    38,    42,   -29,   -29,   -29,
      -3,    80,   212,    45,   212,   212,   212,   212,   -29,   152,
     -29,   212,   212,   -29,   -29,   123,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   242,   -29,   -29,   212,   212,   212,
     212,   212,   182,    48,   -29,    89,   356,   -29,   -29,   -29,
     -29,   356,   -29,   334,   -29,   -29,   -29,   -29,   265,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   -29,   -29,   375,   375,   375,   375,   375,   -29,   -12,
     375,    14,    53,   -29,    64,   -29,   -29,   392,   392,   392,
     392,   392,   392,    26,    26,   -29,   -29,    50,    23,   212,
     -29,    82,    14,     5,   -28,   375,   212,    57,    84,   212,
     -29,   -29,   288,   -29,    59,   311,   -29,   -29,   -29
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     5,     6,     0,     1,     0,     3,
      12,     0,     9,     4,    25,    11,     0,    14,    37,     0,
      37,    15,     0,    10,    35,    36,     0,     8,     0,     7,
      24,    13,    41,    38,    39,     0,     0,    77,    78,    79,
      80,    27,     0,     0,     0,     0,     0,     0,    45,     0,
      16,     0,     0,    20,    23,     0,    17,    76,    75,    73,
      81,    74,    84,    85,     0,    40,    21,     0,     0,     0,
       0,     0,     0,     0,    26,     0,     0,    19,    53,    51,
      52,     0,    83,     0,    54,    55,    42,    22,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    44,    18,    46,    47,    48,    50,    49,    71,     0,
      69,    37,    25,    72,    32,    82,    43,    62,    63,    64,
      67,    65,    66,    56,    57,    58,    59,    60,    61,     0,
      70,     0,    37,     0,     0,    68,     0,    24,     0,     0,
      33,    34,     0,    30,     0,     0,    31,    29,    28
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -29,   -29,   -29,    52,   -29,   -29,   -29,   -29,    85,    51,
     -29,    -4,   -29,   -29,   -23,   -29,   -18,   -19,   -29,   -29,
     -29,   -29,   -29,   -29,   -26
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     2,     3,    53,     5,    19,    12,    16,    17,    54,
      55,    21,    75,    56,    57,    26,    27,    58,    59,    60,
      61,   109,    62,    63,    64
  };

  const short
  Parser::yytable_[] =
  {
      29,    14,    30,    47,    32,     1,   138,    10,    33,    34,
       6,    28,    -2,     8,    67,    22,    76,   129,    78,    79,
      80,    81,   139,    83,     1,    84,    85,     7,    23,    88,
     130,    18,    68,    69,    70,    71,    20,    15,    72,    35,
      14,   103,   104,   105,   106,   107,   110,    11,    95,    96,
      97,    98,     4,    97,    98,     9,    99,   113,    28,    24,
      13,    25,   114,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,    95,    96,    97,    98,    36,
      65,    37,    38,    39,    40,    66,    41,    73,    77,    74,
       1,    42,   111,   131,    43,   112,   134,   132,    44,   136,
     143,   144,   147,   135,    45,    46,    87,    31,   133,    47,
     142,   140,     0,   145,   137,   141,     0,    28,    48,    49,
       0,    50,     0,    51,    36,    52,    37,    38,    39,    40,
       0,    41,     0,     0,     0,     1,    42,     0,     0,    43,
       0,     0,     0,    44,     0,     0,     0,     0,     0,    45,
      46,     0,     0,     0,    47,    37,    38,    39,    40,     0,
       0,     0,    28,    86,    49,    42,    50,     0,    51,     0,
      52,     0,    44,     0,     0,     0,     0,     0,    45,    46,
       0,     0,     0,    47,     0,    37,    38,    39,    40,     0,
       0,    28,     0,    49,    82,    42,     0,    51,     0,    52,
       0,     0,    44,     0,     0,     0,     0,     0,    45,    46,
       0,     0,     0,    47,     0,    37,    38,    39,    40,     0,
       0,    28,     0,    49,   108,    42,     0,    51,     0,    52,
       0,     0,    44,     0,     0,     0,     0,     0,    45,    46,
       0,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,    28,     0,    49,     0,     0,     0,    51,     0,    52,
      89,    90,     0,    91,    92,    93,    94,    95,    96,    97,
      98,     0,     0,     0,     0,    99,   100,     0,     0,     0,
       0,     0,   101,    89,    90,   102,    91,    92,    93,    94,
      95,    96,    97,    98,     0,     0,     0,     0,    99,   100,
       0,     0,     0,     0,     0,   116,    89,    90,   102,    91,
      92,    93,    94,    95,    96,    97,    98,     0,     0,     0,
       0,    99,   100,     0,     0,     0,     0,     0,     0,    89,
      90,   146,    91,    92,    93,    94,    95,    96,    97,    98,
       0,     0,     0,     0,    99,   100,     0,     0,     0,     0,
       0,     0,    89,    90,   148,    91,    92,    93,    94,    95,
      96,    97,    98,     0,     0,     0,     0,    99,   100,     0,
       0,     0,     0,     0,    89,    90,   115,    91,    92,    93,
      94,    95,    96,    97,    98,     0,     0,     0,     0,    99,
     100,     0,     0,    89,    90,    28,    91,    92,    93,    94,
      95,    96,    97,    98,     0,     0,     0,     0,    99,   100,
      -3,    -3,     0,    -3,    -3,    -3,    -3,    95,    96,    97,
      98,     0,     0,     0,     0,    99,   100
  };

  const short
  Parser::yycheck_[] =
  {
      19,     6,    20,    31,     6,    12,     1,     1,    10,    11,
       6,    39,     0,     1,    17,    29,    42,    29,    44,    45,
      46,    47,    17,    49,    12,    51,    52,     0,    42,    55,
      42,    30,    35,    36,    37,    38,    44,    42,    41,    41,
       6,    67,    68,    69,    70,    71,    72,    41,    25,    26,
      27,    28,     0,    27,    28,     3,    33,    76,    39,    45,
       8,    47,    81,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,    25,    26,    27,    28,     1,
      42,     3,     4,     5,     6,    43,     8,     7,    43,     9,
      12,    13,    44,   111,    16,     6,    32,    44,    20,    17,
      43,    17,    43,   129,    26,    27,    55,    22,   112,    31,
     136,   134,    -1,   139,   132,   134,    -1,    39,    40,    41,
      -1,    43,    -1,    45,     1,    47,     3,     4,     5,     6,
      -1,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,    16,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,
      27,    -1,    -1,    -1,    31,     3,     4,     5,     6,    -1,
      -1,    -1,    39,    40,    41,    13,    43,    -1,    45,    -1,
      47,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    -1,    -1,    31,    -1,     3,     4,     5,     6,    -1,
      -1,    39,    -1,    41,    42,    13,    -1,    45,    -1,    47,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    -1,    -1,    31,    -1,     3,     4,     5,     6,    -1,
      -1,    39,    -1,    41,    42,    13,    -1,    45,    -1,    47,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    41,    -1,    -1,    -1,    45,    -1,    47,
      18,    19,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    40,    18,    19,    43,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    40,    18,    19,    43,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      19,    43,    21,    22,    23,    24,    25,    26,    27,    28,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    18,    19,    43,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    18,    19,    42,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    18,    19,    39,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    -1,    33,    34,
      18,    19,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    -1,    -1,    33,    34
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    12,    54,    55,    56,    57,     6,     0,     1,    56,
       1,    41,    59,    56,     6,    42,    60,    61,    30,    58,
      44,    64,    29,    42,    45,    47,    68,    69,    39,    70,
      69,    61,     6,    10,    11,    41,     1,     3,     4,     5,
       6,     8,    13,    16,    20,    26,    27,    31,    40,    41,
      43,    45,    47,    56,    62,    63,    66,    67,    70,    71,
      72,    73,    75,    76,    77,    42,    43,    17,    35,    36,
      37,    38,    41,     7,     9,    65,    77,    43,    77,    77,
      77,    77,    42,    77,    77,    77,    40,    62,    77,    18,
      19,    21,    22,    23,    24,    25,    26,    27,    28,    33,
      34,    40,    43,    77,    77,    77,    77,    77,    42,    74,
      77,    44,     6,    70,    70,    42,    40,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    29,
      42,    69,    44,    64,    32,    77,    17,    69,     1,    17,
      67,    70,    77,    43,    17,    77,    43,    43,    43
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    53,    54,    55,    55,    55,    56,    57,    58,    58,
      59,    59,    59,    60,    60,    61,    62,    62,    62,    62,
      62,    62,    63,    63,    64,    64,    65,    65,    66,    66,
      66,    66,    67,    67,    67,    68,    68,    68,    69,    69,
      69,    69,    70,    70,    70,    70,    71,    71,    71,    71,
      71,    72,    72,    72,    72,    72,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    74,    74,
      75,    75,    76,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     1,     1,     5,     2,     0,
       3,     2,     1,     3,     1,     2,     1,     1,     2,     2,
       1,     2,     2,     1,     2,     0,     1,     0,     7,     7,
       6,     7,     3,     5,     5,     1,     1,     0,     2,     2,
       3,     2,     3,     4,     3,     2,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       4,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "DEC_LITERAL", "TRUE",
  "FALSE", "IDENTIFIER", "UNDERSCORE", "LET", "MUT", "I32", "BOOL", "FN",
  "WHILE", "PRINT_VAR", "PRINT_STRING", "PRINT_LN", "EQ", "EQEQ", "NE",
  "BANG", "LT", "LE", "GT", "GE", "PLUS", "MINUS", "STAR", "SLASH",
  "COMMA", "ARROW", "IF", "ELSE", "L_AND", "L_OR", "PLUS_EQ", "MIN_EQ",
  "MUL_EQ", "DIV_EQ", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "SEMICOLON",
  "COLON", "AMPERSAND", "OR", "AMPERSAND_MUT", "REF", "REF_MUT", "DEREF",
  "UMINUS", "NOT", "$accept", "program", "item_list", "item",
  "function_decl", "func_ret_type", "func_decl_args", "func_arg_list",
  "func_arg", "stmt", "stmt_list", "type_decl", "opt_mut", "let",
  "if_expr", "ref_add", "type", "block_expr", "assignment",
  "unary_op_expr", "bin_op_expr", "call_expr_args", "call_expr",
  "while_expr", "expr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   118,   118,   122,   124,   125,   132,   137,   144,   145,
     150,   151,   152,   156,   157,   161,   164,   165,   166,   167,
     168,   169,   173,   174,   183,   184,   188,   189,   193,   195,
     199,   200,   204,   205,   206,   211,   212,   213,   216,   217,
     218,   219,   224,   225,   226,   227,   231,   232,   233,   234,
     235,   240,   241,   242,   243,   244,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   264,   265,
     273,   274,   277,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293
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
      45,    46,    47,    48,    49,    50,    51,    52
    };
    // Last valid token kind.
    const int code_max = 307;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 38 "parser/yaccfile.yy"
} // mr
#line 2819 "parser/parser.tab.cpp"

#line 296 "parser/yaccfile.yy"


namespace mr
{
    
    void Parser::error(const Parser::location_type &loc, const std::string &message)
    {
        std::cerr << "Error in " << this->input_file_name << ":" << loc.end.line << ":" << loc.end.column
            <<":\n"
            << message << std::endl;
    }
}
