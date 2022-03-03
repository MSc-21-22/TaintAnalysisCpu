#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <array>

#include "analysis.h"

#define THREAD_COUNT 128

using namespace cuda_worklist;

__device__ void add_sucessors_to_worklist(int* successors, int* work_list, Node* nodes){
    int node_index = threadIdx.x + blockDim.x * blockIdx.x;
    for(int i = 0; i < 5; i++){
        int succ_index = successors[i];
        if (succ_index == -1)
            return;
        intptr_t hash = reinterpret_cast<intptr_t>(&nodes[succ_index]);
        while(work_list[hash % THREAD_COUNT] != -1){
            if(work_list[hash % THREAD_COUNT] == succ_index){
                break;
            }
            hash++;
        }
        work_list[hash % THREAD_COUNT] = succ_index;
    }
}


__global__ void analyze(Node nodes[], int work_columns[][THREAD_COUNT], int work_column_count, Transfer transfers[], int node_count, bool* work_to_do, int i){
    int node_index = threadIdx.x + blockDim.x * blockIdx.x;
    int* work_column = work_columns[i];

    if(node_index < THREAD_COUNT && work_column[node_index] != -1){
        Node& current_node = nodes[work_column[node_index]];
        
        BitVector last = current_node.data;
        BitVector current = current_node.data;

        BitVector joined_data = 0;
        //Join
        {
            int pred_index = 0;
            while (current_node.predecessor_index[pred_index] != -1){
                joined_data |= nodes[current_node.predecessor_index[pred_index]].data;
                ++pred_index;
            }
            current |= joined_data & current_node.join_mask;
        }

        //Transfer
        Transfer* transfer;
        int transfer_index = current_node.first_transfer_index;

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

        if(last != current){
            current_node.data = current;
            add_sucessors_to_worklist(current_node.successor_index, work_columns[(i+1) % work_column_count], nodes);
            *work_to_do = true;
        }
        work_column[node_index] = -1;   
    }
}

void error(Node* dev_nodes, Transfer* dev_transfers){
    cudaFree(dev_nodes);

    if(dev_transfers != nullptr){
        cudaFree(dev_transfers);
    }
}

void cuda_worklist::execute_analysis(Node* nodes, int node_count, Transfer* transfers, int transfer_count) {
    Node* dev_nodes = nullptr;
    bool* dev_work_to_do = nullptr;
    Transfer* dev_transfers = nullptr;
    int** dev_worklists = nullptr;

    for(int i = 0; i < node_count; i++){
        nodes[i].data = 1;
    }
    
    bool work_to_do = true;
    int threadsPerBlock = 128;
    int block_count = THREAD_COUNT/threadsPerBlock;    
    int work_column_count = (node_count + THREAD_COUNT - 1)/THREAD_COUNT;

    std::vector<std::array<int, THREAD_COUNT>> worklists{};
    
    for(int i = 0; i < work_column_count; i++){
        worklists.emplace_back(); 
        for(int j = 0; j < THREAD_COUNT; j++){
            if(i*THREAD_COUNT + j < node_count) {
                worklists[i][j] = i*THREAD_COUNT + j;
            }else{
                worklists[i][j] = -1;
            }
        }
    }

    auto cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        error(dev_nodes, dev_transfers);
        return;
    }

    // Allocate work columns
    cudaStatus = cudaMalloc((void**)&dev_worklists, sizeof(int) * THREAD_COUNT * (work_column_count + 1));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        error(dev_nodes, dev_transfers);
        return;
    }

    cudaMemset(dev_worklists, -1, sizeof(int) * THREAD_COUNT * (work_column_count + 1));

    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaStatus = cudaMalloc((void**)&dev_nodes, sizeof(Node)*node_count + 1);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        error(dev_nodes, dev_transfers);
        return;
    }


    if(transfer_count > 0){
        cudaStatus = cudaMalloc((void**)&dev_transfers, sizeof(Transfer)*transfer_count);
        if (cudaStatus != cudaSuccess) {
            fprintf(stderr, "cudaMalloc failed!");
            error(dev_nodes, dev_transfers);
            return;
        }
    }
    dev_work_to_do = (bool*) (dev_nodes + node_count);

    cudaStatus = cudaMemcpy(dev_worklists, &worklists[0], sizeof(int) * THREAD_COUNT * work_column_count, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "Copy worklists to gpu failed");
        error(dev_nodes, dev_transfers);
        return;
    }

    cudaStatus = cudaMemcpy(dev_nodes, nodes, sizeof(Node)*node_count, cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "Copy nodes to gpu failed");
        error(dev_nodes, dev_transfers);
        return;
    }

    if(transfer_count > 0){
        cudaStatus = cudaMemcpy(dev_transfers, transfers, sizeof(Transfer)*transfer_count, cudaMemcpyHostToDevice);
        if (cudaStatus != cudaSuccess) {
            fprintf(stderr, "Copy transfer functions to gpu failed");
            error(dev_nodes, dev_transfers);
            return;
        }
    }
    
    int i = 0;
    while(work_to_do){
        work_to_do = false;
        cudaStatus = cudaMemcpy(dev_work_to_do, &work_to_do, 1, cudaMemcpyHostToDevice);
        if (cudaStatus != cudaSuccess) {
            fprintf(stderr, "cudaMemset failed: %s\n", cudaGetErrorString(cudaStatus));
            goto Error;
        }

        // Launch a kernel on the GPU with one thread for each element.
        analyze<<<block_count, threadsPerBlock>>>(dev_nodes, (int(*)[THREAD_COUNT])dev_worklists, work_column_count+1, dev_transfers, node_count, dev_work_to_do, i);
        
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
        
        cudaStatus = cudaMemcpy((void*)&work_to_do, dev_work_to_do, sizeof(bool), cudaMemcpyDeviceToHost);
        i = (i+1) % (work_column_count+1);
    }


    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(nodes, dev_nodes, sizeof(Node)*node_count, cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed with message: %d", cudaStatus);
        goto Error;
    }

Error:
    cudaFree(dev_nodes);

    if(dev_transfers != nullptr){
        cudaFree(dev_transfers);
    }
}