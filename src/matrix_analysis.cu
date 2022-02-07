#include "matrix_analysis.h"
#include <iostream>
#include "GpuManagement.h"
#include "kernel.h"
#include <map>
#include "transforms_matrix.h"
#include "var_visitor.h"
#include "digraph.h"
#include <chrono>
#include "timing.h"

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

void gpu_analysis(std::vector<std::shared_ptr<Node<std::set<std::string>>>>& nodes){
    Stopwatch stopwatch;
    auto variables = get_variables(nodes);

    // Create transfer matrices
    MatrixTransforms<std::set<std::string>, float> matrixTransformer{variables};
    for(auto& node : nodes){
        (*node).accept(matrixTransformer);
    }
    
    // Create successor matrix
    auto successor_matrix = get_successor_matrix<std::set<std::string>, float>(nodes);
    
    Matrix<float> init_state = get_initial_matrix(matrixTransformer.variables.size(), nodes.size());
    stopwatch.print_time<Microseconds>("Matrix creation ");

    auto result_state = analyse(matrixTransformer.matrices, successor_matrix, init_state).to_matrix();

    // Set the tainted state on nodes
    time_func("Move data to cpu: ", 
        set_node_states, result_state, nodes, matrixTransformer.variables);
}

GpuMatrix<float> analyse(std::vector<Matrix<float>>& transfer_matrices, Matrix<float>& successor_matrix, Matrix<float>& initial_state){

    Stopwatch stopwatch;
    
    std::vector<GpuMatrix<float>> transfers;
    Stopwatch succ_watch;
    GpuMatrix<float> succ(successor_matrix);
    succ_watch.print_time<Microseconds>("Successor matrix allocation ");

    Stopwatch stateWatch;
    GpuMatrix<float> state(initial_state);
    stateWatch.print_time<Microseconds>("State matrix allocation ");

    GpuMatrix<float> next_state(initial_state.rowCount, initial_state.columnCount);
    GpuMatrix<float> result(initial_state.rowCount, initial_state.columnCount);

    std::vector<GpuStream> streams(transfer_matrices.size());

    // Allocate transfer matrices
    Stopwatch transferWatch;
    for(Matrix<float>& transfer : transfer_matrices) {
        streams.emplace_back();
        transfers.emplace_back(transfer);
    }
    transferWatch.print_time<Microseconds>("Transfer matrices allocation ");

    stopwatch.print_time<Microseconds>("Gpu memory alloc/copy ");

    
    Stopwatch analysisStopwatch;
    Stopwatch matrixStopwatch;
    Stopwatch memcmpStopwatch;

    while(true){
        matrixStopwatch.start();
        state.multiply(succ, next_state);


        for(int i = 0; i < transfer_matrices.size(); ++i) {
            streams[i].set_as_current();
            next_state.multiply_vector(i, transfers[i]);
        }
        for(int i = 0; i < transfer_matrices.size(); ++i) {
            streams[i].synchronize();
        }
        matrixStopwatch.stop();        

        memcmpStopwatch.start();
        auto cmp = gpu_mem_cmp(state.resource, next_state.resource);
        memcmpStopwatch.stop();

        if(cmp){
            state = next_state;
            break;
        }
        state = next_state;
    }

    analysisStopwatch.print_time<Microseconds>("Least fixed point algorithm ");
    matrixStopwatch.print_time<Microseconds>("matrix math ");
    memcmpStopwatch.print_time<Microseconds>("gpu memcmp ");

    time_func("Cublas destroy: ",
        destroy_cublas);
    
    return state;
}