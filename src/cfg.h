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
    virtual void visit_assignment(AssignmentNode& node, std::map<Node*, LatticeType>& states) = 0;
    virtual void visit_return(ReturnNode& node, std::map<Node*, LatticeType>& states) = 0;
    virtual void visit_emptyReturn(EmptyReturnNode& node, std::map<Node*, LatticeType>& states) = 0;
    virtual void visit_functionEntry(FunctionEntryNode& node, std::map<Node*, LatticeType>& states) = 0;
    virtual void visit_assignReturn(AssignReturnNode& node, std::map<Node*, LatticeType>& states) = 0;
    virtual void visit_arrayAssignment(ArrayAssignmentNode& node, std::map<Node*, LatticeType>& states) = 0;
    virtual void visit_arrayinit(ArrayInitializerNode& node, std::map<Node*, LatticeType>& states) = 0;
    virtual void visit_propagation(PropagationNode& node, std::map<Node*, LatticeType>& states) = 0;
};

template<typename LatticeType>
class StatefulNode {
public:
    std::shared_ptr<Node> node;
    std::shared_ptr<std::map<Node*, LatticeType>> states;

    StatefulNode(std::shared_ptr<Node> node) : node(node) {
        states = std::make_shared<std::map<Node*, LatticeType>>();
    }

    StatefulNode(std::shared_ptr<Node> node, std::shared_ptr<std::map<Node*, LatticeType>> states) : node(node), states(states) {
        
    }

    std::vector<StatefulNode<LatticeType>> get_successors() const{
        std::vector<StatefulNode<LatticeType>> nodes;
        for(std::shared_ptr<Node> succ : node->successors){
            nodes.emplace_back(succ, states);
        }
        return nodes;
    }

    std::vector<StatefulNode<LatticeType>> get_predecessors() const{
        std::vector<StatefulNode<LatticeType>> nodes;
        for(std::shared_ptr<Node> succ : node->predecessors){
            nodes.emplace_back(succ, states);
        }
        return nodes;
    }

    LatticeType& get_state() {
        return (*states)[node.get()];
    }

    void accept(CfgStateVisitor<LatticeType>& visitor) {
        if(auto node_ptr = dynamic_cast<PropagationNode*>(node.get()); node_ptr){
            visitor.visit_propagation(*node_ptr, *states);
        }else if(auto node_ptr = dynamic_cast<AssignmentNode*>(node.get()); node_ptr){
            visitor.visit_assignment(*node_ptr, *states);
        }else if(auto node_ptr = dynamic_cast<ReturnNode*>(node.get()); node_ptr){
            visitor.visit_return(*node_ptr, *states);
        }else if(auto node_ptr = dynamic_cast<EmptyReturnNode*>(node.get()); node_ptr){
            visitor.visit_emptyReturn(*node_ptr, *states);
        }else if(auto node_ptr = dynamic_cast<FunctionEntryNode*>(node.get()); node_ptr){
            visitor.visit_functionEntry(*node_ptr, *states);
        }else if(auto node_ptr = dynamic_cast<AssignReturnNode*>(node.get()); node_ptr){
            visitor.visit_assignReturn(*node_ptr, *states);
        }else if(auto node_ptr = dynamic_cast<ArrayAssignmentNode*>(node.get()); node_ptr){
            visitor.visit_arrayAssignment(*node_ptr, *states);
        }else if(auto node_ptr = dynamic_cast<ArrayInitializerNode*>(node.get()); node_ptr){
            visitor.visit_arrayinit(*node_ptr, *states);
        }
    }
};

template<typename LatticeType>
StatefulNode<LatticeType> create_state(std::shared_ptr<std::shared_ptr<Node>> node) {
    return StatefulNode<LatticeType>(node);
}

template<typename LatticeType>
std::vector<StatefulNode<LatticeType>> create_states(std::vector<std::shared_ptr<Node>>& nodes, const LatticeType default_state = {}){
    std::vector<StatefulNode<LatticeType>> stateful_nodes;
    
    auto states = std::make_shared<std::map<Node*, LatticeType>>();
    
    for(std::shared_ptr<Node>& node : nodes) {
        stateful_nodes.emplace_back(node, states);
        (*states)[node.get()] = default_state;
    }

    return stateful_nodes;
}


class Node {
public:
    std::set<std::shared_ptr<Node>> predecessors;
    std::set<std::shared_ptr<Node>> successors;

    virtual void accept(CfgVisitor& visitor)=0;
};

class ArrayInitializerNode : public Node {
public:
    std::string type;
    std::string id;
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

