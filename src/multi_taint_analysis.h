#pragma once
#include "cfg.h"
#include <set>
#include <string>
#include <map>
#include <ostream>

typedef std::map<std::string, std::set<int>> SourcedTaintState;

SourcedTaintState least_upper_bound(const SourcedTaintState& left, const SourcedTaintState& right);

void print_taint_source(SourcedTaintState& result, std::ostream& stream);

class MultiTaintAnalyzer : public CfgVisitor<SourcedTaintState> {
    int next_source = 0;

    std::set<int> get_taints(std::shared_ptr<Expression> expression, Node<SourcedTaintState>&node);
public:
    std::map<long long int, int> node_to_source{};

    void visit_assignment(AssignmentNode<SourcedTaintState>& node);
    void visit_return(ReturnNode<SourcedTaintState>& node);
    void visit_emptyReturn(EmptyReturnNode<SourcedTaintState>& node);
    void visit_functionEntry(FunctionEntryNode<SourcedTaintState>& node);
    void visit_assignReturn(AssignReturnNode<SourcedTaintState>& node);
    void visit_propagation(PropagationNode<SourcedTaintState>& node);
};