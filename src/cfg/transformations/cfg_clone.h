#pragma once
#include <cfg/cfg.h>
#include <map>
#include <vector>

class Cloner : public CfgVisitor {
public:
    std::map<void*, std::shared_ptr<Node>> nodeConverter;
    std::vector<std::shared_ptr<FunctionEntryNode>>& entry_nodes;
private:
    std::vector<std::shared_ptr<Node>>* node_vector;



    void visit_children(Node& node, CfgVisitor& visitor){
        for(auto& succ : node.successors){
            succ->accept(visitor);
        }
    }

    void set_successors(std::shared_ptr<Node> node){
        auto old_successors = node->successors;
        node->successors = {};

        for(auto& succ : old_successors){
            auto other = nodeConverter[succ.get()];
            node->add_successor(other);
            other->add_predecessor(node);
        }
    }

    bool has_created(Node& node) {
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

        clone->entry_node = entry_nodes.back();

        return clone;
    }
public:

    Cloner(std::vector<std::shared_ptr<Node>>* node_vector, std::vector<std::shared_ptr<FunctionEntryNode>>& entry_nodes): node_vector(node_vector), entry_nodes(entry_nodes) {}

    void visit_assignment(AssignmentNode& node){
        auto new_node = clone_node<AssignmentNode>(node);
        if(new_node.get() != nullptr){
            new_node->expression = node.expression->deep_copy();
        }
    }
    void visit_arrayAssignment(ArrayAssignmentNode& node){
        auto new_node = clone_node<ArrayAssignmentNode>(node);
        if(new_node.get() != nullptr){
            new_node->expression = node.expression->deep_copy();
        }
    }
    void visit_return(ReturnNode& node){
        auto new_node = clone_node<ReturnNode>(node);
        if(new_node.get() != nullptr){
            new_node->expression = node.expression->deep_copy();
        }
    }
    void visit_emptyReturn(EmptyReturnNode& node){
        clone_node<EmptyReturnNode>(node);
    }
    void visit_functionEntry(FunctionEntryNode& node){
        if(has_created(node))
            return;

        auto clone = std::make_shared<FunctionEntryNode>(node);
        entry_nodes.push_back(clone);
        clone->entry_node = clone;

        visit_children(node, *this);
        clone->predecessors = {};
        nodeConverter[&node] = clone;

        for(std::shared_ptr<Expression>& arg : clone->arguments){
            arg = arg->deep_copy();
        }

        clone->exit = std::static_pointer_cast<PropagationNode>(nodeConverter.at(node.exit.get()));
        node_vector->push_back(clone);
        set_successors(clone);

    }
    void visit_assignReturn(AssignReturnNode& node) {
        clone_node<AssignReturnNode>(node);
    }
    void visit_arrayinit(ArrayInitializerNode& node){
        auto new_node = clone_node<ArrayInitializerNode>(node);
        if(new_node.get() != nullptr){
            for(std::shared_ptr<Expression>& arg : new_node->arrayContent) {
                arg = arg->deep_copy();
            }
        }
    }
    void visit_propagation(PropagationNode& node){
        clone_node<PropagationNode>(node);
    }
};

std::shared_ptr<FunctionEntryNode> clone_entry(std::shared_ptr<FunctionEntryNode> entry, std::vector<std::shared_ptr<Node>>* node_vector, std::vector<std::shared_ptr<FunctionEntryNode>>& entry_nodes);