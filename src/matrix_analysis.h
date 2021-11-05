#pragma once

#include "matrix.h"
#include <vector>
#include "cfg.h"
#include <map>
#include <functional>
#include <iostream>


void gpu_analysis(std::vector<std::shared_ptr<Node<std::set<std::string>>>>& nodes, std::vector<std::shared_ptr<FunctionEntryNode<std::set<std::string>>>>& entryNodes);
Matrix<float> analyse(std::vector<Matrix<float>>& transfer_matrices, Matrix<float>& successor_matrix, Matrix<float>& state);

template<typename LatticeType>
auto print_matrix(std::vector<std::shared_ptr<Node<LatticeType>>>& nodes, std::map<std::string, int>& variables, Matrix<float>& result_matrix){
    std::map<void*, int> node_to_index;

    int i = 0;
    for(auto& node: nodes){
        node_to_index[&node->state] = i++;
    }

    return [node_to_index, result_matrix, variables](LatticeType& state, std::ostream& stream) mutable {
        stream << '\n';
        for(auto it=variables.begin(); it!=variables.end(); it++){
            float value = result_matrix(it->second, node_to_index[&state]);
            stream << it->first << ' ' << value << '\n';
        }
    };
} 

template<typename LatticeType>
auto print_full_matrix(std::vector<std::shared_ptr<Node<LatticeType>>>& nodes, std::map<std::string, int>& variables, std::vector<Matrix<float>>& result_matrices){
    std::map<void*, int> node_to_index;

    int i = 0;
    for(auto& node: nodes){
        node_to_index[&node->state] = i++;
    }

    return [node_to_index, result_matrices, variables](LatticeType& state, std::ostream& stream) mutable {
        stream << '\n';
        stream << result_matrices[node_to_index[&state]].to_string();
    };
} 