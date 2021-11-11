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
#include <chrono>
#include "timing.h"
#include <cubool.h>
#include <stdio.h>
#include "cubool/analysis.h"

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

    timeFunc("Analyzing: ", 
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

        bool gpu_flag = false, multi_taint_flag = false, cubool_flag = false;
        for (int i = 1; i < argc; i++)
        {
            char* arg = argv[i];
            if(strcmp(arg, "--gpu") == 0 || strcmp(arg, "-g") == 0){
                gpu_flag = true;
            }
            if(strcmp(arg, "--multi") == 0 || strcmp(arg, "-m") == 0){
                multi_taint_flag = true;
            }
            if(strcmp(arg, "--benchmark") == 0 || strcmp(arg, "-b") == 0){
                timing::should_benchmark = true;
            }
            if(strcmp(arg, "--cubool") == 0 || strcmp(arg, "-c") == 0){
                cubool_flag = true;
            }
        }

        antlr4::ANTLRFileStream csfile;
        csfile.loadFromFile(argv[argc-1]);
        antlr4::ANTLRInputStream prog(csfile);

        if(gpu_flag){
            if(cubool_flag){
                std::cout << "Running analysis using cuBool on GPU" << std::endl;
                auto program = parse_to_cfg_transformer<std::set<std::string>>(prog);
                cubool_analyse(program.nodes);
            }else{
                std::cout << "Running analysis using cuBLAS on GPU" << std::endl;
                auto program = parse_to_cfg_transformer<std::set<std::string>>(prog);
                gpu_analysis(program.nodes);
                if(!timing::should_benchmark){
                    print_digraph_subgraph(program.entryNodes, std::cout, print_result, "main");
                }
            }
        }else{
            if(multi_taint_flag){
                std::cout << "Running multi-taint analysis using CPU" << std::endl;
                auto program = parse_to_cfg_transformer<SourcedTaintState>(prog);
                cpu_multi_taint_analysis(program);
            }else{
                std::cout << "Running analysis using CPU" << std::endl;

                auto program = timeFunc<ScTransformer<std::set<std::string>>>("Creating CFG nodes: ", 
                    parse_to_cfg_transformer<std::set<std::string>>, prog);
                cpu_analysis(program);
            }
        }

    }
    return 0;
}