#pragma once
#include <cstdint>



struct BitVector {
    int64_t bitfield{ 0 };
public:
    BitVector() = default;
    BitVector(const BitVector&) = default;
    BitVector(BitVector&&) noexcept = default;
    BitVector& operator=(const BitVector&) = default;
    BitVector& operator=(BitVector&&) noexcept = default;
    operator int64_t();

    BitVector(int64_t default_value) : bitfield(default_value) {}

    bool operator[](int index) const;
    bool operator==(const BitVector& rhs) const;
    bool operator<(const BitVector& rhs) const;
    BitVector& operator|=(const BitVector& rhs);
    BitVector operator|(const BitVector& rhs) const;
    BitVector& operator^=(const BitVector& rhs);
    bool operator!=(const BitVector& rhs) const;
    BitVector operator&(const BitVector& rhs) const;
    bool has_overlap(const BitVector& rhs) const;
    void set_bit(int index);
    void flip_bit(int index);
};