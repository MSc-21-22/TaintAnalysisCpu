#pragma once

#include "analysis.h"
#include "bit_cuda_transformer.h"
#include <cfg.h>

void set_bit_cuda_state(BitCudaTransformer<std::set<std::string>>& transformer, 
                   std::vector<std::shared_ptr<Node<std::set<std::string>>>>& nodes){     
    for (int i = 0; i < nodes.size(); i++)
    {
        for (auto& [var_name, var_index] : transformer.variables)
        {
            if((transformer.nodes[i].data.data >> var_index) & 1){
                nodes[i]->state.insert(var_name);
            }
        }                
    }   
}