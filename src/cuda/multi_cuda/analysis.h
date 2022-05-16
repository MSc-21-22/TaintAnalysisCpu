#pragma once
#include <set>
#include <vector>
#include <dynamic_array.h>
#include <base_multi_taint_analysis.h>

namespace multi_cuda{
    void execute_analysis(DynamicArray<multi_taint::Node>& nodes, std::vector<Transfer>& transfers, const std::set<int>& taint_sources, int source_count);
};