#include <iostream>
#include <stdio.h>
#include <vector>
#include <array>
#include "../cuda_common.cuh"

#include <timing.h>
#include "analysis.h"

#define THREAD_COUNT 1024
#define COLLISIONS_BEFORE_SWITCH (1)

using namespace multi_cuda;

__device__ inline Node& get_node(Node* nodes, int index, int node_size){
    int8_t* byte_ptr = (int8_t*)nodes;
    int byte_offset = index * node_size;
    
    return *(Node*)(byte_ptr + byte_offset);
}

__device__ void add_sucessors_to_worklist(int* successors, int work_columns[][THREAD_COUNT], int work_column_count, int current_work_column){
    int initial_work_column = current_work_column;
    for(int i = 0; i < 5; i++){
        int succ_index = successors[i];
        if (succ_index == -1)
            return;
        intptr_t hash = succ_index * 120811; 
        int collision_count = 0;
        int* work_column = work_columns[current_work_column];
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
        work_column[hash % THREAD_COUNT] = succ_index;
    }
}

__device__ BitVector multi_cuda_join(int predecessors[], Node *nodes, int node_size, int source_index){
        BitVector joined_data = 0;
        int pred_index = 0;
        while (predecessors[pred_index] != -1){
            joined_data |= get_node(nodes, predecessors[pred_index], node_size).data[source_index];
            ++pred_index;
        }
        return joined_data;
}

__global__ void analyze(Node* nodes, int work_columns[][THREAD_COUNT], int work_column_count, Transfer transfers[], int node_count, bool* work_to_do, int i, int source_count){
    int node_index = threadIdx.x + blockDim.x * blockIdx.x;
    int* work_column = work_columns[i];
    int node_size = sizeof(Node) + sizeof(BitVector) * source_count;

    if(node_index < THREAD_COUNT && work_column[node_index] != -1){
        int index = node_size * work_column[node_index];
        Node& current_node = get_node(nodes, work_column[node_index], node_size);

        bool add_successors = false;

        for(int source = 0; source < source_count; ++source){
            BitVector last = current_node.data[source];
            BitVector current = last;


            BitVector joined_data = multi_cuda_join(current_node.predecessor_index, nodes, node_size, source);
            current |= joined_data & current_node.join_mask;
            
            joined_data |= current;
            transfer_function(current_node.first_transfer_index, transfers, joined_data, current);

            if(last != current){
                current_node.data[source] = current;
                add_successors = true;
            }
        }

        if(add_successors){
            add_sucessors_to_worklist(current_node.successor_index, work_columns, work_column_count, (i+1) % work_column_count);
            *work_to_do = true;
        }

        work_column[node_index] = -1;   
    }
}

void multi_cuda::execute_analysis(Node* nodes, int node_count, Transfer* transfers, int transfer_count, std::set<int>& taint_sources, int source_count) {
    Node* dev_nodes = nullptr;
    bool* dev_work_to_do = nullptr;
    Transfer* dev_transfers = nullptr;
    int** dev_worklists = nullptr;

    bool work_to_do = true;
    int threadsPerBlock = 128;
    int block_count = THREAD_COUNT/threadsPerBlock;    
    int work_column_count = ((node_count + THREAD_COUNT - 1)/THREAD_COUNT) + 50;

    int node_size = sizeof(BitVector) * source_count + sizeof(Node);

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
    dev_nodes = cuda_allocate_memory<Node>(node_size * node_count + 1);
    cuda_copy_to_device(dev_nodes, nodes, node_size * node_count);

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
        analyze<<<block_count, threadsPerBlock>>>(dev_nodes, (int(*)[THREAD_COUNT])dev_worklists, work_column_count+1, dev_transfers, node_count, dev_work_to_do, i, source_count);
        
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
    cuda_copy_to_host(nodes, dev_nodes, node_size*node_count);

    cuda_free(dev_nodes);
    cuda_free(dev_transfers);
    cuda_free(dev_worklists);
}