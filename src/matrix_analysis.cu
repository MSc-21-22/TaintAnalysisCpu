#include "matrix_analysis.h"
#include <iostream>
#include "GpuManagement.h"


Matrix<float> analyse(std::vector<Matrix<float>>& transfer_matrices, Matrix<float>& successor_matrix, Matrix<float>& initial_state){
    std::vector<GpuMatrix<float>> transfers;
    GpuMatrix<float> succ(successor_matrix);
    GpuMatrix<float> state(initial_state);
    GpuMatrix<float> result(initial_state.rowCount, initial_state.columnCount);
    // Allocate transfer matrices
    for(auto& transfer : transfer_matrices) {
        transfers.push_back(GpuMatrix<float>(transfer));
    }
    
    create_cublas();

    int i = 0;
    i++;
    GpuMatrix<float> next_state = state.multiply(succ);







    destroy_cublas();
    
    return next_state.to_matrix();
}