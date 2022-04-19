#pragma once

#include <unordered_set>
#include <memory>
#include <string>
#include <vector>
#include "iostream"
#include <ostream>
#include "Expression.h"

#define RETURN_VAR "$return"
#define TAINT_VAR "$"

class Node;
class AssignmentNode;
class ReturnNode;
class EmptyReturnNode;
class FunctionEntryNode;
class PropagationNode;
class AssignReturnNode;
class ArrayAssignmentNode;
class ArrayInitializerNode;

class CfgVisitor {
public:
    virtual void visit_assignment(AssignmentNode& node) = 0;
    virtual void visit_return(ReturnNode& node) = 0;
    virtual void visit_emptyReturn(EmptyReturnNode& node) = 0;
    virtual void visit_functionEntry(FunctionEntryNode& node) = 0;
    virtual void visit_assignReturn(AssignReturnNode& node) = 0;
    virtual void visit_arrayAssignment(ArrayAssignmentNode& node) = 0;
    virtual void visit_arrayinit(ArrayInitializerNode& node) = 0;
    virtual void visit_propagation(PropagationNode& node) = 0;
};

template<typename LatticeType>
class CfgStateVisitor {
public:
    virtual void visit_assignment(AssignmentNode& node, std::map<Node*, LatticeType*>& states) = 0;
    virtual void visit_return(ReturnNode& node, std::map<Node*, LatticeType*>& states) = 0;
    virtual void visit_emptyReturn(EmptyReturnNode& node, std::map<Node*, LatticeType*>& states) = 0;
    virtual void visit_functionEntry(FunctionEntryNode& node, std::map<Node*, LatticeType*>& states) = 0;
    virtual void visit_assignReturn(AssignReturnNode& node, std::map<Node*, LatticeType*>& states) = 0;
    virtual void visit_arrayAssignment(ArrayAssignmentNode& node, std::map<Node*, LatticeType*>& states) = 0;
    virtual void visit_arrayinit(ArrayInitializerNode& node, std::map<Node*, LatticeType*>& states) = 0;
    virtual void visit_propagation(PropagationNode& node, std::map<Node*, LatticeType*>& states) = 0;
};

class Node {
public:
    std::vector<std::shared_ptr<Node>> predecessors;
    std::vector<std::shared_ptr<Node>> successors;
    std::shared_ptr<FunctionEntryNode> entry_node;
    int node_index{ -1 };

    virtual void accept(CfgVisitor& visitor)=0;

    void add_successor(std::shared_ptr<Node> node);
    void add_predecessor(std::shared_ptr<Node> node);
};

class ArrayInitializerNode : public Node {
public:
    std::string type;
    std::string id;
    int var_index{ -1 };
    std::string arraySize;
    std::vector<std::shared_ptr<Expression>> arrayContent;

    ArrayInitializerNode(std::string type,
                        std::string id,
                        std::string arraySize, 
                        std::vector<std::shared_ptr<Expression>> arrayContent)
                            : type(type), id(id), arraySize(arraySize), arrayContent(arrayContent){}
    ArrayInitializerNode() = default;

    void accept(CfgVisitor& visitor){
        visitor.visit_arrayinit(*this);
    }
};

class AssignmentNode : public Node {
public:
    std::string id;
    int var_index{ -1 };
    std::shared_ptr<Expression> expression;

    AssignmentNode(std::string id, std::shared_ptr<Expression> expression) : id(id), expression(expression){}
    AssignmentNode() = default;

    void accept(CfgVisitor& visitor){
        visitor.visit_assignment(*this);
    }
};

class ArrayAssignmentNode : public Node {
public:
    std::string id;
    int var_index{ -1 };
    std::string arrayid;
    std::shared_ptr<Expression> expression;

    ArrayAssignmentNode(std::string id,
                        std::string arrayid,
                        std::shared_ptr<Expression> expression)
                            : id(id), arrayid(arrayid), expression(expression) {}
    ArrayAssignmentNode() = default;

    void accept(CfgVisitor& visitor){
        visitor.visit_arrayAssignment(*this);
    }
};

class ReturnNode : public Node {
public:
    std::shared_ptr<Expression> expression;
    std::string functionId;

    ReturnNode(std::shared_ptr<Expression> expr, std::string functionId) : expression(expr), functionId(functionId) {}
    ReturnNode() = default;

    void accept(CfgVisitor& visitor){
        visitor.visit_return(*this);
    }
};


class EmptyReturnNode : public Node {
public:
    std::string functionId;

    EmptyReturnNode(std::string functionId) : functionId(functionId) {}
    EmptyReturnNode() = default;

    void accept(CfgVisitor& visitor){
        visitor.visit_emptyReturn(*this);
    }
};

class FunctionEntryNode : public Node {
public:
    std::shared_ptr<PropagationNode> exit;
    std::string function_id;
    std::vector<std::shared_ptr<Expression>> arguments;
    std::vector<std::string> formal_parameters;
    std::vector<int> formal_parameter_indexes{};

    std::vector<std::string> variable_reduction;

    FunctionEntryNode(std::string function_id, std::vector<std::string> formal_parameters) : function_id(function_id), formal_parameters(formal_parameters) {
        exit = std::make_shared<PropagationNode>("Exit");
    }

    void accept(CfgVisitor& visitor){
        visitor.visit_functionEntry(*this);
    }
};

class AssignReturnNode : public Node {
public:
    std::string id;
    int var_index{ -1 };

    AssignReturnNode(std::string id) : id(id) {}
    AssignReturnNode() = default;

    void accept(CfgVisitor& visitor){
        visitor.visit_assignReturn(*this);
    }
};

class PropagationNode : public Node {
public:
    std::string syntax;

    PropagationNode(std::string syntax) : syntax(syntax) {}
    PropagationNode() = default;

    void accept(CfgVisitor& visitor){
        visitor.visit_propagation(*this);
    }
};

template<typename LatticeType>
class StatefulNode {
public:
    std::shared_ptr<Node> node;
    std::shared_ptr<std::map<Node*, LatticeType*>> states;
    std::shared_ptr<std::vector<LatticeType>> states_vec;

    StatefulNode(std::shared_ptr<Node> node) : node(node) {
        states = std::make_shared<std::map<Node*, LatticeType*>>();
        states_vec = std::make_shared<std::vector<LatticeType>>();
    }

    StatefulNode(std::shared_ptr<Node> node, std::shared_ptr<std::map<Node*, LatticeType*>> states, std::shared_ptr<std::vector<LatticeType>> states_vec) : node(node), states(states), states_vec(states_vec) {
        
    }

    std::vector<StatefulNode<LatticeType>> get_successors() {
        std::vector<StatefulNode<LatticeType>> nodes;
        for(std::shared_ptr<Node> succ : node->successors){
            nodes.emplace_back(succ, states, states_vec);
        }
        return nodes;
    }

    std::vector<StatefulNode<LatticeType>> get_predecessors() {
        std::vector<StatefulNode<LatticeType>> nodes;
        for(std::shared_ptr<Node> pred : node->predecessors){
            nodes.emplace_back(pred, states, states_vec);
        }
        return nodes;
    }

    LatticeType& get_state() {
        return *(*states)[node.get()];
    }

    LatticeType& get_state(int absolute_index) {
        return (*states_vec)[absolute_index];
    }

    void accept(CfgStateVisitor<LatticeType>& visitor) {
        auto propagation_ptr = dynamic_cast<PropagationNode*>(node.get());
        if(propagation_ptr){
            visitor.visit_propagation(*propagation_ptr, *states);
            return;
        }
        auto assignment_ptr = dynamic_cast<AssignmentNode*>(node.get());
        if(assignment_ptr){
            visitor.visit_assignment(*assignment_ptr, *states);
            return;
        }
        auto return_ptr = dynamic_cast<ReturnNode*>(node.get());
        if(return_ptr) {
            visitor.visit_return(*return_ptr, *states);
            return;
        }
        auto empty_return_ptr = dynamic_cast<EmptyReturnNode*>(node.get());
        if(empty_return_ptr){
            visitor.visit_emptyReturn(*empty_return_ptr, *states);
            return;
        }
        auto function_entry_ptr = dynamic_cast<FunctionEntryNode*>(node.get());
        if(function_entry_ptr){
            visitor.visit_functionEntry(*function_entry_ptr, *states);
            return;
        }
        auto assign_return_node = dynamic_cast<AssignReturnNode*>(node.get());
        if(assign_return_node){
            visitor.visit_assignReturn(*assign_return_node, *states);
            return;
        }
        auto array_assignment_ptr = dynamic_cast<ArrayAssignmentNode*>(node.get()); 
        if(array_assignment_ptr){
            visitor.visit_arrayAssignment(*array_assignment_ptr, *states);
            return;
        }
        auto array_init_ptr = dynamic_cast<ArrayInitializerNode*>(node.get());
        if(array_init_ptr){
            visitor.visit_arrayinit(*array_init_ptr, *states);
        }
    }

    void accept(CfgVisitor& visitor) {
        node->accept(visitor);
    }
};

template<typename LatticeType>
std::vector<StatefulNode<LatticeType>> create_states(std::vector<std::shared_ptr<Node>>& nodes, const LatticeType default_state = {}){
    std::vector<StatefulNode<LatticeType>> stateful_nodes;
    
    auto states = std::make_shared<std::map<Node*, LatticeType*>>();
    //Preallocate to avoid dangling pointer upon resize
    auto states_vec = std::make_shared<std::vector<LatticeType>>(nodes.size());
    
    int i = 0;
    for(std::shared_ptr<Node>& node : nodes) {
        stateful_nodes.emplace_back(node, states, states_vec);
        (*states_vec)[i] = default_state;
        (*states)[node.get()] = &(*states_vec)[i];
        ++i;
    }

    return stateful_nodes;
}
