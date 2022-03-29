#include "analysis.h"
#include "../worklist/analysis.cuh"

using namespace cuda_worklist;

class Analyzer {
public:
    using NodeType = Node;
    using NodeContainer = Node*;

    __device__ bool analyze(Node& current_node, NodeContainer nodes, Transfer* transfers){
        BitVector last = current_node.data;
        BitVector current = current_node.data;
        
        BitVector joined_data = join(current_node.predecessor_index, nodes);
        current |= joined_data & current_node.join_mask;

        transfer_function(current_node.first_transfer_index, transfers, joined_data, current);
        current_node.data = current;
        return last != current;
    }
};

void cuda_worklist::execute_analysis(DynamicArray<Node>& nodes, std::vector<Transfer>& transfers, const std::set<int>& taint_sources){
    Analyzer analyzer;

    worklist::NodeUploader<Node*> uploader;
    uploader.dev_nodes = (void**)&uploader.container;
    
    worklist::execute_some_analysis(analyzer, nodes, uploader, &transfers[0], transfers.size(), taint_sources);
}