#pragma once
#include <set>
#include "../cuda_data.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <array>
#include "../cuda_common.cuh"
#include <type_traits>
#include <timing.h>

using namespace cuda;
namespace worklist{
    #define THREAD_COUNT (1024*2)
    #define EXTRA_WORKLISTS_CONSTANT 600
    #define COLLISIONS_BEFORE_SWITCH (1) 

    template<typename INT>
    __device__ void add_sucessors_to_worklist(INT* successors, int work_columns[][THREAD_COUNT], int work_column_count, int initial_work_column, int* worklists_pending){
        static_assert(std::is_same<INT, int>::value, "Paremeter successors must be an int pointer");
        int current_work_column;
        for(int i = 0; i < 5; i++){
            int amount_of_new_worklists = 1;
            current_work_column = initial_work_column;
            int succ_index = successors[i];
            if (succ_index == -1)
                return;
            unsigned long hash = succ_index*120811;
            int collision_count = 0;
            int* work_column = work_columns[current_work_column];

            while(atomicCAS(&work_column[hash % THREAD_COUNT], -1, succ_index) != -1){
                if(work_column[hash % THREAD_COUNT] == succ_index){
                    break;
                }
                
                if(++collision_count >= COLLISIONS_BEFORE_SWITCH){
                    current_work_column = (current_work_column + 1) % work_column_count;
                    work_column = work_columns[current_work_column];
                    amount_of_new_worklists++;
                    collision_count = 0;
                }else{
                    hash++;
                }
            }
        
            atomicMax(worklists_pending, amount_of_new_worklists);
        }
    }
    
    template<typename Analyzer, typename NodeContainer, typename NodeType = typename Analyzer::NodeType>
    __global__ void analyze(Analyzer analyzer, NodeContainer nodes, int work_columns[][THREAD_COUNT], int work_column_count, Transfer transfers[], int node_count, int* worklists_pending, int current_work_column){
        static_assert(std::is_same<NodeType, std::remove_reference_t<decltype(nodes[0])>>::value, "Node types must be identical");
        

        int node_index = threadIdx.x + blockDim.x * blockIdx.x;
        int* work_column = work_columns[current_work_column];

        if(node_index < THREAD_COUNT && work_column[node_index] != -1){
            NodeType& current_node = nodes[work_column[node_index]];
            bool add_successors = analyzer.analyze(current_node, nodes, transfers);

            work_column[node_index] = -1;   

            if(add_successors){
                int next_work_column = (current_work_column+1) % work_column_count;
                add_sucessors_to_worklist(current_node.successor_index, work_columns, work_column_count, next_work_column, worklists_pending);
            }      
        }
    }

    template<typename NodeContainer>
    struct NodeUploader {
        NodeContainer container;
        using Item = std::remove_reference_t<decltype(container[0])>;
        void** dev_nodes;
    };

    template<typename Analyzer, typename NodeContainer, typename NodeType = typename Analyzer::NodeType>
    void execute_some_analysis(Analyzer analyzer, DynamicArray<NodeType>& nodes, NodeUploader<NodeContainer>& uploadable_container, Transfer* transfers, int transfer_count, const std::set<int>& taint_sources){
        static_assert(std::is_same<NodeType, typename NodeUploader<NodeContainer>::Item>::value, "Node uploader Item type must match NodeType");
        static_assert(std::is_same<typename Analyzer::NodeContainer, NodeContainer>::value, "Container types must match");

        int* dev_worklists_pending = nullptr;
        Transfer* dev_transfers = nullptr;
        int** dev_worklists = nullptr;

        int worklists_pending = ((taint_sources.size() + THREAD_COUNT - 1)/THREAD_COUNT);
        int threadsPerBlock = 128;
        int block_count = THREAD_COUNT/threadsPerBlock;    
        int work_column_count = worklists_pending + (nodes.size()/EXTRA_WORKLISTS_CONSTANT);

        std::vector<std::array<int, THREAD_COUNT>> worklists{};

        std::set<int>::iterator it = taint_sources.cbegin();
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
        dev_worklists = cuda_allocate_memory<int*>(sizeof(int) * THREAD_COUNT * work_column_count);
        cudaMemset(dev_worklists, -1, sizeof(int) * THREAD_COUNT * work_column_count);
        cuda_copy_to_device(dev_worklists, &worklists[0], sizeof(int) * THREAD_COUNT * work_column_count);

        // Allocate GPU buffers for three vectors (two input, one output)  
        cuda_allocate_memory(uploadable_container.dev_nodes, nodes.get_item_size()*nodes.size());
        cuda_copy_to_device(*uploadable_container.dev_nodes, nodes.get_ptr(), nodes.get_item_size()*nodes.size());

        // Allocate transfer function
        dev_transfers = cuda_allocate_memory<Transfer>(sizeof(Transfer)*transfer_count);
        cuda_copy_to_device(dev_transfers, transfers, sizeof(Transfer)*transfer_count);
    
        dev_worklists_pending = cuda_allocate_memory<int>(sizeof(int));

        Stopwatch lfp_watch;
        int current_worklist = 0;
        while(worklists_pending > 0){
            --worklists_pending;
            cuda_copy_to_device(dev_worklists_pending, &worklists_pending, sizeof(int));

            // Launch a kernel on the GPU with one thread for each element.
            analyze<<<block_count, threadsPerBlock>>>(analyzer, uploadable_container.container, (int(*)[THREAD_COUNT])dev_worklists, work_column_count, dev_transfers, nodes.size(), dev_worklists_pending, current_worklist);
            
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
            
            cuda_copy_to_host(&worklists_pending, dev_worklists_pending, sizeof(int));
            current_worklist = (current_worklist+1) % work_column_count;
        }
        lfp_watch.print_time<Microseconds>("LFP time: ");


        // Copy output vector from GPU buffer to host memory.
        cuda_copy_to_host(nodes.get_ptr(), *uploadable_container.dev_nodes, nodes.get_item_size()*nodes.size());

        cuda_free(*uploadable_container.dev_nodes);
        cuda_free(dev_transfers);
        cuda_free(dev_worklists);
    }
};