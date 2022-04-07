#pragma once
#include <cfg/cfg.h>
#include <set>
#include <string>
#include <map>
#include <ostream>
#include <taint_analysis.h>

typedef std::map<std::string, std::set<int>> SourcedTaintState;
void print_taint_source(SourcedTaintState& result, std::ostream& stream);

namespace cpu_multi{
void worklist(std::vector<StatefulNode<std::vector<cpu_analysis::BitVector>>>& nodes, const std::vector<int>& node_to_start_transfer, const std::vector<cpu_analysis::Transfer>& transfers, int source_count);
}