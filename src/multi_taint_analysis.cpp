#include "multi_taint_analysis.h"
#include <cfg/transformations/taint_locator.h>

using namespace cpu_analysis;

BitVector join(Node& node, std::map<Node*, std::vector<BitVector>*>& states, int source_index){
    BitVector state = (*states[&node])[source_index];
    bool old_taint_constant = state[0];
    for(const std::shared_ptr<Node>& pred : node.predecessors){
        state |= (*states[pred.get()])[source_index];
    }

    //Dont propagate taint sources
    if(state[0] != old_taint_constant){
        state.flip_bit(0);
    }

    return state;
}

void analyze(Node& node, std::map<Node*, std::vector<BitVector>*>& states, std::vector<Transfer>::const_iterator start_transfer, int source_count){
    std::vector<BitVector>& state = *states[&node];
    for(int source_index = 0; source_index < source_count; ++source_index){
        auto transfer = start_transfer;
        BitVector joined_state = join(node, states, source_index);

        if(joined_state.bitfield == 0)
            continue;

        state[source_index] |= joined_state & transfer->join_mask;
        do{
            if(transfer->transfer_mask.has_overlap(joined_state)){
                state[source_index].set_bit(transfer->var_index);
            }
        }while(transfer++->uses_next);
    }
}

void cpu_multi::worklist(std::vector<StatefulNode<std::vector<BitVector>>>& nodes, const std::vector<int>& node_to_start_transfer, const std::vector<cpu_analysis::Transfer>& transfers, int source_count){
    std::vector<int> worklist;
    std::map<Node*, int> node_to_index;
    TaintSourceLocator locator;

    int taint_index = 0;
    for(int i = 0; i < nodes.size(); ++i){
        node_to_index.insert(std::make_pair(nodes[i].node.get(), i));
        
        //Allocate and initialize bitvectors
        nodes[i].get_state().resize(source_count);

        if(locator.is_taintsource(*nodes[i].node)){
            nodes[i].get_state(i)[taint_index++].set_bit(0);
            worklist.push_back(i);
        }
    }

    
    
    while (!worklist.empty()){
        int index = worklist.back();
        worklist.pop_back();
        
        StatefulNode<std::vector<BitVector>>& currentNode = nodes[index];

        std::vector<BitVector> oldState = currentNode.get_state();
        int offset = node_to_start_transfer[index];
        auto transfer = transfers.cbegin() + offset;
        analyze(*currentNode.node, *currentNode.states, transfer, source_count);

        if (currentNode.get_state() != oldState) {
            for(StatefulNode<std::vector<BitVector>>& succ : currentNode.get_successors()){
                int new_index = node_to_index.at(succ.node.get());
                worklist.push_back(new_index);
            }
        }
    }
}

void print_taint_source(SourcedTaintState& result, std::ostream& stream){
    stream << "\\n{ ";
    for (auto& variable_pair : result){
        if(variable_pair.second.size() == 0)
            continue;

        std::cout << variable_pair.first << ":[";
        for(auto& source : variable_pair.second){
            std::cout << source << ", ";
        }
        std::cout << "]\\n";
    }
    stream << "}";
}