#pragma once
#include "cfg.h"
#include <set>
#include <string>

class TaintAnalyzer : public CfgVisitor<std::set<std::string>> {
public:
    std::set<std::string> taintedReturns{}; 
    void visit_initializtion(InitializerNode<std::set<std::string>>& node);
    void visit_assignment(AssignmentNode<std::set<std::string>>& node);
    void visit_functioncall(FunctionCall<std::set<std::string>>& node);
    void visit_if(IfNode<std::set<std::string>>& node);
    void visit_functiondef(FunctionDefinition<std::set<std::string>>& node);
    void visit_return(ReturnNode<std::set<std::string>>& node);
    void visit_whileloop(WhileLoop<std::set<std::string>>& node);
};