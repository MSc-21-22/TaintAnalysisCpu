#include <iostream>
#include <string>
#include <memory>
#include "antlr4-runtime/scLexer.h"
#include "antlr4-runtime/scParser.h"

int main(){
    std::cout << "Hello, world!" << std::endl;
    
    antlr4::ANTLRInputStream stream("void i() {x = 2;}");
    scLexer lexer(&stream);
    antlr4::CommonTokenStream tokens(&lexer);
    scParser parser(&tokens);

    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    parser.prog();

    std::cout << std::endl;

    return 0;
}