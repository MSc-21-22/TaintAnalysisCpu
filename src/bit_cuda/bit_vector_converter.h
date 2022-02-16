#pragma once

#include "analysis.h"
#include "bit_cuda_transformer.h"
#include <cfg.h>

template<typename K, typename V>
static std::map<V, K> reverse_map(const std::map<K, V>& m) {
    std::map<V, K> r;
    for (const auto& kv : m)
        r[kv.second] = kv.first;
    return r;
}

void set_bit_cuda_state(BitCudaTransformer<std::set<std::string>>& transformer, 
                   std::vector<std::shared_ptr<Node<std::set<std::string>>>>& nodes){
                
    std::map<int, std::string> variables = reverse_map(transformer.variables);          

    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = 0; j < variables.size(); j++)
        {
            if((transformer.nodes[i].data.data >> j) & 1){
                nodes[i]->state.insert(variables[j]);
            }
        }                
    }   
}