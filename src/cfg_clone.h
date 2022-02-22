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

    void visit_assignment(AssignmentNode<LatticeType>& node){
        auto new_node =clone_node<AssignmentNode<LatticeType>>(node);
        new_node->expression = node.expression->deep_copy();
    }
    void visit_arrayAssignment(ArrayAssignmentNode<LatticeType>& node){
        auto new_node = clone_node<ArrayAssignmentNode<LatticeType>>(node);
        new_node->expression = node.expression->deep_copy();
    }
    void visit_return(ReturnNode<LatticeType>& node){
        auto new_node = clone_node<ReturnNode<LatticeType>>(node);
        new_node->expression = node.expression->deep_copy();
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

        for(std::shared_ptr<Expression>& arg : clone->arguments){
            arg = arg->deep_copy();
        }

        clone->exit = std::static_pointer_cast<PropagationNode<LatticeType>>(nodeConverter.at(node.exit.get()));
        node_vector->push_back(clone);
        set_successors(clone);

    }
    void visit_assignReturn(AssignReturnNode<LatticeType>& node) {
        clone_node<AssignReturnNode<LatticeType>>(node);
    }
    void visit_arrayinit(ArrayInitializerNode<LatticeType>& node){
        auto new_node = clone_node<ArrayInitializerNode<LatticeType>>(node);
        for(std::shared_ptr<Expression>& arg : new_node->arrayContent) {
            arg = arg->deep_copy();
        }
    }
    void visit_propagation(PropagationNode<LatticeType>& node){
        clone_node<PropagationNode<LatticeType>>(node);
    }
};

template<typename LatticeType>
std::shared_ptr<FunctionEntryNode<LatticeType>> clone_entry(std::shared_ptr<FunctionEntryNode<LatticeType>> entry, std::vector<std::shared_ptr<Node<LatticeType>>>* node_vector){
    Cloner<LatticeType> cloner(node_vector);
    entry->accept(cloner);

    auto result = cloner.nodeConverter.at(entry.get());
    return std::static_pointer_cast<FunctionEntryNode<LatticeType>>(result);
}