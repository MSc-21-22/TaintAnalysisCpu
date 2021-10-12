cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if(NOT DEFINED ANTLR_EXECUTABLE)
    message(FATAL_ERROR "You must define ANTLR_EXECUTABLE using the flag -D ANTLR_EXECUTABLE=...")
endif()

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_definitions(-DANTLR4CPP_STATIC)
set(ANTLR4_WITH_STATIC_CRT OFF)
include(cmake/ExternalAntlr4Cpp.cmake)    

set(CMAKE_CXX_STANDARD 17)
project(analyzer CXX)

find_package(ANTLR REQUIRED)

include_directories(src/
src/antlr4-runtime
${ANTLR4_INCLUDE_DIRS})
add_executable(analyzer src/main.cpp  src/antlr4-runtime/scBaseVisitor.cpp src/antlr4-runtime/scLexer.cpp src/antlr4-runtime/scParser.cpp src/antlr4-runtime/scVisitor.cpp src/transferfunction.cpp)
add_dependencies(analyzer antlr4_static)
target_link_libraries(analyzer antlr4_static)