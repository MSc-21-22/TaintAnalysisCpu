#pragma once
#include <array>
#include <limits>
namespace bit_cuda{

struct Transfer{ // x = y + z     { x, [y, z]}
    int x;
    int rhs[5] = {-1,-1,-1,-1,-1}; // -1 terminated
    int next_transfer_index = -1;
};

using BitVector = int32_t;

struct Node{
    int first_transfer_index = -1;
    int predecessor_index[5] = {-1,-1,-1,-1,-1};
    BitVector join_mask = INT32_MAX;
    BitVector data;
};

void execute_analysis(Node* nodes, int node_count, Transfer* transfers, int extra_transfer_count);
void execute_analysis_no_transfers(Node* nodes, int node_count);
};