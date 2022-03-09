#include <stdio.h>
#include <cuda/cuda_common.cuh>
#include <cuda/common.h>

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

void init_gpu(){
    auto cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        return;
    }

    int* x = cuda_allocate_memory<int>(4);
    cuda_free(x);
}