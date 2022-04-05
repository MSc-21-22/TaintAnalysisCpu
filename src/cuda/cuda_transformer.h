#pragma once

#include "cuda_data.h"
#include "bit_cuda/analysis.h"
#include "cuda_worklist/analysis.h"
#include "multi_cuda/analysis.h"
#include <cfg/cfg.h>
#include <cfg/transformations/var_visitor.h>
#include <cfg/transformations/taint_locator.h>
#include <assert.h>

template <typename NodeType>
class CudaTransformer : public CfgVisitor
{
public:
    DynamicArray<NodeType> nodes;
    std::vector<Transfer> transfer_functions{};
    std::map<Node*, int> node_to_index{};
    std::map<std::string, int> variables{};
    std::set<int> taint_sources{};

    CudaTransformer(std::set<std::string> progVariables, int node_count, int node_size) : nodes(node_count, node_size){
        int i = 0;
        variables[TAINT_VAR] = i++;
        variables[RETURN_VAR] = i++;

        std::set<std::string>::iterator it;
        for (it=progVariables.begin(); it!=progVariables.end(); it++){
            if(*it != TAINT_VAR && *it != RETURN_VAR){
                variables[*it] = i++;
            }
        }

    }

    CudaTransformer(std::set<std::string> progVariables, int node_count) : CudaTransformer(progVariables, node_count, sizeof(NodeType)){}

    void visit_assignment(AssignmentNode& node) {
        int id = nodes.size();
        node_to_index[&node] = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(node.id, node.expression);
        add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
        node_struct.join_mask ^= 1 << variables[node.id];
    }

    void visit_return(ReturnNode& node) {
        int id = nodes.size();
        node_to_index[&node] = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(RETURN_VAR, node.expression);
        add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
        node_struct.join_mask = 0;
    }

    void visit_emptyReturn(EmptyReturnNode& node) {
        node_to_index[&node] = nodes.size();
        NodeType& node_struct = nodes.emplace_back();
        node_struct.join_mask = 0;
    }

    void visit_functionEntry(FunctionEntryNode& node) { 
        int id = nodes.size();
        node_to_index[&node] = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.join_mask = 0;
        if(node.arguments.size() >= 1){
            node_struct.first_transfer_index = add_transfer_function(node.formal_parameters[0], node.arguments[0]);
            add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
            int last_index = node_struct.first_transfer_index;

            for (int i = 1; i < node.arguments.size(); i++)
            {
                int current_index = add_transfer_function(node.formal_parameters[i], node.arguments[i]);
                transfer_functions[last_index].next_transfer_index = current_index;
                add_taint_source(id, transfer_functions[current_index]);
                last_index = current_index;
            }
        }
    }

    void visit_assignReturn(AssignReturnNode& node) { 
        int id = nodes.size();
        node_to_index[&node] = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(node.id, {RETURN_VAR});
        add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
        node_struct.join_mask ^= 1 << variables[node.id];
        node_struct.join_mask ^= 1 << variables[RETURN_VAR];
    }

    void visit_arrayAssignment(ArrayAssignmentNode& node) { 
        int id = nodes.size();
        node_to_index[&node] = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(node.id, node.expression);
        add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
        node_struct.join_mask ^= 1 << variables[node.id];
    }
    
    void visit_arrayinit(ArrayInitializerNode& node) { 
        int id = nodes.size();
        node_to_index[&node] = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.join_mask ^= 1 << variables[node.id];

        // Get vars from all array element expressions 
        std::set<std::string> expr_vars;
        for(auto& element : node.arrayContent){
            auto vars = element->get_variables();
            std::set_union(expr_vars.begin(), expr_vars.end(),
                           vars.begin(), vars.end(),
                           std::inserter(expr_vars, expr_vars.begin()));
        }

        node_struct.first_transfer_index = add_transfer_function(node.id, expr_vars);
        add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
    }

    void visit_propagation(PropagationNode& node) { 
        node_to_index[&node] = nodes.size();
        NodeType& node_struct = nodes.emplace_back();
    }

private:
    int add_transfer_function(std::string x, std::set<std::string>& vars){
        int index = transfer_functions.size();
        Transfer& current_transfer = transfer_functions.emplace_back();
        current_transfer.x = variables[x];
        current_transfer.rhs = fill_with_variable_indices(vars);

        return index;
    }

    int add_transfer_function(std::string x, std::set<std::string>&& vars){
        return add_transfer_function(x, vars);
    }

    int add_transfer_function(std::string x, std::shared_ptr<Expression>& expression){
        auto vars = expression->get_variables();
        return add_transfer_function(x, vars);
    }

    BitVector fill_with_variable_indices(std::set<std::string>& vars){
        BitVector result = 0;
        for(std::string var : vars){
            if (variables.count(var)){
                result |= 1<<variables[var];
            }
        }
        return result;
    }

    void add_taint_source(int nodeIndex, Transfer& transfer){
        if((transfer.rhs & 1) == 1){
            taint_sources.insert(nodeIndex);
        }
    }
};

template<typename NodeType>
void add_predecessors(std::vector<std::shared_ptr<Node>>& nodes, CudaTransformer<NodeType>& transformer){
    for(int i = 0; i < nodes.size(); i++){
        int pred_index = 0;
        for (auto pred_it = nodes[i]->predecessors.begin(); pred_it != nodes[i]->predecessors.end(); ++pred_it){
            assert(pred_index < 5);
            transformer.nodes[i].predecessor_index[pred_index++] = transformer.node_to_index[pred_it->get()];
        }
    }
}

template<typename NodeType>
void add_neighbours(std::vector<std::shared_ptr<Node>>& nodes, CudaTransformer<NodeType>& transformer){
    for(int i = 0; i < nodes.size(); i++){
        int pred_index = 0;
        for (auto pred_it = nodes[i]->predecessors.begin(); pred_it != nodes[i]->predecessors.end(); ++pred_it){
            assert(pred_index < 5);
            transformer.nodes[i].predecessor_index[pred_index++] = transformer.node_to_index[pred_it->get()];
        }

        int succ_index = 0;
        for (auto succ = nodes[i]->successors.begin(); succ != nodes[i]->successors.end(); ++succ){
            assert(succ_index < 5);
            transformer.nodes[i].successor_index[succ_index++] = transformer.node_to_index[succ->get()];
        }
    }
}

CudaTransformer<bit_cuda::Node> transform_bit_cuda(std::vector<std::shared_ptr<Node>>& nodes);
CudaTransformer<cuda_worklist::Node> transform_cuda_worklist(std::vector<std::shared_ptr<Node>>& nodes);
CudaTransformer<multi_cuda::Node> transform_multi_cuda(std::vector<std::shared_ptr<Node>>& nodes, int max_taint_sources);