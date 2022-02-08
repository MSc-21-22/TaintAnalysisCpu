#pragma once
#include "matrix.h"

void create_cublas();
void destroy_cublas();

class GpuResource{
public:
    void* resource;
    int rowCount, columnCount;
    size_t element_size;

    bool self_freeing{true};

    GpuResource(int rowCount, int columnCount, size_t element_size, void* resource) : resource(resource), rowCount(rowCount), columnCount(columnCount), element_size(element_size){
        self_freeing = false;
    }
    GpuResource(int rowCount, int columnCount, size_t element_size);
    GpuResource(int rowCount, int columnCount, void* data_ptr, size_t element_size);

    GpuResource(const GpuResource& other);
    GpuResource(GpuResource&& other) noexcept;
    GpuResource& operator=(const GpuResource& other);
    GpuResource& operator=(GpuResource&& other) noexcept;

    void multiply_f32_to_f32(const GpuResource& operand, GpuResource& result);
    void multiply_vector_f32_to_f32(int offset, const GpuResource& operand);

    void retrieve_from_gpu(void* dst_ptr);
    ~GpuResource();
};

template<typename ElementType>
class GpuMatrix{
public:
    GpuResource resource;
    

    GpuMatrix(const Matrix<ElementType>& matrix) : resource(matrix.rowCount, matrix.columnCount, matrix.matrix, sizeof(ElementType)){
        }

    GpuMatrix(int rows, int columns) : resource(rows, columns, sizeof(ElementType)) {}

    GpuMatrix(const GpuResource& resource) : resource(resource){}
    GpuMatrix(GpuResource&& resource) : resource(resource){}

    GpuMatrix(const ElementType data[], int rows, int columns) : resource(rows, columns, (void*)data, sizeof(ElementType)) {}

    void multiply(GpuMatrix<float>& other, GpuMatrix<float>& result){
        assert(false);
    }

    void multiply_vector(int column_index, GpuMatrix<ElementType>& other){
        assert(false);
    }

    Matrix<ElementType> to_matrix(){
        Matrix<ElementType> result(resource.rowCount, resource.columnCount);
        resource.retrieve_from_gpu(result.matrix);
        return result;
    }
};

template<typename ElementType>
class GpuMemory {
    ElementType* gpu_pointer;
    size_t allocated_size;
public:
    GpuMemory(const MemoryManager<ElementType>& memory);
    ~GpuMemory();

    GpuResource as_gpu_matrix(const Matrix<ElementType>& matrix);
};