#include <iostream>
#include <string>
#include "antlr4-runtime/scLexer.h"
#include "antlr4-runtime/scParser.h"
#include "transforms.h"
#include "worklist.h"
#include "taint_analysis.h"
#include "digraph.h"
#include "matrix_analysis.h"

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
    worklist(program.nodes, analyzer);

    //print_digraph_with_result<std::set<std::string>>(program.nodes, std::cout, print_result);
    print_digraph_subgraph(program.entryNodes, std::cout, print_result, "main");
}


int main(int argc, char *argv[]){
    if(argc > 1){
        antlr4::ANTLRFileStream csfile;
        csfile.loadFromFile(argv[argc-1]);
        antlr4::ANTLRInputStream prog(csfile);
        auto program = parse_to_cfg_transformer<std::set<std::string>>(prog);
        
        for (auto& node : program.nodes){
            node->state.insert("£");
        }

        if(argc == 3 && (strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "--gpu") == 0)){
            std::cout << "Running analysis using GPU" << std::endl;
            gpu_analysis(program.nodes, program.entryNodes);
        }else{
            std::cout << "Running analysis using CPU" << std::endl;
            cpu_analysis(program);
        }


    }

    //antlr4::ANTLRInputStream stream("int f(int n){a=n+2; return a;} void i(int j) {j=£; x = 2*(5-2); while(x) { y = 3+j; x=x-1; int fr = f(j);} i = y;}");
    return 0;
}