#include <iostream>
#include <string>
#include "antlr4-runtime/scLexer.h"
#include "antlr4-runtime/scParser.h"
#include "transforms.h"
#include "worklist.h"
#include "taint_analysis.h"
#include "multi_taint_analysis.h"
#include "digraph.h"
#include "matrix_analysis.h"
#include "GpuManagement.h"
#include "variable_reduction.h"
#include <chrono>
#include "timing.h"
#include <stdio.h>
#include <fcntl.h>
#include <cstring>
#include "bit_cuda/bit_cuda_transformer.h"
#include "bit_cuda/analysis.h"
#include <bit_cuda/bit_vector_converter.h>
#include "cuda_worklist/cuda_worklist_transformer.h"

void print_result(std::set<std::string>& result, std::ostream& stream){
    stream << "\\n{ ";
    for (auto& x : result){
        if (x!="$"){
            stream << x << " ";
        }
    }
    stream << "}";
}

void cpu_analysis(ScTransformer<std::set<std::string>> program){
    TaintAnalyzer analyzer;

    for(auto& node : program.nodes){
        node->state.insert("$");
    }

    time_func("Analyzing: ", 
        worklist<std::set<std::string>>, program.nodes, analyzer);

    if(!timing::should_benchmark) {
        print_digraph_subgraph(program.entryNodes, std::cout, print_result, "main");
    }
}

void cpu_multi_taint_analysis(ScTransformer<SourcedTaintState> program){
    MultiTaintAnalyzer analyzer;
    worklist(program.nodes, analyzer);

    if(!timing::should_benchmark) {
        print_digraph_subgraph(program.entryNodes, std::cout, print_taint_source, "main");
    }
}

void bit_cuda_analysis(ScTransformer<std::set<std::string>> program){
    time_func("Variable reduction: ", 
                reduce_variables<std::set<std::string>>, program.entryNodes);
    auto transformer = time_func<BitCudaTransformer<std::set<std::string>>>("Gpu structure transformation: ", 
                transform_bit_cuda<std::set<std::string>>, program.nodes);
    
    time_func("Least fixed point algorithm: ",
            bit_cuda::execute_analysis, &transformer.nodes[0], transformer.nodes.size(), &*transformer.transfer_functions.begin(), transformer.transfer_functions.size());

    time_func("Save into nodes", 
                set_bit_cuda_state<bit_cuda::Node>, transformer.nodes, transformer.variables, program.nodes);

    if(!timing::should_benchmark)
        print_digraph_subgraph(program.entryNodes, std::cout, print_result, "main");
}

void bit_cuda_worklist_analysis(ScTransformer<std::set<std::string>> program){
    time_func("Variable reduction: ", 
                reduce_variables<std::set<std::string>>, program.entryNodes);
    auto transformer = time_func<CudaWorklistTransformer<std::set<std::string>>>("Gpu structure transformation: ", 
                transform_cuda_worklist<std::set<std::string>>, program.nodes);
    
    time_func("Least fixed point algorithm: ",
            cuda_worklist::execute_analysis, &transformer.nodes[0], transformer.nodes.size(), &*transformer.transfer_functions.begin(), transformer.transfer_functions.size());

    time_func("Save into nodes", 
                set_bit_cuda_state<cuda_worklist::Node>, transformer.nodes, transformer.variables, program.nodes);

    if(!timing::should_benchmark)
        print_digraph_subgraph(program.entryNodes, std::cout, print_result, "main");
}

int main(int argc, char *argv[]){
    if(argc > 1){

        bool gpu_flag = false, multi_taint_flag = false, cpu_flag = false, benchmark_all = false, cuda_flag = false, cuda_worklist_flag = false;
        for (int i = 1; i < argc; i++)
        {
            char* arg = argv[i];
            if(strcmp(arg, "--benchmark-all") == 0 || strcmp(arg, "-ba") == 0){
                timing::should_benchmark = true;
                benchmark_all = true;
            }

            if(strcmp(arg, "--gpu") == 0 || strcmp(arg, "-g") == 0){
                gpu_flag = true;
            }

            if(strcmp(arg, "--cuda") == 0 || strcmp(arg, "-cu") == 0){
                cuda_flag = true;
            }

            if(strcmp(arg, "--cuda-worklist") == 0 || strcmp(arg, "-cw") == 0){
                cuda_worklist_flag = true;
            }

            if(strcmp(arg, "--benchmark") == 0 || strcmp(arg, "-b") == 0){
                timing::should_benchmark = true;
            }
            if(!gpu_flag){
                if(strcmp(arg, "--cpu") == 0 || strcmp(arg, "-c") == 0){
                    cpu_flag = true;
                    if(strcmp(arg, "--multi") == 0 || strcmp(arg, "-m") == 0){
                        multi_taint_flag = true;
                    }
                }
            }
        }

        antlr4::ANTLRFileStream csfile;
        csfile.loadFromFile(argv[argc-1]);
        antlr4::ANTLRInputStream prog(csfile);

        if(benchmark_all){

            std::cout << "\n⭐ CPU analysis ⭐" << std::endl;
            auto program = parse_to_cfg_transformer<std::set<std::string>>(prog);
            Stopwatch cpu_watch;
            cpu_analysis(program);
            cpu_watch.save_time<Microseconds>();

            std::cout << "\n⭐ GPU cuBLAS analysis ⭐" << std::endl;
            time_func("Cublas creation: ", 
                create_cublas);
            Stopwatch cuBLAS_watch;
            gpu_analysis(program.nodes);
            cuBLAS_watch.save_time<Microseconds>();
            Stopwatch::add_line();
            return 0;
        }

        if(gpu_flag){
            std::cout << "Running analysis using cuBLAS on GPU" << std::endl;
            auto program = parse_to_cfg_transformer<std::set<std::string>>(prog);
            time_func("Cublas creation: ", 
                create_cublas);
            time_func("Variable reduction: ", 
                reduce_variables<std::set<std::string>>, program.entryNodes);
            gpu_analysis(program.nodes);
            if(!timing::should_benchmark){
                print_digraph_subgraph(program.entryNodes, std::cout, print_result, "main");
            }
        }else if(cuda_flag){
            std::cout << "Running bit-cuda analysis" << std::endl;
            auto program = parse_to_cfg_transformer<std::set<std::string>>(prog);
            bit_cuda_analysis(program);
        }else if(cuda_worklist_flag){
            std::cout << "Running bit-cuda analysis using worklists" << std::endl;
            auto program = parse_to_cfg_transformer<std::set<std::string>>(prog);
            bit_cuda_worklist_analysis(program);
        }else if(cpu_flag){
            if(multi_taint_flag){
                std::cout << "Running multi-taint analysis using CPU" << std::endl;
                auto program = parse_to_cfg_transformer<SourcedTaintState>(prog);
                cpu_multi_taint_analysis(program);
            }else{
                std::cout << "Running analysis using CPU" << std::endl;

                auto program = time_func<ScTransformer<std::set<std::string>>>("Creating CFG nodes: ", 
                parse_to_cfg_transformer<std::set<std::string>>, prog);
                cpu_analysis(program);
            }
        }else{
            std::cout << "Invalid command\n";
            std::cout << " --cpu -c for use on cpu\n";
            std::cout << " with cpu flag:\n";
            std::cout << "  --multi -m for multi taint analysis\n";
            std::cout << " --gpu -g for use on gpu\n";
            std::cout << " --cuda -cu for bit-cuda implementation\n";
            std::cout << " --cuda-worklist -cw for bit-cuda implementation using worklist\n";
            std::cout << " --benchmark -b to enable benchmarking where possible\n";
        }

    }
    return 0;
}