#include <cfg.h>
#include "analysis.h"
#include <var_visitor.h>

#define RETURN_VAR "$return"
#define TAINT_VAR "$"

template <typename LatticeType>
class BitCudaTransformer : public CfgVisitor<LatticeType>
{
public:
    std::vector<bit_cuda::Node> nodes{};
    std::vector<bit_cuda::Transfer> extra_transfers{};
    std::map<Node<LatticeType>*, int> node_to_index{};
    std::map<std::string, int> variables{};

    BitCudaTransformer(std::set<std::string> progVariables){
        int i = 0;
        variables[TAINT_VAR] = i++;
        variables[RETURN_VAR] = i++;

        std::cout << TAINT_VAR << " -> " << variables[TAINT_VAR] <<'\n';
        std::cout << RETURN_VAR << " -> " << variables[RETURN_VAR] <<'\n';

        std::set<std::string>::iterator it;
        for (it=progVariables.begin(); it!=progVariables.end(); it++){
            if(*it != TAINT_VAR && *it != RETURN_VAR){
                variables[*it] = i++;
                std::cout << *it << " -> " << variables[*it] <<'\n';
            }
        }

    }

    void visit_assignment(AssignmentNode<LatticeType>& node) {
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();

        node_struct.transfer.x = variables[node.id];
        fill_with_variable_indices(node_struct.transfer.rhs, node.expression);
    }

    void visit_return(ReturnNode<LatticeType>& node) {
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();

        node_struct.transfer.x = variables[RETURN_VAR];
        fill_with_variable_indices(node_struct.transfer.rhs, node.expression);
    }

    void visit_emptyReturn(EmptyReturnNode<LatticeType>& node) {
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();
    }

    void visit_functionEntry(FunctionEntryNode<LatticeType>& node) { 
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();

        if(node.arguments.size() >= 1){
            bit_cuda::Transfer& last = node_struct.transfer;
            fill_with_variable_indices(node_struct.transfer.rhs, node.arguments[0]);

            for (int i = 1; i < node.arguments.size(); i++)
            {
                last.next_transfer_index = extra_transfers.size();

                extra_transfers.emplace_back();
                fill_with_variable_indices(extra_transfers.back().rhs, node.arguments[i]);
                last = extra_transfers.back();
            }
        }
    }

    void visit_assignReturn(AssignReturnNode<LatticeType>& node) { 
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();

        node_struct.transfer.x = variables[node.id];
        node_struct.transfer.rhs[0] = variables[RETURN_VAR];
    }

    void visit_arrayAssignment(ArrayAssignmentNode<LatticeType>& node) { 
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();

        node_struct.transfer.x = variables[node.id];
        fill_with_variable_indices(node_struct.transfer.rhs, node.expression);
    }
    
    void visit_arrayinit(ArrayInitializerNode<LatticeType>& node) { 
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();

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
    }

    void visit_propagation(PropagationNode<LatticeType>& node) { 
        node_to_index[&node] = nodes.size();
        bit_cuda::Node& node_struct = nodes.emplace_back();
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
void add_predecessors(std::vector<std::shared_ptr<Node<LatticeType>>>& nodes, BitCudaTransformer<LatticeType>& transformer){
    for(int i = 0; i < nodes.size(); i++){
        int j = 0;
        for (auto pred_it = nodes[i]->predecessors.begin(); pred_it != nodes[i]->predecessors.end(); ++pred_it){
            transformer.nodes[i].predecessor_index[j++] = transformer.node_to_index[pred_it->get()];
        }
    }
}

template<typename LatticeType>
BitCudaTransformer<LatticeType> transform_bit_cuda(std::vector<std::shared_ptr<Node<LatticeType>>>& nodes) {
    auto variables = get_variables(nodes);
    BitCudaTransformer<LatticeType> transformer(variables);
    for(auto &node : nodes){
        node->accept(transformer);
    }
    add_predecessors(nodes, transformer);
    return transformer;
}