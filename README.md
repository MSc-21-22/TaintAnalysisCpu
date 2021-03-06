# Dependencies - Linux
First install the required dependencies to compile

    sudo apt-get install pkg-config uuid-dev cmake build-essential

Then download the antlr4 jar file and save it a place you remember.

# Dependencies - Windows
First install the required dependencies to compile

- CMake
- C++ Compiler of your choice (MSVC has been tested)
- Antlr4 jar executable file (v. 4.9.3)


# Cuda
This project depends on Cuda to run code on GPUs, so to compile you need the Cuda Toolkit.
Which is available at https://developer.nvidia.com/cuda-toolkit

After installation it is recommended to set your editor up with the Cuda include files. On windows machines these includes can live in the folder

`C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\{Cuda version}\include`

It is also recommended to the following page to find out what computability version your GPU supports.

`https://developer.nvidia.com/cuda-gpus`

# Compiling

Start by downloading or updating the git submodule dependencies

    git submodule update --init --recursive

Then use cmake to compile the dependencies and the project

    cmake -B build/ -D ANTLR_EXECUTABLE={path to jar file} -D CMAKE_CUDA_ARCHITECTURES={computability version}
    cmake --build build/


# Usage

    analyzer [OPTIONS] path/to/program.sc

## Options
--gpu | -g : run the analysis using the GPU otherwise defaults to running the analysis on the CPU

--cuda | -cu : run using the bit-cuda implementation

--cuda-worklist | -cw : run using the bit-cuda implementation using a worklist

--multi | -m : run multi-coloured taint analysis on CPU

-- multi-cuda | -mc : run multi-colored taint analysis on GPU

--benchmark | -b : output execution time of the different phases of the analysis

--benchmark-all-multi | -bam to compare all multi-colored taint analysis options and output results into timings.csv

When using expandable calls with identifiers set count of identifer id to x with

-d {id} {x}