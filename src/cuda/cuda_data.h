#pragma once
#include <array>
#include <limits>
#include <memory>
#include <cstring>
#include <dynamic_array.h>

namespace cuda {

using BitVector = int32_t;

struct Transfer{ // x = y + z     { x, [y, z]}
    int x;
    BitVector rhs = 0;
    int next_transfer_index = -1;
};
}