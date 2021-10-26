#pragma once

#include <memory>
#include <algorithm>

class Matrix{

    public:
        std::shared_ptr<int[]> matrix;
        int rowSize;

        Matrix(int rowSize): rowSize(rowSize){
            std::shared_ptr<int[]> new_matrix(new int[rowSize * rowSize]);
            matrix = new_matrix;
        }

        void to_unit_matrix(){
            int size = rowSize*rowSize;
            std::fill(matrix.get(), matrix.get() + size, 0);
            for(int i = 0; i < rowSize; i++){
                matrix.get()[rowSize*i+i] = 1;
            }
        }

        int& operator()(int row, int column){
            return matrix.get()[rowSize*row+column];
        }

        std::string to_string(){
            std::string res;
            for(int i = 0; i<rowSize; i++){
                for(int j = 0; j<rowSize; j++){
                    res += std::to_string(matrix.get()[i*rowSize+j]);
                }
                res += " ";
            }
            return res;
        }
};

Matrix unit_matrix(int row_size) {
    Matrix matrix(row_size);
    matrix.to_unit_matrix();
    return matrix;
}

Matrix empty_matrix(int row_size) {
    Matrix matrix(row_size);
    //Set taint constant to 1
    matrix(row_size, row_size) = 1;
    return matrix;
}