#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser/location.hh"
#include "parser/parser.tab.hpp" // Make sure to include the generated parser header

namespace mr {
    class Lexer : public yyFlexLexer {

        Parser::value_type* yylval = nullptr;

        Parser::location_type* loc = nullptr;

        Parser::location_type prev_token_loc = {
            position{}, position{}
        }; // 1.1, dont know if this will work
        size_t current_byte{};

        void copyValue(
            const std::size_t leftTrim = 0, const std::size_t rightTrim = 0,
            const bool trimCr = false
        );

      public:
        Lexer(std::istream& in, const bool) : yyFlexLexer(&in) {}

        int yylex(Parser::value_type* const lval, Parser::location_type* const lloc);
    };

    inline void Lexer::copyValue(
        const std::size_t leftTrim, const std::size_t rightTrim, const bool trimCr
    ) {
        std::size_t endPos = yyleng - rightTrim;
        if (trimCr && endPos != 0 && yytext[endPos - 1] == '\r') --endPos;
        yylval->build(std::string(yytext + leftTrim, yytext + endPos));
    }

} // namespace mr
