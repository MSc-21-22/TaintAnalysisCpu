#include <cfg.h>
#include "analysis.h"
#include <var_visitor.h>

#define RETURN_VAR "£return"
#define TAINT_VAR "£"

template <typename LatticeType>
class BitCudaTransformer : public CfgVisitor<LatticeType>
{
public:
    std::vector<bit_cuda::Node> nodes{};
    std::map<Node<LatticeType>*, int> node_to_index{};
    std::map<std::string, int> variables{};

    BitCudaTransformer(std::set<std::string> progVariables){
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
        struct bit_cuda::Node node_struct;
        node_struct.transfer.x = variables[node.id];

        fill_with_variable_indices(node_struct.transfer.rhs, node.expression);

        node_to_index[&node] = nodes.size();
        nodes.push_back(node_struct);
    }

    void visit_return(ReturnNode<LatticeType>& node) {
        struct bit_cuda::Node node_struct;
        node_struct.transfer.x = variables[RETURN_VAR];

        fill_with_variable_indices(node_struct.transfer.rhs, node.expression);

        node_to_index[&node] = nodes.size();
        nodes.push_back(node_struct);
    }

    void visit_emptyReturn(EmptyReturnNode<LatticeType>& node) {
        struct bit_cuda::Node node_struct;

        node_to_index[&node] = nodes.size();
        nodes.push_back(node_struct);
    }

    void visit_functionEntry(FunctionEntryNode<LatticeType>& node) { 
        struct bit_cuda::Node node_struct;

        //TODO: handle multiple transfer_functions
        for (int i = 0; i < node.arguments.size(); i++)
        {
            struct bit_cuda::Transfer transfer_function;
            fill_with_variable_indices(transfer_function.rhs, node.arguments[i]);
        }
        
        node_to_index[&node] = nodes.size();
        nodes.push_back(node_struct);
    }

    void visit_assignReturn(AssignReturnNode<LatticeType>& node) { 
        struct bit_cuda::Node node_struct;
        node_struct.transfer.x = variables[node.id];
        node_struct.transfer.rhs[0] = variables[RETURN_VAR];

        node_to_index[&node] = nodes.size();
        nodes.push_back(node_struct);
    }

    void visit_arrayAssignment(ArrayAssignmentNode<LatticeType>& node) { 
        struct bit_cuda::Node node_struct;
        node_struct.transfer.x = variables[node.id];

        fill_with_variable_indices(node_struct.transfer.rhs, node.expression);

        node_to_index[&node] = nodes.size();
        nodes.push_back(node_struct);
    }
    
    void visit_arrayinit(ArrayInitializerNode<LatticeType>& node) { 
        struct bit_cuda::Node node_struct;
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

        node_to_index[&node] = nodes.size();
        nodes.push_back(node_struct);
    }

    void visit_propagation(PropagationNode<LatticeType>& node) { 
        struct bit_cuda::Node node_struct;

        node_to_index[&node] = nodes.size();
        nodes.push_back(node_struct);
    }

private:
    void fill_with_variable_indices(int* arr, std::shared_ptr<Expression>& expression){
        auto variables = expression->get_variables();
        fill_with_variable_indices(arr, variables);
    }

    void fill_with_variable_indices(int* arr, std::set<std::string>& vars){
        int i = 0;
        for(std::string var : vars){
            if (variables.count(var)){
                arr[i++] = variables[var];
            }
        } 
    }
};

template<typename LatticeType>
void add_predecessors(std::vector<std::shared_ptr<Node<LatticeType>>>& nodes, BitCudaTransformer<LatticeType> transformer){
    for(int i = 0; i < nodes.size(); i++){
        for (int j = 0; j < nodes[i].predecessors.size(); j++){
            transformer.nodes[i].predecessor_index[j] = transformer.node_to_index[&(nodes[i].predecessors[j])];
        }
    }
}

template<typename LatticeType>
std::vector<bit_cuda::Node> transform_bit_cuda(std::vector<std::shared_ptr<Node<LatticeType>>>& nodes) {
    auto variables = get_variables(nodes);
    BitCudaTransformer<LatticeType> transformer(variables);
    for(auto &node : nodes){
        node->accept(transformer);
    }
    return transformer.nodes;
}