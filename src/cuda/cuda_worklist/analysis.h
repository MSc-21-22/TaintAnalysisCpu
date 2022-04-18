#pragma once
#include <set>
#include "../cuda_data.h"
#include <vector>

namespace cuda_worklist{
    struct Node{
        int first_transfer_index = -1;
        int predecessor_index[5] = {-1,-1,-1,-1,-1};
        int successor_index[5] = {-1,-1,-1,-1,-1};
        cuda::BitVector join_mask = INT32_MAX;
        cuda::BitVector data = 1;
    };

    void execute_analysis(DynamicArray<Node>& nodes, std::vector<cuda::Transfer>& transfers, const std::set<int>& taint_sources);
};