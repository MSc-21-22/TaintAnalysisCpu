#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <stdio.h>
#include "../cuda_common.cuh"

#include "analysis.h"

using namespace bit_cuda;
using namespace taint;

__global__ void analyze(Node nodes[], Transfer transfers[], bool* has_changed, int node_count){
    int node_index = threadIdx.x + blockDim.x * blockIdx.x;

    if(node_index < node_count){
        Node& current_node = nodes[node_index];
        
        BitVector current = current_node.data;
        BitVector last = current_node.data;
        
        BitVector joined_data = join(current_node.predecessor_index, nodes);
        current.bitfield |= joined_data.bitfield & current_node.join_mask.bitfield;

        transfer_function(current_node.first_transfer_index, transfers, joined_data, current);

        if(last.bitfield != current.bitfield){
            current_node.data = current;
            *has_changed = true;
        }
    }
}

void bit_cuda::execute_analysis(DynamicArray<taint::Node>& nodes, std::vector<Transfer>& transfers) {
    Node* dev_nodes = nullptr;
    bool* dev_has_changed = nullptr;
    Transfer* dev_transfers = nullptr;

    int block_count = nodes.size() / 128 + 1;
    dim3 threadsPerBlock(128);
    auto cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        exit(1);
    }

    // Allocate GPU buffers for three vectors (two input, one output)
    dev_nodes = cuda_allocate_memory<Node>(nodes.full_size() + 1);
    cuda_copy_to_device(dev_nodes, nodes.get_ptr(), nodes.full_size());

    dev_transfers = cuda_allocate_memory<Transfer>(sizeof(Transfer)*transfers.size());
    cuda_copy_to_device(dev_transfers, transfers.data(), sizeof(Transfer) * transfers.size());
    
    dev_has_changed = (bool*) (dev_nodes + nodes.size());

    bool has_changed = true;
    while(has_changed){
        has_changed = false;
        cuda_copy_to_device(dev_has_changed, &has_changed, sizeof(bool));

        // Launch a kernel on the GPU with one thread for each element.
        analyze<<<block_count, threadsPerBlock>>>(dev_nodes, dev_transfers, dev_has_changed, nodes.size());
        
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
    }


    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        exit(1);
    }

    // Copy output vector from GPU buffer to host memory.
    cuda_copy_to_host(nodes.get_ptr(), dev_nodes, nodes.full_size());

    cuda_free(dev_nodes);
    cuda_free(dev_transfers);
}