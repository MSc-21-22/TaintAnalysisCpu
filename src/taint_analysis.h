#pragma once
#include <set>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>
#include <bit_vector.h>
#include <base_taint_analysis.h>
#include <dynamic_array.h>

namespace cpu_analysis{
std::vector<BitVector> worklist(DynamicArray<taint::Node>& nodes, const std::vector<Transfer>& transfers, std::vector<int> worklist);
}
