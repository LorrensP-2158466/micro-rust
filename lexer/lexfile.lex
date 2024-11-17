%{

/* 
lex file for micro-rust
*/
#include "lexer.hpp"
#include "token.hpp"
#include "span.hpp"
#include "../parser/parser.tab.hpp"
#include <string.h>

using namespace mr;

#undef  YY_DECL
#define YY_DECL int Lexer::yylex(Parser::semantic_type *yylval, Parser::location_type *yylloc)

// Define YY_USER_ACTION for updating location
#define YY_USER_ACTION {\
  yylloc->columns(yyleng); \
  yylval->build(Token{{yytext}, Span{this->prev_token_loc.end, yylloc->end}, (size_t) yyleng});\
  this->prev_token_loc = *yylloc;\
  }


%}
%option c++ noyywrap
%option yyclass="mr::Lexer"
%option nodefault

%x comment

DIGIT       [0-9]
LETTER      [a-zA-Z_]
IDENTIFIER  {LETTER}({LETTER}|{DIGIT})*
DEC_LITERAL {DIGIT}+({IDENTIFIER})?
FLOAT_LITERAL {DIGIT}+\.{DIGIT}*{IDENTIFIER}
STR_LITERAL   \"[^\"]*\"

%%

%{
  using Token_T = Parser::token;
%}


"i8"                        { return Token_T::I8;}
"i16"                       { return Token_T::I16;}
"i32"                       { return Token_T::I32;}
"i64"                       { return Token_T::I64;}
"isize"                     { return Token_T::ISIZE;}
"u8"                        { return Token_T::U8;}
"u16"                       { return Token_T::U16;}
"u32"                       { return Token_T::U32;}
"u64"                       { return Token_T::U64;}
"usize"                     { return Token_T::USIZE;}
"bool"                      { return Token_T::BOOL; }
"true"                      { return Token_T::TRUE; }
"false"                     { return Token_T::FALSE; }
"let"                       { return Token_T::LET; }
"mut"                       { return Token_T::MUT; }
"if"                        { return Token_T::IF; }
"else"                      { return Token_T::ELSE; }
"while"                     { return Token_T::WHILE; }
"fn"                        { return Token_T::FN; }
"_"                         { return Token_T::UNDERSCORE; }
"println\!"                 { return Token_T::PRINT_LN; }

{DEC_LITERAL}               { return Token_T::DEC_LITERAL; }
{STR_LITERAL}               { return Token_T::STR_LITERAL; }
{IDENTIFIER}                { return Token_T::IDENTIFIER; }

"="                         { return Token_T::EQ; }
"=="                        { return Token_T::EQEQ; }
"!="                        { return Token_T::NE; }
"!"                         { return Token_T::BANG; }
"<"                         { return Token_T::LT; }
"<="                        { return Token_T::LE; }
">"                         { return Token_T::GT; }
">="                        { return Token_T::GE; }
"&&"                        { return Token_T::L_AND; }
"||"                        { return Token_T::L_OR; }
"&"                         { return Token_T::AMPERSAND; }
"&mut"                      { return Token_T::AMPERSAND_MUT; }

"+"                         { return Token_T::PLUS; }
"-"                         { return Token_T::MINUS; }
"*"                         { return Token_T::STAR; }
"/"                         { return Token_T::SLASH; }
"+="                        { return Token_T::PLUS_EQ; }
"-="                        { return Token_T::MIN_EQ; }
"*="                        { return Token_T::MUL_EQ; }
"/="                        { return Token_T::DIV_EQ; }

"{"                         { return Token_T::LBRACE; }
"}"                         { return Token_T::RBRACE; }
"("                         { return Token_T::LPAREN; }
")"                         { return Token_T::RPAREN; }
";"                         { return Token_T::SEMICOLON; }
":"                         { return Token_T::COLON; }
","                         { return Token_T::COMMA; }
"->"                        { return Token_T::ARROW; }

"//".*                      { /* ignore comments */ }
"/*"                        BEGIN(comment);
<comment>[^*\n]             { /* skip */ }
<comment>[^*\n]*\n          { yylloc->lines(1); }
<comment>"*"+[^*/\n]*       { /* skip */ }
<comment>"*"+[^*/\n]*\n     { yylloc->lines(1); }
<comment>"*"+"/"            BEGIN(INITIAL);

\n                          { yylloc->lines(1); yylloc->step();  /* update line and col number but ignore it the actual 'token' */ }
[ \t\r]+                    { /* ignore whitespace */ }



.      {
  if (yytext[0] < ' '){ /* non-printable char */
    /*yyerror*/ fprintf(stderr,"illegal character: ^%c",yytext[0] + '@'); 
  }
  else {
    if (yytext[0] > '~') {
      /* non-printable char printed as octal int padded with zeros, eg \012*/
      /*yyerror(*/fprintf(stderr,"illegal character: \\%03o", (int) yytext[0]);
    }
    else {
      /*yyerror(*/fprintf(stderr,"illegal character: %s",yytext);
    }
  }
  /* lex read exactly one char; the illegal one */
    std::cerr << " at " << *yylloc << std::endl;
	}
%%


