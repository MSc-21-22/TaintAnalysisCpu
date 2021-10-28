#pragma once

#include <memory>
#include <algorithm>
#include <assert.h>

class Matrix{

    public:
        std::shared_ptr<int[]> matrix;
        int rowCount;
        int columnCount;
        int size;

        Matrix(int rowCount): rowCount(rowCount), columnCount(rowCount){
            create_matrix();
        }

        Matrix(int rowCount, int columnCount) : rowCount(rowCount), columnCount(columnCount){
            create_matrix();
        }

        void to_unit_matrix(){
            assert(rowCount==columnCount);
            for(int i = 0; i < rowCount; i++){
                matrix.get()[rowCount*i+i] = 1;
            }
        }

        int& operator()(int row, int column){
            return matrix.get()[row+column*rowCount];
        }

        std::string to_string(){
            std::string res;
            for(int row = 0; row<rowCount; row++){
                for(int column = 0; column<columnCount; column++){
                    res += std::to_string(matrix.get()[row+column*rowCount]);
                }
                res += " ";
            }
            return res;
        }

    private:
        void create_matrix(){
            size = rowCount*columnCount;
            std::shared_ptr<int[]> new_matrix(new int[size]);
            matrix = new_matrix;
            std::fill(matrix.get(), matrix.get() + size, 0);
        }
};

Matrix unit_matrix(int row_size);

Matrix base_transfer_matrix(int row_size);