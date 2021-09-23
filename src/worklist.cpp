#include "vector"
#include "cfg.h"

template<typename LaticeType, typename TransferFunction>
LaticeType worklist(std::vector<Node<LaticeType>> nodes, TransferFunction transferFunction){
    auto worklistLatice = std::copy(nodes.begin()->state);
    while (!nodes.empty()){
        auto currentNode = nodes[0];
        nodes.erase(0);
        auto transformedLactice = transferFunction(currentNode);
        if (transformedLactice != worklistLatice) {
            worklistLatice = transformedLactice;
            for(auto succ : currentNode.successors){
                nodes.push_back(succ);
            }
        }
    }
    return worklistLatice;
}