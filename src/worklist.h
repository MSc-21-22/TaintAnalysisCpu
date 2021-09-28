#include "vector"
#include "cfg.h"

template<typename LatticeType>
void worklist(std::vector<std::shared_ptr<Node<LatticeType>>> nodes, CfgVisitor<LatticeType>& transferFunction){
    while (!nodes.empty()){
        std::shared_ptr<Node<LatticeType>> currentNode = nodes.front();
        nodes.erase(nodes.begin());
        LatticeType oldState = currentNode->state;

        currentNode->accept(transferFunction);

        if (currentNode->state != oldState) {
            for(auto& succ : currentNode->successors){
                nodes.push_back(succ);
            }
        }
    }
}