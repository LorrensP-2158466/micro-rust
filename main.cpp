#include "ast/module.hpp"
#include "expr/module.hpp"
#include "lexer/lexer.hpp"
#include "mr_util.hpp"
#include "parser/parser.tab.hpp"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

mr::Unique<Ast> root;

int main(int argc, char** argv) {

    if (argc < 1) {
        // If a file is provided as an argument, open it
        exit(1);
    }

    std::ifstream input_file(argv[1], std::ios::in);
    const bool    debug = argc > 1 && std::strcmp(argv[1], "--debug") == 0;
    mr::Lexer     lexer(input_file, debug);
    mr::Parser    parser(lexer, debug, argv[1]);

    // i really don't care if parsing failed
    // i'm still checking the ast.
    parser.parse();

    // Access the AST root
    const auto ast = std::move(root); // i don't like globals
    if (ast) {
        // root->print();
        for (const auto& item : ast->items_slice()) {
            if (auto fun_decl = dynamic_cast<FunDecl*>(item.get())) {
                std::cout << "fun_delc: " << fun_decl->name() << std::endl;
            }
        }
    } else {
        std::cerr << "No AST was generated.\n";
    }
}
