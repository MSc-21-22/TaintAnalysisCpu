#pragma once

#include "matrix.h"
#include <vector>
#include "cfg.h"

void gpu_analysis(std::vector<std::shared_ptr<Node<std::set<std::string>>>> nodes);
Matrix<float> analyse(std::vector<Matrix<float>>& transfer_matrices, Matrix<float>& successor_matrix, Matrix<float>& state);