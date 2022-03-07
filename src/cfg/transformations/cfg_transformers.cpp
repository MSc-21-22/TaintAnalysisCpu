#include <cfg/transformations/var_visitor.h>
#include <cfg/transformations/variable_reduction.h>
#include <cfg/transformations/cfg_clone.h>
#include <cfg/transformations/get_taint_sources.h>

std::set<std::string> get_variables(std::vector<std::shared_ptr<Node>>& nodes){
    VarVisitor varAnalyzer;
    for(auto& node : nodes){
        (*node).accept(varAnalyzer);
    }
    return varAnalyzer.variables;
}

void reduce_variables(std::vector<std::shared_ptr<FunctionEntryNode>>& entry_nodes) {
    VariableReducer reducer({TAINT_VAR, RETURN_VAR});
    for(auto &entry : entry_nodes){
        entry->accept(reducer);
    }
}

std::shared_ptr<FunctionEntryNode> clone_entry(std::shared_ptr<FunctionEntryNode> entry, std::vector<std::shared_ptr<Node>>* node_vector){
    Cloner cloner(node_vector);
    entry->accept(cloner);

    auto result = cloner.nodeConverter.at(entry.get());
    return std::static_pointer_cast<FunctionEntryNode>(result);
}

std::vector<std::shared_ptr<Node>> get_taint_sources(const std::vector<std::shared_ptr<Node>>& nodes) {
    std::vector<std::shared_ptr<Node>> result;
    
    TaintSourceChecker checker;
    for(auto& node : nodes){
        node->accept(checker);
        if(checker.is_taint_source){
            result.push_back(node);
        }
    }
    return result;
}