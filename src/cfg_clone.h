#pragma once
#include "cfg.h"
#include <map>
#include <vector>

template<typename LatticeType>
class Cloner : public CfgVisitor<LatticeType> {
public:
    std::map<void*, std::shared_ptr<Node<LatticeType>>> nodeConverter;
private:
    std::vector<std::shared_ptr<Node<LatticeType>>>* node_vector;



    void visit_children(Node<LatticeType>& node, CfgVisitor<LatticeType>& visitor){
        for(auto& succ : node.successors){
            succ->accept(visitor);
        }
    }

    void set_successors(std::shared_ptr<Node<LatticeType>> node){
        auto old_successors = node->successors;
        node->successors = {};

        for(auto& succ : old_successors){
            auto other = nodeConverter[succ.get()];
            node->successors.insert(other);
            other->predecessors.insert(node);
        }
    }

    bool has_created(Node<LatticeType>& node) {
        return nodeConverter.find(&node) != nodeConverter.end();
    }

    template<typename NodeType>
    std::shared_ptr<NodeType> clone_node(NodeType& node){
        if(has_created(node))
            return nullptr;

        auto clone = std::make_shared<NodeType>(node);
        clone->predecessors = {};
        nodeConverter[&node] = clone;
        visit_children(node, *this);
        
        node_vector->push_back(clone);
        set_successors(clone);

        return clone;
    }
public:

    Cloner(std::vector<std::shared_ptr<Node<LatticeType>>>* node_vector): node_vector(node_vector){}

    void visit_initializtion(InitializerNode<LatticeType>& node){
        clone_node<InitializerNode<LatticeType>>(node);
    }
    void visit_assignment(AssignmentNode<LatticeType>& node){
        clone_node<AssignmentNode<LatticeType>>(node);
    }
    void visit_arrayAssignment(ArrayAssignmentNode<LatticeType>& node){
        clone_node<ArrayAssignmentNode<LatticeType>>(node);
    }
    void visit_if(IfNode<LatticeType>& node){
        clone_node<IfNode<LatticeType>>(node);
    }
    void visit_functioncall(FunctionCall<LatticeType>& node){
        clone_node<FunctionCall<LatticeType>>(node);
    }
    void visit_functiondef(FunctionDefinition<LatticeType>& node){
        clone_node<FunctionDefinition<LatticeType>>(node);
    }
    void visit_return(ReturnNode<LatticeType>& node){
        clone_node<ReturnNode<LatticeType>>(node);
    }
    void visit_whileloop(WhileLoop<LatticeType>& node){
        clone_node<WhileLoop<LatticeType>>(node);
    }
    void visit_emptyReturn(EmptyReturnNode<LatticeType>& node){
        clone_node<EmptyReturnNode<LatticeType>>(node);
    }
    void visit_functionEntry(FunctionEntryNode<LatticeType>& node){
        if(has_created(node))
            return;

        visit_children(node, *this);
        auto clone = std::make_shared<FunctionEntryNode<LatticeType>>(node);
        clone->predecessors = {};
        nodeConverter[&node] = clone;

        clone->exit = std::static_pointer_cast<FunctionExitNode<LatticeType>>(nodeConverter.at(node.exit.get()));
        node_vector->push_back(clone);
        set_successors(clone);
    }
    void visit_functionExit(FunctionExitNode<LatticeType>& node){
        clone_node<FunctionExitNode<LatticeType>>(node);
    }
    void visit_assignReturn(AssignReturnNode<LatticeType>& node) {
        clone_node<AssignReturnNode<LatticeType>>(node);
    }
};

template<typename LatticeType>
std::shared_ptr<FunctionEntryNode<LatticeType>> clone_entry(std::shared_ptr<FunctionEntryNode<LatticeType>> entry, std::vector<std::shared_ptr<Node<LatticeType>>>* node_vector){
    Cloner<LatticeType> cloner(node_vector);
    entry->accept(cloner);

    auto result = cloner.nodeConverter.at(entry.get());
    return std::static_pointer_cast<FunctionEntryNode<LatticeType>>(result);
}