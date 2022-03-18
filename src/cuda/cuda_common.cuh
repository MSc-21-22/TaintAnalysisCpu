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
        while (pred_index < 5 && predecessors[pred_index] != -1){
            joined_data |= nodes[predecessors[pred_index]].data;
            ++pred_index;
        }
        return joined_data;
}

void cuda_copy_to_device(void *dst, const void *src, size_t size);
void cuda_copy_to_host(void *dst, const void *src, size_t size);
void cuda_free(void* devPtr);

template<typename BitVectorType>
__device__ void transfer_function(int first_transfer_index, Transfer transfers[], BitVectorType& joined_data, BitVectorType& current){
    Transfer* transfer;
    int transfer_index = first_transfer_index;

    while(transfer_index != -1){
        transfer = &transfers[transfer_index];
        int var_index = 0;
        int next_var = transfer->rhs[var_index];
        while(next_var != -1){

            if((joined_data & (1 << next_var)) != 0){
                current |= (1 << transfer->x);
                break;
            }
            ++var_index;
            next_var = transfer->rhs[var_index];
        }
        transfer_index = transfer->next_transfer_index;
    }
}