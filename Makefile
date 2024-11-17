CXX = clang++
CXXFLAGS = -std=c++20 -g

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

# MIDDLE 
MIDDLE_DIR = ./middle
MIDDLE_HEADERS = $(wildcard $(MIDDLE_DIR)/*.hpp)

# MIDDLE -> IR
IR_DIR = MIDDLE_DIR/ir
IR_HEADERS = $(wildcard $(IR_DIR)/*.hpp)

# MIDDLE -> BUILD -> 
MIDDLE_BUILD = $(MIDDLE_DIR)/expr/
MIDDLE_BUILD_HEADERS = $(wildcard $(MIDDLE_BUILD)/*.hpp)

# MIDDLE -> TAST
TAST_DIR = $(MIDDLE_DIR)/tast
TAST_HEADERS = $(wildcard $(TAST_DIR)/*.hpp)




# MIDDLE -> TAST -> EXPR
TAST_EXPR_DIR = $(TAST_DIR)/expr/
TAST_EXPR_HEADERS = $(wildcard $(TAST_EXPR_DIR)/*.hpp)
# MIDDLE -> TAST -> STMT
TAST_STMT_DIR = $(TAST_DIR)/tast/
TAST_STMT_HEADERS = $(wildcard $(TAST_STMT_DIR)/*.hpp)

INCLUDE_DIR = ./include
INCLUDE_HEADERS = $(wildcard $(INCLUDE_DIR)/*.hpp)


COMPILER_DEPS = Makefile \
	$(MAIN_SOURCE) \
	$(LEXER_OUTPUT)  \
	$(PARSER_OUTPUT)  \
	$(EXPR_HEADERS) \
	$(AST_HEADERS) \
	$(MIDDLE_HEADERS) \
	$(TAST_HEADERS) \
	$(TAST_EXPR_HEADERS) \
	$(TAST_STMT_HEADERS) \
	$(MIDDLE_BUILD_HEADERS) \
	$(INCLUDE_HEADERS)


.PHONY: all clean

all: $(MAIN_OUTPUT)

$(MAIN_OUTPUT): $(COMPILER_DEPS)
	$(CXX) $(CXXFLAGS) $(MAIN_SOURCE) $(LEXER_OUTPUT) $(PARSER_OUTPUT) -o $(MAIN_OUTPUT) -I $(INCLUDE_PATHS)

$(LEXER_OUTPUT): $(LEXER_SOURCE)
	flex -o $(LEXER_OUTPUT) $(LEXER_SOURCE) 

$(PARSER_OUTPUT): $(PARSER_SOURCE) $(AST_DIR)/ast.hpp
	bison -d -o $(PARSER_OUTPUT) $(PARSER_SOURCE)

clean:
	rm -f $(LEXER_OUTPUT) $(PARSER_OUTPUT) $(PARSER_HEADER) $(MAIN_OUTPUT)
