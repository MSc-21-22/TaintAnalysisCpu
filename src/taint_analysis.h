#pragma once
#include "cfg.h"
#include <set>
#include <string>
#include <algorithm>

std::set<std::string> least_upper_bound(const std::set<std::string>& left, const std::set<std::string>& right);


class TaintAnalyzer : public CfgStateVisitor<std::set<std::string>> {
public:
    std::set<std::string> taintedReturns{}; 
    void visit_assignment(AssignmentNode& node, std::map<Node*, std::set<std::string>>& states);
    void visit_return(ReturnNode& node, std::map<Node*, std::set<std::string>>& states);
    void visit_emptyReturn(EmptyReturnNode& node, std::map<Node*, std::set<std::string>>& states);
    void visit_functionEntry(FunctionEntryNode& node, std::map<Node*, std::set<std::string>>& states);
    void visit_assignReturn(AssignReturnNode& node, std::map<Node*, std::set<std::string>>& states);
    void visit_arrayAssignment(ArrayAssignmentNode& node, std::map<Node*, std::set<std::string>>& states);
    void visit_arrayinit(ArrayInitializerNode& node, std::map<Node*, std::set<std::string>>& states);
    void visit_propagation(PropagationNode& node, std::map<Node*, std::set<std::string>>& states);

};