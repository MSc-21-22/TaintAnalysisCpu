#include "analysis.h"
#include "../worklist/worklist.cuh"

using namespace multi_taint;

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
        BitVector joined_data;
        int pred_index = 0;
        while (predecessors[pred_index] != -1){
            joined_data.bitfield |= nodes[predecessors[pred_index]].data[source_index].bitfield;
            ++pred_index;
        }
        return joined_data;
    }

public:
    Analyzer(int source_count) : source_count(source_count){}

    __device__ bool analyze(Node& current_node, NodeContainer& nodes, Transfer* transfers){
        bool add_successors = false;
        for(int source = 0; source < source_count; ++source){
            BitVector joined_data = multi_cuda_join(current_node.predecessor_index, nodes, source);

            BitVector last = current_node.data[source];
            BitVector current = last;
            
            joined_data.bitfield |= current.bitfield;

            if(joined_data.bitfield == 0)
                continue;

            transfer_function(current_node.first_transfer_index, transfers, joined_data, current);

            current.bitfield |= joined_data.bitfield & current_node.join_mask.bitfield;
            if(last.bitfield != current.bitfield){
                current_node.data[source] = current;
                add_successors = true;
            }
        }
        return add_successors;
    }
};

void multi_cuda::execute_analysis(DynamicArray<Node>& nodes, std::vector<Transfer>& transfers, const std::set<int>& taint_sources, int source_count){
    //Analyzer analyzer(source_count);

    //worklist::NodeUploader<SizedArray<Node>> uploader;
    //uploader.container.item_size = nodes.get_item_size();
    //uploader.dev_nodes = (void**)&uploader.container.items;

    //worklist::execute_some_analysis(analyzer, nodes, uploader, &transfers[0], transfers.size(), taint_sources);
}