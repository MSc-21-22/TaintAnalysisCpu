#pragma once
#include "cfg.h"
#include <set>
#include <string>

class TaintAnalyzer : public CfgVisitor<std::set<std::string>> {
public:
    std::set<std::string> taintedReturns{}; 
    virtual void visit_initializtion(InitializerNode<std::set<std::string>>& node);
    virtual void visit_assignment(AssignmentNode<std::set<std::string>>& node);
    virtual void visit_functioncall(FunctionCall<std::set<std::string>>& node);
    virtual void visit_functiondef(FunctionDefinition<std::set<std::string>>& node);
    virtual void visit_return(ReturnNode<std::set<std::string>>& node);
};