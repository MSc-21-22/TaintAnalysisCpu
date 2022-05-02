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
#include <cfg/transformations/analysis_converter.h>

void print_result(std::set<std::string>& result, std::ostream& stream){
    stream << "\\n{ ";
    for (auto& x : result){
        stream << x << " ";
    }
    stream << "}";
}

void print_cpu_result(cpu_analysis::BitVector& result, std::ostream& stream){
    stream << "\\n{ ";
    stream << result.bitfield;
    stream << "}";
}

std::vector<StatefulNode<std::set<std::string>>> run_cpu_analysis(ScTransformer program){
    reduce_variables(program.entryNodes);
    TransferCreator analyis_info = get_analysis_information(program.nodes);
    std::vector<StatefulNode<cpu_analysis::BitVector>> nodes = create_states<cpu_analysis::BitVector>(program.nodes, cpu_analysis::BitVector(1));
    time_func("Analyzing: ", 
        cpu_analysis::worklist, nodes, analyis_info.node_to_index, analyis_info.transfers);

    std::vector<StatefulNode<std::set<std::string>>> comparable_nodes = create_states<std::set<std::string>>(program.nodes, {TAINT_VAR});
    set_bit_vector_state(nodes, comparable_nodes);

    if(!timing::should_benchmark) {
        print_digraph_with_result(comparable_nodes, std::cout, print_result);
    }
    return comparable_nodes;
}

std::vector<StatefulNode<std::vector<cpu_analysis::BitVector>>> cpu_multi_taint_analysis(ScTransformer& program){
    reduce_variables(program.entryNodes);
    TransferCreator analyis_info = get_analysis_information(program.nodes);
    std::vector<StatefulNode<std::vector<cpu_analysis::BitVector>>> nodes = create_states<std::vector<cpu_analysis::BitVector>>(program.nodes);
    
    //Count sources
    int source_count = 0;
    TaintSourceLocator locator;
    for(auto& node : nodes){
        if(locator.is_taintsource(*node.node)){
            ++source_count;
        }
    }

    time_func("Analyzing: ",
        cpu_multi::worklist, nodes, analyis_info.node_to_index, analyis_info.transfers, source_count);

    if(!timing::should_benchmark) {
        std::vector<StatefulNode<SourcedTaintState>> printable_nodes = create_states<SourcedTaintState>(program.nodes);
        set_multi_bit_vector_state(nodes, printable_nodes);
        print_digraph_subgraph(printable_nodes, std::cout, print_taint_source, "main");
    }
    return nodes;
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
                set_bit_cuda_state<bit_cuda::Node>, transformer.nodes, nodes);

    if(!timing::should_benchmark)
        print_digraph_with_result(nodes, std::cout, print_result);

    return nodes;
}

std::vector<StatefulNode<std::set<std::string>>> bit_cuda_worklist_analysis(ScTransformer& program){
    init_gpu();
    time_func("Variable reduction: ",
        reduce_variables, program.entryNodes);
    auto transformer = time_func<CudaTransformer<cuda_worklist::Node>>("Gpu structure transformation: ", 
                transform_cuda_worklist, program.nodes);
    time_func("Least fixed point algorithm: ",
            cuda_worklist::execute_analysis, transformer.nodes, transformer.transfer_functions, transformer.taint_sources);

    std::vector<StatefulNode<std::set<std::string>>> nodes = create_states<std::set<std::string>>(program.nodes);
    time_func("Save into nodes", 
            set_bit_cuda_state<cuda_worklist::Node>, transformer.nodes, nodes);
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
            multi_cuda::execute_analysis, transformer.nodes, transformer.transfer_functions, transformer.taint_sources, source_count);

    std::vector<StatefulNode<SourcedTaintState>> nodes = create_states<SourcedTaintState>(program.nodes);
    time_func("Save into nodes", 
                set_bit_cuda_multi_state, transformer.nodes, source_count, nodes);
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

bool state_multi_equality(std::vector<StatefulNode<SourcedTaintState>>& lhs, std::vector<StatefulNode<SourcedTaintState>>& rhs){
    int size = lhs.size();
    if (size != rhs.size())
        return false;

    DigraphPrinter printer(std::cout);

    for(int i = 0; i < size; ++i){
        for(auto &[var_name, sources_set1] : lhs[i].get_state()){
            auto& sources_set2 = rhs[i].get_state()[var_name];
            if(sources_set1 != sources_set2){
                std::cout << "Difference on node " << i << "    "; 
                lhs[i].accept(printer);
                print_taint_source(lhs[i].get_state(), std::cout);
                std::cout << "    !=    ";
                rhs[i].accept(printer);
                print_taint_source(rhs[i].get_state(), std::cout);
                std::cout << '\n';
                return false;
            }
        }
    }
    return true;
}

void benchmark_all_multi_taint(antlr4::ANTLRInputStream& prog, std::string file_name, std::map<std::string, int>& call_counts){
    Stopwatch::add_header(file_name);

    std::cout << "\n⭐ CPU analysis ⭐" << std::endl;
    auto program = parse_to_cfg_transformer(prog, call_counts);
    reduce_variables(program.entryNodes);
    Stopwatch cpu_watch;
    TransferCreator analyis_info = get_analysis_information(program.nodes);
    std::vector<StatefulNode<std::vector<cpu_analysis::BitVector>>> nodes = create_states<std::vector<cpu_analysis::BitVector>>(program.nodes);
    
    //Count sources
    int source_count = 0;
    TaintSourceLocator locator;
    for(auto& node : nodes){
        if(locator.is_taintsource(*node.node)){
            ++source_count;
        }
    }

    cpu_multi::worklist(nodes, analyis_info.node_to_index, analyis_info.transfers, source_count);

    cpu_watch.save_time<Microseconds>();
    cpu_watch.print_time<Microseconds>("Run time: ");
    std::vector<StatefulNode<SourcedTaintState>> comparable_cpu_nodes = create_states<SourcedTaintState>(program.nodes);
    set_multi_bit_vector_state(nodes, comparable_cpu_nodes);


    {
        init_gpu();
        std::cout << "\n⭐ GPU analysis ⭐" << std::endl;
        program = parse_to_cfg_transformer(prog, call_counts);
        Stopwatch gpu_watch;
        auto gpu_nodes = multi_bit_cuda_worklist_analysis(program);
        gpu_watch.save_time<Microseconds>();

        if(!state_multi_equality(comparable_cpu_nodes, gpu_nodes)){
            std::cout << "###### cpu != gpu #####" << std::endl;
        }
        Stopwatch::add_line();
    }
}

int main(int argc, char *argv[]){
    std::map<std::string, int> call_counts{};
    if(argc > 1){

        bool gpu_flag = false, multi_taint_flag = false, cpu_flag = false, benchmark_all = false, benchmark_all_multi = false, cuda_flag = false, cuda_worklist_flag = false, multi_source_cuda = false;
        for (int i = 1; i < argc; i++)
        {
            char* arg = argv[i];

            if(strncmp(arg, "-d", 3) == 0){
                call_counts[argv[i+1]] = std::stoi(argv[i+2]);
                i += 2;
                continue;
            }
            
            if(strcmp(arg, "--benchmark-all") == 0 || strcmp(arg, "-ba") == 0){
                timing::should_benchmark = true;
                benchmark_all = true;
            }

            if(strcmp(arg, "--benchmark-all-multi") == 0 || strcmp(arg, "-bam") == 0){
                timing::should_benchmark = true;
                benchmark_all_multi = true;
            }

            if(strcmp(arg, "--gpu") == 0 || strcmp(arg, "-g") == 0){
                gpu_flag = true;
            }

            if(strcmp(arg, "--cuda") == 0 || strcmp(arg, "-cu") == 0){
                cuda_flag = true;
            }

            if(strcmp(arg, "--multi") == 0 || strcmp(arg, "-m") == 0){
                multi_taint_flag = true;
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

        if(benchmark_all_multi){
            benchmark_all_multi_taint(prog, file_name, call_counts);
            return 0;
        }

        if(benchmark_all){

            Stopwatch::add_header(file_name);

            std::cout << "\n⭐ CPU analysis ⭐" << std::endl;
            auto program = parse_to_cfg_transformer(prog, call_counts);
            reduce_variables(program.entryNodes);
            Stopwatch cpu_watch;
            TransferCreator analyis_info = get_analysis_information(program.nodes);
            std::vector<StatefulNode<cpu_analysis::BitVector>> nodes = create_states<cpu_analysis::BitVector>(program.nodes, cpu_analysis::BitVector(1));
            time_func("Analyzing: ", 
                cpu_analysis::worklist, nodes, analyis_info.node_to_index, analyis_info.transfers);
            cpu_watch.save_time<Microseconds>();
            std::vector<StatefulNode<std::set<std::string>>> cpu_nodes = create_states<std::set<std::string>>(program.nodes, {TAINT_VAR});
            set_bit_vector_state(nodes, cpu_nodes);

            init_gpu();

            std::cout << "\n⭐ bit-cuda analysis ⭐" << std::endl;
            program = parse_to_cfg_transformer(prog, call_counts);
            Stopwatch bit_cuda_watch;
            auto bit_cuda_nodes = bit_cuda_analysis(program);
            bit_cuda_watch.save_time<Microseconds>();

            if(!state_equality(cpu_nodes, bit_cuda_nodes)){
                std::cout << "###### cpu != bit-cuda #####" << std::endl;
            }

            std::cout << "\n⭐ bit-cuda worklist analysis ⭐" << std::endl;
            program = parse_to_cfg_transformer(prog, call_counts);
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
                parse_to_cfg_transformer, prog, call_counts);

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
                run_cpu_analysis(program);
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
            std::cout << "  when using expandable calls with identifiers\n";
            std::cout << "  set count of identifer id to x with\n";
            std::cout << "  -d {id} {x}\n";

        }

    }else{
        antlr4::ANTLRFileStream csfile;
        csfile.loadFromFile("./sampleprograms/multiplefunc.sc");
        antlr4::ANTLRInputStream prog(csfile);

        auto program = time_func<ScTransformer>("Creating CFG nodes: ", 
            parse_to_cfg_transformer, prog, call_counts);

        std::vector<StatefulNode<std::set<std::string>>> result1 = bit_cuda_worklist_analysis(program);
        std::cout << "#######\n";
        std::cout << "#######\n";
        std::cout << "#######\n";
        std::cout << "#######\n";
        std::cout << "#######\n";
        std::cout << "#######\n";
        std::vector<StatefulNode<std::set<std::string>>> result2 = run_cpu_analysis(program);



        std::cout << "The result1 == result2 = " << state_equality(result1, result2) << "\n";
    }
    return 0;
}