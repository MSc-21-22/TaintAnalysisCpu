#pragma once
#include <cfg/cfg.h>

class TaintSourceLocator : public CfgVisitor {
    const std::set<std::string> taint_constant{TAINT_VAR};
protected:
    bool last_is_taintsource{false};
public:
    bool is_taintsource(Node& node);

    void visit_assignment(AssignmentNode& node);
    void visit_return(ReturnNode& node);
    void visit_emptyReturn(EmptyReturnNode& node);
    void visit_functionEntry(FunctionEntryNode& node);
    void visit_assignReturn(AssignReturnNode& node);
    void visit_arrayAssignment(ArrayAssignmentNode& node);
    void visit_arrayinit(ArrayInitializerNode& node);
    void visit_propagation(PropagationNode& node);
};