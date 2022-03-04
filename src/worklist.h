#pragma once
#include <vector>
#include <cfg/cfg.h>

template<typename LatticeType>
void worklist(std::vector<StatefulNode<LatticeType>> worklist, CfgStateVisitor<LatticeType>& transferFunction){
    while (!worklist.empty()){
        StatefulNode<LatticeType> currentNode = worklist.front();
        worklist.erase(worklist.begin());
        LatticeType oldState = currentNode.get_state();

        currentNode.accept(transferFunction);

        if (currentNode.get_state() != oldState) {
            for(StatefulNode<LatticeType>& succ : currentNode.get_successors()){
                worklist.push_back(succ);
            }
        }
    }
}