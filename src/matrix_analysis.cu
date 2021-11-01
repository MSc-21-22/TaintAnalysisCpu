#include "matrix_analysis.h"
#include <iostream>
#include "GpuManagement.h"
#include "kernel.h"

Matrix<float> analyse(std::vector<Matrix<float>>& transfer_matrices, Matrix<float>& successor_matrix, Matrix<float>& initial_state){
    create_cublas();
    std::vector<GpuMatrix<float>> transfers;
    GpuMatrix<float> succ(successor_matrix);
    GpuMatrix<float> state(initial_state);
    GpuMatrix<float> result(initial_state.rowCount, initial_state.columnCount);
    // Allocate transfer matrices
    for(Matrix<float>& transfer : transfer_matrices) {
        GpuMatrix<float> mama_mia(transfer);
        transfers.push_back(std::move(mama_mia));
    }
    
    while(true){
        GpuMatrix<float> next_state = state.multiply(succ);
    
        for(int i = 0; i < transfer_matrices.size(); ++i) {
            next_state.multiply_vector(i, transfers[i]);
        }


        if(gpu_mem_cmp(state.resource, next_state.resource)){
            break;
        }
        state = next_state;
    }

    Matrix<float> output = state.to_matrix();

    destroy_cublas();
    
    return output;
}