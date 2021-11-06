#pragma once

#include <string>
#include <set>
#include <memory>
#include <algorithm>
#include <map>
#include "cfg.h"
#include "matrix.h"

#define RETURN_VAR "£return"
#define TAINT_VAR "£"

template <typename LatticeType, typename ElementType>
class MatrixTransforms : public CfgVisitor<LatticeType>
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


        void visit_initializtion(InitializerNode<LatticeType>& node){
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

        void visit_functiondef(FunctionDefinition<LatticeType>& node){
            matrices.push_back(unit_matrix<ElementType>(rowSize));
        }
        
        void visit_assignReturn(AssignReturnNode<LatticeType>& node){
            auto matrix = unit_matrix<ElementType>(rowSize);
            int id_index = variables[node.id];

            matrix(id_index,id_index) = 0.0f;
            matrix(variables[RETURN_VAR],variables[RETURN_VAR]) = 0.0f;
            matrix(id_index, variables[RETURN_VAR]) = 1.0f;
            
            matrices.push_back(matrix);
        }

        void visit_assignment(AssignmentNode<LatticeType>& node){
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

        void visit_functioncall(FunctionCall<LatticeType>& node){
            matrices.push_back(unit_matrix<ElementType>(rowSize));
        }

        void visit_if(IfNode<LatticeType>& node){
            matrices.push_back(unit_matrix<ElementType>(rowSize));
        }

        void visit_return(ReturnNode<LatticeType>& node){
            auto matrix = base_transfer_matrix<ElementType>(rowSize);
            std::set<std::string> expr_vars = node.expression->get_variables();

            for(std::string expr_var : expr_vars){
                if (variables.count(expr_var)){
                    matrix(variables[RETURN_VAR], variables[expr_var]) = 1.0f;
                }
            } 
            matrices.push_back(matrix);
        }

        void visit_whileloop(WhileLoop<LatticeType>& node){
            matrices.push_back(unit_matrix<ElementType>(rowSize));
        }

        void visit_emptyReturn(EmptyReturnNode<LatticeType>& node){
            matrices.push_back(unit_matrix<ElementType>(rowSize));
        }

        void visit_functionEntry(FunctionEntryNode<LatticeType>& node){
            auto matrix = base_transfer_matrix<ElementType>(rowSize);
            if (node.successors.size() == 0)
                return;

            auto def = std::static_pointer_cast<FunctionDefinition<LatticeType>>(*(node.successors.begin()));


            for(auto& pred : node.predecessors){
                auto call = std::static_pointer_cast<FunctionCall<LatticeType>>(pred);

                
                if (call->arguments.size() != def->formalParameters.size()){
                    throw "Function call " + call->functionId + " didnt match the number of arguments";
                }


                for(int i = 0; i < call->arguments.size(); ++i){
                    auto vars = call->arguments[i]->get_variables();
                    int param_id = variables[def->formalParameters[i]];
                    for(auto& var : vars) {
                        int arg_id = variables[var];
                        matrix(param_id, arg_id) = 1.0f;
                    }
                }
            }
            matrices.push_back(matrix);
        }

        void visit_functionExit(FunctionExitNode<LatticeType>& node) {
            matrices.push_back(unit_matrix<ElementType>(rowSize));
        }
};

template<typename LatticeType, typename ElementType>
Matrix<ElementType> get_successor_matrix(std::vector<std::shared_ptr<Node<LatticeType>>> nodes){
    Matrix<ElementType> matrix = unit_matrix<ElementType>(nodes.size());
    std::map<std::shared_ptr<Node<LatticeType>>, int> node_map{};

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