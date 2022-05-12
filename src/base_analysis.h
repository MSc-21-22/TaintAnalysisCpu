#pragma once
#include <bit_vector.h>

#define TAINT_VAR "$"
#define TAINT_VAR_INDEX 0

#define RETURN_VAR "$-return"
#define RETURN_VAR_INDEX 1

struct Transfer {
    int var_index;
    BitVector rhs = 0;
    int next_transfer_index = -1;
};