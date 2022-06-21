#pragma once
#include <vector>
#include <base_taint_analysis.h>
#include <dynamic_array.h>

namespace cuda_worklist{
    std::vector<BitVector> execute_analysis(DynamicArray<taint::Node>& nodes, std::vector<Transfer>& transfers, const std::vector<int>& taint_sources);
};