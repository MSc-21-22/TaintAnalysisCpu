#include <iostream>
#include <string>
#include "antlr4-runtime/scLexer.h"
#include "antlr4-runtime/scParser.h"
#include "taint_analysis.h"
#include "multi_taint_analysis.h"
#include <chrono>
#include "timing.h"
#include <stdio.h>
#include <fcntl.h>
#include <cstring>
#include <cuda/common.h>
#include <cuda/sc_transformer.h>
#include <cuda/digraph.h>
#include <base_taint_analysis.h>
#include <cuda/bit_cuda/analysis.h>
#include <cuda/cuda_worklist/analysis.h>


template<typename Node>
bool is_equal(DynamicArray<Node>& nodes, DynamicArray<Node>& other_nodes) {
    if (nodes.size() != other_nodes.size())
        return false;

    for (int i = 0; i < nodes.size(); ++i) {
        if (!(nodes[i].data == other_nodes[i].data)) {
            return false;
        }
    }

    return true;
}

DynamicArray<taint::Node> run_cpu_analysis(antlr4::ANTLRInputStream& program, std::map<std::string, int>& call_counts){
    auto transformer = time_func<ScCudaTransformer<taint::Node>>("Parsing: ",
        parse_to_cuda_transformer<taint::Node>, program, call_counts);
    time_func("Analyzing: ", 
        cpu_analysis::worklist, transformer.get_nodes(), transformer.get_transfers(), std::move(transformer.get_sources()));

    if (!timing::should_benchmark)
        cuda::print_digraph(transformer.get_nodes());

    return transformer.get_nodes();
}

DynamicArray<multi_taint::Node> cpu_multi_taint_analysis(antlr4::ANTLRInputStream& program, std::map<std::string, int>& call_counts){
    std::cout << "Feature currently unsupported\n";
    //reduce_variables(program.entryNodes);
    //TransferCreator analyis_info = get_analysis_information(program.nodes);
    //std::vector<StatefulNode<std::vector<BitVector>>> nodes = create_states<std::vector<BitVector>>(program.nodes);
    //
    ////Count sources
    //int source_count = 0;
    //TaintSourceLocator locator;
    //for(auto& node : nodes){
    //    if(locator.is_taintsource(*node.node)){
    //        ++source_count;
    //    }
    //}

    //time_func("Analyzing: ",
    //    cpu_multi::worklist, nodes, analyis_info.node_to_index, analyis_info.transfers, source_count);

    //if(!timing::should_benchmark) {
    //    std::vector<StatefulNode<SourcedTaintState>> printable_nodes = create_states<SourcedTaintState>(program.nodes);
    //    set_multi_bit_vector_state(nodes, printable_nodes);
    //    print_digraph_subgraph(printable_nodes, std::cout, print_taint_source, "main");
    //}
    //return nodes;
    return DynamicArray<multi_taint::Node>();
}

ScCudaTransformer<taint::Node> bit_cuda_analysis(antlr4::ANTLRInputStream& program, std::map<std::string, int>& call_counts){
    auto transformer = time_func<ScCudaTransformer<taint::Node>>("Parsing: ",
        parse_to_cuda_transformer<taint::Node>, program, call_counts);
        
    time_func("Least fixed point algorithm: ",
            bit_cuda::execute_analysis, transformer.get_nodes(), transformer.get_transfers());

    if(!timing::should_benchmark)
        cuda::print_digraph(transformer.get_nodes());

    return transformer;
}

ScCudaTransformer<taint::Node> bit_cuda_worklist_analysis(antlr4::ANTLRInputStream& program, std::map<std::string, int>& call_counts){
    auto transformer = time_func<ScCudaTransformer<taint::Node>>("Parsing: ",
        parse_to_cuda_transformer<taint::Node>, program, call_counts);

    time_func("Least fixed point algorithm: ",
            cuda_worklist::execute_analysis, transformer.get_nodes(), transformer.get_transfers(), transformer.get_sources());

    if (!timing::should_benchmark)
        cuda::print_digraph(transformer.get_nodes());

    return transformer;
}

DynamicArray<multi_taint::Node> multi_bit_cuda_worklist_analysis(antlr4::ANTLRInputStream& program, std::map<std::string, int>& call_counts){
    std::cout << "Feature currently unsupported\n";
    //init_gpu();
    //time_func("Variable reduction: ",
    //    reduce_variables, program.entryNodes);
    //int source_count = count_taint_sources(program.nodes);
    //auto transformer = time_func<CudaTransformer<multi_cuda::Node>>("Gpu structure transformation: ", 
    //            transform_multi_cuda, program.nodes, source_count);
    //            
    //time_func("Least fixed point algorithm: ",
    //        multi_cuda::execute_analysis, transformer.nodes, transformer.transfer_functions, transformer.taint_sources, source_count);

    //std::vector<StatefulNode<SourcedTaintState>> nodes = create_states<SourcedTaintState>(program.nodes);
    //time_func("Save into nodes", 
    //            set_bit_cuda_multi_state, transformer.nodes, source_count, nodes);
    //if(!timing::should_benchmark)
    //    print_digraph_subgraph(nodes, std::cout, print_taint_source, "main");

    //return nodes;
    return DynamicArray<multi_taint::Node>();
}

void benchmark_all_multi_taint(antlr4::ANTLRInputStream& prog, std::string file_name, std::map<std::string, int>& call_counts){
    std::cout << "Feature currently unsupported\n";

    //std::stringstream header;
    //if (call_counts.find("f") == call_counts.end()) {
    //    header << file_name;
    //}
    //else {
    //    header << file_name << " : " << call_counts["f"];
    //}
    //Stopwatch::add_header(header.str());

    //std::cout << "\n⭐ CPU analysis ⭐" << std::endl;
    //auto program = parse_to_cfg_transformer(prog, call_counts);
    //reduce_variables(program.entryNodes);
    //Stopwatch cpu_watch;
    //TransferCreator analyis_info = get_analysis_information(program.nodes);
    //std::vector<StatefulNode<std::vector<BitVector>>> nodes = create_states<std::vector<BitVector>>(program.nodes);
    //
    ////Count sources
    //int source_count = 0;
    //TaintSourceLocator locator;
    //for(auto& node : nodes){
    //    if(locator.is_taintsource(*node.node)){
    //        ++source_count;
    //    }
    //}

    //cpu_multi::worklist(nodes, analyis_info.node_to_index, analyis_info.transfers, source_count);

    //cpu_watch.save_time<Microseconds>();
    //cpu_watch.print_time<Microseconds>("Run time: ");
    //std::vector<StatefulNode<SourcedTaintState>> comparable_cpu_nodes = create_states<SourcedTaintState>(program.nodes);
    //set_multi_bit_vector_state(nodes, comparable_cpu_nodes);


    //init_gpu();
    //std::cout << "\n⭐ GPU analysis ⭐" << std::endl;
    //program = parse_to_cfg_transformer(prog, call_counts);
    //Stopwatch gpu_watch;
    //auto gpu_nodes = multi_bit_cuda_worklist_analysis(program);
    //gpu_watch.save_time<Microseconds>();

    //if(!state_multi_equality(comparable_cpu_nodes, gpu_nodes)){
    //    std::cout << "###### cpu != gpu #####" << std::endl;
    //}
    //Stopwatch::add_line();
}

int main(int argc, char *argv[]){
    std::map<std::string, int> call_counts{};

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
            gpu_flag = true;
        }

        if(strcmp(arg, "--benchmark-all-multi") == 0 || strcmp(arg, "-bam") == 0){
            timing::should_benchmark = true;
            benchmark_all_multi = true;
            gpu_flag = true;
        }

        if(strcmp(arg, "--cuda") == 0 || strcmp(arg, "-cu") == 0){
            cuda_flag = true;
            gpu_flag = true;
        }

        if(strcmp(arg, "--multi") == 0 || strcmp(arg, "-m") == 0){
            multi_taint_flag = true;
        }

        if(strcmp(arg, "--multi-cuda") == 0 || strcmp(arg, "-mc") == 0){
            multi_source_cuda = true;
            gpu_flag = true;
        }

        if(strcmp(arg, "--cuda-worklist") == 0 || strcmp(arg, "-cw") == 0){
            cuda_worklist_flag = true;
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

    if (gpu_flag) {
        init_gpu();
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

        std::stringstream header;
        if (call_counts.find("f") == call_counts.end()) {
            header << file_name;
        }
        else {
            header << file_name << " : " << call_counts["f"];
        }

        auto debug_transformer = parse_to_cuda_transformer<taint::Node>(prog, call_counts);

        std::cout << "CFG Nodes: " << debug_transformer.get_nodes().size() << "\n" << std::endl;
        header << ";" << debug_transformer.get_nodes().size();
        Stopwatch::add_header(header.str());

        std::cout << "\n⭐ CPU analysis ⭐" << std::endl;
        Stopwatch cpu_watch;
        auto cpu_transformer = time_func<ScCudaTransformer<taint::Node>>("Parsing: ",
            parse_to_cuda_transformer<taint::Node>, prog, call_counts);
        time_func("Analyzing: ",
            cpu_analysis::worklist, cpu_transformer.get_nodes(), cpu_transformer.get_transfers(), std::move(cpu_transformer.get_sources()));
        cpu_watch.save_time<Microseconds>();

        std::cout << "\n⭐ bit-cuda analysis ⭐" << std::endl;
        Stopwatch bit_cuda_watch;
        auto bit_cuda = bit_cuda_analysis(prog, call_counts);
        bit_cuda_watch.save_time<Microseconds>();

        if(!is_equal(cpu_transformer.get_nodes(), bit_cuda.get_nodes())) {
            std::cout << "###### cpu != bit-cuda #####" << std::endl;
        }

        std::cout << "\n⭐ bit-cuda worklist analysis ⭐" << std::endl;
        Stopwatch cuda_worklist_watch;
        auto cuda_worklist = bit_cuda_worklist_analysis(prog, call_counts);
        cuda_worklist_watch.save_time<Microseconds>();

        if (!is_equal(bit_cuda.get_nodes(), cuda_worklist.get_nodes())) {
            std::cout << "##### bit cuda != bit cuda worklist #####" << std::endl;
        }
        if (!is_equal(cpu_transformer.get_nodes(), cuda_worklist.get_nodes())) {
            std::cout << "##### bit cuda != bit cuda worklist #####" << std::endl;
        }

        Stopwatch::add_line();
        return 0;
    }

    if(cuda_flag){
        std::cout << "Running bit-cuda analysis" << std::endl;
        bit_cuda_analysis(prog, call_counts);
    }else if(cuda_worklist_flag){
        std::cout << "Running bit-cuda analysis using worklists" << std::endl;
        bit_cuda_worklist_analysis(prog, call_counts);
    }else if(multi_source_cuda){
        std::cout << "Running multi-colored bit-cuda analysis using worklists" << std::endl;
        multi_bit_cuda_worklist_analysis(prog, call_counts);
    }else if(cpu_flag){
        if(multi_taint_flag){
            std::cout << "Running multi-taint analysis using CPU" << std::endl;
            cpu_multi_taint_analysis(prog, call_counts);
        }else{
            std::cout << "Running analysis using CPU" << std::endl;
            run_cpu_analysis(prog, call_counts);
        }
    }else{
        std::cout << "Invalid command\n";
        std::cout << " --cpu -c for use on cpu\n";
        std::cout << " with cpu flag:\n";
        std::cout << " --multi -m for multi taint analysis\n\n";
        std::cout << " --cuda -cu for bit-cuda implementation\n";
        std::cout << " --cuda-worklist -cw for bit-cuda implementation using worklist\n";
        std::cout << " --multi-cuda -mc for multi colored taint analysis using cuda and worklist\n";
        std::cout << " --benchmark -b to enable benchmarking where possible\n";
        std::cout << "  when using expandable calls with identifiers\n";
        std::cout << "  set count of identifer id to x with\n";
        std::cout << "  -d {id} {x}\n";

    }
    return 0;
}