#pragma once
#include "cfg.h"
#include <set>
#include <string>
#include <algorithm>

std::set<std::string> least_upper_bound(const std::set<std::string>& left, const std::set<std::string>& right);


class TaintAnalyzer : public CfgVisitor<std::set<std::string>> {
public:
    std::set<std::string> taintedReturns{}; 
    void visit_assignment(AssignmentNode<std::set<std::string>>& node);
    void visit_return(ReturnNode<std::set<std::string>>& node);
    void visit_emptyReturn(EmptyReturnNode<std::set<std::string>>& node);
    void visit_functionEntry(FunctionEntryNode<std::set<std::string>>& node);
    void visit_assignReturn(AssignReturnNode<std::set<std::string>>& node);
    void visit_propagation(PropagationNode<std::set<std::string>>& node);
};