#include <iostream>
#include <string>
#include <memory>
#include "antlr4-runtime/scLexer.h"
#include "antlr4-runtime/scParser.h"
#include "transforms.h"
#include "worklist.h"
#include "taint_analysis.h"
#include "digraph.h"
#include "kernel.h"
#include "var_visitor.h"
#include "transforms_matrix.h"

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

void gpu_analysis(ScTransformer<std::set<std::string>> program){
    // VarVisitor<std::set<std::string>> varAnalyzer;
    // for(auto& node : program.nodes){
    //     (*node).accept(varAnalyzer);
    // }
    // for(std::string var: varAnalyzer.variables){
    //     std::cout << var << std::endl;
    // }
    // MatrixTransforms<std::set<std::string>> matrixTransformer{varAnalyzer.variables};
    // for(auto& node : program.nodes){
    //     (*node).accept(matrixTransformer);
    // }
}

int main(int argc, char *argv[]){

    const int arraySize = 3 * 2;
    const int a[arraySize] = { 1, 2, 3, 4, 5, 6 };
    const int b[arraySize] = { 10, 20, 30, 40, 50, 60 };
    int c[arraySize] = { 0 };

    // Add vectors in parallel.
    auto cudaStatus = add_with_cuda(c, a, b, 3, 2);

    if(cudaStatus == KernelResult::Success){
        std::cout << "Succeded with " << c[0] << ", " << c[1] << ", " << c[2] << std::endl;
        std::cout << "              " << c[3] << ", " << c[4] << ", " << c[5] << std::endl;
    }else{
        std::cout << "Kernel failed" << std::endl;
    }

    if(argc == 2){
        antlr4::ANTLRFileStream csfile;
        csfile.loadFromFile(argv[1]);
        antlr4::ANTLRInputStream prog(csfile);
        auto program = parse_to_cfg_transformer<std::set<std::string>>(prog);
        
        for (auto& node : program.nodes){
            node->state.insert("£");
        }

        // cpu_analysis(program);
        gpu_analysis(program);

    }

    //antlr4::ANTLRInputStream stream("int f(int n){a=n+2; return a;} void i(int j) {j=£; x = 2*(5-2); while(x) { y = 3+j; x=x-1; int fr = f(j);} i = y;}");
    return 0;
}