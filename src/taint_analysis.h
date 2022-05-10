#pragma once
#include <cfg/cfg.h>
#include <set>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>
#include <bit_vector.h>

#define TAINT_VAR_INDEX 0 
#define RETURN_VAR_INDEX 1

namespace cpu_analysis{

struct Transfer{
    BitVector transfer_mask{0};
    BitVector join_mask{INT64_MAX};
    int8_t var_index = 0;
    bool uses_next = false;
};

void worklist(std::vector<StatefulNode<BitVector>>& nodes, const std::vector<int>& node_to_start_transfer, const std::vector<Transfer>& transfers);
}