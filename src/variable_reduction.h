#pragma once
#include "cfg.h"
#include "Expression.h"
#include <map>

template<typename LatticeType>
class VariableReducer : public CfgVisitor<LatticeType> {
    std::map<std::string, std::string> name_map;
    std::map<std::string, std::string> initial_map{};
    std::set<intptr_t> nodes_traversed;

public:
    VariableReducer() = default;
    VariableReducer(std::vector<std::string> ignored_variables){
        for(auto& var : ignored_variables) {
            initial_map[var] = var;
        }
    }

private:
    std::string get_new_variable(const std::string& variable) {
        auto new_id = name_map.find(variable);
        if(new_id != name_map.end()){
            return new_id->second;
        }else{
            name_map[variable] = "v" + std::to_string(name_map.size());
            return name_map[variable];
        }
    }

    void visit_children(Node<LatticeType>& node){
        for(auto& child : node.successors)
        {
            if(!dynamic_cast<FunctionEntryNode<LatticeType>*>(child.get()) && nodes_traversed.find((intptr_t)child.get()) == nodes_traversed.end()){
                nodes_traversed.insert((intptr_t)child.get());
                child->accept(*this);
            }
        }
    }

    void visit_assignment(AssignmentNode<LatticeType>& node){
        node.id = get_new_variable(node.id);
        node.expression->replace_names(name_map);

        visit_children(node);
    }
    void visit_propagation(PropagationNode<LatticeType>& node){
        visit_children(node);
    }
    void visit_return(ReturnNode<LatticeType>& node){
        node.expression->replace_names(name_map);

        visit_children(node);
    }
    void visit_emptyReturn(EmptyReturnNode<LatticeType>& node){
        visit_children(node);
    }
    void visit_functionEntry(FunctionEntryNode<LatticeType>& node){
        name_map = initial_map;
        nodes_traversed = {};

        for(auto& param : node.formal_parameters){
            param = get_new_variable(param);
        }

        for(auto& arg: node.arguments){
            arg->replace_names(name_map);
        }

        visit_children(node);
    }
    void visit_assignReturn(AssignReturnNode<LatticeType>& node){
        node.id = get_new_variable(node.id);

        visit_children(node);
    }

    void visit_arrayinit(ArrayInitializerNode<LatticeType>& node){
        node.id = get_new_variable(node.id);
        for (auto& expression : node.arrayContent){
            expression->replace_names(name_map);
        }
        visit_children(node);
    }

    void visit_arrayAssignment(ArrayAssignmentNode<LatticeType>& node){
        node.id = get_new_variable(node.id);
        node.expression->replace_names(name_map);

        visit_children(node);
    }
};

template<typename LatticeType>
void reduce_variables(std::vector<std::shared_ptr<FunctionEntryNode<LatticeType>>>& entry_nodes) {
    VariableReducer<LatticeType> reducer({"£"});
    for(auto &entry : entry_nodes){
        entry->accept(reducer);
    }
}