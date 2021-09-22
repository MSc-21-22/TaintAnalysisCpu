cmake_minimum_required(VERSION 3.16)

project(analyzer CXX)

include_directories(src/)
add_executable(analyzer src/main.cpp)