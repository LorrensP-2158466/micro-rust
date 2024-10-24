CXX = clang++
CXXFLAGS = -std=c++17 -g

MAIN_SOURCE = main.cpp
MAIN_OUTPUT = main
INCLUDE_PATHS = /opt/homebrew/opt/flex/include -I ./include

LEXER_DIR = lexer
LEXER_HEADERS = $(wildcard $(LEXER_DIR)/*.hpp)
LEXER_SOURCE = $(LEXER_DIR)/lexfile.lex
LEXER_OUTPUT = $(LEXER_DIR)/lexer.yy.cpp

PARSER_DIR = parser
PARSER_SOURCE = $(PARSER_DIR)/yaccfile.yy
PARSER_OUTPUT = $(PARSER_DIR)/parser.tab.cpp
PARSER_HEADER = $(PARSER_DIR)/parser.tab.hpp

AST_DIR = ./ast
AST_HEADERS = $(wildcard $(AST_DIR)/*.hpp)

EXPR_DIR = ./expr
EXPR_HEADERS = $(wildcard $(EXPR_DIR)/*.hpp)
.PHONY: all clean

all: $(MAIN_OUTPUT)

$(MAIN_OUTPUT): Makefile $(MAIN_SOURCE) $(LEXER_OUTPUT) $(PARSER_OUTPUT) $(EXPR_HEADERS) $(AST_HEADERS)
	$(CXX) $(CXXFLAGS) $(MAIN_SOURCE) $(LEXER_OUTPUT) $(PARSER_OUTPUT) -o $(MAIN_OUTPUT) -I $(INCLUDE_PATHS)

$(LEXER_OUTPUT): $(LEXER_SOURCE)
	flex -o $(LEXER_OUTPUT) $(LEXER_SOURCE) 

$(PARSER_OUTPUT): $(PARSER_SOURCE) $(AST_DIR)/ast.hpp
	bison -d -o $(PARSER_OUTPUT) $(PARSER_SOURCE)

clean:
	rm -f $(LEXER_OUTPUT) $(PARSER_OUTPUT) $(PARSER_HEADER) $(MAIN_OUTPUT)
