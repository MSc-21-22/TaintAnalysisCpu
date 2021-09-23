cmake_minimum_required(VERSION 3.16)

project(analyzer CXX)

include_directories(src/)
add_executable(analyzer src/main.cpp src/antlr4-runtime/scBaseVisitor.cpp src/antlr4-runtime/scLexer.cpp src/antlr4-runtime/scVisitor.cpp src/worklist.cpp)