#include <iostream>
#include <string>
#include <memory>
#include "antlr4-runtime/scLexer.h"
#include "antlr4-runtime/scParser.h"
#include "transforms.h"
#include "worklist.h"
#include "taint_analysis.h"
#include "digraph.h"

void print_result(std::set<std::string>& result, std::ostream& stream){
    stream << "\\n{ ";
    for (auto& x : result){
        if (x != "£return" && x!="£"){
            stream << x << " ";
        }
    }
    stream << "}";
}

int main(int argc, char *argv[]){
    if(argc == 2){
        std::cout << "1" << std::endl;
        antlr4::ANTLRFileStream csfile;
        csfile.loadFromFile(argv[1]);
        antlr4::ANTLRInputStream prog(csfile);
        auto nodes = parse_to_cfg<std::set<std::string>>(prog);
        for (auto& node : nodes){
            node->state.insert("£");
        }
        std::cout << "2" << std::endl;

        TaintAnalyzer analyzer;
        worklist(nodes, analyzer);
        std::cout << "3" << std::endl;

        print_digraph_with_result<std::set<std::string>>(nodes, std::cout, print_result);

    }

    //antlr4::ANTLRInputStream stream("int f(int n){a=n+2; return a;} void i(int j) {j=£; x = 2*(5-2); while(x) { y = 3+j; x=x-1; int fr = f(j);} i = y;}");
    return 0;
}