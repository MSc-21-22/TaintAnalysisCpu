#include "analysis.h"
#include "../worklist/worklist.cuh"

using namespace cuda_worklist;
using namespace taint;

class Analyzer {
public:
    using NodeType = Node;
    using NodeContainer = Node*;

    __device__ bool analyze(Node& current_node, BitVector data[], int node_index, NodeContainer nodes, Transfer* transfers) {
        BitVector last = data[node_index];
        BitVector current = data[node_index];
        
        BitVector joined_data = join(current_node.predecessor_index, nodes, data);
        current.bitfield |= joined_data.bitfield & current_node.join_mask.bitfield;

        transfer_function(current_node.first_transfer_index, transfers, joined_data, current);
        data[node_index] = current;
        return last.bitfield != current.bitfield;
    }
};

std::vector<BitVector> cuda_worklist::execute_analysis(DynamicArray<Node>& nodes, std::vector<Transfer>& transfers, const std::vector<int>& taint_sources) {
    Analyzer analyzer;

    worklist::NodeUploader<Node*> uploader;
    uploader.dev_nodes = (void**)&uploader.container;

    return worklist::execute_some_analysis(analyzer, nodes, uploader, &transfers[0], transfers.size(), taint_sources);
}