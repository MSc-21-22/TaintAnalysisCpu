#pragma once
#include "matrix.h"

void create_cublas();
void destroy_cublas();

class GpuResource{
public:
    void* resource;
    int rowCount, columnCount;
    size_t element_size;

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

class GpuMatrix{
public:
    GpuResource resource;
    
    GpuMatrix(const Matrix<float>& matrix) : resource(matrix.rowCount, matrix.columnCount, matrix.matrix.get(), sizeof(float)){
    }

    GpuMatrix(int rows, int columns) : resource(rows, columns, sizeof(float)) {}

    GpuMatrix(const GpuResource& resource) : resource(resource){}

    GpuMatrix(const float data[], int rows, int columns) : resource(rows, columns, (void*)data, sizeof(float)) {}

    void multiply(GpuMatrix& other, GpuMatrix& result);

    void multiply_vector(int column_index, GpuMatrix& other);

    Matrix<float> to_matrix(){
        Matrix<float> result(resource.rowCount, resource.columnCount);
        resource.retrieve_from_gpu(result.matrix.get());
        return result;
    }
};