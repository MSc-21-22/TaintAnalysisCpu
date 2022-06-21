#include "multi_taint_analysis.h"

using namespace cpu_analysis;
using namespace multi_taint;

BitVector join(Node& node, DynamicArray<Node>& nodes, int source_index){
    BitVector state = node.data[source_index];
    bool old_taint_constant = state[0];
    for (int i = 0; i < 5 && node.predecessor_index[i] != -1; ++i) {
        state |= nodes[node.predecessor_index[i]].data[source_index];
    }

    //Dont propagate taint sources
    if(state[0] != old_taint_constant){
        state.flip_bit(0);
    }

    return state;
}

void transfer(const std::vector<Transfer>& transfers, multi_taint::Node& node, BitVector& joined_state, int source_index)
{
    const Transfer* transfer = &transfers[node.first_transfer_index];
    do {
        if (transfer->rhs.has_overlap(joined_state)) {
            node.data[source_index].set_bit(transfer->var_index);
        }
    } while (transfer++->next_transfer_index != -1);
}

void analyze(Node& node, DynamicArray<Node>& nodes, const std::vector<Transfer>& transfers, int source_count){
    for(int source_index = 0; source_index < source_count; ++source_index){
        BitVector joined_state = join(node, nodes, source_index);

        if(joined_state.bitfield == 0)
            continue;

        node.data[source_index] |= joined_state & node.join_mask;

        if (node.first_transfer_index != -1) {
            transfer(transfers, node, joined_state, source_index);
        }
    }
}

bool is_source_node(const Node& node, const std::vector<Transfer>& transfers) {
    const Transfer* transfer = &transfers[node.first_transfer_index];
    do {
        if (transfer->rhs[0]) {
            return true;
        }
    } while (transfer++->next_transfer_index != -1);
    return false;
}

void cpu_multi::worklist(DynamicArray<multi_taint::Node>& nodes, const std::vector<Transfer>& transfers, int source_count){
    std::vector<int> worklist(source_count);
    std::map<Node*, int> node_to_index;

    int taint_index = 0;
    for(int i = 0; i < nodes.size(); ++i){
        if(is_source_node(nodes[i], transfers)) {
            nodes[i].data[taint_index++].set_bit(0);
            worklist.push_back(i);
        }
    }

    
    
    while (!worklist.empty()){
        int index = worklist.back();
        worklist.pop_back();
        
        Node& currentNode = nodes[index];
        
        std::vector<BitVector> oldState(source_count);
        std::copy(currentNode.data, currentNode.data + source_count, oldState.data());

        analyze(currentNode, nodes, transfers, source_count);

        if (memcmp(currentNode.data, oldState.data(), sizeof(BitVector) * source_count)) {
            for (int i = 0; i < 5 && currentNode.successor_index[i] != -1; ++i) {
                worklist.push_back(currentNode.successor_index[i]);
            }
        }
    }
}