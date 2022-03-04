#include "matrix_analysis.h"
#include <iostream>
#include "GpuManagement.h"
#include "kernel.h"
#include <map>
#include <cfg/transformations/transforms_matrix.h>
#include <cfg/transformations/var_visitor.h>
#include <cfg/digraph.h>
#include <chrono>
#include "timing.h"

void set_node_states(Matrix<float>& state, std::vector<StatefulNode<std::set<std::string>>>& nodes, const std::map<std::string, int>& variables){
    for(int i = 0; i<nodes.size(); i++){
        std::set<std::string> taint_state;
        for (auto it = variables.begin(); it != variables.end(); it++){
            if(state(it->second,i) != 0){
                taint_state.insert(it->first);
            }
        }
        nodes[i].get_state() = taint_state;
    }
}

Matrix<float> get_initial_matrix(int var_count, int node_count){
    Matrix<float> init_state(var_count, node_count);
    for(int i = 0; i<node_count; i++){
        init_state(var_count-1,i) = 1;      // set row of taint variable to 1
    }
    return init_state;
}

std::vector<StatefulNode<std::set<std::string>>> gpu_analysis(std::vector<std::shared_ptr<Node>>& cfg_nodes){
    Stopwatch test_watch;
    test_watch.print_time<Microseconds>("test timer ");

    Stopwatch stopwatch;
    auto variables = get_variables(cfg_nodes);

    // Create transfer matrices
    MatrixTransforms<float> matrixTransformer{variables};
    for(auto& node : cfg_nodes){
        (*node).accept(matrixTransformer);
    }
    
    // Create successor matrix
    auto successor_matrix = get_successor_matrix<float>(cfg_nodes);
    
    Matrix<float> init_state = get_initial_matrix(matrixTransformer.variables.size(), cfg_nodes.size());
    stopwatch.print_time<Microseconds>("Matrix creation ");

    auto result_state = analyse(matrixTransformer.matrices, successor_matrix, init_state).to_matrix();

    std::vector<StatefulNode<std::set<std::string>>> nodes = create_states<std::set<std::string>>(cfg_nodes);
    // Set the tainted state on nodes
    time_func("Move data to cpu: ", 
        set_node_states, result_state, nodes, matrixTransformer.variables);
    return nodes;
}

GpuMatrix analyse(std::vector<Matrix<float>>& transfer_matrices, Matrix<float>& successor_matrix, Matrix<float>& initial_state){

    Stopwatch stopwatch;
    
    std::vector<GpuMatrix> transfers;
    Stopwatch succ_watch;
    GpuMatrix succ(successor_matrix);
    succ_watch.print_time<Microseconds>("Successor matrix allocation ");

    Stopwatch stateWatch;
    GpuMatrix state(initial_state);
    stateWatch.print_time<Microseconds>("State matrix allocation ");

    GpuMatrix next_state(initial_state.rowCount, initial_state.columnCount);
    GpuMatrix result(initial_state.rowCount, initial_state.columnCount);

    // Allocate transfer matrices
    Stopwatch transferWatch;
    for(Matrix<float>& transfer : transfer_matrices) {
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
            next_state.multiply_vector(i, transfers[i]);
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