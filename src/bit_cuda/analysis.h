#pragma once

struct Transfer{ // x = y + z     { x, [y, z]}
    int x;
    int rhs[5]; // -1 terminated
};

struct BitVector{
    long int data;
};

struct Node{
    Transfer transfer;
    int predecessor_index[5];
    BitVector data;
};

void execute_analysis(Node* nodes, int node_count);