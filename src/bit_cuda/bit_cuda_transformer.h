#pragma once

#include <cfg.h>
#include "analysis.h"
#include <var_visitor.h>

#define RETURN_VAR "$return"
#define TAINT_VAR "$"

template <typename LatticeType>
class BitCudaTransformer : public CfgVisitor<LatticeType>
{
public:
    std::vector<bit_cuda::Node> nodes{};
    std::vector<bit_cuda::Transfer> transfer_functions{};
    std::map<Node<LatticeType>*, int> node_to_index{};
    std::map<std::string, int> variables{};

    BitCudaTransformer(std::set<std::string> progVariables){
        int i = 0;
        variables[TAINT_VAR] = i++;
        variables[RETURN_VAR] = i++;

        std::cout << TAINT_VAR << " -> " << variables[TAINT_VAR] << " : " << (1 << variables[TAINT_VAR])  <<'\n';
        std::cout << RETURN_VAR << " -> " << variables[RETURN_VAR] << " : " << (1 << variables[RETURN_VAR])  <<'\n';

        std::set<std::string>::iterator it;
        for (it=progVariables.begin(); it!=progVariables.end(); it++){
            if(*it != TAINT_VAR && *it != RETURN_VAR){
                variables[*it] = i++;
                std::cout << *it << " -> " << variables[*it] << " : " << (1 << variables[*it])  <<'\n';
            }
        }

    }

    void visit_assignment(AssignmentNode<LatticeType>& node) {
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(node.id, node.expression);
    }

    void visit_return(ReturnNode<LatticeType>& node) {
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(RETURN_VAR, node.expression);
    }

    void visit_emptyReturn(EmptyReturnNode<LatticeType>& node) {
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();
    }

    void visit_functionEntry(FunctionEntryNode<LatticeType>& node) { 
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();


        if(node.arguments.size() >= 1){
            bit_cuda::Transfer* last;
            int last_index;
            
            for (int i = 0; i < node.arguments.size(); i++)
            {
                last_index = add_transfer_function(node.formal_parameters[i], node.arguments[i]);
                if(i == 0){
                    node_struct.first_transfer_index = last_index;
                }else{
                    last = &transfer_functions[last_index];
                    last->next_transfer_index = add_transfer_function(node.formal_parameters[0], node.arguments[i]);
                }
            }
        }
    }

    void visit_assignReturn(AssignReturnNode<LatticeType>& node) { 
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(node.id, {RETURN_VAR});
    }

    void visit_arrayAssignment(ArrayAssignmentNode<LatticeType>& node) { 
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(node.id, node.expression);
    }
    
    void visit_arrayinit(ArrayInitializerNode<LatticeType>& node) { 
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();

        // Get vars from all array element expressions 
        std::set<std::string> expr_vars;
        for(auto& element : node.arrayContent){
            auto vars = element->get_variables();
            std::set_union(expr_vars.begin(), expr_vars.end(),
                           vars.begin(), vars.end(),
                           std::inserter(expr_vars, expr_vars.begin()));
        }

        node_struct.first_transfer_index = add_transfer_function(node.id, expr_vars);
    }

    void visit_propagation(PropagationNode<LatticeType>& node) { 
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();
    }

private:
    int add_transfer_function(std::string x, std::set<std::string>& vars){
        int index = transfer_functions.size();
        bit_cuda::Transfer& current_transfer = transfer_functions.emplace_back();
        current_transfer.x = variables[x];
        fill_with_variable_indices(current_transfer.rhs, vars);
        return index;
    }

    int add_transfer_function(std::string x, std::set<std::string>&& vars){
        return add_transfer_function(x, vars);
    }

    int add_transfer_function(std::string x, std::shared_ptr<Expression>& expression){
        auto vars = expression->get_variables();
        return add_transfer_function(x, vars);
    }

    void fill_with_variable_indices(int* arr, std::set<std::string>& vars){
        int i = 0;
        for(std::string var : vars){
            if (variables.count(var)){
                arr[i++] = variables[var];
            }
        } 
    }
};

template<typename LatticeType>
void add_predecessors(std::vector<std::shared_ptr<Node<LatticeType>>>& nodes, BitCudaTransformer<LatticeType>& transformer){
    for(int i = 0; i < nodes.size(); i++){
        int j = 0;
        for (auto pred_it = nodes[i]->predecessors.begin(); pred_it != nodes[i]->predecessors.end(); ++pred_it){
            transformer.nodes[i].predecessor_index[j++] = transformer.node_to_index[pred_it->get()];
        }
    }
}

template<typename LatticeType>
BitCudaTransformer<LatticeType> transform_bit_cuda(std::vector<std::shared_ptr<Node<LatticeType>>>& nodes) {
    auto variables = get_variables(nodes);
    BitCudaTransformer<LatticeType> transformer(variables);
    for(auto &node : nodes){
        node->accept(transformer);
    }
    add_predecessors(nodes, transformer);
    return transformer;
}