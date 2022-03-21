#include "cfg.h"
#include <algorithm>

bool contains(const std::vector<std::shared_ptr<Node>>& vector, const std::shared_ptr<Node>& node){
    return std::count(vector.begin(), vector.end(), node) != 0;
}

void Node::add_successor(std::shared_ptr<Node> node){
    if(!contains(successors, node)){
        successors.push_back(node);
    }
}
void Node::add_predecessor(std::shared_ptr<Node> node){
    if(!contains(predecessors, node)){
        predecessors.push_back(node);
    }
}