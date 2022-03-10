#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <stdio.h>
#include "../cuda_common.cuh"

#include "analysis.h"

using namespace bit_cuda;

__device__ BitVector join(int predecessors[], Node nodes[]){
        BitVector joined_data = 1;
        int pred_index = 0;
        while (predecessors[pred_index] != -1){
            joined_data |= nodes[predecessors[pred_index]].data;
            ++pred_index;
        }
        return joined_data;
}

__device__ void transfer_function_bit_cuda(int first_transfer_index, Transfer transfers[], BitVector& joined_data, BitVector& current){
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

__global__ void analyze(Node nodes[], Transfer transfers[], bool* has_changed, int node_count){
    int node_index = threadIdx.x + blockDim.x * blockIdx.x;

    if(node_index < node_count){
        Node& current_node = nodes[node_index];
        
        BitVector current = current_node.data;
        BitVector last = current_node.data;
        
        BitVector joined_data = join(current_node.predecessor_index, nodes);
        current |= joined_data & current_node.join_mask;

        transfer_function_bit_cuda(current_node.first_transfer_index, transfers, joined_data, current);

        if(last != current){
            current_node.data = current;
            *has_changed = true;
        }
    }
}

void bit_cuda::execute_analysis(Node* nodes, int node_count, Transfer* transfers, int transfer_count) {
    Node* dev_nodes = nullptr;
    bool* dev_has_changed = nullptr;
    Transfer* dev_transfers = nullptr;

    int block_count = node_count/128 + 1;
    dim3 threadsPerBlock(128);
    auto cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        exit(1);
    }

    // Allocate GPU buffers for three vectors (two input, one output)
    dev_nodes = cuda_allocate_memory<Node>(sizeof(Node)*node_count + 1);
    cuda_copy_to_device(dev_nodes, nodes, sizeof(Node)*node_count);

    dev_transfers = cuda_allocate_memory<Transfer>(sizeof(Transfer)*transfer_count);
    cuda_copy_to_device(dev_transfers, transfers, sizeof(Transfer)*transfer_count);
    
    dev_has_changed = (bool*) (dev_nodes + node_count);

    bool has_changed = true;
    while(has_changed){
        has_changed = false;
        cuda_copy_to_device(dev_has_changed, &has_changed, sizeof(bool));

        // Launch a kernel on the GPU with one thread for each element.
        analyze<<<block_count, threadsPerBlock>>>(dev_nodes, dev_transfers, dev_has_changed, node_count);
        
        // Check for any errors launching the kernel
        cudaStatus = cudaGetLastError();
        if (cudaStatus != cudaSuccess) {
            fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
            exit(1);
        }

        // cudaDeviceSynchronize waits for the kernel to finish, and returns
        // any errors encountered during the launch.
        cudaStatus = cudaDeviceSynchronize();
        if (cudaStatus != cudaSuccess) {
            fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        }

        cuda_copy_to_host((void*)&has_changed, dev_has_changed, sizeof(bool));
        std::cout << "has changed: " << has_changed << std::endl;
    }


    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        exit(1);
    }

    // Copy output vector from GPU buffer to host memory.
    cuda_copy_to_host(nodes, dev_nodes, sizeof(Node)*node_count);

    cuda_free(dev_nodes);
    cuda_free(dev_transfers);
}