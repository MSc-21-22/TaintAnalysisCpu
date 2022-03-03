#pragma once
#include "../cuda_data.h"

using BitVector = int32_t;

namespace bit_cuda{
    struct Node{
        int first_transfer_index = -1;
        int predecessor_index[5] = {-1,-1,-1,-1,-1};
        BitVector join_mask = INT32_MAX;
        BitVector data;
    };

    void execute_analysis(Node* nodes, int node_count, Transfer* transfers, int extra_transfer_count);
};