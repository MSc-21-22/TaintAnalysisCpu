#pragma once
#include <cfg/cfg.h>
#include <map>
#include <assert.h>
#include <iostream>

class VariableReducer : public CfgVisitor {
    int next_index{ 0 };
    std::set<intptr_t> nodes_traversed{};
    std::vector<Node*> node_stack{};
    std::map<std::string, int> initial_map{};

public:
    std::map<std::string, int> name_map;
    FunctionEntryNode* last_entry;

    VariableReducer() {
        initial_map[TAINT_VAR] = 0;
        initial_map[RETURN_VAR] = 1;
    }

    void visit_node(Node& node) {
        node_stack = {};
        node.accept(*this);
        while(node_stack.size() > 0){
            Node* other_node = node_stack.back();
            node_stack.pop_back();
            other_node->accept(*this);
        }
    }
private:
    int get_new_variable(const std::string& variable) {
        auto new_id = name_map.find(variable);
        if(new_id != name_map.end()){
            return new_id->second;
        }else{
            name_map.insert(std::make_pair(variable, name_map.size()));
            return name_map.size() - 1;
        }
    }

    void visit_children(Node& node){
        for(auto& child : node.successors)
        {
            auto* function_entry = dynamic_cast<FunctionEntryNode*>(child.get());
            if(!function_entry){
                if (nodes_traversed.count((intptr_t)child.get()) == 0){
                    nodes_traversed.insert((intptr_t)child.get());
                    node_stack.push_back(child.get());
                }
            }else{
                for(auto& arg: function_entry->arguments){
                    arg->replace_names(name_map);
                }
            }
        }
    }

    void visit_assignment(AssignmentNode& node){
        node.var_index = get_new_variable(node.id);
        node.expression->replace_names(name_map);

        visit_children(node);
    }
    void visit_propagation(PropagationNode& node){
        if(node.syntax != "Exit")
            visit_children(node);
    }
    void visit_return(ReturnNode& node){
        node.expression->replace_names(name_map);

        visit_children(node);
    }
    void visit_emptyReturn(EmptyReturnNode& node){
        visit_children(node);
    }
    void visit_functionEntry(FunctionEntryNode& node){
        name_map = initial_map;
        nodes_traversed = {};

        for(auto& param : node.formal_parameters){
            node.formal_parameter_indexes.push_back(get_new_variable(param));
        }

        visit_children(node);

        node.variable_reduction = std::vector<std::string>(name_map.size());
        for(auto& [var_name, index] : name_map){
            node.variable_reduction[index] = var_name;
        }
    }
    void visit_assignReturn(AssignReturnNode& node){
        node.var_index = get_new_variable(node.id);

        visit_children(node);
    }

    void visit_arrayinit(ArrayInitializerNode& node){
        node.var_index = get_new_variable(node.id);
        for (auto& expression : node.arrayContent){
            expression->replace_names(name_map);
        }
        visit_children(node);
    }

    void visit_arrayAssignment(ArrayAssignmentNode& node){
        node.var_index = get_new_variable(node.id);
        node.expression->replace_names(name_map);

        visit_children(node);
    }
};

void reduce_variables(std::vector<std::shared_ptr<FunctionEntryNode>>& entry_nodes);