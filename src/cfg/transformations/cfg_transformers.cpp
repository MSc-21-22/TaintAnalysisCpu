#include <cfg/transformations/var_visitor.h>
#include <cfg/transformations/variable_reduction.h>
#include <cfg/transformations/cfg_clone.h>
#include <cfg/transformations/variable_deducer.h>>

std::set<std::string> get_variables(std::vector<std::shared_ptr<Node>>& nodes){
    VarVisitor varAnalyzer;
    for(auto& node : nodes){
        (*node).accept(varAnalyzer);
    }
    return varAnalyzer.variables;
}

void reduce_variables(std::vector<std::shared_ptr<FunctionEntryNode>>& entry_nodes) {
    VariableReducer reducer;
    for(auto &entry : entry_nodes){
        reducer.visit_node(*entry);
    }
}

std::shared_ptr<FunctionEntryNode> clone_entry(std::shared_ptr<FunctionEntryNode> entry, std::vector<std::shared_ptr<Node>>* node_vector, std::vector<std::shared_ptr<FunctionEntryNode>>& entry_nodes){
    Cloner cloner(node_vector, entry_nodes);
    entry->accept(cloner);

    auto result = cloner.nodeConverter.at(entry.get());
    return std::static_pointer_cast<FunctionEntryNode>(result);
}

void deduce_variables(std::vector<std::shared_ptr<Node>> entry_nodes, std::map<Node*, cpu_analysis::BitVector>& states, std::map<Node*, std::set<std::string>>& result){
    VariableDeducer deducer(states, result);
    for(auto entry : entry_nodes){
        entry->accept(deducer);
    }
}