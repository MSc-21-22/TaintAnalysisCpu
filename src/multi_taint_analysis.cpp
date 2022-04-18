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

void analyze(Node& node, std::map<Node*, std::vector<BitVector>*>& states, std::vector<Transfer>::const_iterator transfer, int source_count){
    for(int source_index = 0; source_index < source_count; ++source_index){
        BitVector joined_state = join(node, states, source_index);

        (*states[&node])[source_index] |= joined_state & transfer->join_mask;
        do{
            if(transfer->transfer_mask.has_overlap(joined_state)){
                (*states[&node])[source_index].set_bit(transfer->var_index);
            }
        }while(transfer++->uses_next);
    }
}

void cpu_multi::worklist(std::vector<StatefulNode<std::vector<BitVector>>>& nodes, const std::vector<int>& node_to_start_transfer, const std::vector<cpu_analysis::Transfer>& transfers, int source_count){
    std::vector<int> worklist;
    std::map<Node*, int> node_to_index;
    TaintSourceLocator locator;
    for(int i = nodes.size() - 1; i>=0; --i){
        node_to_index.insert(std::make_pair(nodes[i].node.get(), i));
        
        //Allocate and initialize bitvectors
        nodes[i].get_state().resize(source_count);

        if(locator.is_taintsource(*nodes[i].node)){
            worklist.push_back(i);
        }
    }

    
    
    while (!worklist.empty()){
        int index = worklist.back();
        worklist.pop_back();
        
        StatefulNode<std::vector<BitVector>>& currentNode = nodes[index];

        std::vector<BitVector> oldState = currentNode.get_state();

        analyze(*currentNode.node, *currentNode.states, transfers.cbegin() + node_to_start_transfer[index], source_count);

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