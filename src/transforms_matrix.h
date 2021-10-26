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
            progVariables.insert("£");
            progVariables.insert("£return");
            rowSize = progVariables.size();
            size = rowSize * rowSize;
            int i = 0;
            std::set<std::string>::iterator it;
            for (it=progVariables.begin(); it!=progVariables.end(); it++){
                variables[*it] = i++;
            }
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

        }
        
        void visit_assignReturn(AssignReturnNode<LatticeType>& node){
        }

        void visit_assignment(AssignmentNode<LatticeType>& node){
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

        void visit_functioncall(FunctionCall<LatticeType>& node){}
        void visit_if(IfNode<LatticeType>& node){}
        void visit_return(ReturnNode<LatticeType>& node){}
        void visit_whileloop(WhileLoop<LatticeType>& node){}
        void visit_emptyReturn(EmptyReturnNode<LatticeType>& node){}
        void visit_functionEntry(FunctionEntryNode<LatticeType>& node){}
        void visit_functionExit(FunctionExitNode<LatticeType>& node) {}
};