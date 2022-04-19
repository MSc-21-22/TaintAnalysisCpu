#pragma once

#include "cuda_data.h"
#include "bit_cuda/analysis.h"
#include "cuda_worklist/analysis.h"
#include "multi_cuda/analysis.h"
#include <cfg/cfg.h>
#include <cfg/transformations/var_visitor.h>
#include <cfg/transformations/taint_locator.h>
#include <taint_analysis.h>
#include <assert.h>

template <typename NodeType>
class CudaTransformer : public CfgVisitor
{
public:
    DynamicArray<NodeType> nodes;
    std::vector<cuda::Transfer> transfer_functions{};
    std::set<int> taint_sources{};

    CudaTransformer(int node_count, int node_size) : nodes(node_count, node_size){}
    CudaTransformer(int node_count) : CudaTransformer(node_count, sizeof(NodeType)){}

    void visit_assignment(AssignmentNode& node) {
        int id = nodes.size();
        node.node_index = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(node.var_index, node.expression);
        add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
        node_struct.join_mask ^= 1 << node.var_index;
    }

    void visit_return(ReturnNode& node) {
        int id = nodes.size();
        node.node_index = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(RETURN_VAR_INDEX, node.expression);
        add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
        node_struct.join_mask = 0;
    }

    void visit_emptyReturn(EmptyReturnNode& node) {
        node.node_index = nodes.size();
        NodeType& node_struct = nodes.emplace_back();
        node_struct.join_mask = 0;
    }

    void visit_functionEntry(FunctionEntryNode& node) { 
        int id = nodes.size();
        node.node_index = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.join_mask = 0;
        if(node.arguments.size() >= 1){
            node_struct.first_transfer_index = add_transfer_function(node.formal_parameter_indexes[0], node.arguments[0]);
            add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
            int last_index = node_struct.first_transfer_index;

            for (int i = 1; i < node.arguments.size(); i++)
            {
                int current_index = add_transfer_function(node.formal_parameter_indexes[i], node.arguments[i]);
                transfer_functions[last_index].next_transfer_index = current_index;
                add_taint_source(id, transfer_functions[current_index]);
                last_index = current_index;
            }
        }
    }

    void visit_assignReturn(AssignReturnNode& node) { 
        int id = nodes.size();
        node.node_index = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(node.var_index, cuda::BitVector(1 << RETURN_VAR_INDEX));
        add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
        node_struct.join_mask ^= 1 << node.var_index;
        node_struct.join_mask ^= 1 << RETURN_VAR_INDEX;
    }

    void visit_arrayAssignment(ArrayAssignmentNode& node) { 
        int id = nodes.size();
        node.node_index = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.first_transfer_index = add_transfer_function(node.var_index, node.expression);
        add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
        node_struct.join_mask ^= 1 << node.var_index;
    }
    
    void visit_arrayinit(ArrayInitializerNode& node) { 
        int id = nodes.size();
        node.node_index = id;
        NodeType& node_struct = nodes.emplace_back();

        node_struct.join_mask ^= 1 << node.var_index;

        // Get vars from all array element expressions
        cuda::BitVector rhs(0);
        for(auto& element : node.arrayContent){
            element->each_variable([&rhs](int index) {
                rhs |= 1 << index;
            });
        }

        node_struct.first_transfer_index = add_transfer_function(node.var_index, rhs);
        add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
    }

    void visit_propagation(PropagationNode& node) { 
        node.node_index = nodes.size();
        NodeType& node_struct = nodes.emplace_back();
    }

private:


    int add_transfer_function(int x, std::shared_ptr<Expression>& expression){
        int index = transfer_functions.size();
        cuda::Transfer& current_transfer = transfer_functions.emplace_back();
        current_transfer.x = x;

        expression->each_variable([&](int var_index) {
            current_transfer.rhs |= 1 << var_index;
        });

        return index;
    }

    int add_transfer_function(int x, cuda::BitVector rhs) {
        int index = transfer_functions.size();
        cuda::Transfer& current_transfer = transfer_functions.emplace_back();
        current_transfer.x = x;
        current_transfer.rhs = rhs;

        return index;
    }

    void add_taint_source(int nodeIndex, cuda::Transfer& transfer){
        if((transfer.rhs & 1) == 1){
            taint_sources.insert(nodeIndex);
        }
    }
};

template<typename NodeType>
void add_predecessors(std::vector<std::shared_ptr<Node>>& nodes, CudaTransformer<NodeType>& transformer){
    for(int i = 0; i < nodes.size(); i++){
        int pred_index = 0;
        for (auto& pred : nodes[i]->predecessors) {
            transformer.nodes[i].predecessor_index[pred_index++] = pred->node_index;
        }
    }
}

template<typename NodeType>
void add_neighbours(std::vector<std::shared_ptr<Node>>& nodes, CudaTransformer<NodeType>& transformer){
    for(int i = 0; i < nodes.size(); i++){
        int pred_index = 0;
        for (auto& pred : nodes[i]->predecessors) {
            transformer.nodes[i].predecessor_index[pred_index++] = pred->node_index;
        }

        int succ_index = 0;
        for (auto& succ : nodes[i]->successors){
            transformer.nodes[i].successor_index[succ_index++] = succ->node_index;
        }
    }
}

CudaTransformer<bit_cuda::Node> transform_bit_cuda(std::vector<std::shared_ptr<Node>>& nodes);
CudaTransformer<cuda_worklist::Node> transform_cuda_worklist(std::vector<std::shared_ptr<Node>>& nodes);
CudaTransformer<multi_cuda::Node> transform_multi_cuda(std::vector<std::shared_ptr<Node>>& nodes, int max_taint_sources);