cmake_minimum_required(VERSION 3.16)

include(cmake/ExternalAntlr4Cpp.cmake)    
set(ANTLR4CPP_JAR_LOCATION /usr/local/lib/antlr-4.9.2-complete.jar)
message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4_INCLUDE_DIRS} ")
message(STATUS "Antlr root: ${ANTLR4_ROOT}")

project(analyzer CXX)


link_directories( ${ANTLR4_STATIC_LIBRARIES} ${ANTLR4_RUNTIME_LIBRARIES} )
include_directories(src/
    src/antlr4-runtime
    ${ANTLR4_INCLUDE_DIRS})
add_executable(analyzer src/main  src/antlr4-runtime/scBaseVisitor src/antlr4-runtime/scLexer src/antlr4-runtime/scVisitor)
add_dependencies(analyzer antlr4_static)
target_link_libraries(analyzer antlr4_static)