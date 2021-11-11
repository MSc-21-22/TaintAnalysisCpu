cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if(NOT DEFINED ANTLR_EXECUTABLE)
    message(FATAL_ERROR "You must define ANTLR_EXECUTABLE using the flag -D ANTLR_EXECUTABLE=...")
endif()

if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
    message(FATAL_ERROR "You must define CMAKE_CUDA_ARCHITECTURES using the flag -D CMAKE_CUDA_ARCHITECTURES={compute computablity version i.e 61} Go to https://developer.nvidia.com/cuda-gpus and find your graphics card computability version (dont forget to remove the . between the numbers)")
endif()


set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra")
set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_definitions(-DANTLR4CPP_STATIC)
set(ANTLR4_WITH_STATIC_CRT OFF)
include(cmake/ExternalAntlr4Cpp.cmake)   

project(analyzer CXX CUDA)

find_package(ANTLR REQUIRED)

if(NOT DEFINED CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES)
    message(FATAL_ERROR "The cuda toolkit was not found?!")
endif()

set( CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS}" "-lcublas" )

include_directories(src/
    src/antlr4-runtime
    ${ANTLR4_INCLUDE_DIRS}
    ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
    tests/)
#link_directories(/opt/nvidia/hpc_sdk/Linux_x86_64/21.9/math_libs/11.4/targets/x86_64-linux/lib/)

add_library(analyze_lib src/antlr4-runtime/scBaseVisitor.cpp src/antlr4-runtime/scLexer.cpp src/antlr4-runtime/scParser.cpp src/antlr4-runtime/scVisitor.cpp 
                src/taint_analysis.cpp src/matrix_analysis.cu src/kernel.cu src/GpuManagement.cu src/digraph.cpp src/multi_taint_analysis.cpp src/timing.cpp)
target_link_libraries(analyze_lib cublas)

add_executable(analyzer src/main.cpp)
add_dependencies(analyzer antlr4_static)
add_dependencies(analyze_lib antlr4_static)
target_link_libraries(analyzer antlr4_static analyze_lib)
#target_compile_features(particles PUBLIC cxx_std_14)

add_executable(test tests/test_transforms_matrix.cpp)
target_link_libraries(test analyze_lib)