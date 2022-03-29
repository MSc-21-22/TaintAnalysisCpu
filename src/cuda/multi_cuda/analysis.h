#pragma once
#include <set>
#include "../cuda_data.h"
#include <vector>

namespace multi_cuda{
    struct Node{
        int first_transfer_index = -1;
        int predecessor_index[5] = {-1,-1,-1,-1,-1};
        int successor_index[5] = {-1,-1,-1,-1,-1};
        BitVector join_mask = INT32_MAX - 1;
        BitVector data[];
    };

    void execute_analysis(DynamicArray<Node>& nodes, std::vector<Transfer>& transfers, const std::set<int>& taint_sources, int source_count);
};