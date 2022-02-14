#pragma once

#include <unordered_set>
#include <memory>
#include <string>
#include <vector>
#include "iostream"
#include <ostream>
#include "Expression.h"

template<typename LatticeType>
class Node;
template<typename LatticeType>
class AssignmentNode;
template<typename LatticeType>
class ReturnNode;
template<typename LatticeType>
class EmptyReturnNode;
template<typename LatticeType>
class FunctionEntryNode;
template<typename LatticeType>
class PropagationNode;
template<typename LatticeType>
class AssignReturnNode;

template<typename LatticeType>
class CfgVisitor {
public:
    virtual void visit_assignment(AssignmentNode<LatticeType>& node) = 0;
    virtual void visit_return(ReturnNode<LatticeType>& node) = 0;
    virtual void visit_emptyReturn(EmptyReturnNode<LatticeType>& node) = 0;
    virtual void visit_functionEntry(FunctionEntryNode<LatticeType>& node) = 0;
    virtual void visit_assignReturn(AssignReturnNode<LatticeType>& node) = 0;
    virtual void visit_propagation(PropagationNode<LatticeType>& node) = 0;
};

template<typename LatticeType>
class Node {
public:
    std::set<std::shared_ptr<Node<LatticeType>>> predecessors;
    std::set<std::shared_ptr<Node<LatticeType>>> successors;
    LatticeType state;

    virtual void accept(CfgVisitor<LatticeType>& visitor)=0;
};

template<typename LatticeType>
class AssignmentNode : public Node<LatticeType> {
public:
    std::string id;
    std::shared_ptr<Expression> expression;

    AssignmentNode(std::string id, std::shared_ptr<Expression> expression) : id(id), expression(expression){}
    AssignmentNode() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_assignment(*this);
    }
};

template<typename LatticeType>
class ReturnNode : public Node<LatticeType> {
public:
    std::shared_ptr<Expression> expression;
    std::string functionId;

    ReturnNode(std::shared_ptr<Expression> expr, std::string functionId) : expression(expr), functionId(functionId) {}
    ReturnNode() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_return(*this);
    }
};


template<typename LatticeType>
class EmptyReturnNode : public Node<LatticeType> {
public:
    std::string functionId;

    EmptyReturnNode(std::string functionId) : functionId(functionId) {}
    EmptyReturnNode() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_emptyReturn(*this);
    }
};

template<typename LatticeType>
class FunctionEntryNode : public Node<LatticeType> {
public:
    std::shared_ptr<PropagationNode<LatticeType>> exit;
    std::string function_id;
    std::vector<std::shared_ptr<Expression>> arguments;
    std::vector<std::string> formal_parameters;

    FunctionEntryNode(std::string function_id, std::vector<std::string> formal_parameters) : function_id(function_id), formal_parameters(formal_parameters) {
        exit = std::make_shared<PropagationNode<LatticeType>>("Exit");
    }

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_functionEntry(*this);
    }
};

template<typename LatticeType>
class AssignReturnNode : public Node<LatticeType> {
public:
    std::string id;

    AssignReturnNode(std::string id) : id(id) {}
    AssignReturnNode() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_assignReturn(*this);
    }
};

template<typename LatticeType>
class PropagationNode : public Node<LatticeType> {
public:
    std::string syntax;

    PropagationNode(std::string syntax) : syntax(syntax) {}
    PropagationNode() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_propagation(*this);
    }
};

