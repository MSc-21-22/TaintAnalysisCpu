#include "matrix.h"

Matrix unit_matrix(int row_size) {
    Matrix matrix(row_size);
    matrix.to_unit_matrix();
    return matrix;
}

Matrix base_transfer_matrix(int row_size) {
    Matrix matrix(row_size);
    //Set taint constant to 1
    matrix(row_size-1, row_size-1) = 1;
    return matrix;
}