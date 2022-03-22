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

ScTransformer parse_to_cfg_transformer(antlr4::ANTLRInputStream stream)
{
    scLexer lexer(&stream);
    antlr4::CommonTokenStream tokens(&lexer);
    scParser parser(&tokens);

    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    ScTransformer transformer;
    parser.prog()->accept(&transformer);

    remove_unused_functions(transformer);

    return transformer;
}

std::vector<std::shared_ptr<Node>> parse_to_cfg(antlr4::ANTLRInputStream stream)
{
    scLexer lexer(&stream);
    antlr4::CommonTokenStream tokens(&lexer);
    scParser parser(&tokens);

    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    ScTransformer transformer;
    parser.prog()->accept(&transformer);
    return transformer.nodes;
}

void remove_unused_functions(ScTransformer& transformer){
    for (auto functionEntry : transformer.functionNodes){
        if(functionEntry->function_id != "main"){
            for (auto succ : functionEntry->successors)
            {
                remove_node(succ, transformer);
            }
            
        }
    }
}

void remove_node(std::shared_ptr<Node> node, ScTransformer& transformer){
    for (auto succ : node->successors){
        auto entry = dynamic_cast<FunctionEntryNode*>(succ.get());
        if(entry){
            if(entry->function_id != "main"){
                remove_node(succ, transformer);
            }else{
                break;
            }
        }
        auto it = std::find(transformer.nodes.begin(), transformer.nodes.end(), node);
        if (it != transformer.nodes.end()){
            transformer.nodes.erase(it);
        }
    }
}