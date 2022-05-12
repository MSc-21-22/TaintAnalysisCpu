#include "bit_vector.h"

BitVector::operator int64_t()
{
    return bitfield;
}

bool BitVector::operator[](int index) const {
    return (bitfield & 1ll << index) != 0;
}
BitVector& BitVector::operator|=(const BitVector& rhs) {
    this->bitfield |= rhs.bitfield;
    return *this;
}

BitVector& BitVector::operator^=(const BitVector& rhs) {
    bitfield ^= rhs.bitfield;
    return *this;
}

bool BitVector::operator!=(const BitVector& rhs) const {
    return this->bitfield != rhs.bitfield;
}

bool BitVector::operator==(const BitVector& rhs) const {
    return bitfield == rhs.bitfield;
}

bool BitVector::operator<(const BitVector& rhs) const {
    return bitfield < rhs.bitfield;
}

BitVector BitVector::operator|(const BitVector& rhs) const {
    return BitVector(this->bitfield | rhs.bitfield);
}

BitVector BitVector::operator&(const BitVector& rhs) const {
    return BitVector(this->bitfield & rhs.bitfield);
}

bool BitVector::has_overlap(const BitVector& rhs) const {
    return (this->bitfield & rhs.bitfield) != 0;
}

void BitVector::set_bit(int index) {
    bitfield |= 1ll << index;
}
void BitVector::flip_bit(int index) {
    bitfield ^= 1ll << index;
}