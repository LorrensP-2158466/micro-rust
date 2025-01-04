// #pragma once

// #include "location.hh"
// #include "mr_util.hpp"
// #include "span.hpp"
// #include "token.hpp"

// namespace mr {
//     namespace parser {
//         struct BisonError : public error::Error {
//             std::string message;
//             location    loc;

//             error::Diagnostic create_diag() const override {
//                 TODO("CREATE DIAGNOSTIC FOR: UnCaughtBisonError");
//             };
//         };

//         struct Expected : public error::Error {
//             location    loc;
//             std::string expected;
//             std::string actual;

//             static inline Expected unexpected_token(Token tok, std::string expected) {}

//             error::Diagnostic create_diag() const override {
//                 TODO("CREATE DIAGNOSTIC FOR: Expected");
//             };
//         };

//     } // namespace parser

// } // namespace mr
