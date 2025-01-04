#pragma once
#include "errors/ctx.hpp"
#include "fstream"
#include "high/ast/module.hpp"
#include "interpreter/interpreter.hpp"
#include "lexer/lexer.hpp"
#include "middle/middle_phase.hpp"
#include "mr_util.hpp"
#include "parser/parser.tab.hpp"
#include <fmt/format.h>

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

          private:
            void show_errors() {
                _input_file.seekg(0);
                std::vector<std::string> source_in_lines;
                std::string              line;
                while (std::getline(_input_file, line)) {
                    source_in_lines.push_back(line);
                }
                _err_ctx.show_errors(file_name, source_in_lines);

                fmt::println(
                    "\nCompilation failed due to `{}` errors", _err_ctx.error_amount()
                );
            }
        };
    } // namespace driver
} // namespace mr
