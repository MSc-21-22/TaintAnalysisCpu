#pragma once
#include "../cuda_data.h"

namespace bit_cuda{
    struct Node{
        int first_transfer_index = -1;
        int predecessor_index[5] = {-1,-1,-1,-1,-1};
        cuda::BitVector join_mask = INT32_MAX;
        cuda::BitVector data = 1;
    };

    void execute_analysis(Node* nodes, int node_count, cuda::Transfer* transfers, int extra_transfer_count);
};