#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <base_analysis.h>

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

void cuda_allocate_memory(void** devPtr, size_t size);

template<typename NodeType>
__device__ BitVector join(int predecessors[], NodeType nodes[], BitVector data[]) {
        BitVector joined_data;
        joined_data.bitfield = 1;

        int pred_index = 0;
        while (pred_index < 5 && predecessors[pred_index] != -1){
            joined_data.bitfield |= data[predecessors[pred_index]].bitfield;
            ++pred_index;
        }
        return joined_data;
}

void cuda_copy_to_device(void *dst, const void *src, size_t size);
void cuda_copy_to_host(void *dst, const void *src, size_t size);
void cuda_free(void* devPtr);
void cuda_memset(void* devPtr, int value, size_t size);

template<typename BitVectorType>
__device__ void transfer_function(int first_transfer_index, Transfer transfers[], BitVectorType& joined_data, BitVectorType& current){
    Transfer* transfer;
    int transfer_index = first_transfer_index;

    while(transfer_index != -1){
        transfer = &transfers[transfer_index];
        if((joined_data.bitfield & transfer->rhs.bitfield) != 0){
            current.bitfield |= (1 << transfer->var_index);
        }
        transfer_index = transfer->next_transfer_index;
    }
}