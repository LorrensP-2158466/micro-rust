%require "3.2"
%language "c++"


%code requires {


#include "../ast/module.hpp"
#include "../expr/module.hpp"
#include "mr_util.hpp"
#include "../lexer/span.hpp"
#include "../lexer/token.hpp"
#include <string>
#include <variant>
#include <cstddef>
#include <memory>
namespace mr {
  class Lexer; // Forward declaration
}

// this makes everything cleaner even though im against this
using namespace mr::ast;
using namespace mr::expr;
}

%code top {

    #include <iostream>
    #include "../lexer/lexer.hpp"
    #include "parser.tab.hpp"
    #include "location.hh"
namespace mr {
  class Lexer; // Forward declaration
}

    extern mr::Unique<Ast> root;  
}
%define api.namespace {mr}
%define api.parser.class {Parser}
%define api.value.type variant
%locations
%define parse.error verbose
%define parse.trace

%header
%verbose

%parse-param {Lexer &lexer}
%parse-param {const bool debug}
%parse-param {const char* input_file_name}

%initial-action
{
    #if YYDEBUG != 0
        set_debug_level(debug);
    #endif
};

%code {
    #define yylex lexer.yylex
}

%defines

%token <Token> DEC_LITERAL
%token <Token> TRUE FALSE
%token <Token> IDENTIFIER UNDERSCORE
%token <Token> LET MUT I32 BOOL FN WHILE PRINT_VAR PRINT_STRING PRINT_LN
%token <Token> EQ EQEQ NE BANG LT LE GT GE PLUS MINUS STAR SLASH COMMA ARROW
%token <Token> IF ELSE
%token <Token> L_AND L_OR
%token <Token> PLUS_EQ MIN_EQ MUL_EQ DIV_EQ
%token <Token> LBRACE RBRACE LPAREN RPAREN SEMICOLON COLON
%token <Token> AMPERSAND /* & */ OR /* | */ AMPERSAND_MUT

%nterm <std::vector<Unique<Stmt>>> stmt_list 
%nterm <Unique<Stmt>> stmt 
%nterm <Unique<Expr>> expr 
%nterm <Unique<UnaryOpExpr>> unary_op_expr
%nterm <Unique<Item>> item 
%nterm <Unique<AssignExpr>> assignment
%nterm <std::vector<Unique<Item>>> item_list 
%nterm <Unique<BlockExpr>> block_expr
%nterm <Unique<FunDecl>> function_decl
%nterm <Unique<LetStmt>> let 
%nterm <FuncArg> func_arg
%nterm <std::vector<FuncArg>> func_arg_list func_decl_args
%nterm <Type> type 
%nterm <std::optional<Type>> func_ret_type
%nterm <std::optional<Type>> type_decl
%nterm <bool> opt_mut
%nterm <Unique<Ast>> program 
%nterm <Unique<IfElse>> if_expr
%nterm <uint8_t> ref_add
%nterm <Unique<BinOpExpr>> bin_op_expr
%nterm <Unique<CallExpr>> call_expr
%nterm <std::vector<Unique<Expr>>> call_expr_args
%nterm <Unique<WhileLoop>> while_expr


%nonassoc PLUS_EQ MIN_EQ DIV_EQ MUL_EQ EQ // assignment operators
%nonassoc LT LE GT GE NE EQEQ  // Comparison operators
%left L_OR                    // Logical OR
%left L_AND                   // Logical AND
%left PLUS MINUS              // Arithmetic addition/subtraction
%left STAR SLASH              // Arithmetic multiplication/division
%right REF REF_MUT DEREF UMINUS NOT  // Unary operators

%expect 0

%start program
%%


// vul aan met producties

program
    : item_list { root = std::make_unique<Ast>(std::move($1)); }
    ;

item_list
    : item_list item {$1.push_back(std::move($2)); $$ = std::move($1);}
    // error in item, just keep going
    | item_list error item {$1.push_back(std::move($3)); $$ = std::move($1);}
    | item {
        auto vec = std::vector<Unique<Item>>();
        vec.push_back(std::move($1));
         $$ = std::move(vec) ;}
    ;

item
  : function_decl { $$ = std::move($1); }
  // struct decl, ....
  ;

function_decl
    : FN IDENTIFIER func_decl_args func_ret_type block_expr 
    { 
        $$ = FunDecl::make_unique($2.string_value(), $3, $4, std::move($5));
    }
    ;

func_ret_type
    : ARROW type { $$ = {$2}; }
    | { $$ = {primitive_type::Unit, 0}; } // no arrow with type is the same as -> ()
    ;


func_decl_args
    : LPAREN func_arg_list RPAREN {$$ = std::move($2);}
    | LPAREN RPAREN { $$ = std::vector<FuncArg>{};}
    | error { $$ = std::vector<FuncArg>{};}
    ;

func_arg_list
    : func_arg_list COMMA func_arg { $1.push_back($3); $$ = $1;}
    | func_arg { $$ = std::vector<FuncArg>{ $1 }; }
    ;

func_arg
    : IDENTIFIER type_decl { $$ = FuncArg{$1.string_value(), *$2}; }
    ;

stmt: SEMICOLON {/* An empty statement */}
    | let { $$ = std::move($1); }
    | expr SEMICOLON { $$ = std::move($1); }
    | PRINT_LN SEMICOLON { $$ = std::make_unique<PrintLn>($1.string_value()); }
    | item { $$ = std::move($1); }
    | error SEMICOLON {/* just keep going */}
    ;

stmt_list
    : stmt_list stmt { $1.push_back(std::move($2)); $$ = std::move($1); }
    | stmt {
        auto vec = std::vector<Unique<Stmt>>();
        vec.push_back(std::move($1));
        $$ = std::move(vec); 
      } 
    ;


type_decl
    : COLON type { $$ = $2; } // set type to output
    | { $$ = {}; } // no type decl no type
    ;

opt_mut
  : MUT  { $$ = true; }
  |      { $$ = false; }
  ;

let
    : LET opt_mut IDENTIFIER type_decl EQ expr SEMICOLON
      {$$ = LetStmt::make_unique_init($3.string_value(), $4, std::move($6), $2);}  
    | LET opt_mut IDENTIFIER type_decl error EQ SEMICOLON
      {
        $$ = LetStmt::make_unique_init($3.string_value(), $4, std::unique_ptr<Expr>(nullptr), $2); 
      }   
    | LET opt_mut IDENTIFIER COLON type SEMICOLON { $$ = LetStmt::make_unique_decl($3.string_value(), $5, $2); }
    | LET UNDERSCORE COLON type EQ expr SEMICOLON { printf("INIT no named\n"); }
    ;

if_expr
    : IF expr block_expr { $$ = std::make_unique<IfElse>(std::move($2), std::move($3)); } 
    | IF expr block_expr ELSE if_expr {$$ = std::make_unique<IfElse>(std::move($2), std::move($3), std::move($5)); }
    | IF expr block_expr ELSE block_expr {$$ = std::make_unique<IfElse>(std::move($2), std::move($3), std::move($5)); }
    ;


ref_add
    : AMPERSAND {$$ = Type::ref_flag; }
    | AMPERSAND_MUT {$$ = Type::ref_mut_flag; }
    | { $$ = 0; }

type
    : ref_add I32 { $$ = Type{primitive_type::I32, $1}; }
    | ref_add BOOL { $$ = {primitive_type::Bool, $1}; }
    | ref_add LPAREN RPAREN { $$ = {primitive_type::Unit, $1}; }
    | ref_add IDENTIFIER { $$ = Type{$2.string_value(), $1}; }
    ;


block_expr
    : LBRACE stmt_list RBRACE { $$ = std::make_unique<BlockExpr>(std::move($2), std::make_unique<Unit>()); }
    | LBRACE stmt_list expr RBRACE  { $$ = std::make_unique<BlockExpr>(std::move($2), std::move($3)); }
    | LBRACE expr RBRACE  { $$ = std::make_unique<BlockExpr>(std::vector<Unique<Stmt>>{}, std::move($2)); }
    | LBRACE RBRACE  { $$ = std::make_unique<BlockExpr>(std::vector<Unique<Stmt>>{}, std::make_unique<Unit>()); }
    ;

assignment
    : IDENTIFIER EQ expr { $$ = std::make_unique<AssignExpr>($1.string_value(), AssignOp::Eq, std::move($3));}
    | IDENTIFIER PLUS_EQ expr { $$ = std::make_unique<AssignExpr>($1.string_value(), AssignOp::PlusEq, std::move($3));}
    | IDENTIFIER MIN_EQ expr { $$ = std::make_unique<AssignExpr>($1.string_value(), AssignOp::MinEq, std::move($3));}
    | IDENTIFIER DIV_EQ expr { $$ = std::make_unique<AssignExpr>($1.string_value(), AssignOp::DivEq, std::move($3));}
    | IDENTIFIER MUL_EQ expr { $$ = std::make_unique<AssignExpr>($1.string_value(), AssignOp::MulEq, std::move($3));}
    ;


unary_op_expr
    : MINUS expr %prec UMINUS { $$ = std::make_unique<UnaryOpExpr>(UnaryOp::Negate, std::move($2));}
    | STAR expr %prec DEREF { $$ = std::make_unique<UnaryOpExpr>(UnaryOp::Deref, std::move($2));}
    | BANG expr %prec NOT { $$ = std::make_unique<UnaryOpExpr>(UnaryOp::Not, std::move($2));}
    | AMPERSAND expr %prec REF { $$ = std::make_unique<UnaryOpExpr>(UnaryOp::Borrow, std::move($2));}
    | AMPERSAND_MUT expr %prec REF_MUT { $$ = std::make_unique<UnaryOpExpr>(UnaryOp::MutBorrow, std::move($2));}
    ;

bin_op_expr
    : expr PLUS expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::Plus, std::move($3)); }
    | expr MINUS expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::Min, std::move($3)); }
    | expr STAR expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::Mul, std::move($3)); }
    | expr SLASH expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::Div, std::move($3)); }
    | expr L_AND expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::L_AND, std::move($3)); }
    | expr L_OR expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::L_OR, std::move($3)); }
    | expr EQEQ expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::Eq, std::move($3)); }
    | expr NE expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::NEq, std::move($3)); }
    | expr LT expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::Lt, std::move($3)); }
    | expr GT expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::Gt, std::move($3)); }
    | expr GE expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::GtEq, std::move($3)); }
    | expr LE expr { $$ =std::make_unique<BinOpExpr>(std::move($1), BinOp::LtEq, std::move($3)); }
    ;


call_expr_args
    : call_expr_args COMMA expr {$1.push_back(std::move($3)); $$ = std::move($1); }
    | expr { 
        auto vec = std::vector<Unique<Expr>>();
        vec.push_back(std::move($1));
        $$ = std::move(vec);
        }
    ;

call_expr
    : IDENTIFIER LPAREN call_expr_args RPAREN { $$ = std::make_unique<CallExpr>($1.string_value(), std::move($3)); }
    | IDENTIFIER LPAREN RPAREN { $$ = std::make_unique<CallExpr>($1.string_value(), std::vector<Unique<Expr>>{}); }

while_expr
    : WHILE expr block_expr {$$ = std::make_unique<WhileLoop>(std::move($2), std::move($3)); }
    ;

expr
    : assignment { $$ = std::move($1); }
    | bin_op_expr { $$ = std::move($1); }
    | block_expr { $$ = std::move($1); }
    | if_expr { $$ = std::move($1); }
    | DEC_LITERAL { $$ = std::make_unique<DecLiteral>($1.size_t_value()); }
    | TRUE { $$ = std::make_unique<BoolLit>($1.bool_value()); }
    | FALSE { $$ = std::make_unique<BoolLit>($1.bool_value()); }
    | IDENTIFIER { $$ = std::make_unique<Identifier>($1.string_value()); }
    | unary_op_expr  {$$ = std::move($1); }
    | LPAREN expr RPAREN { $$ = std::move($2); }
    | LPAREN RPAREN { $$ = std::make_unique<Unit>(); }
    | call_expr { $$ = std::move($1); }
    | while_expr { $$ = std::move($1); }
    ;

%%

namespace mr
{
    
    void Parser::error(const Parser::location_type &loc, const std::string &message)
    {
        std::cerr << "Error in " << this->input_file_name << ":" << loc.end.line << ":" << loc.end.column
            <<":\n"
            << message << std::endl;
    }
}