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
class InitializerNode;
template<typename LatticeType>
class AssignmentNode;
template<typename LatticeType>
class IfNode;
template<typename LatticeType>
class FunctionCall;
template<typename LatticeType>
class FunctionDefinition;
template<typename LatticeType>
class ReturnNode;
template<typename LatticeType>
class WhileLoop;
template<typename LatticeType>
class EmptyReturnNode;
template<typename LatticeType>
class FunctionEntryNode;
template<typename LatticeType>
class FunctionExitNode;
template<typename LatticeType>
class AssignReturnNode;
template<typename LatticeType>
class ArrayAssignmentNode;

template<typename LatticeType>
class CfgVisitor {
public:
    virtual void visit_initializtion(InitializerNode<LatticeType>& node) = 0;
    virtual void visit_assignment(AssignmentNode<LatticeType>& node) = 0;
    virtual void visit_if(IfNode<LatticeType>& node) = 0;
    virtual void visit_functioncall(FunctionCall<LatticeType>& node) = 0;
    virtual void visit_functiondef(FunctionDefinition<LatticeType>& node) = 0;
    virtual void visit_return(ReturnNode<LatticeType>& node) = 0;
    virtual void visit_whileloop(WhileLoop<LatticeType>& node) = 0;
    virtual void visit_emptyReturn(EmptyReturnNode<LatticeType>& node) = 0;
    virtual void visit_functionEntry(FunctionEntryNode<LatticeType>& node) = 0;
    virtual void visit_functionExit(FunctionExitNode<LatticeType>& node) = 0;
    virtual void visit_assignReturn(AssignReturnNode<LatticeType>& node) = 0;
    virtual void visit_arrayAssignment(ArrayAssignmentNode<LatticeType>& node) = 0;
};

template<typename LatticeType>
class Node {
public:
    std::unordered_set<std::shared_ptr<Node<LatticeType>>> predecessors;
    std::unordered_set<std::shared_ptr<Node<LatticeType>>> successors;
    LatticeType state;

    virtual void accept(CfgVisitor<LatticeType>& visitor)=0;
};

template<typename LatticeType>
class InitializerNode : public Node<LatticeType> {
public:
    std::string type; // Consider switching to enum
    std::string id;
    std::shared_ptr<Expression> expression;

    InitializerNode(std::string type, std::string id, std::shared_ptr<Expression> expression) : type(type), id(id), expression(expression){}
    InitializerNode() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_initializtion(*this);
    }
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
class ArrayAssignmentNode : public Node<LatticeType> {
public:
    std::string id;
    std::shared_ptr<Expression> indexExpression;
    std::shared_ptr<Expression> expression;

    ArrayAssignmentNode(std::string id, std::shared_ptr<Expression> indexExpression, std::shared_ptr<Expression> expression){}
    ArrayAssignmentNode() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_arrayAssignment(*this);
    }
};

template<typename LatticeType>
class IfNode : public Node<LatticeType>{
public:
    std::shared_ptr<Expression> expression;

    IfNode(std::shared_ptr<Expression> expression) : expression(expression){}
    IfNode() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_if(*this);
    }
};

template<typename LatticeType>
class FunctionCall : public Node<LatticeType> {
public:
    std::string type;
    std::string variableId;
    std::string functionId;
    std::vector<std::shared_ptr<Expression>> arguments;

    FunctionCall(std::string functionId, std::vector<std::shared_ptr<Expression>> arguments) : functionId(functionId), arguments(arguments) {

    }
    FunctionCall() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_functioncall(*this);
    }
};

template<typename LatticeType>
class FunctionDefinition : public Node<LatticeType> {
public:
    std::string functionId{};
    std::vector<std::string> formalParameters{};
    std::string returnType{};
    std::vector<std::shared_ptr<Node<LatticeType>>> returns;

    FunctionDefinition(std::string functionId, std::vector<std::string> parameters) : functionId(functionId), formalParameters(parameters){
        returnType = "void";
    }

    FunctionDefinition(std::string functionId, std::vector<std::string> parameters, std::string returnType) : functionId(functionId), formalParameters(parameters), returnType(returnType){}
    FunctionDefinition() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_functiondef(*this);
    }
};

template<typename LatticeType>
class WhileLoop : public Node<LatticeType> {
public:
    std::shared_ptr<Expression> condition;

    WhileLoop(std::shared_ptr<Expression> condition) : condition(condition) {}
    WhileLoop() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_whileloop(*this);
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
    std::shared_ptr<FunctionExitNode<LatticeType>> exit;

    FunctionEntryNode() {
        exit = std::make_shared<FunctionExitNode<LatticeType>>();
    }

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_functionEntry(*this);
    }
};

template<typename LatticeType>
class FunctionExitNode : public Node<LatticeType> {
public:
    FunctionExitNode() = default;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_functionExit(*this);
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

