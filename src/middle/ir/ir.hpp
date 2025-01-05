#pragma once

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

#include <span>
#include <unordered_map>
#include <vector>

#include "function.hpp"
#include "mr_util.hpp"
#include "types/type.hpp"

namespace mr {
    namespace middle {
        namespace ir {
            class Ir {
                struct FunctionId {
                    size_t id;
                    auto operator<=>(const FunctionId&) const = default;
                };
                std::unordered_map<std::string, Function> _functions;

               public:
                auto& functions() { return _functions; }
                const auto& functions() const { return _functions; }

                void register_function(std::string name, Function fn) {
                    _functions.emplace(std::move(name), std::move(fn));
                }

                void register_functions(std::vector<std::pair<std::string, Function>> fns) {
                    _functions.reserve(_functions.size() + fns.size());
                    for (auto& [name, fn] : fns) {
                        register_function(std::move(name), std::move(fn));
                    }
                }

                bool has_main() const noexcept { return _functions.contains("main"); }

                Function& get_function_by_name(const std::string& name) { return _functions.at(name); }

                void dump() {
                    for (const auto& [fn_name, ir_fn] : _functions) {
                        const auto args =
                            std::span(ir_fn.locals.cbegin() + 1, ir_fn.locals.cbegin() + 1 + ir_fn.arg_count);
                        fmt::println("function {}({}) -> {} {{", fn_name, fmt::join(args, ", "), ir_fn.locals[0].ty);
                        size_t i = 0;
                        for (const auto& local : ir_fn.locals) {
                            fmt::println("  let {} _{}: {} => {}", local.mutablity, i++, local.ty, local.id);
                        }
                        fmt::println("");
                        i = 0;
                        for (auto& bb : ir_fn._blocks) {
                            fmt::println("  bb{}: {{", i++);
                            for (const auto& stmt : bb.statements) {
                                std::cout << "\t" << stmt;
                            }
                            fmt::println("\t{}", bb.terminator());
                            fmt::println("  }}\n");
                        }
                        fmt::println("}}\n");
                    }
                }
            };
        }  // namespace ir

    }  // namespace middle

}  // namespace mr
