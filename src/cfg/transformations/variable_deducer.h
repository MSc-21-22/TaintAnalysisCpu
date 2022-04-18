#pragma once
#include <cfg/cfg.h>
#include <taint_analysis.h>
#include <algorithm>
using namespace cpu_analysis;


class VariableDeducer : public CfgVisitor {
    int next_index{ 0 };
    std::set<intptr_t> nodes_traversed{};
    std::vector<Node*> node_stack{};
    std::vector<std::string> initial_map{};
    std::map<Node*, cpu_analysis::BitVector>& states;
    std::map<Node*, std::set<std::string>>& result;

public:
    std::vector<std::string> variables;

    VariableDeducer(std::map<Node*, cpu_analysis::BitVector>& states, std::map<Node*, std::set<std::string>>& result) : states(states), result(result)  {
        initial_map.emplace_back(TAINT_VAR);
        initial_map.emplace_back(RETURN_VAR);
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

    void add_variable(std::string& var){
        if(std::count(variables.begin(), variables.end(), var) == 0){
            variables.emplace_back(var);
        }
    }

    void set_state(Node& node){
        int comparator = 1;
        for(int i = 0; i < variables.size(); ++i){
            if(states[&node][comparator]){
                result[&node].insert(variables[i]);
            }

            comparator << 1;
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
                
            }
        }
    }

    void visit_assignment(AssignmentNode& node){
        add_variable(node.id);

        set_state(node);
        visit_children(node);
    }
    void visit_propagation(PropagationNode& node){
        if(node.syntax != "Exit"){
            set_state(node);
            visit_children(node);
        }
    }
    void visit_return(ReturnNode& node){
        set_state(node);
        visit_children(node);
    }
    void visit_emptyReturn(EmptyReturnNode& node){
        set_state(node);
        visit_children(node);
    }
    void visit_functionEntry(FunctionEntryNode& node){
        nodes_traversed = {};
        variables = initial_map;

        for(auto& param : node.formal_parameters){
            add_variable(param);
        }

        set_state(node);
        visit_children(node);
    }
    void visit_assignReturn(AssignReturnNode& node){
        add_variable(node.id);

        set_state(node);
        visit_children(node);
    }

    void visit_arrayinit(ArrayInitializerNode& node){
        add_variable(node.id);

        set_state(node);
        visit_children(node);
    }

    void visit_arrayAssignment(ArrayAssignmentNode& node){
        add_variable(node.id);

        set_state(node);
        visit_children(node);
    }
};

void deduce_variables(std::vector<std::shared_ptr<Node>> entry_nodes, std::map<Node*, cpu_analysis::BitVector>& states, std::map<Node*, std::set<std::string>>& result);