#include "matrix_analysis.h"
#include <iostream>
#include "GpuManagement.h"
#include "kernel.h"
#include <map>
#include "transforms_matrix.h"
#include "var_visitor.h"
#include "digraph.h"
#include <chrono>

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
    auto start = std::chrono::system_clock::now();
    auto variables = get_variables(nodes);

    // Create transfer matrices
    MatrixTransforms<std::set<std::string>, float> matrixTransformer{variables};
    for(auto& node : nodes){
        (*node).accept(matrixTransformer);
    }
    
    // Create successor matrix
    auto successor_matrix = get_successor_matrix<std::set<std::string>, float>(nodes);
    
    Matrix<float> init_state = get_initial_matrix(matrixTransformer.variables.size(), nodes.size());
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Matrix creation " << diff.count() << "s\n";

    auto result_state = analyse(matrixTransformer.matrices, successor_matrix, init_state).to_matrix();


    start = std::chrono::system_clock::now();
    set_node_states(result_state, nodes, matrixTransformer.variables);
    end = std::chrono::system_clock::now();
    diff = end - start;
    std::cout << "Move data to cpu " << diff.count() << "s\n";
    // Set the tainted state on nodes
}

GpuMatrix<float> analyse(std::vector<Matrix<float>>& transfer_matrices, Matrix<float>& successor_matrix, Matrix<float>& initial_state){
    auto start = std::chrono::system_clock::now();
    create_cublas(); 
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Cublas creation " << diff.count() << "s\n";


    start = std::chrono::system_clock::now();
    
    std::vector<GpuMatrix<float>> transfers;
    GpuMatrix<float> succ(successor_matrix);
    GpuMatrix<float> state(initial_state);
    GpuMatrix<float> result(initial_state.rowCount, initial_state.columnCount);
    // Allocate transfer matrices
    for(Matrix<float>& transfer : transfer_matrices) {
        transfers.emplace_back(transfer);
    }

    end = std::chrono::system_clock::now();
    diff = end - start;
    std::cout << "Gpu memory alloc/copy " << diff.count() << "s\n";

    
    start = std::chrono::system_clock::now();

    std::chrono::duration<double> matrix_diff;
    std::chrono::duration<double> memcmp_diff;

    while(true){
        auto _start = std::chrono::system_clock::now();
        GpuMatrix<float> next_state = state.multiply(succ);


        for(int i = 0; i < transfer_matrices.size(); ++i) {
            next_state.multiply_vector(i, transfers[i]);
        }
        auto _end = std::chrono::system_clock::now();
        matrix_diff += _end - _start;
        

        _start = std::chrono::system_clock::now();
        auto cmp = gpu_mem_cmp(state.resource, next_state.resource);
        _end = std::chrono::system_clock::now();
        memcmp_diff += _end - _start;

        if(cmp){
            state = next_state;
            break;
        }
        state = next_state;
    }

    end = std::chrono::system_clock::now();
    diff = end - start;
    std::cout << "analysis " << diff.count() << "s\n";
    std::cout << "matrix math " << matrix_diff.count() << "s\n";
    std::cout << "gpu memcmp " << memcmp_diff.count() << "s\n";


    start = std::chrono::system_clock::now();
    destroy_cublas();
    end = std::chrono::system_clock::now();
    diff = end - start;
    std::cout << "cublas destroy " << diff.count() << "s\n";

    
    return state;
}