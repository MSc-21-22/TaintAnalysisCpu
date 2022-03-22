#pragma once
#include <set>
#include "../cuda_data.h"

namespace multi_cuda{
    struct Node{
        int first_transfer_index = -1;
        int predecessor_index[5] = {-1,-1,-1,-1,-1};
        int successor_index[5] = {-1,-1,-1,-1,-1};
        BitVector join_mask = INT32_MAX;
        BitVector data[]; // Experiment with different types might be faster consider 32 and 64 bit numbers
    };

    void execute_analysis(Node* nodes, int node_count, Transfer* transfers, int transfer_count, std::set<int>& taint_sources, int source_count);
};