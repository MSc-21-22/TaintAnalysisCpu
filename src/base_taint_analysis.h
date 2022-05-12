#pragma once
#include <bit_vector.h>
#include <base_analysis.h>

namespace taint {
struct Node {
    int first_transfer_index = -1;
    int predecessor_index[5] = { -1,-1,-1,-1,-1 };
    int successor_index[5] = { -1,-1,-1,-1,-1 };
    BitVector join_mask = INT32_MAX;
    BitVector data = 1;
};
}