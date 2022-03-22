#include <iostream>
#include <string>
#include "antlr4-runtime/scLexer.h"
#include "antlr4-runtime/scParser.h"
#include <cfg/sc_transformer.h>
#include "worklist.h"
#include "taint_analysis.h"
#include "multi_taint_analysis.h"
#include <cfg/digraph.h>
#include <cfg/transformations/taint_locator.h>
#include "matrix_analysis.h"
#include "GpuManagement.h"
#include "cfg/transformations/variable_reduction.h"
#include <chrono>
#include "timing.h"
#include <stdio.h>
#include <fcntl.h>
#include <cstring>
#include "cuda/bit_vector_converter.h"
#include "cuda/cuda_transformer.h"
#include <cuda/common.h>

void print_result(std::set<std::string>& result, std::ostream& stream){
    stream << "\\n{ ";
    for (auto& x : result){
        stream << x << " ";
    }
    stream << "}";
}

std::vector<StatefulNode<std::set<std::string>>> cpu_analysis(ScTransformer program){
    TaintAnalyzer analyzer;

    std::vector<StatefulNode<std::set<std::string>>> nodes = create_states<std::set<std::string>>(program.nodes, {TAINT_VAR});
    time_func("Analyzing: ", 
        worklist<std::set<std::string>>, nodes, analyzer);

    if(!timing::should_benchmark) {
        print_digraph_subgraph(nodes, std::cout, print_result, "main");
    }
    return nodes;
}

void cpu_multi_taint_analysis(ScTransformer& program){
    MultiTaintAnalyzer analyzer;
    std::vector<StatefulNode<SourcedTaintState>> nodes = create_states<SourcedTaintState>(program.nodes);
    worklist<SourcedTaintState>(nodes, analyzer);

    if(!timing::should_benchmark) {
        print_digraph_subgraph(nodes, std::cout, print_taint_source, "main");
    }
}

std::vector<StatefulNode<std::set<std::string>>> bit_cuda_analysis(ScTransformer& program){
    init_gpu();
    time_func("Variable reduction: ", 
                reduce_variables, program.entryNodes);
    auto transformer = time_func<CudaTransformer<bit_cuda::Node>>("Gpu structure transformation: ", 
                transform_bit_cuda, program.nodes);
        
    time_func("Least fixed point algorithm: ",
            bit_cuda::execute_analysis, &transformer.nodes[0], transformer.nodes.size(), &*transformer.transfer_functions.begin(), transformer.transfer_functions.size());

    std::vector<StatefulNode<std::set<std::string>>> nodes = create_states<std::set<std::string>>(program.nodes);
    time_func("Save into nodes", 
                set_bit_cuda_state<bit_cuda::Node>, transformer.nodes, transformer.variables, nodes);

    if(!timing::should_benchmark)
        print_digraph_subgraph(nodes, std::cout, print_result, "main");

    return nodes;
}

std::vector<StatefulNode<std::set<std::string>>> bit_cuda_worklist_analysis(ScTransformer& program){
    init_gpu();
    time_func("Variable reduction: ", 
                reduce_variables, program.entryNodes);
    auto transformer = time_func<CudaTransformer<cuda_worklist::Node>>("Gpu structure transformation: ", 
                transform_cuda_worklist, program.nodes);
    
    time_func("Least fixed point algorithm: ",
            cuda_worklist::execute_analysis, &transformer.nodes[0], transformer.nodes.size(), &*transformer.transfer_functions.begin(), transformer.transfer_functions.size(), transformer.taint_sources);

    std::vector<StatefulNode<std::set<std::string>>> nodes = create_states<std::set<std::string>>(program.nodes);
    time_func("Save into nodes", 
                set_bit_cuda_state<cuda_worklist::Node>, transformer.nodes, transformer.variables, nodes);
    if(!timing::should_benchmark)
        print_digraph_subgraph(nodes, std::cout, print_result, "main");

    return nodes;
}

std::vector<StatefulNode<SourcedTaintState>> multi_bit_cuda_worklist_analysis(ScTransformer& program){
    init_gpu();
    time_func("Variable reduction: ", 
                reduce_variables, program.entryNodes);
    int source_count = count_taint_sources(program.nodes);
    auto transformer = time_func<CudaTransformer<multi_cuda::Node>>("Gpu structure transformation: ", 
                transform_multi_cuda, program.nodes, source_count);
    
    time_func("Least fixed point algorithm: ",
            multi_cuda::execute_analysis, &transformer.nodes[0], transformer.nodes.size(), &*transformer.transfer_functions.begin(), transformer.transfer_functions.size(), transformer.taint_sources, source_count);

    std::vector<StatefulNode<SourcedTaintState>> nodes = create_states<SourcedTaintState>(program.nodes);
    time_func("Save into nodes", 
                set_bit_cuda_multi_state<multi_cuda::Node>, transformer.nodes, transformer.variables, source_count, nodes);
    if(!timing::should_benchmark)
        print_digraph_subgraph(nodes, std::cout, print_taint_source, "main");

    return nodes;
}

bool state_equality(std::vector<StatefulNode<std::set<std::string>>>& lhs, std::vector<StatefulNode<std::set<std::string>>>& rhs){
    int size = lhs.size();
    if (size != rhs.size())
        return false;

    DigraphPrinter printer(std::cout);

    for(int i = 0; i < size; ++i){
        for(const std::string& item : lhs[i].get_state()){
            if(rhs[i].get_state().count(item) == 0){
                std::cout << "Difference on node " << i << "    "; 
                lhs[i].accept(printer);
                print_result(lhs[i].get_state(), std::cout);
                std::cout << "    !=    ";
                rhs[i].accept(printer);
                print_result(rhs[i].get_state(), std::cout);
                std::cout << '\n';
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[]){
    if(argc > 1){

        bool gpu_flag = false, multi_taint_flag = false, cpu_flag = false, benchmark_all = false, cuda_flag = false, cuda_worklist_flag = false, multi_source_cuda = false;
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

            if(strcmp(arg, "--multi-cuda") == 0 || strcmp(arg, "-mc") == 0){
                multi_source_cuda = true;
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
        const std::string& file_name = argv[argc-1];
        csfile.loadFromFile(file_name);
        antlr4::ANTLRInputStream prog(csfile);

        if(benchmark_all){

            Stopwatch::add_header(file_name);

            std::cout << "\n⭐ CPU analysis ⭐" << std::endl;
            auto program = parse_to_cfg_transformer(prog);
            reduce_variables(program.entryNodes);
            Stopwatch cpu_watch;
            auto cpu_nodes = cpu_analysis(program);
            cpu_watch.save_time<Microseconds>();

            init_gpu();

            std::cout << "\n⭐ GPU cuBLAS analysis ⭐" << std::endl;
            program = parse_to_cfg_transformer(prog);
            time_func("Cublas creation: ", 
                create_cublas);
            Stopwatch cuBLAS_watch;
            reduce_variables(program.entryNodes);
            auto cublas_nodes = gpu_analysis(program.nodes);
            cuBLAS_watch.save_time<Microseconds>();

            if(!state_equality(cpu_nodes, cublas_nodes)){
                std::cout << "###### cpu != cublas #####" << std::endl;
            }

            std::cout << "\n⭐ bit-cuda analysis ⭐" << std::endl;
            program = parse_to_cfg_transformer(prog);
            Stopwatch bit_cuda_watch;
            auto bit_cuda_nodes = bit_cuda_analysis(program);
            bit_cuda_watch.save_time<Microseconds>();

            if(!state_equality(cublas_nodes, bit_cuda_nodes)){
                std::cout << "###### cublas != bit-cuda #####" << std::endl;
            }

            std::cout << "\n⭐ bit-cuda worklist analysis ⭐" << std::endl;
            program = parse_to_cfg_transformer(prog);
            Stopwatch cuda_worklist_watch;
            auto cuda_worklist_nodes = bit_cuda_worklist_analysis(program);
            cuda_worklist_watch.save_time<Microseconds>();

            if(!state_equality(bit_cuda_nodes, cuda_worklist_nodes)){
                std::cout << "###### bit-cuda != cuda-worklist #####" << std::endl;
            }

            Stopwatch::add_line();
            return 0;
        }

        auto program = time_func<ScTransformer>("Creating CFG nodes: ", 
                parse_to_cfg_transformer, prog);

        if(gpu_flag){
            std::cout << "Running analysis using cuBLAS on GPU" << std::endl;
            time_func("Cublas creation: ", 
                create_cublas);
            time_func("Variable reduction: ", 
                reduce_variables, program.entryNodes);
            auto stateful_nodes = gpu_analysis(program.nodes);
            if(!timing::should_benchmark){
                print_digraph_subgraph(stateful_nodes, std::cout, print_result, "main");
            }
        }else if(cuda_flag){
            std::cout << "Running bit-cuda analysis" << std::endl;
            bit_cuda_analysis(program);
        }else if(cuda_worklist_flag){
            std::cout << "Running bit-cuda analysis using worklists" << std::endl;
            bit_cuda_worklist_analysis(program);
        }else if(multi_source_cuda){
            std::cout << "Running multi-colored bit-cuda analysis using worklists" << std::endl;
            multi_bit_cuda_worklist_analysis(program);
        }else if(cpu_flag){
            if(multi_taint_flag){
                std::cout << "Running multi-taint analysis using CPU" << std::endl;
                cpu_multi_taint_analysis(program);
            }else{
                std::cout << "Running analysis using CPU" << std::endl;
                cpu_analysis(program);
            }
        }else{
            std::cout << "Invalid command\n";
            std::cout << " --cpu -c for use on cpu\n";
            std::cout << " with cpu flag:\n";
            std::cout << " --multi -m for multi taint analysis\n";
            std::cout << " --gpu -g for use on gpu\n";
            std::cout << " --cuda -cu for bit-cuda implementation\n";
            std::cout << " --cuda-worklist -cw for bit-cuda implementation using worklist\n";
            std::cout << " --multi-cuda -mc for multi colored taint analysis using cuda and worklist\n";
            std::cout << " --benchmark -b to enable benchmarking where possible\n";
        }

    }else{
        antlr4::ANTLRFileStream csfile;
        csfile.loadFromFile("./sampleprograms/multiplefunc.sc");
        antlr4::ANTLRInputStream prog(csfile);

        auto program = time_func<ScTransformer>("Creating CFG nodes: ", 
            parse_to_cfg_transformer, prog);

        std::vector<StatefulNode<std::set<std::string>>> result1 = bit_cuda_worklist_analysis(program);
        std::cout << "#######\n";
        std::cout << "#######\n";
        std::cout << "#######\n";
        std::cout << "#######\n";
        std::cout << "#######\n";
        std::cout << "#######\n";
        std::vector<StatefulNode<std::set<std::string>>> result2 = cpu_analysis(program);



        std::cout << "The result1 == result2 = " << state_equality(result1, result2) << "\n";
    }
    return 0;
}