#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <stdio.h>

#include "analysis.h"

using namespace bit_cuda;

__global__ void analyze(Node nodes[], Transfer transfers[], bool* has_changed, int node_count){
    int node_index = threadIdx.x + blockDim.x * blockIdx.x;

    if(node_index == 0)
        *has_changed = true;

    if(node_index < node_count){
        nodes[node_index].data = 1; // Set taint constant to true
        
        bool is_changed = true;
        BitVector last_joined = 0;
        BitVector current = nodes[node_index].data;

        while(*has_changed){
            if(node_index == 0)
                *has_changed = false;
            BitVector joined_data = 0;
            //Join
            {
                int pred_index = 0;
                while (nodes[node_index].predecessor_index[pred_index] != -1){
                    joined_data |= nodes[nodes[node_index].predecessor_index[pred_index]].data;
                    ++pred_index;
                }

                is_changed |= last_joined != joined_data;
                last_joined = joined_data;
                current |= joined_data & nodes[node_index].join_mask;
            }

            //Transfer
            if(is_changed){
                Transfer* transfer;
                int transfer_index = nodes[node_index].first_transfer_index;

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

                nodes[node_index].data = current;
                *has_changed = true;
                is_changed = false;
                // __syncthreads();
            }
            __syncthreads();
            __threadfence();
        }
    }

}

void bit_cuda::execute_analysis(Node* nodes, int node_count, Transfer* transfers, int transfer_count) {
    Node* dev_nodes = nullptr;
    bool* dev_has_changed = nullptr;
    Transfer* dev_extra_transfers = nullptr;

    int block_count = node_count/128 + 1;
    dim3 threadsPerBlock(128);

    auto cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaStatus = cudaMalloc((void**)&dev_nodes, sizeof(Node)*node_count + 1);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    if(transfer_count > 0){
        cudaStatus = cudaMalloc((void**)&dev_extra_transfers, sizeof(Transfer)*transfer_count);
        if (cudaStatus != cudaSuccess) {
            fprintf(stderr, "cudaMalloc failed!");
            goto Error;
        }
    }
    dev_has_changed = (bool*) (dev_nodes + (sizeof(Node)*node_count));

    cudaStatus = cudaMemcpy(dev_nodes, nodes, sizeof(Node)*node_count, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "Copy false to gpu failed");
        goto Error;
    }

    if(transfer_count > 0){
        cudaStatus = cudaMemcpy(dev_extra_transfers, transfers, sizeof(Transfer)*transfer_count, cudaMemcpyHostToDevice);
        if (cudaStatus != cudaSuccess) {
            fprintf(stderr, "Copy false to gpu failed");
            goto Error;
        }
    }
    // Launch a kernel on the GPU with one thread for each element.
    analyze<<<block_count, threadsPerBlock>>>(dev_nodes, dev_extra_transfers, dev_has_changed, node_count);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }

    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(nodes, dev_nodes, sizeof(Node)*node_count, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed with message: %d", cudaStatus);
        goto Error;
    }

Error:
    cudaFree(dev_nodes);

    if(dev_extra_transfers != nullptr){
        cudaFree(dev_extra_transfers);
    }
}