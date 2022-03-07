#include <cfg/sc_transformer.h>
#include <antlr4-runtime.h>
#include <antlr4-runtime/scLexer.h>

std::string stringify_parameters(std::vector<std::string> content){
    std::string result = "(";
    if(content.size() > 0){
        result += content.front();
        for(auto it = content.begin() + 1; it != content.end(); ++it){
            result += ", " + *it;
        }
    }
    result += ")";
    return result;
}

ScTransformer parse_to_cfg_transformer(antlr4::ANTLRInputStream &stream)
{
    scLexer lexer(&stream);
    antlr4::CommonTokenStream tokens(&lexer);
    scParser parser(&tokens);

    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    ScTransformer transformer;
    parser.prog()->accept(&transformer);

    return transformer;
}

std::vector<std::shared_ptr<Node>> parse_to_cfg(antlr4::ANTLRInputStream &stream)
{
    scLexer lexer(&stream);
    antlr4::CommonTokenStream tokens(&lexer);
    scParser parser(&tokens);

    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    ScTransformer transformer;
    parser.prog()->accept(&transformer);
    return transformer.nodes;
}