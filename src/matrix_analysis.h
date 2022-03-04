#pragma once

#include "matrix.h"
#include <vector>
#include <cfg/cfg.h>
#include "GpuManagement.h"


std::vector<StatefulNode<std::set<std::string>>> gpu_analysis(std::vector<std::shared_ptr<Node>>& cfg_nodes);
GpuMatrix analyse(std::vector<Matrix<float>>& transfer_matrices, Matrix<float>& successor_matrix, Matrix<float>& initial_state);