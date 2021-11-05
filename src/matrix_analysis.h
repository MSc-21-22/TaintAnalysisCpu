#pragma once

#include "matrix.h"
#include <vector>
#include "cfg.h"
#include "GpuManagement.h"


void gpu_analysis(std::vector<std::shared_ptr<Node<std::set<std::string>>>>& nodes);
GpuMatrix<float> analyse(std::vector<Matrix<float>>& transfer_matrices, Matrix<float>& successor_matrix, Matrix<float>& initial_state);