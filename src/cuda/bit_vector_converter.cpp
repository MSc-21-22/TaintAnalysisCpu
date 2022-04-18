#include "bit_vector_converter.h"

void set_bit_vector_state(std::vector<StatefulNode<cpu_analysis::BitVector>>& nodes,
                   std::vector<StatefulNode<std::set<std::string>>>& cfg_nodes){     
    for (int i = 0; i < cfg_nodes.size(); i++)
    {
        for (auto& [var_name, var_index] : cfg_nodes[i].node->entry_node->variable_reduction)
        {
            if(nodes[i].get_state()[var_index]){
                cfg_nodes[i].get_state().insert(var_name);
            }
        }                
    }   
}

void set_multi_bit_vector_state(std::vector<StatefulNode<std::vector<cpu_analysis::BitVector>>>& nodes, std::vector<StatefulNode<SourcedTaintState>>& cfg_nodes){
    for (int i = 0; i < cfg_nodes.size(); i++)
    {
        for (auto& [var_name, var_index] : cfg_nodes[i].node->entry_node->variable_reduction)
        {
            for(int j = 0; j < nodes[i].get_state().size(); ++j){
                if(nodes[i].get_state()[j][var_index]){
                    cfg_nodes[i].get_state()[var_name].insert(i);
                }
            }
        }                
    }
}

void set_bit_cuda_multi_state(DynamicArray<multi_cuda::Node>& nodes, int source_count, std::vector<StatefulNode<SourcedTaintState>>& cfg_nodes){     
    for (int i = 0; i < cfg_nodes.size(); i++)
    {
        for(int source = 0; source < source_count; ++source) 
        {
            for (auto& [var_name, var_index] : cfg_nodes[i].node->entry_node->variable_reduction)
            {
                if((nodes[i].data[source] >> var_index) & 1){
                    cfg_nodes[i].get_state()[var_name].insert(source);
                }
            }                
        }
    }   
}