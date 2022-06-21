#include "taint_analysis.h"
#include <map>

using namespace cpu_analysis;
using namespace taint;

BitVector join(const Node &node, std::vector<BitVector>& data)
{   
    BitVector state(1);
    for (int i = 0; i < 5 && node.predecessor_index[i] != -1; ++i) {
        state |= data[node.predecessor_index[i]];
    }
    return state;
}

void transfer(const std::vector<Transfer>& transfers, int first_transfer_index, BitVector& joined_state, BitVector& current)
{
    const Transfer* transfer = &transfers[first_transfer_index];
    do {
        if (transfer->rhs.has_overlap(joined_state)) {
            current.set_bit(transfer->var_index);
        }
    } while (transfer++->next_transfer_index != -1);
}

void analyze(Node& node, int current_index, std::vector<BitVector>& data, const std::vector<Transfer>& transfers){
    BitVector joined_state = join(node, data);

    data[current_index] |= joined_state & node.join_mask;

    if (node.first_transfer_index != -1) {
        transfer(transfers, node.first_transfer_index, joined_state, data[current_index]);
    }
}

std::vector<BitVector> cpu_analysis::worklist(DynamicArray<Node>& nodes, const std::vector<Transfer>& transfers, std::vector<int> worklist) {
    std::vector<BitVector> data(nodes.size(), 1);
    while (!worklist.empty()){
        int index = worklist.back();
        worklist.pop_back();
        
        Node& currentNode = nodes[index];

        BitVector oldState = data[index];

        analyze(currentNode, index, data, transfers);

        if (data[index] != oldState) {
            for (int i = 0; i < 5 && currentNode.successor_index[i] != -1; ++i) {
                int new_index = currentNode.successor_index[i];
                worklist.push_back(new_index);
            }
        }
    }
    return data;
}