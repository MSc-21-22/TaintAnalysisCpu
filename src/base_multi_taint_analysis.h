#pragma once
#include <base_analysis.h>
#include <bit_vector.h>

namespace multi_taint {
struct Node {
    int first_transfer_index = -1;
    int predecessor_index[5] = { -1,-1,-1,-1,-1 };
    int successor_index[5] = { -1,-1,-1,-1,-1 };
    BitVector join_mask = INT32_MAX - 1;
    BitVector data[];
};
}