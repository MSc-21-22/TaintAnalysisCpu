#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <stdio.h>

#include "analysis.h"

using namespace bit_cuda;

__global__ void analyze(Node nodes[], bool* has_changed, int node_count){
    int node_index = threadIdx.x + blockDim.x * blockIdx.x;

    if(node_index < node_count){
        nodes[node_index].data.data = 1; // Set taint constant to true

        while(*has_changed){
            *has_changed = false;
            bool is_changed = false;
            long int new_data = 0;
            //Join
            {
                long int old_data = nodes[node_index].data.data;
                new_data = old_data;
                int pred_index = 0;
                while (nodes[node_index].predecessor_index[pred_index] != -1){
                    new_data |= nodes[nodes[node_index].predecessor_index[pred_index]].data.data;
                    ++pred_index;
                }

                is_changed = old_data == new_data;
            }

            //Transfer
            if(is_changed){
                int var_index = 0;
                int next_var = nodes[node_index].transfer.rhs[var_index];
                while(next_var != -1){
                    if(nodes[node_index].data.data & (1 << next_var) > 0){
                        nodes[node_index].data.data |= nodes[node_index].transfer.x;
                        break;
                    }
                    ++var_index;
                    next_var = nodes[node_index].transfer.rhs[var_index];
                }

                *has_changed = true;
            }
        }
    }

}

void bit_cuda::execute_analysis(Node* nodes, int node_count) {
    Node* dev_nodes = nullptr;
    bool* dev_has_changed = nullptr;

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

    dev_has_changed = (bool*) (dev_nodes + (sizeof(Node)*node_count));

    cudaStatus = cudaMemcpy(dev_nodes, nodes, sizeof(Node)*node_count, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "Copy false to gpu failed");
        goto Error;
    }

    // Launch a kernel on the GPU with one thread for each element.
    analyze<<<block_count, threadsPerBlock>>>(dev_nodes, dev_has_changed, node_count);

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
    cudaStatus = cudaMemcpy(&nodes, dev_nodes, sizeof(Node)*node_count, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed with message: %d", cudaStatus);
        goto Error;
    }

Error:
    cudaFree(dev_nodes);
}