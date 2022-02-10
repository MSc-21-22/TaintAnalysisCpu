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
#include <io.h>
#include <fcntl.h>

void print_result(std::set<std::string>& result, std::ostream& stream){
    stream << "\\n{ ";
    for (auto& x : result){
        if (x!="£"){
            stream << x << " ";
        }
    }
    stream << "}";
}

void cpu_analysis(ScTransformer<std::set<std::string>> program){
    TaintAnalyzer analyzer;

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

int main(int argc, char *argv[]){
    if(argc > 1){

        bool gpu_flag = false, multi_taint_flag = false, cpu_flag = false, benchmark_all = false;
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
            std::cout << " with gpu flag:\n";
            std::cout << "  --cubool -c to use cubool gpu library\n";
            std::cout << " --benchmark -b to enable benchmarking where possible\n";
        }

    }
    return 0;
}