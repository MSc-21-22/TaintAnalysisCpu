#pragma once
#include <cfg/cfg.h>
#include <set>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>

namespace cpu_analysis{


struct BitVector{
    int64_t bitfield;
public:
    BitVector() = default;
    BitVector(const BitVector&) = default;
    BitVector(BitVector&&) noexcept = default;
    BitVector& operator=(const BitVector&) = default;
    BitVector& operator=(BitVector&&) noexcept = default;

    BitVector(int64_t default_value) : bitfield(default_value){}

    bool operator[](int index);
    bool operator==(const BitVector& rhs) const;
    bool operator<(const BitVector& rhs) const;
    BitVector& operator|=(const BitVector& rhs);
    BitVector operator|(const BitVector& rhs) const;
    bool operator!=(const BitVector& rhs) const;
    BitVector operator&(const BitVector& rhs) const;
    bool has_overlap(const BitVector&rhs) const;
    void set_bit(int index);
    void flip_bit(int index);
};

struct Transfer{
    BitVector transfer_mask{0};
    BitVector join_mask{INT64_MAX};
    int8_t var_index = 0;
    bool uses_next = false;
};

void worklist(std::vector<StatefulNode<BitVector>>& nodes, const std::vector<int>& node_to_start_transfer, const std::vector<Transfer>& transfers);
}