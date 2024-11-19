cmake_minimum_required(VERSION 3.20)
project(YourCompilerProject CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(
    /opt/homebrew/include/
    /opt/homebrew/opt/flex/include
    ./include
    ${CMAKE_CURRENT_SOURCE_DIR}/lexer
    ${CMAKE_CURRENT_SOURCE_DIR}/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/ast
    ${CMAKE_CURRENT_SOURCE_DIR}/expr
    ${CMAKE_CURRENT_SOURCE_DIR}/middle
    ${CMAKE_CURRENT_SOURCE_DIR}/middle/ir
    ${CMAKE_CURRENT_SOURCE_DIR}/middle/build
    ${CMAKE_CURRENT_SOURCE_DIR}/middle/tast
    ${CMAKE_CURRENT_SOURCE_DIR}/middle/tast/expr
    ${CMAKE_CURRENT_SOURCE_DIR}/middle/tast/tast
)

# Find required packages
find_package(spdlog REQUIRED)

# Flex (Lexer) generation
find_package(FLEX REQUIRED)
FLEX_TARGET(Lexer 
    ${CMAKE_CURRENT_SOURCE_DIR}/lexer/lexfile.lex 
    ${CMAKE_CURRENT_SOURCE_DIR}/lexer/lexer.yy.cpp
)

# Bison (Parser) generation
find_package(BISON REQUIRED)
BISON_TARGET(Parser 
    ${CMAKE_CURRENT_SOURCE_DIR}/parser/yaccfile.yy 
    ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.tab.cpp 
    DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.tab.hpp
)

# Add executable
add_executable(main 
    main.cpp
    ${FLEX_Lexer_OUTPUTS}
    ${BISON_Parser_OUTPUTS}
)

# Link libraries
target_link_libraries(main 
    spdlog::spdlog
)

# Compiler flags
target_compile_options(main PRIVATE 
    -g 
    -ferror-limit=40
)

# Clean target (optional, as CMake handles this differently)
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove 
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer/lexer.yy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.tab.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.tab.hpp
        ${CMAKE_CURRENT_BINARY_DIR}/main
    COMMENT "Cleaning generated files"
)