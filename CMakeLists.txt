cmake_minimum_required(VERSION 3.20)
project(MicroRust CXX)
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(
    /opt/homebrew/include/
    /opt/homebrew/opt/flex/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lexer
    ${CMAKE_SOURCE_DIR}/parser
    ${CMAKE_SOURCE_DIR}/ast
    ${CMAKE_SOURCE_DIR}/expr
    ${CMAKE_SOURCE_DIR}/middle
    ${CMAKE_SOURCE_DIR}/middle/ir
    ${CMAKE_SOURCE_DIR}/middle/build
    ${CMAKE_SOURCE_DIR}/middle/tast
)

# Find required packages
find_package(spdlog REQUIRED)

# Flex (Lexer) generation
find_package(FLEX REQUIRED)
FLEX_TARGET(Lexer 
    ${CMAKE_SOURCE_DIR}/lexer/lexfile.lex 
    ${CMAKE_SOURCE_DIR}/lexer/lexer.yy.cpp
)

# Bison (Parser) generation
find_package(BISON REQUIRED)
BISON_TARGET(Parser 
    ${CMAKE_SOURCE_DIR}/parser/yaccfile.yy 
    ${CMAKE_SOURCE_DIR}/parser/parser.tab.cpp 
    DEFINES_FILE ${CMAKE_SOURCE_DIR}/parser/parser.tab.hpp
)

# Add executable
add_executable(mr 
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${FLEX_Lexer_OUTPUTS}
    ${BISON_Parser_OUTPUTS}
)

# Link libraries
target_link_libraries(mr 
    spdlog::spdlog
)

# Compiler flags
target_compile_options(mr PRIVATE 
    -g 
    -ferror-limit=40
)

# Clean target (optional, as CMake handles this differently)
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove 
        ${CMAKE_SOURCE_DIR}/lexer/lexer.yy.cpp
        ${CMAKE_SOURCE_DIR}/parser/parser.tab.cpp
        ${CMAKE_SOURCE_DIR}/parser/parser.tab.hpp
        ${CMAKE_SOURCE_DIR}/main
    COMMENT "Cleaning generated files"
)