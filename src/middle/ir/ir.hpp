#pragma once

#include "../type.hpp"
#include "function.hpp"
#include "mr_util.hpp"
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <span>
#include <spdlog/spdlog.h>
#include <unordered_map>
#include <vector>

namespace mr {
    namespace middle {
        namespace ir {
            class Ir {
                struct FunctionId {
                    size_t id;
                    auto   operator<=>(const FunctionId&) const = default;
                };
                std::unordered_map<std::string, Function> _functions;

              public:
                void register_function(std::string name, Function fn) {
                    _functions.emplace(std::move(name), std::move(fn));
                }

                void dump() {
                    for (const auto& [fn_name, ir_fn] : _functions) {
                        const auto args = std::span(
                            ir_fn.locals.cbegin() + 1,
                            ir_fn.locals.cbegin() + 1 + ir_fn.arg_count
                        );
                        fmt::println(
                            "function {}({}) -> {} {{",
                            fn_name,
                            fmt::join(args, ", "),
                            ir_fn.locals[0].ty
                        );
                        size_t i = 0;
                        for (const auto& local : ir_fn.locals) {
                            fmt::println(
                                "  let {} _{}: {} => {}",
                                local.mutablity,
                                i++,
                                local.ty,
                                local.id
                            );
                        }
                        fmt::println("");
                        i = 0;
                        for (auto& bb : ir_fn._blocks) {
                            fmt::println("  bb{}: {{", i++);
                            for (const auto& stmt : bb.statements) {
                                std::cout << "\t";
                                stmt.print();
                            }
                            if (!bb.terminator) {
                                spdlog::critical("Terminator Doesnt Exist");
                                std::runtime_error("");
                            }
                            fmt::println("\t{}", *bb.terminator);
                            fmt::println("  }}\n");
                        }
                        fmt::println("}}\n");
                    }
                }
            };
        } // namespace ir

    } // namespace middle

} // namespace mr
