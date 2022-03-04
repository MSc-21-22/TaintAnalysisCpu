#pragma once
#include <cfg/cfg.h>
#include <set>
#include <string>
#include <map>
#include <ostream>

typedef std::map<std::string, std::set<int>> SourcedTaintState;

SourcedTaintState least_upper_bound(const SourcedTaintState& left, const SourcedTaintState& right);

void print_taint_source(SourcedTaintState& result, std::ostream& stream);

class MultiTaintAnalyzer : public CfgStateVisitor<SourcedTaintState> {
    int next_source = 0;

    std::set<int> get_taints(std::shared_ptr<Expression> expression, const Node& node, SourcedTaintState& state);
public:
    std::map<long long int, int> node_to_source{};

    void visit_assignment(AssignmentNode& node, std::map<Node*, SourcedTaintState>& state);
    void visit_return(ReturnNode& node, std::map<Node*, SourcedTaintState>& state);
    void visit_emptyReturn(EmptyReturnNode& node, std::map<Node*, SourcedTaintState>& state);
    void visit_functionEntry(FunctionEntryNode& node, std::map<Node*, SourcedTaintState>& state);
    void visit_assignReturn(AssignReturnNode& node, std::map<Node*, SourcedTaintState>& state);
    void visit_arrayAssignment(ArrayAssignmentNode& node, std::map<Node*, SourcedTaintState>& state);
    void visit_arrayinit(ArrayInitializerNode& node, std::map<Node*, SourcedTaintState>& state);
    void visit_propagation(PropagationNode& node, std::map<Node*, SourcedTaintState>& state);
};