#pragma once
#include "../cuda_data.h"

using BitVector = int32_t;

namespace cuda_worklist{
    struct Node{
        int first_transfer_index = -1;
        int predecessor_index[5] = {-1,-1,-1,-1,-1};
        int successor_index[5] = {-1,-1,-1,-1,-1};
        BitVector join_mask = INT32_MAX;
        BitVector data = 1;
    };

    void execute_analysis(Node* nodes, int node_count, Transfer* transfers, int extra_transfer_count);
};