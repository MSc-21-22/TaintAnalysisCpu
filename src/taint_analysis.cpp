#include "taint_analysis.h"
#include <cfg/transformations/taint_locator.h>

using namespace cpu_analysis;

BitVector join(const Node &node, std::map<Node*, BitVector*> &states)
{   
    BitVector state(1);
    for(const std::shared_ptr<Node>& pred : node.predecessors)
    {
        state |= *states[pred.get()];
    }
    return state;
}

void analyze(Node& node, BitVector& state, std::map<Node*, BitVector*>& states, std::vector<Transfer>::const_iterator transfer){
    BitVector joined_state = join(node, states);

    state |= joined_state & transfer->join_mask;
    do{
        if(transfer->transfer_mask.has_overlap(joined_state)){
            state.set_bit(transfer->var_index);
        }
    }while(transfer++->uses_next);
}

void cpu_analysis::worklist(std::vector<StatefulNode<BitVector>>& nodes, const std::vector<int>& node_to_start_transfer, const std::vector<Transfer>& transfers){
    std::vector<int> worklist;
    std::map<Node*, int> node_to_index;
    TaintSourceLocator locator;
    for(int i = nodes.size() - 1; i>=0; --i){
        node_to_index.insert(std::make_pair(nodes[i].node.get(), i));
        
        if(locator.is_taintsource(*nodes[i].node)){
            worklist.push_back(i);
        }
    }
    
    while (!worklist.empty()){
        int index = worklist.back();
        worklist.pop_back();
        
        StatefulNode<BitVector>& currentNode = nodes[index];

        BitVector oldState = currentNode.get_state();

        analyze(*currentNode.node, currentNode.get_state(index), *currentNode.states, transfers.cbegin() + node_to_start_transfer[index]);

        if (currentNode.get_state() != oldState) {
            for(StatefulNode<BitVector>& succ : currentNode.get_successors()){
                int new_index = node_to_index.at(succ.node.get());
                worklist.push_back(new_index);
            }
        }
    }
}