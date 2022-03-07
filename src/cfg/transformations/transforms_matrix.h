#pragma once

#include <string>
#include <set>
#include <memory>
#include <algorithm>
#include <map>
#include <cfg/cfg.h>
#include "matrix.h"

template <typename ElementType>
class MatrixTransforms : public CfgVisitor
{
public:
    std::map<std::string, int> variables{};
    std::vector<Matrix<ElementType>> matrices{};
    int size;
    int rowSize;

    MatrixTransforms(std::set<std::string> progVariables){
        rowSize = progVariables.size() + 2;
        size = rowSize * rowSize;
        int i = 0;
        std::set<std::string>::iterator it;
        for (it=progVariables.begin(); it!=progVariables.end(); it++){
            if(*it != TAINT_VAR && *it != RETURN_VAR){
                variables[*it] = i++;
            }
        }
        variables[RETURN_VAR] = i++;
        variables[TAINT_VAR] = i++;
    }
    
    void visit_assignReturn(AssignReturnNode& node){
        auto matrix = unit_matrix<ElementType>(rowSize);
        int id_index = variables[node.id];

        matrix(id_index,id_index) = 0.0f;
        matrix(variables[RETURN_VAR],variables[RETURN_VAR]) = 0.0f;
        matrix(id_index, variables[RETURN_VAR]) = 1.0f;
        
        matrices.push_back(matrix);
    }

    void visit_assignment(AssignmentNode& node){
        auto matrix = unit_matrix<ElementType>(rowSize);
        std::set<std::string> expr_vars = node.expression->get_variables();
        int id_index = variables[node.id];

        matrix(id_index,id_index) = 0.0f;

        for(std::string expr_var : expr_vars){
            if (variables.count(expr_var)){
                matrix(id_index, variables[expr_var]) = 1.0f;
            }
        }     
        

        matrices.push_back(matrix);
    }

    void visit_propagation(PropagationNode& node){
        matrices.push_back(unit_matrix<ElementType>(rowSize));
    }

    void visit_return(ReturnNode& node){
        auto matrix = base_transfer_matrix<ElementType>(rowSize);
        std::set<std::string> expr_vars = node.expression->get_variables();

        for(std::string expr_var : expr_vars){
            if (variables.count(expr_var)){
                matrix(variables[RETURN_VAR], variables[expr_var]) = 1.0f;
            }
        } 
        matrices.push_back(matrix);
    }

    void visit_emptyReturn(EmptyReturnNode& node){
        matrices.push_back(unit_matrix<ElementType>(rowSize));
    }

    void visit_functionEntry(FunctionEntryNode& node){
        auto matrix = base_transfer_matrix<ElementType>(rowSize);
        if (node.successors.size() == 0)
            return;

        for(int i = 0; i < node.arguments.size(); ++i){
            auto vars = node.arguments[i]->get_variables();
            int param_id = variables[node.formal_parameters[i]];
            for(auto& var : vars) {
                int arg_id = variables[var];
                matrix(param_id, arg_id) = 1.0f;
            }
        }
        matrices.push_back(matrix);
    }

    void visit_arrayinit(ArrayInitializerNode& node){
        auto matrix = unit_matrix<ElementType>(rowSize);
        std::set<std::string> expr_vars;

        for(auto& element : node.arrayContent){
            auto vars = element->get_variables();
            std::set_union(expr_vars.begin(), expr_vars.end(),
                           vars.begin(), vars.end(),
                           std::inserter(expr_vars, expr_vars.begin()));
        }
        
        int id_index = variables[node.id];
        matrix(id_index,id_index) = 0.0f;

        for(std::string expr_var : expr_vars){
            if (variables.count(expr_var)){
                matrix(id_index, variables[expr_var]) = 1.0f;
            }
        }     
        
        matrices.push_back(matrix);
    }

    void visit_arrayAssignment(ArrayAssignmentNode& node){
        auto matrix = unit_matrix<ElementType>(rowSize);
        std::set<std::string> expr_vars = node.expression->get_variables();
        int id_index = variables[node.id];

        matrix(id_index,id_index) = 0.0f;

        for(std::string expr_var : expr_vars){
            if (variables.count(expr_var)){
                matrix(id_index, variables[expr_var]) = 1.0f;
            }
        }     

        matrices.push_back(matrix);
    }
};

template<typename ElementType>
Matrix<ElementType> get_successor_matrix(std::vector<std::shared_ptr<Node>> nodes){
    Matrix<ElementType> matrix = unit_matrix<ElementType>(nodes.size());
    std::map<std::shared_ptr<Node>, int> node_map{};

    int i = 0;
    for(auto node : nodes){
        node_map[node] = i++;
    }

    for(auto node : nodes){
        int node_index = node_map[node];
        for (auto succ_node : node->successors){
            matrix(node_index, node_map[succ_node]) = 1.0f;
        }
    }
    return matrix;
}