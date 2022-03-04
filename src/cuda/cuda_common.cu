#include <stdio.h>

void cuda_allocate_memory(void **devPtr, size_t size){
    auto cudaStatus = cudaMalloc(devPtr, size);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed: %s\n", cudaGetErrorString(cudaStatus));
        exit(1);
    }
}

void cuda_copy_to_device(void *dst, const void *src, size_t size){
    auto cudaStatus = cudaMemcpy(dst, src, size, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy to gpu failed: %s\n", cudaGetErrorString(cudaStatus));
        exit(1);
    }
}

void cuda_copy_to_host(void *dst, const void *src, size_t size){
    auto cudaStatus = cudaMemcpy(dst, src, size, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy to host failed: %s\n", cudaGetErrorString(cudaStatus));
        exit(1);
    }
}

void cuda_free(void* devPtr){
    auto cudaStatus = cudaFree(devPtr);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaFree failed: %s\n", cudaGetErrorString(cudaStatus));
        exit(1);
    }
}