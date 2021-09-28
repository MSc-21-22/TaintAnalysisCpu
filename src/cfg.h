#pragma once

#include <unordered_set>
#include <memory>
#include <string>
#include <vector>
#include "iostream"
#include <ostream>
#include "Expression.h"

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vec){
    auto it = vec.begin();
    while(it != vec.end()){
        stream << *it;

        it++;
        if (it != vec.end()){
            stream << ", ";
        }
    }

    return stream;
}

template<typename LatticeType>
class Node;
template<typename LatticeType>
class InitializerNode;
template<typename LatticeType>
class AssignmentNode;
template<typename LatticeType>
class FunctionCall;
template<typename LatticeType>
class FunctionDefinition;
template<typename LatticeType>
class ReturnNode;

template<typename LatticeType>
class CfgVisitor {
public:
    virtual void visit_initializtion(InitializerNode<LatticeType>& node) = 0;
    virtual void visit_assignment(AssignmentNode<LatticeType>& node) = 0;
    virtual void visit_functioncall(FunctionCall<LatticeType>& node) = 0;
    virtual void visit_functiondef(FunctionDefinition<LatticeType>& node) = 0;
    virtual void visit_return(ReturnNode<LatticeType>& node) = 0;
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
    std::shared_ptr<Expression> expression; // Type should probably be changed

    InitializerNode(std::string type, std::string id, std::shared_ptr<Expression> expression) : type(type), id(id), expression(expression){}

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

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_assignment(*this);
    }
};

template<typename LatticeType>
class FunctionCall : public Node<LatticeType> {
public:
    std::string functionId;
    std::vector<std::string> arguments;

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

    FunctionDefinition(std::string functionId, std::vector<std::string> parameters) : functionId(functionId), formalParameters(parameters){
        returnType = "void";
    }

    FunctionDefinition(std::string functionId, std::vector<std::string> parameters, std::string returnType) : functionId(functionId), formalParameters(parameters), returnType(returnType){}

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_functiondef(*this);
    }
};

template<typename LatticeType>
class ReturnNode : public Node<LatticeType> {
public:
    std::shared_ptr<Expression> expression;
    std::string functionId;

    ReturnNode(std::shared_ptr<Expression> expr, std::string functionId) : expression(expr), functionId(functionId) {}

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_return(*this);
    }
};


