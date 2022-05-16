#pragma once
#include <set>
#include <string>
#include <map>
#include <ostream>
#include <taint_analysis.h>
#include <base_multi_taint_analysis.h>

namespace cpu_multi{
void worklist(DynamicArray<multi_taint::Node>& nodes, const std::vector<Transfer>& transfers, int source_count);
}