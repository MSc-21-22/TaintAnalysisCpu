#pragma once

#include <string>
#include <set>
#include <memory>
#include <algorithm>
#include <map>
#include "cfg.h"
#include "matrix.h"

template <typename LatticeType>
class MatrixTransforms : public CfgVisitor<LatticeType>
{
    public:
        std::map<std::string, int> variables{};
        std::vector<Matrix> matrices{};
        int size;
        int rowSize;

        MatrixTransforms(std::set<std::string> progVariables){
            rowSize = progVariables.size() + 2;
            size = rowSize * rowSize;
            int i = 0;
            std::set<std::string>::iterator it;
            for (it=progVariables.begin(); it!=progVariables.end(); it++){
                variables[*it] = i++;
            }
            variables["£return"] = i++;
            variables["£"] = i++;
        }


        void visit_initializtion(InitializerNode<LatticeType>& node){
            Matrix matrix(rowSize);
            std::set<std::string> expr_vars = node.expression->get_variables();
            int id_index = variables[node.id];

            matrix(id_index,id_index) = 0;

            for(std::string expr_var : expr_vars){
                if (variables.count(expr_var)){
                    matrix(id_index, variables[expr_var]) = 1;
                }
            }     
            

            matrices.push_back(matrix);
        }

        void visit_functiondef(FunctionDefinition<LatticeType>& node){
            matrices.push_back(unit_matrix(rowSize));
        }
        
        void visit_assignReturn(AssignReturnNode<LatticeType>& node){
        }

        void visit_assignment(AssignmentNode<LatticeType>& node){
            Matrix matrix = unit_matrix(rowSize);
            std::set<std::string> expr_vars = node.expression->get_variables();
            int id_index = variables[node.id];

            matrix(id_index,id_index) = 0;

            for(std::string expr_var : expr_vars){
                if (variables.count(expr_var)){
                    matrix(id_index, variables[expr_var]) = 1;
                }
            }     
            

            matrices.push_back(matrix);
        }

        void visit_functioncall(FunctionCall<LatticeType>& node){}

        void visit_if(IfNode<LatticeType>& node){
            matrices.push_back(unit_matrix(rowSize));
        }

        void visit_return(ReturnNode<LatticeType>& node){}

        void visit_whileloop(WhileLoop<LatticeType>& node){
            matrices.push_back(unit_matrix(rowSize));
        }

        void visit_emptyReturn(EmptyReturnNode<LatticeType>& node){
            matrices.push_back(unit_matrix(rowSize));
        }

        void visit_functionEntry(FunctionEntryNode<LatticeType>& node){
            Matrix matrix = empty_matrix(rowSize);
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
                        matrix(param_id, arg_id) = 1;
                    }
                }
            }
            matrices.push_back(matrix);
        }

        void visit_functionExit(FunctionExitNode<LatticeType>& node) {}
};