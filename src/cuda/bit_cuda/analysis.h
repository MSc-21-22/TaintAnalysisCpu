#pragma once
#include <base_taint_analysis.h>
#include <dynamic_array.h>
#include <vector>

namespace bit_cuda{
    void execute_analysis(DynamicArray<taint::Node>& nodes, std::vector<Transfer>& transfers);
};