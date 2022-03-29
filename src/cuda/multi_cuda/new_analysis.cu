#include "analysis.h"
#include "../worklist/analysis.cuh"

using namespace multi_cuda;

template<typename Node>
struct SizedArray{
public:
    char* items;
    int item_size;
    __device__ Node& operator[](int index) {
        return * (Node*) (items + (index * item_size));
    }
};

class Analyzer {
public:
    using NodeType = Node;
    using NodeContainer = SizedArray<NodeType>;
private:
    int source_count;

    __device__ BitVector multi_cuda_join(int predecessors[], NodeContainer& nodes, int source_index){
        BitVector joined_data = 0;
        int pred_index = 0;
        while (predecessors[pred_index] != -1){
            joined_data |= nodes[predecessors[pred_index]].data[source_index];
            ++pred_index;
        }
        return joined_data;
    }

public:
    Analyzer(int source_count) : source_count(source_count){}

    __device__ bool analyze(Node& current_node, NodeContainer& nodes, Transfer* transfers){
        bool add_successors = false;
        for(int source = 0; source < source_count; ++source){
            BitVector last = current_node.data[source];
            BitVector current = last;


            BitVector joined_data = multi_cuda_join(current_node.predecessor_index, nodes, source);
            current |= joined_data & current_node.join_mask;
            
            joined_data |= current;
            transfer_function(current_node.first_transfer_index, transfers, joined_data, current);

            if(last != current){
                current_node.data[source] = current;
                add_successors = true;
            }
        }
        return add_successors;
    }
};

void multi_cuda::generic_analysis(DynamicArray<Node>& nodes, std::vector<Transfer>& transfers, const std::set<int>& taint_sources, int source_count){
    Analyzer analyzer(source_count);
    
    worklist::NodeUploader<SizedArray<Node>> uploader;
    uploader.container.item_size = nodes.get_item_size();
    uploader.dev_nodes = (void**)&uploader.container.items;

    worklist::execute_some_analysis(analyzer, nodes, uploader, &transfers[0], transfers.size(), taint_sources);
}