#pragma once
#include <array>
namespace bit_cuda{

struct Transfer{ // x = y + z     { x, [y, z]}
    int x;
    int rhs[5]{-1}; // -1 terminated
    int next_transfer_index{-1};
};

struct BitVector{
    long int data;
};

struct Node{
    Transfer transfer;
    int predecessor_index[5]{-1};
    BitVector data;
};

void execute_analysis(Node* nodes, int node_count, Transfer* transfers, int extra_transfer_count);
void execute_analysis(Node* nodes, int node_count);
};