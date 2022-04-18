#include "bit_vector_converter.h"

void set_bit_vector_state(std::vector<StatefulNode<cpu_analysis::BitVector>>& nodes,
                   std::vector<StatefulNode<std::set<std::string>>>& cfg_nodes){     
    for (int i = 0; i < cfg_nodes.size(); i++)
    {
        for (int j = 0; j < cfg_nodes[i].node->entry_node->variable_reduction.size(); ++j)
        {
            if(nodes[i].get_state()[j]){
                auto var_name = cfg_nodes[i].node->entry_node->variable_reduction[j];
                cfg_nodes[i].get_state(i).insert(var_name);
            }
        }                
    }   
}

void set_multi_bit_vector_state(std::vector<StatefulNode<std::vector<cpu_analysis::BitVector>>>& nodes, std::vector<StatefulNode<SourcedTaintState>>& cfg_nodes){
    for (int i = 0; i < cfg_nodes.size(); i++)
    {
        for (int z = 0; z < cfg_nodes[i].node->entry_node->variable_reduction.size(); ++z)
        {
            for(int j = 0; j < nodes[i].get_state().size(); ++j){
                if(nodes[i].get_state()[j][z]){
                    auto var_name = cfg_nodes[i].node->entry_node->variable_reduction[z];
                    cfg_nodes[i].get_state(i)[var_name].insert(i);
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
            for (int j = 0; j < cfg_nodes[i].node->entry_node->variable_reduction.size(); ++j)
            {
                if((nodes[i].data[source] >> j) & 1){
                    auto var_name = cfg_nodes[i].node->entry_node->variable_reduction[j];
                    cfg_nodes[i].get_state(i)[var_name].insert(source);
                }
            }                
        }
    }   
}