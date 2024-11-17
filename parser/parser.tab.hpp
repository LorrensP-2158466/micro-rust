// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file parser/parser.tab.hpp
 ** Define the mr::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_PARSER_TAB_HPP_INCLUDED
// "%code requires" blocks.
#line 4 "parser/yaccfile.yy"



#include "../ast/module.hpp"
#include "../expr/module.hpp"
#include "mr_util.hpp"
#include "../lexer/span.hpp"
#include "../lexer/token.hpp"
#include <string>
#include <variant>
#include <cstddef>
#include <memory>
#include <assert.h>
namespace mr {
  class Lexer; // Forward declaration
}

// this makes everything cleaner even though im against this
using namespace mr::ast;
using namespace mr::expr;


#line 72 "parser/parser.tab.hpp"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 39 "parser/yaccfile.yy"
namespace mr {
#line 208 "parser/parser.tab.hpp"




  /// A Bison parser.
  class Parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // func_arg
      char dummy1[sizeof (FunArg)];

      // DEC_LITERAL
      // FLOAT_LITERAL
      // STR_LITERAL
      // TRUE
      // FALSE
      // IDENTIFIER
      // UNDERSCORE
      // I8
      // I16
      // I32
      // I64
      // ISIZE
      // U8
      // U16
      // U32
      // U64
      // USIZE
      // LET
      // MUT
      // BOOL
      // FN
      // WHILE
      // PRINT_LN
      // EQ
      // EQEQ
      // NE
      // BANG
      // LT
      // LE
      // GT
      // GE
      // PLUS
      // MINUS
      // STAR
      // SLASH
      // COMMA
      // ARROW
      // IF
      // ELSE
      // L_AND
      // L_OR
      // PLUS_EQ
      // MIN_EQ
      // MUL_EQ
      // DIV_EQ
      // LBRACE
      // RBRACE
      // LPAREN
      // RPAREN
      // SEMICOLON
      // COLON
      // AMPERSAND
      // OR
      // AMPERSAND_MUT
      char dummy2[sizeof (Token)];

      // func_ret_type
      // type
      char dummy3[sizeof (Type)];

      // assignment
      char dummy4[sizeof (Unique<AssignExpr>)];

      // program
      char dummy5[sizeof (Unique<Ast>)];

      // bin_op_expr
      char dummy6[sizeof (Unique<BinOpExpr>)];

      // block_expr
      char dummy7[sizeof (Unique<BlockExpr>)];

      // call_expr
      char dummy8[sizeof (Unique<CallExpr>)];

      // expr
      // expr_stmt
      // expr_w_block
      // expr_wo_block
      char dummy9[sizeof (Unique<Expr>)];

      // function_decl
      char dummy10[sizeof (Unique<FunDecl>)];

      // if_expr
      char dummy11[sizeof (Unique<IfElse>)];

      // item
      char dummy12[sizeof (Unique<Item>)];

      // let
      char dummy13[sizeof (Unique<LetStmt>)];

      // literal
      char dummy14[sizeof (Unique<Literal>)];

      // print_ln
      char dummy15[sizeof (Unique<PrintLn>)];

      // stmt
      char dummy16[sizeof (Unique<Stmt>)];

      // unary_op_expr
      char dummy17[sizeof (Unique<UnaryOpExpr>)];

      // while_expr
      char dummy18[sizeof (Unique<WhileLoop>)];

      // opt_mut
      char dummy19[sizeof (bool)];

      // type_decl
      char dummy20[sizeof (std::optional<Type>)];

      // func_decl_args
      // func_arg_list
      char dummy21[sizeof (std::vector<FunArg>)];

      // call_expr_args
      char dummy22[sizeof (std::vector<Unique<Expr>>)];

      // item_list
      char dummy23[sizeof (std::vector<Unique<Item>>)];

      // stmt_list
      char dummy24[sizeof (std::vector<Unique<Stmt>>)];

      // ref_add
      char dummy25[sizeof (uint8_t)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    DEC_LITERAL = 258,             // DEC_LITERAL
    FLOAT_LITERAL = 259,           // FLOAT_LITERAL
    STR_LITERAL = 260,             // STR_LITERAL
    TRUE = 261,                    // TRUE
    FALSE = 262,                   // FALSE
    IDENTIFIER = 263,              // IDENTIFIER
    UNDERSCORE = 264,              // UNDERSCORE
    I8 = 265,                      // I8
    I16 = 266,                     // I16
    I32 = 267,                     // I32
    I64 = 268,                     // I64
    ISIZE = 269,                   // ISIZE
    U8 = 270,                      // U8
    U16 = 271,                     // U16
    U32 = 272,                     // U32
    U64 = 273,                     // U64
    USIZE = 274,                   // USIZE
    LET = 275,                     // LET
    MUT = 276,                     // MUT
    BOOL = 277,                    // BOOL
    FN = 278,                      // FN
    WHILE = 279,                   // WHILE
    PRINT_LN = 280,                // PRINT_LN
    EQ = 281,                      // EQ
    EQEQ = 282,                    // EQEQ
    NE = 283,                      // NE
    BANG = 284,                    // BANG
    LT = 285,                      // LT
    LE = 286,                      // LE
    GT = 287,                      // GT
    GE = 288,                      // GE
    PLUS = 289,                    // PLUS
    MINUS = 290,                   // MINUS
    STAR = 291,                    // STAR
    SLASH = 292,                   // SLASH
    COMMA = 293,                   // COMMA
    ARROW = 294,                   // ARROW
    IF = 295,                      // IF
    ELSE = 296,                    // ELSE
    L_AND = 297,                   // L_AND
    L_OR = 298,                    // L_OR
    PLUS_EQ = 299,                 // PLUS_EQ
    MIN_EQ = 300,                  // MIN_EQ
    MUL_EQ = 301,                  // MUL_EQ
    DIV_EQ = 302,                  // DIV_EQ
    LBRACE = 303,                  // LBRACE
    RBRACE = 304,                  // RBRACE
    LPAREN = 305,                  // LPAREN
    RPAREN = 306,                  // RPAREN
    SEMICOLON = 307,               // SEMICOLON
    COLON = 308,                   // COLON
    AMPERSAND = 309,               // AMPERSAND
    OR = 310,                      // OR
    AMPERSAND_MUT = 311,           // AMPERSAND_MUT
    REF = 312,                     // REF
    REF_MUT = 313,                 // REF_MUT
    DEREF = 314,                   // DEREF
    UMINUS = 315,                  // UMINUS
    NOT = 316                      // NOT
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 62, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_DEC_LITERAL = 3,                       // DEC_LITERAL
        S_FLOAT_LITERAL = 4,                     // FLOAT_LITERAL
        S_STR_LITERAL = 5,                       // STR_LITERAL
        S_TRUE = 6,                              // TRUE
        S_FALSE = 7,                             // FALSE
        S_IDENTIFIER = 8,                        // IDENTIFIER
        S_UNDERSCORE = 9,                        // UNDERSCORE
        S_I8 = 10,                               // I8
        S_I16 = 11,                              // I16
        S_I32 = 12,                              // I32
        S_I64 = 13,                              // I64
        S_ISIZE = 14,                            // ISIZE
        S_U8 = 15,                               // U8
        S_U16 = 16,                              // U16
        S_U32 = 17,                              // U32
        S_U64 = 18,                              // U64
        S_USIZE = 19,                            // USIZE
        S_LET = 20,                              // LET
        S_MUT = 21,                              // MUT
        S_BOOL = 22,                             // BOOL
        S_FN = 23,                               // FN
        S_WHILE = 24,                            // WHILE
        S_PRINT_LN = 25,                         // PRINT_LN
        S_EQ = 26,                               // EQ
        S_EQEQ = 27,                             // EQEQ
        S_NE = 28,                               // NE
        S_BANG = 29,                             // BANG
        S_LT = 30,                               // LT
        S_LE = 31,                               // LE
        S_GT = 32,                               // GT
        S_GE = 33,                               // GE
        S_PLUS = 34,                             // PLUS
        S_MINUS = 35,                            // MINUS
        S_STAR = 36,                             // STAR
        S_SLASH = 37,                            // SLASH
        S_COMMA = 38,                            // COMMA
        S_ARROW = 39,                            // ARROW
        S_IF = 40,                               // IF
        S_ELSE = 41,                             // ELSE
        S_L_AND = 42,                            // L_AND
        S_L_OR = 43,                             // L_OR
        S_PLUS_EQ = 44,                          // PLUS_EQ
        S_MIN_EQ = 45,                           // MIN_EQ
        S_MUL_EQ = 46,                           // MUL_EQ
        S_DIV_EQ = 47,                           // DIV_EQ
        S_LBRACE = 48,                           // LBRACE
        S_RBRACE = 49,                           // RBRACE
        S_LPAREN = 50,                           // LPAREN
        S_RPAREN = 51,                           // RPAREN
        S_SEMICOLON = 52,                        // SEMICOLON
        S_COLON = 53,                            // COLON
        S_AMPERSAND = 54,                        // AMPERSAND
        S_OR = 55,                               // OR
        S_AMPERSAND_MUT = 56,                    // AMPERSAND_MUT
        S_REF = 57,                              // REF
        S_REF_MUT = 58,                          // REF_MUT
        S_DEREF = 59,                            // DEREF
        S_UMINUS = 60,                           // UMINUS
        S_NOT = 61,                              // NOT
        S_YYACCEPT = 62,                         // $accept
        S_program = 63,                          // program
        S_item_list = 64,                        // item_list
        S_item = 65,                             // item
        S_function_decl = 66,                    // function_decl
        S_func_ret_type = 67,                    // func_ret_type
        S_func_decl_args = 68,                   // func_decl_args
        S_func_arg_list = 69,                    // func_arg_list
        S_func_arg = 70,                         // func_arg
        S_stmt = 71,                             // stmt
        S_stmt_list = 72,                        // stmt_list
        S_print_ln = 73,                         // print_ln
        S_type_decl = 74,                        // type_decl
        S_opt_mut = 75,                          // opt_mut
        S_let = 76,                              // let
        S_if_expr = 77,                          // if_expr
        S_ref_add = 78,                          // ref_add
        S_type = 79,                             // type
        S_block_expr = 80,                       // block_expr
        S_assignment = 81,                       // assignment
        S_unary_op_expr = 82,                    // unary_op_expr
        S_bin_op_expr = 83,                      // bin_op_expr
        S_literal = 84,                          // literal
        S_call_expr_args = 85,                   // call_expr_args
        S_call_expr = 86,                        // call_expr
        S_while_expr = 87,                       // while_expr
        S_expr = 88,                             // expr
        S_expr_stmt = 89,                        // expr_stmt
        S_expr_w_block = 90,                     // expr_w_block
        S_expr_wo_block = 91                     // expr_wo_block
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_func_arg: // func_arg
        value.move< FunArg > (std::move (that.value));
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
        value.move< Token > (std::move (that.value));
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.move< Type > (std::move (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< Unique<AssignExpr> > (std::move (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< Unique<Ast> > (std::move (that.value));
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.move< Unique<BinOpExpr> > (std::move (that.value));
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.move< Unique<BlockExpr> > (std::move (that.value));
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.move< Unique<CallExpr> > (std::move (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_expr_w_block: // expr_w_block
      case symbol_kind::S_expr_wo_block: // expr_wo_block
        value.move< Unique<Expr> > (std::move (that.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.move< Unique<FunDecl> > (std::move (that.value));
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.move< Unique<IfElse> > (std::move (that.value));
        break;

      case symbol_kind::S_item: // item
        value.move< Unique<Item> > (std::move (that.value));
        break;

      case symbol_kind::S_let: // let
        value.move< Unique<LetStmt> > (std::move (that.value));
        break;

      case symbol_kind::S_literal: // literal
        value.move< Unique<Literal> > (std::move (that.value));
        break;

      case symbol_kind::S_print_ln: // print_ln
        value.move< Unique<PrintLn> > (std::move (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< Unique<Stmt> > (std::move (that.value));
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.move< Unique<UnaryOpExpr> > (std::move (that.value));
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.move< Unique<WhileLoop> > (std::move (that.value));
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< std::optional<Type> > (std::move (that.value));
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.move< std::vector<FunArg> > (std::move (that.value));
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.move< std::vector<Unique<Expr>> > (std::move (that.value));
        break;

      case symbol_kind::S_item_list: // item_list
        value.move< std::vector<Unique<Item>> > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<Unique<Stmt>> > (std::move (that.value));
        break;

      case symbol_kind::S_ref_add: // ref_add
        value.move< uint8_t > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, FunArg&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const FunArg& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Token&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Token& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Type&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Type& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<AssignExpr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<AssignExpr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<Ast>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<Ast>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<BinOpExpr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<BinOpExpr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<BlockExpr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<BlockExpr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<CallExpr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<CallExpr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<Expr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<Expr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<FunDecl>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<FunDecl>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<IfElse>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<IfElse>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<Item>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<Item>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<LetStmt>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<LetStmt>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<Literal>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<Literal>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<PrintLn>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<PrintLn>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<Stmt>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<Stmt>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<UnaryOpExpr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<UnaryOpExpr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Unique<WhileLoop>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Unique<WhileLoop>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::optional<Type>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::optional<Type>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<FunArg>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<FunArg>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<Unique<Expr>>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<Unique<Expr>>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<Unique<Item>>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<Unique<Item>>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<Unique<Stmt>>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<Unique<Stmt>>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, uint8_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const uint8_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_func_arg: // func_arg
        value.template destroy< FunArg > ();
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
        value.template destroy< Token > ();
        break;

      case symbol_kind::S_func_ret_type: // func_ret_type
      case symbol_kind::S_type: // type
        value.template destroy< Type > ();
        break;

      case symbol_kind::S_assignment: // assignment
        value.template destroy< Unique<AssignExpr> > ();
        break;

      case symbol_kind::S_program: // program
        value.template destroy< Unique<Ast> > ();
        break;

      case symbol_kind::S_bin_op_expr: // bin_op_expr
        value.template destroy< Unique<BinOpExpr> > ();
        break;

      case symbol_kind::S_block_expr: // block_expr
        value.template destroy< Unique<BlockExpr> > ();
        break;

      case symbol_kind::S_call_expr: // call_expr
        value.template destroy< Unique<CallExpr> > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_expr_w_block: // expr_w_block
      case symbol_kind::S_expr_wo_block: // expr_wo_block
        value.template destroy< Unique<Expr> > ();
        break;

      case symbol_kind::S_function_decl: // function_decl
        value.template destroy< Unique<FunDecl> > ();
        break;

      case symbol_kind::S_if_expr: // if_expr
        value.template destroy< Unique<IfElse> > ();
        break;

      case symbol_kind::S_item: // item
        value.template destroy< Unique<Item> > ();
        break;

      case symbol_kind::S_let: // let
        value.template destroy< Unique<LetStmt> > ();
        break;

      case symbol_kind::S_literal: // literal
        value.template destroy< Unique<Literal> > ();
        break;

      case symbol_kind::S_print_ln: // print_ln
        value.template destroy< Unique<PrintLn> > ();
        break;

      case symbol_kind::S_stmt: // stmt
        value.template destroy< Unique<Stmt> > ();
        break;

      case symbol_kind::S_unary_op_expr: // unary_op_expr
        value.template destroy< Unique<UnaryOpExpr> > ();
        break;

      case symbol_kind::S_while_expr: // while_expr
        value.template destroy< Unique<WhileLoop> > ();
        break;

      case symbol_kind::S_opt_mut: // opt_mut
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.template destroy< std::optional<Type> > ();
        break;

      case symbol_kind::S_func_decl_args: // func_decl_args
      case symbol_kind::S_func_arg_list: // func_arg_list
        value.template destroy< std::vector<FunArg> > ();
        break;

      case symbol_kind::S_call_expr_args: // call_expr_args
        value.template destroy< std::vector<Unique<Expr>> > ();
        break;

      case symbol_kind::S_item_list: // item_list
        value.template destroy< std::vector<Unique<Item>> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.template destroy< std::vector<Unique<Stmt>> > ();
        break;

      case symbol_kind::S_ref_add: // ref_add
        value.template destroy< uint8_t > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Token v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const Token& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
    };

    /// Build a parser object.
    Parser (Lexer &lexer_yyarg, const bool debug_yyarg, const char* input_file_name_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF (location_type l)
      {
        return symbol_type (token::YYEOF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYEOF (const location_type& l)
      {
        return symbol_type (token::YYEOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEC_LITERAL (Token v, location_type l)
      {
        return symbol_type (token::DEC_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DEC_LITERAL (const Token& v, const location_type& l)
      {
        return symbol_type (token::DEC_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT_LITERAL (Token v, location_type l)
      {
        return symbol_type (token::FLOAT_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT_LITERAL (const Token& v, const location_type& l)
      {
        return symbol_type (token::FLOAT_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STR_LITERAL (Token v, location_type l)
      {
        return symbol_type (token::STR_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STR_LITERAL (const Token& v, const location_type& l)
      {
        return symbol_type (token::STR_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRUE (Token v, location_type l)
      {
        return symbol_type (token::TRUE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TRUE (const Token& v, const location_type& l)
      {
        return symbol_type (token::TRUE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FALSE (Token v, location_type l)
      {
        return symbol_type (token::FALSE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FALSE (const Token& v, const location_type& l)
      {
        return symbol_type (token::FALSE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (Token v, location_type l)
      {
        return symbol_type (token::IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const Token& v, const location_type& l)
      {
        return symbol_type (token::IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNDERSCORE (Token v, location_type l)
      {
        return symbol_type (token::UNDERSCORE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNDERSCORE (const Token& v, const location_type& l)
      {
        return symbol_type (token::UNDERSCORE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_I8 (Token v, location_type l)
      {
        return symbol_type (token::I8, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_I8 (const Token& v, const location_type& l)
      {
        return symbol_type (token::I8, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_I16 (Token v, location_type l)
      {
        return symbol_type (token::I16, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_I16 (const Token& v, const location_type& l)
      {
        return symbol_type (token::I16, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_I32 (Token v, location_type l)
      {
        return symbol_type (token::I32, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_I32 (const Token& v, const location_type& l)
      {
        return symbol_type (token::I32, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_I64 (Token v, location_type l)
      {
        return symbol_type (token::I64, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_I64 (const Token& v, const location_type& l)
      {
        return symbol_type (token::I64, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ISIZE (Token v, location_type l)
      {
        return symbol_type (token::ISIZE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ISIZE (const Token& v, const location_type& l)
      {
        return symbol_type (token::ISIZE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U8 (Token v, location_type l)
      {
        return symbol_type (token::U8, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_U8 (const Token& v, const location_type& l)
      {
        return symbol_type (token::U8, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U16 (Token v, location_type l)
      {
        return symbol_type (token::U16, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_U16 (const Token& v, const location_type& l)
      {
        return symbol_type (token::U16, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U32 (Token v, location_type l)
      {
        return symbol_type (token::U32, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_U32 (const Token& v, const location_type& l)
      {
        return symbol_type (token::U32, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U64 (Token v, location_type l)
      {
        return symbol_type (token::U64, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_U64 (const Token& v, const location_type& l)
      {
        return symbol_type (token::U64, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USIZE (Token v, location_type l)
      {
        return symbol_type (token::USIZE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_USIZE (const Token& v, const location_type& l)
      {
        return symbol_type (token::USIZE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LET (Token v, location_type l)
      {
        return symbol_type (token::LET, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LET (const Token& v, const location_type& l)
      {
        return symbol_type (token::LET, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MUT (Token v, location_type l)
      {
        return symbol_type (token::MUT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MUT (const Token& v, const location_type& l)
      {
        return symbol_type (token::MUT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOL (Token v, location_type l)
      {
        return symbol_type (token::BOOL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BOOL (const Token& v, const location_type& l)
      {
        return symbol_type (token::BOOL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FN (Token v, location_type l)
      {
        return symbol_type (token::FN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FN (const Token& v, const location_type& l)
      {
        return symbol_type (token::FN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (Token v, location_type l)
      {
        return symbol_type (token::WHILE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WHILE (const Token& v, const location_type& l)
      {
        return symbol_type (token::WHILE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PRINT_LN (Token v, location_type l)
      {
        return symbol_type (token::PRINT_LN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PRINT_LN (const Token& v, const location_type& l)
      {
        return symbol_type (token::PRINT_LN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQ (Token v, location_type l)
      {
        return symbol_type (token::EQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EQ (const Token& v, const location_type& l)
      {
        return symbol_type (token::EQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQEQ (Token v, location_type l)
      {
        return symbol_type (token::EQEQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EQEQ (const Token& v, const location_type& l)
      {
        return symbol_type (token::EQEQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NE (Token v, location_type l)
      {
        return symbol_type (token::NE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NE (const Token& v, const location_type& l)
      {
        return symbol_type (token::NE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BANG (Token v, location_type l)
      {
        return symbol_type (token::BANG, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BANG (const Token& v, const location_type& l)
      {
        return symbol_type (token::BANG, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LT (Token v, location_type l)
      {
        return symbol_type (token::LT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LT (const Token& v, const location_type& l)
      {
        return symbol_type (token::LT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LE (Token v, location_type l)
      {
        return symbol_type (token::LE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LE (const Token& v, const location_type& l)
      {
        return symbol_type (token::LE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GT (Token v, location_type l)
      {
        return symbol_type (token::GT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_GT (const Token& v, const location_type& l)
      {
        return symbol_type (token::GT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GE (Token v, location_type l)
      {
        return symbol_type (token::GE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_GE (const Token& v, const location_type& l)
      {
        return symbol_type (token::GE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS (Token v, location_type l)
      {
        return symbol_type (token::PLUS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS (const Token& v, const location_type& l)
      {
        return symbol_type (token::PLUS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS (Token v, location_type l)
      {
        return symbol_type (token::MINUS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MINUS (const Token& v, const location_type& l)
      {
        return symbol_type (token::MINUS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STAR (Token v, location_type l)
      {
        return symbol_type (token::STAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STAR (const Token& v, const location_type& l)
      {
        return symbol_type (token::STAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SLASH (Token v, location_type l)
      {
        return symbol_type (token::SLASH, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SLASH (const Token& v, const location_type& l)
      {
        return symbol_type (token::SLASH, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (Token v, location_type l)
      {
        return symbol_type (token::COMMA, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const Token& v, const location_type& l)
      {
        return symbol_type (token::COMMA, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARROW (Token v, location_type l)
      {
        return symbol_type (token::ARROW, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ARROW (const Token& v, const location_type& l)
      {
        return symbol_type (token::ARROW, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (Token v, location_type l)
      {
        return symbol_type (token::IF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const Token& v, const location_type& l)
      {
        return symbol_type (token::IF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (Token v, location_type l)
      {
        return symbol_type (token::ELSE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const Token& v, const location_type& l)
      {
        return symbol_type (token::ELSE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_L_AND (Token v, location_type l)
      {
        return symbol_type (token::L_AND, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_L_AND (const Token& v, const location_type& l)
      {
        return symbol_type (token::L_AND, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_L_OR (Token v, location_type l)
      {
        return symbol_type (token::L_OR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_L_OR (const Token& v, const location_type& l)
      {
        return symbol_type (token::L_OR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS_EQ (Token v, location_type l)
      {
        return symbol_type (token::PLUS_EQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS_EQ (const Token& v, const location_type& l)
      {
        return symbol_type (token::PLUS_EQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MIN_EQ (Token v, location_type l)
      {
        return symbol_type (token::MIN_EQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MIN_EQ (const Token& v, const location_type& l)
      {
        return symbol_type (token::MIN_EQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MUL_EQ (Token v, location_type l)
      {
        return symbol_type (token::MUL_EQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MUL_EQ (const Token& v, const location_type& l)
      {
        return symbol_type (token::MUL_EQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV_EQ (Token v, location_type l)
      {
        return symbol_type (token::DIV_EQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DIV_EQ (const Token& v, const location_type& l)
      {
        return symbol_type (token::DIV_EQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACE (Token v, location_type l)
      {
        return symbol_type (token::LBRACE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LBRACE (const Token& v, const location_type& l)
      {
        return symbol_type (token::LBRACE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACE (Token v, location_type l)
      {
        return symbol_type (token::RBRACE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RBRACE (const Token& v, const location_type& l)
      {
        return symbol_type (token::RBRACE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (Token v, location_type l)
      {
        return symbol_type (token::LPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LPAREN (const Token& v, const location_type& l)
      {
        return symbol_type (token::LPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (Token v, location_type l)
      {
        return symbol_type (token::RPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RPAREN (const Token& v, const location_type& l)
      {
        return symbol_type (token::RPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON (Token v, location_type l)
      {
        return symbol_type (token::SEMICOLON, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SEMICOLON (const Token& v, const location_type& l)
      {
        return symbol_type (token::SEMICOLON, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (Token v, location_type l)
      {
        return symbol_type (token::COLON, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const Token& v, const location_type& l)
      {
        return symbol_type (token::COLON, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AMPERSAND (Token v, location_type l)
      {
        return symbol_type (token::AMPERSAND, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AMPERSAND (const Token& v, const location_type& l)
      {
        return symbol_type (token::AMPERSAND, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR (Token v, location_type l)
      {
        return symbol_type (token::OR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OR (const Token& v, const location_type& l)
      {
        return symbol_type (token::OR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AMPERSAND_MUT (Token v, location_type l)
      {
        return symbol_type (token::AMPERSAND_MUT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AMPERSAND_MUT (const Token& v, const location_type& l)
      {
        return symbol_type (token::AMPERSAND_MUT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REF (location_type l)
      {
        return symbol_type (token::REF, std::move (l));
      }
#else
      static
      symbol_type
      make_REF (const location_type& l)
      {
        return symbol_type (token::REF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REF_MUT (location_type l)
      {
        return symbol_type (token::REF_MUT, std::move (l));
      }
#else
      static
      symbol_type
      make_REF_MUT (const location_type& l)
      {
        return symbol_type (token::REF_MUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEREF (location_type l)
      {
        return symbol_type (token::DEREF, std::move (l));
      }
#else
      static
      symbol_type
      make_DEREF (const location_type& l)
      {
        return symbol_type (token::DEREF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UMINUS (location_type l)
      {
        return symbol_type (token::UMINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_UMINUS (const location_type& l)
      {
        return symbol_type (token::UMINUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT (location_type l)
      {
        return symbol_type (token::NOT, std::move (l));
      }
#else
      static
      symbol_type
      make_NOT (const location_type& l)
      {
        return symbol_type (token::NOT, l);
      }
#endif


    class context
    {
    public:
      context (const Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 475,     ///< Last index in yytable_.
      yynnts_ = 30,  ///< Number of nonterminal symbols.
      yyfinal_ = 8 ///< Termination state number.
    };


    // User arguments.
    Lexer &lexer;
    const bool debug;
    const char* input_file_name;

  };


#line 39 "parser/yaccfile.yy"
} // mr
#line 2931 "parser/parser.tab.hpp"




#endif // !YY_YY_PARSER_PARSER_TAB_HPP_INCLUDED
