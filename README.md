# Dependencies - Linux
First install the required dependencies to compile

    sudo apt-get install pkg-config uuid-dev cmake build-essential

Then download the antlr4 jar file and save it a place you remember.

# Dependencies - Windows
First install the required dependencies to compile

- CMake
- C++ Compiler of your choice (MSVC has been tested)
- Antlr4 jar executable file


# Cuda
This project depends on Cuda to run code on GPUs, so to compile you need the Cuda Toolkit.
Which is available at https://developer.nvidia.com/cuda-toolkit

After installation it is recommended to set your editor up with the Cuda include files. On windows machines these includes can live in the folder

`C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\{Cuda version}\include`

It is also recommended to the following page to find out what computability version your GPU supports.

`https://developer.nvidia.com/cuda-gpus`

# Compiling

The use cmake to compile antlr and the project

    cmake -B build/ -D ANTLR_EXECUTABLE={path to jar file} -D CMAKE_CUDA_ARCHITECTURES={computability version}
    cmake --build build/


# Usage

    analyser [--gpu | -g] path/to/program.sc

--gpu | -g : run the analysis using the GPU otherwise defaults to running the analysis on the CPU

