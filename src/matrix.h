#pragma once

#include <memory>
#include <algorithm>

class Matrix{

    public:
        std::shared_ptr<int[]> matrix;
        int rowSize;

        Matrix(int rowSize): rowSize(rowSize){
            matrix = unit_matrix();
        }

        std::shared_ptr<int[]> unit_matrix(){
            int size = rowSize*rowSize;
            std::shared_ptr<int[]> matrix(new int[size]);
            std::fill(matrix.get(), matrix.get() + size, 0);
            for(int i = 0; i < rowSize; i++){
                matrix.get()[rowSize*i+i] = 1;
            }
            return matrix;
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