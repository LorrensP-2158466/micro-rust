%require "3.8"
%language "c++"

%defines
%define api.namespace {mr}
%define api.parser.class {Parser}
%define api.value.type variant

%locations
%define parse.error detailed
%define parse.trace

%header
%verbose

%code requires {
namespace mr {
    class Lexer;
    namespace driver {
        class MRDriver;
    }
}
#include "lexer/token.hpp"
#include "high/ast/module.hpp"
#include "high/expr/module.hpp"
#include "mr_util.hpp"

using namespace mr;
using namespace mr::ast;
using namespace mr::expr;
}

%parse-param {driver::MRDriver& driver}
%parse-param {Lexer &lexer}
%parse-param {const bool debug}
%parse-param {const char* input_file_name}

%code top{
#include <string>
#include <variant>
#include <cstddef>
#include <memory>
#include <assert.h>
#include "lexer/lexer.hpp"
#include "driver/mr_driver.hpp"

    #define yylex lexer.yylex
    #define DEFAULT_ACTION(to, from) do { to = std::move(from);} while(0)
}


%token <Token> DEC_LITERAL
%token <Token> FLOAT_LITERAL
%token <Token> STR_LITERAL
%token <Token> TRUE FALSE
%token <Token> IDENTIFIER UNDERSCORE
%token <Token> I8 I16 I32 I64 ISIZE U8 U16 U32 U64 USIZE
%token <Token> LET MUT BOOL FN WHILE PRINT_LN
%token <Token> EQ EQEQ NE BANG LT LE GT GE PLUS MINUS STAR SLASH COMMA ARROW
%token <Token> IF ELSE
%token <Token> RETURN BREAK CONTINUE
%token <Token> L_AND L_OR
%token <Token> PLUS_EQ MIN_EQ MUL_EQ DIV_EQ
%token <Token> LBRACE RBRACE LPAREN RPAREN SEMICOLON COLON
%token <Token> AMPERSAND /* & */ OR /* | */ AMPERSAND_MUT
%token <Token> DOT

%nterm <std::vector<U<Stmt>>> stmt_list 
%nterm <U<Stmt>> stmt 
%nterm <U<Expr>> expr expr_stmt expr_w_block expr_wo_block 
%nterm <U<UnaryOpExpr>> unary_op_expr
%nterm <U<Item>> item 
%nterm <std::vector<U<Item>>> item_list 
%nterm <U<BlockExpr>> block_expr
%nterm <U<FunDecl>> function_decl
%nterm <U<LetStmt>> let 
%nterm <std::vector<U<Expr>>> expr_list
%nterm <FunArg> func_arg
%nterm <std::vector<FunArg>> func_arg_list func_decl_args
%nterm <Type> type 
%nterm <std::vector<Type>> type_list
%nterm <Type> func_ret_type
%nterm <std::optional<Type>> type_decl
%nterm <bool> opt_mut
%nterm <U<Ast>> program 
%nterm <U<IfElse>> if_expr
%nterm <U<Expr>> bin_op_expr
%nterm <U<CallExpr>> call_expr
%nterm <U<TupleIndexExpr>> tuple_index_expr
%nterm <std::vector<U<Expr>>> call_expr_args
%nterm <U<WhileLoop>> while_expr
%nterm <U<Literal>> literal
%nterm <U<PrintLn>> print_ln


%right EQ PLUS_EQ MIN_EQ MUL_EQ DIV_EQ MOD_EQ BIT_AND_EQ BIT_OR_EQ BIT_XOR_EQ SHL_EQ SHR_EQ    // right to left
// %left DOT DOT_EQ                                     // Require parentheses
%left L_OR                                           // left to right ||
%left L_AND                                          // left to right &&
// %left BIT_OR                                         // left to right |
// %left BIT_XOR                                        // left to right ^
// %left BIT_AND                                        // left to right &
%left EQEQ NE LT GT LE GE                           // Require parentheses for comparisons
// %left SHL SHR                                        // left to right << >>
%left PLUS MINUS                                     // left to right
%left STAR SLASH MOD                                 // left to right
// %right AS                                            // left to right type casting
%right UMINUS DEREF NOT REF REF_MUT                 // Unary operators - * ! & &mut
%left METHOD_CALL FIELD_ACCESS FUNC_CALL            // Field expressions, Function calls, array indexing
%left PATH // paths are identifiers for now

// for the expr_wo_block, we need some ordering as well
%left CALL_INDEX
%left UNARY
%left BIN_OP
%left CONTROL_FLOW


%start program
%%


// vul aan met producties


program
    : item_list { driver.set_ast(std::make_unique<Ast>(std::move($1))); }
    ;

item_list
    : item_list item {$1.push_back(std::move($2)); DEFAULT_ACTION($$, $1);}
    | item {
        auto vec = std::vector<U<Item>>();
        vec.push_back(std::move($1));
        $$ = std::move(vec) ;}
    ;

item
  : function_decl { DEFAULT_ACTION($$, $1); }
  /* | error { std::cout << "Expected item\n"; exit(-1);} */
  ;

function_decl
    : FN IDENTIFIER func_decl_args func_ret_type block_expr 
    { 
        $$ = FunDecl::make_unique($2.string_value(), std::move($3), std::move($4), std::move($5));
    }
    ;

func_ret_type
    : ARROW type { DEFAULT_ACTION($$, $2); }
    /* | ARROW error { driver.ecx().emit_error(std::make_unique<parser::) } */
    | { $$ = Type(); } // no arrow with type is the same as -> ()
    ;


func_decl_args
    : LPAREN func_arg_list RPAREN {$$ = std::move($2);}
    | LPAREN RPAREN { $$ = std::vector<FunArg>{};}
    | error { $$ = std::vector<FunArg>{};}
    ;

func_arg_list
    : func_arg_list COMMA func_arg { $1.push_back(std::move($3)); DEFAULT_ACTION($$, $1);}
    | func_arg { $$ = std::vector<FunArg>{}; $$.push_back(std::move($1)); }
    ;

func_arg
    : opt_mut IDENTIFIER COLON type { $$ = FunArg{$2.string_value(), std::move($4), $1}; }
    | opt_mut IDENTIFIER error { std::cerr << "Expected type declaration\n";}
    ;

stmt: SEMICOLON {$$ = std::make_unique<EmptyStmt>();}
    | let { DEFAULT_ACTION($$, $1); }
    | RETURN SEMICOLON {  $$ = std::make_unique<Return>(std::make_unique<Unit>()); }
    | BREAK SEMICOLON {  $$ = std::make_unique<Break>(std::make_unique<Unit>()); }
    | CONTINUE SEMICOLON {  $$ = std::make_unique<Continue>(); }
    | expr_stmt { DEFAULT_ACTION($$, $1);}
    | print_ln SEMICOLON { DEFAULT_ACTION($$, $1);}
    | item { DEFAULT_ACTION($$, $1); }
    ;

stmt_list
    : stmt_list stmt { $1.push_back(std::move($2)); DEFAULT_ACTION($$, $1); }
    // error in statement, don't care go ahead
    | stmt_list error { DEFAULT_ACTION($$, $1);}
    | stmt {
        auto vec = std::vector<U<Stmt>>();
        vec.push_back(std::move($1));
        $$ = std::move(vec); 
      } 
    
    ;

print_ln
    : PRINT_LN LPAREN STR_LITERAL RPAREN { $$ = std::make_unique<PrintLn>($3.string_value()); }


type_decl
    : COLON type { DEFAULT_ACTION($$, $2); } // set type to output
    | COLON error { $$ = Type::infer();  } 
    | { $$ = {}; } // no type decl no type
    ;

opt_mut
  : MUT  { $$ = true; }
  |      { $$ = false; }
  ;

let
    : LET opt_mut IDENTIFIER type_decl EQ expr SEMICOLON
      {$$ = LetStmt::make_unique_init($3.string_value(), std::move($4), std::move($6), $2);}   
    | LET opt_mut IDENTIFIER type_decl SEMICOLON {
        $$ = LetStmt::make_unique_decl($3.string_value(), std::move($4), $2);
    }
    ;

if_expr
    : IF expr block_expr { $$ = std::make_unique<IfElse>(std::move($2), std::move($3)); } 
    | IF expr block_expr ELSE if_expr {$$ = std::make_unique<IfElse>(std::move($2), std::move($3), std::move($5)); }
    | IF expr block_expr ELSE block_expr {$$ = std::make_unique<IfElse>(std::move($2), std::move($3), std::move($5)); }
    ;


/* ref_add
    : AMPERSAND {$$ = Type::ref_flag; }
    | AMPERSAND_MUT {$$ = Type::ref_mut_flag; }
    | { $$ = 0; }
    ; */

type_list
    : type_list COMMA type {$$ = std::move($1); $$.push_back(std::move($3));}
    | type {$$ = std::vector<Type>(); $$.push_back(std::move($1));}
    ;

type
    : I8 { $$ = Type(primitive_type::I8); }
    | I16 { $$ = Type(primitive_type::I16); }
    | I32{ $$ = Type(primitive_type::I32); }
    | I64 { $$ = Type(primitive_type::I64); }
    | ISIZE { $$ = Type(primitive_type::ISIZE); }
    | U8 { $$ = Type(primitive_type::U8); }
    | U16 { $$ = Type(primitive_type::U16); }
    | U32{ $$ = Type(primitive_type::U32); }
    | U64 { $$ = Type(primitive_type::U64); }
    | USIZE { $$ = Type(primitive_type::USIZE); }
    | BOOL { $$ = Type(primitive_type::BOOL); }
    | LPAREN type_list RPAREN { $$ = Type(std::move($2));}
    | LPAREN RPAREN { $$ = Type(); }
    ;


block_expr
    : LBRACE stmt_list RBRACE { $$ = std::make_unique<BlockExpr>(std::move($2), std::make_unique<Unit>()); }
    | LBRACE stmt_list expr RBRACE  { $$ = std::make_unique<BlockExpr>(std::move($2), std::move($3)); }
    | LBRACE expr RBRACE  { $$ = std::make_unique<BlockExpr>(std::vector<U<Stmt>>{}, std::move($2)); }
    | LBRACE RBRACE  { $$ = std::make_unique<BlockExpr>(std::vector<U<Stmt>>{}, std::make_unique<Unit>()); }
    ;

unary_op_expr
    : MINUS expr %prec UMINUS { $$ = std::make_unique<UnaryOpExpr>(UnaryOp::Negate, std::move($2));}
    | STAR expr %prec DEREF { $$ = std::make_unique<UnaryOpExpr>(UnaryOp::Deref, std::move($2));}
    | BANG expr %prec NOT { $$ = std::make_unique<UnaryOpExpr>(UnaryOp::Not, std::move($2));}
    | AMPERSAND expr %prec REF { $$ = std::make_unique<UnaryOpExpr>(UnaryOp::Borrow, std::move($2));}
    | AMPERSAND_MUT expr %prec REF_MUT { $$ = std::make_unique<UnaryOpExpr>(UnaryOp::MutBorrow, std::move($2));}
    ;

bin_op_expr
    : expr PLUS expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::Plus, std::move($3)); }
    | expr MINUS expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::Min, std::move($3)); }
    | expr STAR expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::Mul, std::move($3)); }
    | expr SLASH expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::Div, std::move($3)); }
    | expr L_AND expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::L_AND, std::move($3)); }
    | expr L_OR expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::L_OR, std::move($3)); }
    | expr EQEQ expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::Eq, std::move($3)); }
    | expr NE expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::NEq, std::move($3)); }
    | expr LT expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::Lt, std::move($3)); }
    | expr GT expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::Gt, std::move($3)); }
    | expr GE expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::GtEq, std::move($3)); }
    | expr LE expr { $$ = std::make_unique<BinOpExpr>(std::move($1), BinOp::LtEq, std::move($3)); }
    // this fixes shift/reduce conflicts
    | expr EQ expr      { $$ = std::make_unique<AssignExpr>(std::move($1), AssignOp::Eq, std::move($3));}
    | expr PLUS_EQ expr { $$ = std::make_unique<AssignExpr>(std::move($1), AssignOp::PlusEq, std::move($3));}
    | expr MIN_EQ expr  { $$ = std::make_unique<AssignExpr>(std::move($1), AssignOp::MinEq, std::move($3));}
    | expr DIV_EQ expr  { $$ = std::make_unique<AssignExpr>(std::move($1), AssignOp::DivEq, std::move($3));}
    | expr MUL_EQ expr  { $$ = std::make_unique<AssignExpr>(std::move($1), AssignOp::MulEq, std::move($3));}
    ;

literal
    : DEC_LITERAL { $$ = Literal::make_int_lit($1.symbol);}
    | STR_LITERAL { $$ = Literal::make_str_lit($1.symbol); }
    | FLOAT_LITERAL { assert(1 && "How did we get here"); }
    | TRUE { $$ = Literal::make_bool_lit($1.symbol); }
    | FALSE { $$ = Literal::make_bool_lit($1.symbol); }
    ;


call_expr_args
    : call_expr_args COMMA expr { $1.push_back(std::move($3)); DEFAULT_ACTION($$, $1); }
    | expr { 
        auto vec = std::vector<U<Expr>>();
        vec.push_back(std::move($1));
        $$ = std::move(vec);
        }
    ;

call_expr
    : IDENTIFIER LPAREN call_expr_args RPAREN { $$ = std::make_unique<CallExpr>($1.string_value(), std::move($3)); }
    | IDENTIFIER LPAREN RPAREN { $$ = std::make_unique<CallExpr>($1.string_value(), std::vector<U<Expr>>{}); }

while_expr
    : WHILE expr block_expr {$$ = std::make_unique<WhileLoop>(std::move($2), std::move($3)); }
    ;

tuple_index_expr
    : expr DOT DEC_LITERAL { $$ = std::make_unique<TupleIndexExpr>(std::move($1), Literal::make_int_lit($3.symbol));}
    ;


expr
    : expr_w_block { DEFAULT_ACTION($$, $1);}
    | expr_wo_block { DEFAULT_ACTION($$, $1);}
    ;

expr_list
    : expr_list COMMA expr { $1.push_back(std::move($3)); $$ = std::move($1);}
    | expr {$$ = std::vector<U<Expr>>(); $$.push_back(std::move($1));}
    ;

expr_stmt
    : expr_w_block  { DEFAULT_ACTION($$, $1);}
    | expr_wo_block SEMICOLON { DEFAULT_ACTION($$, $1); }
    ;

expr_w_block
    : while_expr { DEFAULT_ACTION($$, $1); }
    | if_expr { DEFAULT_ACTION($$, $1); }
    | block_expr { DEFAULT_ACTION($$, $1); }
    ;
expr_wo_block
    : LPAREN expr RPAREN { DEFAULT_ACTION($$, $2); }
    | bin_op_expr %prec BIN_OP{ DEFAULT_ACTION($$, $1); }
    | tuple_index_expr %prec FIELD_ACCESS { DEFAULT_ACTION($$, $1); }
    | IDENTIFIER %prec PATH { $$ = std::make_unique<Identifier>($1.string_value()); }
    | unary_op_expr %prec UNARY {DEFAULT_ACTION($$, $1); }
    | LPAREN RPAREN %prec PATH { $$ = std::make_unique<Unit>(); }
    | call_expr %prec CALL_INDEX { DEFAULT_ACTION($$, $1); }
    | RETURN expr %prec CONTROL_FLOW { $$ = std::make_unique<Return>(std::move($2)); }
    | BREAK expr %prec CONTROL_FLOW { $$ = std::make_unique<Break>(std::move($2)); }
    | CONTINUE %prec CONTROL_FLOW { $$ = std::make_unique<Continue>(); }
    | LPAREN expr_list opt_comma  RPAREN { $$ = std::make_unique<TupleExpr>(std::move($2)); }
    | literal { DEFAULT_ACTION($$, $1); }
    ;


opt_comma
    : COMMA {}
    | {}
    ;
%%

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