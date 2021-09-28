#include <iostream>
#include <string>
#include <memory>
#include "antlr4-runtime/scLexer.h"
#include "antlr4-runtime/scParser.h"
#include "transforms.h"

int main(){
    std::cout << "Hello, world!" << std::endl << std::endl;

    antlr4::ANTLRInputStream stream("void i(int j, int z) {x = 2; y = 3;} void j(){n = 3; i(2,3);}");
    auto functions = parse_to_cfg<int>(stream);

    functions[0]->dotPrint(std::cout);
    functions[1]->dotPrint(std::cout);

    return 0;
}