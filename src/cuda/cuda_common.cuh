#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "cuda_data.h"

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

template<typename NodeType>
__device__ BitVector join(int predecessors[], NodeType nodes[]){
        BitVector joined_data = 1;
        int pred_index = 0;
        while (predecessors[pred_index] != -1){
            joined_data |= nodes[predecessors[pred_index]].data;
            ++pred_index;
        }
        return joined_data;
}

void cuda_copy_to_device(void *dst, const void *src, size_t size);
void cuda_copy_to_host(void *dst, const void *src, size_t size);
void cuda_free(void* devPtr);