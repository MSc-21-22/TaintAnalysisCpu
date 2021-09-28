#include <iostream>
#include <string>
#include <memory>
#include "antlr4-runtime/scLexer.h"
#include "antlr4-runtime/scParser.h"
#include "transforms.h"
#include "worklist.h"
#include "taint_analysis.h"

int main(){
    std::cout << "Hello, world!" << std::endl << std::endl;

    antlr4::ANTLRInputStream stream("void i(int j) {x = 2*(5-2); y = 3+j;}");
    auto nodes = parse_to_cfg<std::set<std::string>>(stream);
    nodes.front()->state.insert("j");


    TaintAnalyzer analyzer;
    worklist(nodes, analyzer);

    int i = 0;
    for(auto& node : nodes){
        std::cout << "Tainted variables in " << ++i << ":";
        for (auto& var : node->state){
            std::cout << var << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}