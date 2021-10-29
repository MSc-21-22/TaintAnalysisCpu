#include <cublas.h>
#include <iostream>
#include <assert.h>
#include "GpuManagement.h"

static cublasHandle_t handle;

cublasHandle_t get_cublas(){
    return handle;
}
void create_cublas(){
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
    if(cublasAlloc(rowCount*columnCount, element_size, &resource) != CUBLAS_STATUS_SUCCESS){
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

void GpuResource::retrieve_from_gpu(void* dst_ptr){
    std::cout << "Retrieving "<<rowCount << "x"<<columnCount << " with "<<element_size << std::endl;
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
    auto status = cublasSgemmEx(get_cublas(), CUBLAS_OP_N, CUBLAS_OP_N, 
        operand.rowCount, operand.columnCount, columnCount,
        &alpha, resource, CUDA_R_32F, rowCount,
        operand.resource, CUDA_R_32F, operand.rowCount,
        &beta, result.resource, CUDA_R_32F, result.rowCount);

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
        std::cout << "Matrix multiplication failed with " << status << std::endl;
    }
}

GpuResource::~GpuResource(){
    cublasFree(resource);
}


template<>
GpuMatrix<float> GpuMatrix<float>::multiply(GpuMatrix<float>& other) {
    GpuMatrix<float> result(resource.rowCount, resource.columnCount);
    resource.multiply_f32_to_f32(other.resource, result.resource);
    return result;
}

template<>
void GpuMatrix<float>::multiply_vector(int column_index, GpuMatrix<float>& other){
    int offset = column_index * resource.columnCount;
    resource.multiply_vector_f32_to_f32(offset, other.resource);
}