#include <unordered_set>
#include <memory>
#include <string>
#include <vector>
#include "Expression.h"



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
    std::unordered_set<std::shared_ptr<Node>> predecessors;
    std::unordered_set<std::shared_ptr<Node>> successors;
    LatticeType state;

    virtual void accept(CfgVisitor<LatticeType>& visitor);
};

template<typename LatticeType>
class InitializerNode : public Node<LatticeType> {
public:
    std::string type; // Consider switching to enum
    std::string id;
    Expression expression; // Type should probably be changed

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_initializtion(&this);
    }
};

template<typename LatticeType>
class AssignmentNode : public Node<LatticeType> {
public:
    std::string id;
    Expression expression;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_assignment(&this);
    }
};

template<typename LatticeType>
class FunctionCall : public Node<LatticeType> {
public:
    std::string functionId;
    std::vector<std::string> arguments;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_functioncall(&this);
    }
};

template<typename LatticeType>
class FunctionDefinition : public Node<LatticeType> {
public:
    std::string functionId;
    std::vector<std::string> formalParameters;
    std::string returnType;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_functiondef(&this);
    }
};

template<typename LatticeType>
class ReturnNode : public Node<LatticeType> {
public:
    Expression expression;

    void accept(CfgVisitor<LatticeType>& visitor){
        visitor.visit_return(&this);
    }
};


