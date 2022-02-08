#pragma once

#include <memory>
#include <algorithm>
#include <assert.h>

template<typename ElementType>
class MemoryManager {
public:
    ElementType* memory;
    size_t current_offset;
    MemoryManager() {
        memory = nullptr;
        current_offset = 0;
    }
    MemoryManager(size_t max_size) {
        memory = new ElementType[max_size];
    }

    ~MemoryManager() {
        delete memory;
    }

    size_t allocate(ElementType*& ptr, size_t size) {
        ptr = memory + current_offset;
        auto old_offset = current_offset;
        current_offset += size;
        return old_offset;
    }
};

void init_memory(size_t max_size);
MemoryManager<float>& get_custom_memory();
void free_manager();

template<typename ElementType>
class Matrix{

    public:
        ElementType* matrix;
        size_t memory_offset;
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
                matrix[rowCount*i+i] = 1.0f;
            }
        }

        ElementType& operator()(int row, int column){
            return matrix[row+column*rowCount];
        }

        std::string to_string(){
            std::string res;
            for(int row = 0; row<rowCount; row++){
                for(int column = 0; column<columnCount; column++){
                    res += std::to_string((int)(matrix[row+column*rowCount]));
                }
                res += "\n";
            }
            return res;
        }

    private:
        void create_matrix(){
            size = rowCount*columnCount;
            memory_offset = get_custom_memory().allocate(matrix, size * sizeof(ElementType));
            std::fill(matrix, matrix + size, 0);
        }
};

template<typename ElementType>
Matrix<ElementType> unit_matrix(int row_size) {
    Matrix<ElementType> matrix(row_size);
    matrix.to_unit_matrix();
    return matrix;
}

template<typename ElementType>
Matrix<ElementType> base_transfer_matrix(int row_size) {
    Matrix<ElementType> matrix(row_size);
    //Set taint constant to 1
    matrix(row_size-1, row_size-1) = 1.0f;
    return matrix;
}