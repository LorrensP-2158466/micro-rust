#include "ast/module.hpp"
#include "expr/module.hpp"
#include "lexer/lexer.hpp"
#include "middle/module.hpp"
#include "mr_util.hpp"
#include "parser/parser.tab.hpp"
#include "spdlog/spdlog.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace mr;

Unique<Ast> root;

int main(int argc, char** argv) {

    if (argc < 1) {
        // If a file is provided as an argument, open it
        exit(1);
    }

    std::ifstream input_file(argv[1], std::ios::in);
    Lexer         lexer(input_file, false);
    Parser        parser(lexer, false, argv[1]);
    spdlog::info("Starting Compiler");
    // i really don't care if parsing failed
    // i'm still checking the ast.
    parser.parse();

    // Access the AST root
    auto ast = std::move(root); // i don't like globals
    if (!ast) {
        std::cerr << "No AST was generated.\n";
        return 1;
    }
    ast->print();
    auto lowerer = middle::AstLowerer();
    lowerer.lower(std::move(ast));

    auto inf = mr::middle::inference::TyInferer();
}
