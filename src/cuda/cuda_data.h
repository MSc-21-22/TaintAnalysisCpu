#pragma once
#include <array>
#include <limits>

using BitVector = int32_t;

struct Transfer{ // x = y + z     { x, [y, z]}
    int x;
    int rhs[5] = {-1,-1,-1,-1,-1}; // -1 terminated
    int next_transfer_index = -1;
};