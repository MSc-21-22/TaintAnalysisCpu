#include <iostream>
#include <stdio.h>
#include <vector>
#include <array>
#include "../cuda_common.cuh"

#include <timing.h>
#include "analysis.h"

#define THREAD_COUNT 1024
#define COLLISIONS_BEFORE_SWITCH (1) 

using namespace cuda_worklist;

__device__ void add_sucessors_to_worklist(int* successors, int work_columns[][THREAD_COUNT], int work_column_count, int current_work_column, Node* nodes){
    int initial_work_column = current_work_column;
    for(int i = 0; i < 5; i++){
        int succ_index = successors[i];
        if (succ_index == -1)
            return;
        intptr_t hash = reinterpret_cast<intptr_t>(&nodes[succ_index]);
        int collision_count = 0;
        int* work_column = work_columns[current_work_column];

        int old;
        do{
            while(work_column[hash % THREAD_COUNT] != -1){
                if(work_column[hash % THREAD_COUNT] == succ_index){
                    break;
                }
                

                if(++collision_count >= COLLISIONS_BEFORE_SWITCH){
                    current_work_column = (current_work_column + 1) % work_column_count;
                    work_column = work_columns[current_work_column];
                }else{
                    hash++;
                }
            }
            // work_column[hash % THREAD_COUNT] = succ_index;

            old = atomicCAS(&work_column[hash % THREAD_COUNT], -1, succ_index);
        }while (old == -1);
    }
}

__global__ void analyze(Node nodes[], int work_columns[][THREAD_COUNT], int work_column_count, Transfer transfers[], int node_count, bool* work_to_do, int i){
    int node_index = threadIdx.x + blockDim.x * blockIdx.x;
    int* work_column = work_columns[i];

    if(node_index < THREAD_COUNT && work_column[node_index] != -1){
        Node& current_node = nodes[work_column[node_index]];
        
        BitVector last = current_node.data;
        BitVector current = current_node.data;

        BitVector joined_data = join(current_node.predecessor_index, nodes);
        current |= joined_data & current_node.join_mask;

        transfer_function(current_node.first_transfer_index, transfers, joined_data, current);

        if(last != current){
            current_node.data = current;
            add_sucessors_to_worklist(current_node.successor_index, work_columns, work_column_count, (i+1) % work_column_count, nodes);
            *work_to_do = true;
        }
        work_column[node_index] = -1;   
    }
}

void cuda_worklist::execute_analysis(Node* nodes, int node_count, Transfer* transfers, int transfer_count, std::set<int>& taint_sources) {
    Node* dev_nodes = nullptr;
    bool* dev_work_to_do = nullptr;
    Transfer* dev_transfers = nullptr;
    int** dev_worklists = nullptr;

    bool work_to_do = true;
    int threadsPerBlock = 128;
    int block_count = THREAD_COUNT/threadsPerBlock;    
    int work_column_count = ((node_count + THREAD_COUNT - 1)/THREAD_COUNT) + 50;

    std::vector<std::array<int, THREAD_COUNT>> worklists{};

    std::set<int>::iterator it = taint_sources.begin();
    for(int i = 0; i < work_column_count; i++){
        worklists.emplace_back(); 
        for(int j = 0; j < THREAD_COUNT; j++){
            if(it != taint_sources.end()) {
                worklists[i][j] = *it;
                it++;
            }else{
                worklists[i][j] = -1;
            }
        }
    }

    auto cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        return;
    }

    // Allocate work columns
    dev_worklists = cuda_allocate_memory<int*>(sizeof(int) * THREAD_COUNT * (work_column_count + 1));
    cudaMemset(dev_worklists, -1, sizeof(int) * THREAD_COUNT * (work_column_count + 1));
    cuda_copy_to_device(dev_worklists, &worklists[0], sizeof(int) * THREAD_COUNT * work_column_count);

    // Allocate GPU buffers for three vectors (two input, one output)  
    dev_nodes = cuda_allocate_memory<Node>(sizeof(Node)*node_count + 1);
    cuda_copy_to_device(dev_nodes, nodes, sizeof(Node)*node_count);

    dev_work_to_do = (bool*) (dev_nodes + node_count);

    // Allocate transfer function
    dev_transfers = cuda_allocate_memory<Transfer>(sizeof(Transfer)*transfer_count);
    cuda_copy_to_device(dev_transfers, transfers, sizeof(Transfer)*transfer_count);
  
    Stopwatch lfp_watch;
    int i = 0;
    while(work_to_do){
        work_to_do = false;
        cuda_copy_to_device(dev_work_to_do, &work_to_do, 1);

        // Launch a kernel on the GPU with one thread for each element.
        analyze<<<block_count, threadsPerBlock>>>(dev_nodes, (int(*)[THREAD_COUNT])dev_worklists, work_column_count+1, dev_transfers, node_count, dev_work_to_do, i);
        
        // Check for any errors launching the kernel
        cudaStatus = cudaGetLastError();
        if (cudaStatus != cudaSuccess) {
            fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        }

        // cudaDeviceSynchronize waits for the kernel to finish, and returns
        // any errors encountered during the launch.
        cudaStatus = cudaDeviceSynchronize();
        if (cudaStatus != cudaSuccess) {
            fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        }
        
        cuda_copy_to_host((void*)&work_to_do, dev_work_to_do, sizeof(bool));
        i = (i+1) % (work_column_count+1);
    }
    lfp_watch.print_time<Microseconds>("LFP time: ");


    // Copy output vector from GPU buffer to host memory.
    cuda_copy_to_host(nodes, dev_nodes, sizeof(Node)*node_count);

    cuda_free(dev_nodes);
    cuda_free(dev_transfers);
    cuda_free(dev_worklists);
}