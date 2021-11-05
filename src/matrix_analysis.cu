#include "matrix_analysis.h"
#include <iostream>
#include "GpuManagement.h"
#include "kernel.h"
#include <map>
#include "transforms_matrix.h"
#include "var_visitor.h"
#include "digraph.h"

void set_node_states(Matrix<float>& state, std::vector<std::shared_ptr<Node<std::set<std::string>>>>& nodes, const std::map<std::string, int>& variables){
    for(int i = 0; i<nodes.size(); i++){
        std::set<std::string> taint_state;
        for (auto it = variables.begin(); it != variables.end(); it++){
            if(state(it->second,i) != 0){
                taint_state.insert(it->first);
            }
        }
        nodes[i]->state = taint_state;
    }
}

Matrix<float> get_initial_matrix(int var_count, int node_count){
    Matrix<float> init_state(var_count, node_count);
    for(int i = 0; i<node_count; i++){
        init_state(var_count-1,i) = 1;      // set row of taint variable to 1
    }
    return init_state;
}

std::set<std::string> get_variables(std::vector<std::shared_ptr<Node<std::set<std::string>>>>& nodes){
    VarVisitor<std::set<std::string>> varAnalyzer;
    for(auto& node : nodes){
        (*node).accept(varAnalyzer);
    }
    return varAnalyzer.variables;
}

void gpu_analysis(std::vector<std::shared_ptr<Node<std::set<std::string>>>>& nodes){
    
    auto variables = get_variables(nodes);

    // Create transfer matrices
    MatrixTransforms<std::set<std::string>, float> matrixTransformer{variables};
    for(auto& node : nodes){
        (*node).accept(matrixTransformer);
    }
    
    // Create successor matrix
    auto successor_matrix = get_successor_matrix<std::set<std::string>, float>(nodes);
    
    Matrix<float> init_state = get_initial_matrix(matrixTransformer.variables.size(), nodes.size());
    auto result_state = analyse(matrixTransformer.matrices, successor_matrix, init_state).to_matrix();

    // Set the tainted state on nodes
    set_node_states(result_state, nodes, matrixTransformer.variables);
}

GpuMatrix<float> analyse(std::vector<Matrix<float>>& transfer_matrices, Matrix<float>& successor_matrix, Matrix<float>& initial_state){
    create_cublas();
    std::vector<GpuMatrix<float>> transfers;
    GpuMatrix<float> succ(successor_matrix);
    GpuMatrix<float> state(initial_state);
    GpuMatrix<float> result(initial_state.rowCount, initial_state.columnCount);
    // Allocate transfer matrices
    for(Matrix<float>& transfer : transfer_matrices) {
        transfers.emplace_back(transfer);
    }
    
    int i = 0;
    while(true){
        GpuMatrix<float> next_state = state.multiply(succ);

        for(int i = 0; i < transfer_matrices.size(); ++i) {
            next_state.multiply_vector(i, transfers[i]);
        }
        
        if(i > 19 && gpu_mem_cmp(state.resource, next_state.resource)){
            i++;
        state = next_state;
            break;
        }
        i++;
        state = next_state;
    }
    std::cout << "Analysis took " << i << " iterations \n";

    destroy_cublas();
    
    return state;
}