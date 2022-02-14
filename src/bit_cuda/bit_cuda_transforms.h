#include "../cfg.h"
#include "analysis.h"

#define RETURN_VAR "£return"
#define TAINT_VAR "£"

template <typename LatticeType, typename ElementType>
class BitCudaTransforms : public CfgVisitor<LatticeType>
{
public:
    std::vector<Node> nodes{};
    std::map<std::string, int> variables{};

    BitCudaTransforms(std::set<std::string> progVariables){
        int i = 0;
        variables[RETURN_VAR] = i++;
        variables[TAINT_VAR] = i++;

        std::set<std::string>::iterator it;
        for (it=progVariables.begin(); it!=progVariables.end(); it++){
            if(*it != TAINT_VAR && *it != RETURN_VAR){
                variables[*it] = i++;
            }
        }

    }

    void visit_assignment(AssignmentNode<LatticeType>& node) {
        struct Node node_struct;
        node_struct.transfer.x = variables[node.id]:

        fill_with_variable_indices(node_struct.transfer.rhs, node.expression);

        nodes.push_back(node_struct);
    }

    void visit_return(ReturnNode<LatticeType>& node) {
        struct Node node_struct;
        node_struct.transfer.x = variables[RETURN_VAR]:

        fill_with_variable_indices(node_struct.transfer.rhs, node.expression);

        nodes.push_back(node_struct);
    }

    void visit_emptyReturn(EmptyReturnNode<LatticeType>& node) {
        struct Node node_struct;

        nodes.push_back(node_struct);
    }

    void visit_functionEntry(FunctionEntryNode<LatticeType>& node) { 
        struct Node node_struct;

        //TODO: handle multiple transfer_functions
        for (int i = 0; i < node.arguments.size(); i++)
        {
            struct Transfer transfer_function;
            fill_with_variable_indices(transfer_function.rhs, node.arguments[i])
        }
        
        nodes.push_back(node_struct);
    }

    void visit_assignReturn(AssignReturnNode<LatticeType>& node) { 
        struct Node node_struct;
        node_struct.transfer.x = variables[node.id];
        node_struct.transfer.rhs[0] = variables[RETURN_VAR];
        nodes.push_back(node_struct);
    }

    void visit_arrayAssignment(ArrayAssignmentNode<LatticeType>& node) { 
        struct Node node_struct;
        node_struct.transfer.x = variables[node.id]:

        fill_with_variable_indices(node_struct.transfer.rhs, node.expression);

        nodes.push_back(node_struct);
    }
    
    void visit_arrayinit(ArrayInitializerNode<LatticeType>& node) { 
        struct Node node_struct;
        node_struct.transfer.x = variables[node.id];

        // Get vars from all array element expressions 
        std::set<std::string> expr_vars;
        for(auto& element : node.arrayContent){
            auto vars = element->get_variables();
            std::set_union(expr_vars.begin(), expr_vars.end(),
                           vars.begin(), vars.end(),
                           std::inserter(expr_vars, expr_vars.begin()));
        }

        fill_with_variable_indices(node_struct.transfer.rhs, expr_vars);
        nodes.push_back(node_struct);
    }

    void visit_propagation(PropagationNode<LatticeType>& node) { 
        struct Node node_struct;

        nodes.push_back(node_struct);
    }

private:
    void fill_with_variable_indices(int *arr, std::shared_ptr<Expression> expression){
        fill_with_variable_indices(arr, expression->get_variables());
    }

    void fill_with_variable_indices(int *arr, std::set<std::string>& vars){
        int i = 0;
        for(std::string var : vars){
            if (variables.count(var)){
                arr[i++] = variables[var];
            }
        } 
    }
};