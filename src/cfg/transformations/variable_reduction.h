#pragma once
#include <cfg/cfg.h>
#include <map>

class VariableReducer : public CfgVisitor {
    std::map<FunctionEntryNode*, std::map<std::string, std::string>> args;
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
            name_map[variable] = "v" + std::to_string(name_map.size() - 1);
            return name_map[variable];
        }
    }

    void visit_children(Node& node){
        for(auto& child : node.successors)
        {
            auto* function_entry = dynamic_cast<FunctionEntryNode*>(child.get());
            if(!function_entry){
                if (nodes_traversed.count((intptr_t)child.get()) == 0){
                    nodes_traversed.insert((intptr_t)child.get());
                    child->accept(*this);
                }
            }else{
                for(auto& arg: function_entry->arguments){
                    arg->replace_names(name_map);
                }
            }
        }
    }

    void visit_assignment(AssignmentNode& node){
        node.id = get_new_variable(node.id);
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
            param = get_new_variable(param);
        }

        visit_children(node);
    }
    void visit_assignReturn(AssignReturnNode& node){
        node.id = get_new_variable(node.id);

        visit_children(node);
    }

    void visit_arrayinit(ArrayInitializerNode& node){
        node.id = get_new_variable(node.id);
        for (auto& expression : node.arrayContent){
            expression->replace_names(name_map);
        }
        visit_children(node);
    }

    void visit_arrayAssignment(ArrayAssignmentNode& node){
        node.id = get_new_variable(node.id);
        node.expression->replace_names(name_map);

        visit_children(node);
    }
};

void reduce_variables(std::vector<std::shared_ptr<FunctionEntryNode>>& entry_nodes);