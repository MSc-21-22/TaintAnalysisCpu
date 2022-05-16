#include "taint_analysis.h"
#include <map>

using namespace cpu_analysis;
using namespace taint;

BitVector join(const Node &node, DynamicArray<Node>& nodes)
{   
    BitVector state(1);
    for (int i = 0; i < 5 && node.predecessor_index[i] != -1; ++i) {
        state |= nodes[node.predecessor_index[i]].data;
    }
    return state;
}

void transfer(const std::vector<Transfer>& transfers, taint::Node& node, BitVector& joined_state)
{
    const Transfer* transfer = &transfers[node.first_transfer_index];
    do {
        if (transfer->rhs.has_overlap(joined_state)) {
            node.data.set_bit(transfer->var_index);
        }
    } while (transfer++->next_transfer_index != -1);
}

void analyze(Node& node, DynamicArray<Node>& nodes, const std::vector<Transfer>& transfers){
    BitVector joined_state = join(node, nodes);

    node.data |= joined_state & node.join_mask;

    if (node.first_transfer_index != -1) {
        transfer(transfers, node, joined_state);
    }
}

void cpu_analysis::worklist(DynamicArray<Node>& nodes, const std::vector<Transfer>& transfers, std::vector<int> worklist){   
    while (!worklist.empty()){
        int index = worklist.back();
        worklist.pop_back();
        
        Node& currentNode = nodes[index];

        BitVector oldState = currentNode.data;

        analyze(currentNode, nodes, transfers);

        if (currentNode.data != oldState) {
            for (int i = 0; i < 5 && currentNode.successor_index[i] != -1; ++i) {
                int new_index = currentNode.successor_index[i];
                worklist.push_back(new_index);
            }
        }
    }
}