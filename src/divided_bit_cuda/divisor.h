#pragma once

#include "../cfg.h"
#include <vector>
#include "../transforms.h"

template<typename LatticeType>
class FunctionSeperator : public CfgVisitor<LatticeType>
{
    std::vector<std::shared_ptr<Node<LatticeType>>>* current_function;
    std::set<Node<LatticeType>*> visited_nodes{};

public:
    std::vector<std::vector<std::shared_ptr<Node<LatticeType>>>> function_split_nodes{};

    void visit_assignment(AssignmentNode<LatticeType>& node) override {
        visit_children(node);
        current_function->push_back(std::make_shared<AssignmentNode<LatticeType>>(node));
    }
    void visit_return(ReturnNode<LatticeType>& node) override {
        visit_children(node);
        current_function->push_back(std::make_shared<ReturnNode<LatticeType>>(node));
    }
    void visit_emptyReturn(EmptyReturnNode<LatticeType>& node) override {
        visit_children(node);
        current_function->push_back(std::make_shared<EmptyReturnNode<LatticeType>>(node));
    }
    void visit_functionEntry(FunctionEntryNode<LatticeType>& node) override {
        current_function = &function_split_nodes.emplace_back();
        visited_nodes.clear();
        visit_children(node);
        current_function->push_back(std::make_shared<FunctionEntryNode<LatticeType>>(node));
    }
    void visit_assignReturn(AssignReturnNode<LatticeType>& node) override {
        visit_children(node);
        current_function->push_back(std::make_shared<AssignReturnNode<LatticeType>>(node));
    }
    void visit_arrayAssignment(ArrayAssignmentNode<LatticeType>& node) override {
        visit_children(node);
        current_function->push_back(std::make_shared<ArrayAssignmentNode<LatticeType>>(node));
    }
    void visit_arrayinit(ArrayInitializerNode<LatticeType>& node) override {
        visit_children(node);
        current_function->push_back(std::make_shared<ArrayInitializerNode<LatticeType>>(node));
    }
    void visit_propagation(PropagationNode<LatticeType>& node) override {
        current_function->push_back(std::make_shared<PropagationNode<LatticeType>>(node));

        if(node.syntax != "Exit"){
            visit_children(node);
        }
    }
private:
    void visit_children(Node<LatticeType>& node) {
        for(auto& child_ptr : node.successors){
            if(dynamic_cast<FunctionEntryNode<LatticeType>*>(child_ptr.get()) == nullptr && visited_nodes.count(child_ptr.get()) == 0){
                visited_nodes.insert(child_ptr.get());
                child_ptr->accept(*this);
            }
        }
    }

};

template<typename LatticeType>
std::vector<std::vector<std::shared_ptr<Node<LatticeType>>>> split_by_function(std::vector<std::shared_ptr<FunctionEntryNode<LatticeType>>>& entry_nodes){
    FunctionSeperator<LatticeType> seperator;
    for(auto& entry_node : entry_nodes){
        entry_node->accept(seperator);
    }
    return seperator.function_split_nodes;
}