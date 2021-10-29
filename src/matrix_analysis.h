#pragma once

#include "matrix.h"
#include <vector>
Matrix<float> analyse(std::vector<Matrix<float>>& transfer_matrices, Matrix<float>& successor_matrix, Matrix<float>& state);