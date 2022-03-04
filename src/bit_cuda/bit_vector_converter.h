#pragma once

#include "analysis.h"
#include "bit_cuda_transformer.h"
#include <cfg/cfg.h>

void set_bit_cuda_state(BitCudaTransformer& transformer, 
                   std::vector<StatefulNode<std::set<std::string>>>& nodes){     
    for (int i = 0; i < nodes.size(); i++)
    {
        for (auto& [var_name, var_index] : transformer.variables)
        {
            if((transformer.nodes[i].data >> var_index) & 1){
                nodes[i].get_state().insert(var_name);
            }
        }                
    }   
}