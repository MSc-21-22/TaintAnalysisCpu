cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
    message(FATAL_ERROR "You must define CMAKE_CUDA_ARCHITECTURES using the flag -D CMAKE_CUDA_ARCHITECTURES={compute computablity version i.e 61} Go to https://developer.nvidia.com/cuda-gpus and find your graphics card computability version (dont forget to remove the . between the numbers)")
endif()



set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_definitions(-DANTLR4CPP_STATIC)
find_package(ANTLR REQUIRED)
set(ANTLR4_WITH_STATIC_CRT OFF)
include(cmake/ExternalAntlr4Cpp.cmake)   
project(analyzer CXX CUDA)


if(NOT DEFINED CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES)
    message(FATAL_ERROR "The cuda toolkit was not found?!")
endif()

set( CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS}" "-lcublas" )

include_directories(src/
    src/antlr4-runtime
    ${ANTLR4_INCLUDE_DIRS}
    ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
    tests/)

add_library(gpu_lib src/matrix_analysis.cu src/kernel.cu src/GpuManagement.cu src/timing.cpp src/cuda/bit_cuda/analysis.cu src/cuda/cuda_worklist/analysis.cu src/cuda/cuda_common.cu src/cfg/transformations/cfg_transformers.cpp src/cuda/multi_cuda/analysis.cu src/cfg/cfg.cpp)

add_library(analyze_lib src/antlr4-runtime/scBaseVisitor.cpp src/antlr4-runtime/scLexer.cpp src/antlr4-runtime/scParser.cpp src/antlr4-runtime/scVisitor.cpp 
                src/taint_analysis.cpp src/cfg/digraph.cpp src/multi_taint_analysis.cpp src/timing.cpp src/cfg/sc_transformer.cpp src/cfg/transformations/taint_locator.cpp src/cuda/cuda_transformer.cpp)
add_dependencies(analyze_lib antlr4_static)
target_link_libraries(analyze_lib cublas antlr4_static)

add_executable(analyzer src/main.cpp)
add_dependencies(analyzer antlr4_static analyze_lib gpu_lib)
target_link_libraries(analyzer antlr4_static analyze_lib gpu_lib)

add_executable(test-gpu tests/test_gpu.cpp)
add_dependencies(test-gpu analyze_lib gpu_lib)
target_link_libraries(test-gpu analyze_lib gpu_lib)

add_executable(test-cpu tests/test_cpu.cpp)
add_dependencies(test-cpu analyze_lib gpu_lib)
target_link_libraries(test-cpu analyze_lib gpu_lib)