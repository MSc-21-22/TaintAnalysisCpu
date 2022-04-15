#include <cfg/transformations/var_visitor.h>
#include <cfg/transformations/variable_reduction.h>
#include <cfg/transformations/cfg_clone.h>

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
        reducer.visit_node(*entry);
    }
}

std::shared_ptr<FunctionEntryNode> clone_entry(std::shared_ptr<FunctionEntryNode> entry, std::vector<std::shared_ptr<Node>>* node_vector){
    Cloner cloner(node_vector);
    entry->accept(cloner);

    auto result = cloner.nodeConverter.at(entry.get());
    return std::static_pointer_cast<FunctionEntryNode>(result);
}