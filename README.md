# Dependencies - Linux
First install the required dependencies to compile

    sudo apt-get install pkg-config uuid-dev cmake build-essential

Then download the antlr4 jar file and save it a place you remember.

# Dependencies - Windows
First install the required dependencies to compile

- CMake
- C++ Compiler of your choice (MSVC has been tested)
- Antlr4 jar executable file

# Compiling

The use cmake to compile antlr and the project

    cmake -B build/ -D ANTLR_EXECUTABLE={path to jar file}
    cmake --build build/
