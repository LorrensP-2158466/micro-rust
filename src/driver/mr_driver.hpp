#pragma once
#include "errors/ctx.hpp"
#include "fstream"
#include "high/ast/module.hpp"
#include "interpreter/interpreter.hpp"
#include "lexer/lexer.hpp"
#include "middle/middle_phase.hpp"
#include "mr_util.hpp"
#include "parser/parser.tab.hpp"

namespace mr {
    namespace driver {
        class MRDriver {
            // file stuff
            const char*         file_name;
            std::ifstream       _input_file;
            U<ast::Ast>         _ast;
            error::ErrorCtx     _err_ctx{};
            middle::MiddlePhase _middle_phase{_err_ctx};

            std::ifstream create_input(int argc, char** argv) {
                if (argc < 1) { exit(1); }
                return std::ifstream(argv[1], std::ios::in);
            }

          public:
            MRDriver(int argc, char** argv)
                : file_name(argv[1]), _input_file(create_input(argc, argv)) {}

            int start();

            void set_ast(U<ast::Ast> ast) { _ast = std::move(ast); }

            error::ErrorCtx& ecx() { return _err_ctx; }
        };
    } // namespace driver
} // namespace mr
