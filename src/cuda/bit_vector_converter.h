#pragma once

#include "cuda_data.h"
#include <cfg/cfg.h>

template<typename NodeType>
void set_bit_cuda_state(std::vector<NodeType>& nodes, std::map<std::string, int>& variables, 
                   std::vector<StatefulNode<std::set<std::string>>>& cfg_nodes){     
    for (int i = 0; i < cfg_nodes.size(); i++)
    {
        for (auto& [var_name, var_index] : variables)
        {
            if((nodes[i].data >> var_index) & 1){
                cfg_nodes[i].get_state().insert(var_name);
            }
        }                
    }   
}