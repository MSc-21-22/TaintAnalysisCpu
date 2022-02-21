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
class ArrayAssignmentNode;
template<typename LatticeType>
class ArrayInitializerNode;

template<typename LatticeType>
class CfgVisitor {
public:
    virtual void visit_assignment(AssignmentNode<LatticeType>& node) = 0;
    virtual void visit_return(ReturnNode<LatticeType>& node) = 0;
    virtual void visit_emptyReturn(EmptyReturnNode<LatticeType>& node) = 0;
    virtual void visit_functionEntry(FunctionEntryNode<LatticeType>& node) = 0;
    virtual void visit_assignReturn(AssignReturnNode<LatticeType>& node) = 0;
    virtual void visit_arrayAssignment(ArrayAssignmentNode<LatticeType>& node) = 0;
    virtual void visit_arrayinit(ArrayInitializerNode<LatticeType>& node) = 0;
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
class ArrayInitializerNode : public Node<LatticeType> {
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
    ArrayInitializerNode(ArrayInitializerNode<LatticeType>&& node) = default;
    ArrayInitializerNode(const ArrayInitializerNode<LatticeType>& node) = default;
    ArrayInitializerNode& operator=(const ArrayInitializerNode<LatticeType>& node) = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_arrayinit(*this);
    }
};

template<typename LatticeType>
class AssignmentNode : public Node<LatticeType> {
public:
    std::string id;
    std::shared_ptr<Expression> expression;

    AssignmentNode(AssignmentNode<LatticeType>&& node) = default;
    AssignmentNode(std::string id, std::shared_ptr<Expression> expression) : id(id), expression(expression){}
    AssignmentNode() = default;
    AssignmentNode(const AssignmentNode<LatticeType>& node) = default;
    AssignmentNode& operator=(const AssignmentNode<LatticeType>& node) = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_assignment(*this);
    }
};

template<typename LatticeType>
class ArrayAssignmentNode : public Node<LatticeType> {
public:
    std::string id;
    std::string arrayid;
    std::shared_ptr<Expression> expression;

    ArrayAssignmentNode(ArrayAssignmentNode<LatticeType>&& node) = default;
    ArrayAssignmentNode(std::string id,
                        std::string arrayid,
                        std::shared_ptr<Expression> expression)
                            : id(id), arrayid(arrayid), expression(expression) {}
    ArrayAssignmentNode() = default;
    ArrayAssignmentNode(const ArrayAssignmentNode<LatticeType>& node) = default;
    ArrayAssignmentNode& operator=(const ArrayAssignmentNode<LatticeType>& node) = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_arrayAssignment(*this);
    }
};

template<typename LatticeType>
class ReturnNode : public Node<LatticeType> {
public:
    std::shared_ptr<Expression> expression;
    std::string functionId;

    ReturnNode(ReturnNode<LatticeType>&& node) = default;
    ReturnNode(std::shared_ptr<Expression> expr, std::string functionId) : expression(expr), functionId(functionId) {}
    ReturnNode() = default;
    ReturnNode(const ReturnNode<LatticeType>& node) = default;
    ReturnNode& operator=(const ReturnNode<LatticeType>& node) = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_return(*this);
    }
};


template<typename LatticeType>
class EmptyReturnNode : public Node<LatticeType> {
public:
    std::string functionId;

    EmptyReturnNode(EmptyReturnNode<LatticeType>&& node) = default;
    EmptyReturnNode(std::string functionId) : functionId(functionId) {}
    EmptyReturnNode() = default;
    EmptyReturnNode(const EmptyReturnNode<LatticeType>& node) = default;
    EmptyReturnNode& operator=(const EmptyReturnNode<LatticeType>& node) = default;

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
    FunctionEntryNode(FunctionEntryNode<LatticeType>&& node) = default;
    FunctionEntryNode(const FunctionEntryNode<LatticeType>& node) = default;
    FunctionEntryNode& operator=(const FunctionEntryNode<LatticeType>& node) = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_functionEntry(*this);
    }
};

template<typename LatticeType>
class AssignReturnNode : public Node<LatticeType> {
public:
    std::string id;

    AssignReturnNode(AssignReturnNode<LatticeType>&& node) = default;
    AssignReturnNode(std::string id) : id(id) {}
    AssignReturnNode() = default;
    AssignReturnNode(const AssignReturnNode<LatticeType>& node) = default;
    AssignReturnNode& operator=(const AssignReturnNode<LatticeType>& node) = default;

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
    PropagationNode(PropagationNode<LatticeType>&& node) = default;
    PropagationNode(const PropagationNode<LatticeType>& node) = default;
    PropagationNode& operator=(const PropagationNode<LatticeType>& node) = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_propagation(*this);
    }
};

