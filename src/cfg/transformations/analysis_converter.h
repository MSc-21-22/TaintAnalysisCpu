#include <cfg/cfg.h>
#include <map>
#include <string>
#include <taint_analysis.h>

class TransferCreator : public CfgVisitor{
private:
    int next_var_index{RETURN_VAR_INDEX + 1};

public:
    std::vector<cpu_analysis::Transfer> transfers;
    std::vector<int> node_to_index;

    void visit_assignment(AssignmentNode& node) override;
    void visit_return(ReturnNode& node) override;
    void visit_emptyReturn(EmptyReturnNode& node) override;
    void visit_functionEntry(FunctionEntryNode& node) override;
    void visit_assignReturn(AssignReturnNode& node) override;
    void visit_arrayAssignment(ArrayAssignmentNode& node) override;
    void visit_arrayinit(ArrayInitializerNode& node) override;
    void visit_propagation(PropagationNode& node) override;
};

TransferCreator get_analysis_information(std::vector<std::shared_ptr<Node>>& nodes);