#pragma once

template<typename ReturnType>
ReturnType* cuda_allocate_memory(size_t size){
    void* devPtr;
    auto cudaStatus = cudaMalloc(&devPtr, size);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed: %s\n", cudaGetErrorString(cudaStatus));
        exit(1);
    }
    return (ReturnType*)devPtr;
}

void cuda_copy_to_device(void *dst, const void *src, size_t size);
void cuda_copy_to_host(void *dst, const void *src, size_t size);
void cuda_free(void* devPtr);