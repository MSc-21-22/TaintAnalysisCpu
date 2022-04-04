#include "taint_analysis.h"
#include <cfg/transformations/taint_locator.h>

using namespace cpu_analysis;

bool BitVector::operator[](int index) {
    return (bitfield & 1<<index) != 0;
}
BitVector& BitVector::operator|=(const BitVector& rhs){
    this->bitfield |= rhs.bitfield;
    return *this;
}

bool BitVector::operator!=(const BitVector& rhs) const{
    return this->bitfield != rhs.bitfield;
}

BitVector BitVector::operator|(const BitVector& rhs) const{
    return BitVector(this->bitfield | rhs.bitfield);
}

BitVector BitVector::operator&(const BitVector& rhs) const {
    return BitVector(this->bitfield & rhs.bitfield);
}

bool BitVector::has_overlap(const BitVector&rhs) const{
    return (this->bitfield & rhs.bitfield) != 0;
}

void BitVector::set_bit(int index){
    bitfield |= 1<<index;
}
void BitVector::flip_bit(int index){
    bitfield ^= 1<<index;
}

BitVector join(const Node &node, std::map<Node*, BitVector> &states)
{   
    if(node.predecessors.size() == 0)
        return BitVector(1);

    auto it = node.predecessors.begin();
    auto state = states[it->get()];
    it++;
    while(it != node.predecessors.end())
    {
        state |= states[it->get()];
        it++;
    }
    return state;
}

void analyze(Node& node, std::map<Node*, BitVector>& states, std::vector<Transfer>::const_iterator transfer){
    BitVector joined_state = join(node, states);

    states[&node] |= joined_state & transfer->join_mask;
    do{
        if(transfer->transfer_mask.has_overlap(joined_state)){
            states[&node].set_bit(transfer->var_index);
        }
    }while(transfer++->uses_next);
}

#include <iostream>

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

        analyze(*currentNode.node, *currentNode.states, transfers.cbegin() + node_to_start_transfer[index]);

        if (currentNode.get_state() != oldState) {
            for(StatefulNode<BitVector>& succ : currentNode.get_successors()){
                int new_index = node_to_index.at(succ.node.get());
                worklist.push_back(new_index);
            }
        }
    }
}