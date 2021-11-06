#include <cublas.h>
#include <iostream>
#include <assert.h>
#include "GpuManagement.h"
#include <cuda.h>

static cublasHandle_t handle;

cublasHandle_t get_cublas(){
    return handle;
}
void create_cublas(){
    cudaSetDevice(0);
    if(cublasCreate_v2(&handle) != CUBLAS_STATUS_SUCCESS){
        std::cout << "Create cublas failed" << std::endl;
    }
}
void destroy_cublas(){
    cublasDestroy_v2(handle);
}

GpuResource::GpuResource(int rowCount, int columnCount, void* data_ptr, size_t element_size){
    this->rowCount = rowCount;
    this->columnCount = columnCount;
    this->element_size = element_size;
    if(cudaMalloc(&resource, element_size*rowCount*columnCount) != 0){
        std::cout << "allocation of matrix failed" << std::endl;
    }
    if(cublasSetMatrix(rowCount, columnCount, element_size, data_ptr, rowCount, resource, rowCount) != CUBLAS_STATUS_SUCCESS){
        std::cout << "setMatrix of matrix failed" << std::endl;
    }
}

GpuResource::GpuResource(int rowCount, int columnCount, size_t element_size): rowCount(rowCount), columnCount(columnCount){
    this->element_size = element_size;
    if(cublasAlloc(rowCount*columnCount, element_size, &resource) != CUBLAS_STATUS_SUCCESS){
        std::cout << "allocation of resource failed" << std::endl;
    }
}

GpuResource::GpuResource(const GpuResource& other){
    this->rowCount = other.rowCount;
    this->columnCount = other.columnCount;
    this->element_size = other.element_size;
    size_t size = element_size*rowCount*columnCount;
    if(cudaMalloc(&resource, size) != 0){
        std::cout << "allocation of matrix failed" << std::endl;
    }

    if(cudaMemcpy(resource, other.resource, size, cudaMemcpyDeviceToDevice) != 0){
        std::cout << "Failed to copy gpu matrix to new gpu matrix" << std::endl;
    }
}
GpuResource::GpuResource(GpuResource&& other) noexcept{
    rowCount = other.rowCount;
    other.rowCount = 0;

    columnCount = other.columnCount;
    other.columnCount = 0;

    element_size = other.element_size;
    other.element_size = 0;

    resource = other.resource;
    other.resource = nullptr;
}
GpuResource& GpuResource::operator=(const GpuResource& other){
    //Deallocate old resource first
    cudaFree(resource);

    this->rowCount = other.rowCount;
    this->columnCount = other.columnCount;
    this->element_size = other.element_size;
    size_t size = element_size*rowCount*columnCount;
    if(cudaMalloc(&resource, size) != 0){
        std::cout << "allocation of matrix failed" << std::endl;
    }

    if(cudaMemcpy(resource, other.resource, size, cudaMemcpyDeviceToDevice) != 0){
        std::cout << "Failed to copy gpu matrix to new gpu matrix" << std::endl;
    }
    return *this;
}
GpuResource& GpuResource::operator=(GpuResource&& other) noexcept{
    //Deallocate old resource first
    cudaFree(resource);

    rowCount = other.rowCount;
    other.rowCount = 0;

    columnCount = other.columnCount;
    other.columnCount = 0;

    element_size = other.element_size;
    other.element_size = 0;

    resource = other.resource;
    other.resource = nullptr;
    return *this;
}

void GpuResource::retrieve_from_gpu(void* dst_ptr){
    auto status = cublasGetMatrix(rowCount, columnCount, element_size, resource, rowCount, dst_ptr, rowCount);
    if(status != CUBLAS_STATUS_SUCCESS){
        std::cout << "cublas_get_matrix failed with " << status << std::endl;
    }
}

void GpuResource::multiply_f32_to_f32(const GpuResource& operand, GpuResource& result){
    assert(rowCount == result.rowCount);
    assert(operand.columnCount == result.columnCount);
    assert(columnCount == operand.rowCount);
    float alpha = 1;
    float beta = 0;
    auto status = cublasSgemm_v2(get_cublas(), CUBLAS_OP_N, CUBLAS_OP_N, 
        rowCount, operand.columnCount, columnCount,
        &alpha, (float*)resource, rowCount,
        (float*)operand.resource, operand.rowCount,
        &beta, (float*)result.resource, result.rowCount);

    if(status != CUBLAS_STATUS_SUCCESS) {
        std::cout << "Matrix multiplication failed with " << status << std::endl;
    }
}    


void GpuResource::multiply_vector_f32_to_f32(int offset, const GpuResource& operand){
    float* float_resource = (float*)resource;

    float alpha = 1;
    float beta = 0;
    auto status = cublasSgemv_v2(get_cublas(), CUBLAS_OP_N, 
        operand.rowCount, operand.columnCount,
        &alpha,
        (float *)operand.resource, operand.rowCount,
        float_resource + offset, 1, 
        &beta, float_resource + offset, 1);

    if(status != CUBLAS_STATUS_SUCCESS) {
        std::cout << "Matrix vector multiplication failed with " << status << std::endl;
    }
}

GpuResource::~GpuResource(){
    cudaFree(resource);
}


template<>
GpuMatrix<float> GpuMatrix<float>::multiply(GpuMatrix<float>& other) {
    GpuMatrix<float> result(resource.rowCount, resource.columnCount);
    resource.multiply_f32_to_f32(other.resource, result.resource);
    return result;
}

template<>
void GpuMatrix<float>::multiply_vector(int column_index, GpuMatrix<float>& other){
    int offset = column_index * resource.rowCount;
    resource.multiply_vector_f32_to_f32(offset, other.resource);
}