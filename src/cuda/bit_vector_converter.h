#pragma once

#include "cuda_data.h"
#include "multi_cuda/analysis.h"
#include <cfg/cfg.h>
#include <taint_analysis.h>
#include <multi_taint_analysis.h>

template<typename NodeType>
void set_bit_cuda_state(DynamicArray<NodeType>& nodes, std::vector<StatefulNode<std::set<std::string>>>& cfg_nodes){
    for (int i = 0; i < cfg_nodes.size(); i++)
    {
        for (auto& [var_name, var_index] : cfg_nodes[i].node->entry_node->variable_reduction)
        {
            if(((1 << var_index) & (nodes[i].data)) != 0){
                cfg_nodes[i].get_state().insert(var_name.data());
            }
        }                
    }   
}

void set_bit_vector_state(std::vector<StatefulNode<cpu_analysis::BitVector>>& nodes, std::vector<StatefulNode<std::set<std::string>>>& cfg_nodes);
void set_multi_bit_vector_state(std::vector<StatefulNode<std::vector<cpu_analysis::BitVector>>>& nodes, std::vector<StatefulNode<SourcedTaintState>>& cfg_nodes);
void set_bit_cuda_multi_state(DynamicArray<multi_cuda::Node>& nodes, int source_count, std::vector<StatefulNode<SourcedTaintState>>& cfg_nodes);