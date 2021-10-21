#pragma once

#include <string>
#include <set>
#include <memory>
#include <algorithm>
#include <map>
#include "cfg.h"

template <typename LatticeType>
class MatrixTransforms : public CfgVisitor<LatticeType>
{
    public:
        std::map<std::string, int> variables{};
        std::vector<std::shared_ptr<int[]>> matrices;
        int size;
        int rowSize;

        MatrixTransforms(std::set<std::string> progVariables){
            rowSize = progVariables.size() + 1;
            size = rowSize * rowSize;
            int i = 0;
            std::set<std::string>::iterator it;
            for (it=progVariables.begin(); it!=progVariables.end(); it++){
                variables[*it] = i++;
            }
            variables["€"] = i;
        }

        std::shared_ptr<int[]> unit_matrix(){
            std::shared_ptr<int[]> matrix(new int[size]);
            std::fill(matrix.get(), matrix.get() + size, 0);
            for(int i = 0; i < variables.size(); i++){
                matrix.get()[rowSize*i+i] = 1;
            }
            return matrix;
        }


        void visit_initializtion(InitializerNode<LatticeType>& node){
            std::shared_ptr<int[]> matrix = unit_matrix();
            std::set<std::string> expr_vars = node.expression->get_variables();;
            int id_index = variables[node.id];

            matrix.get()[rowSize*id_index+id_index] = 0;

            for(std::string expr_var : expr_vars){
                if (variables.count(expr_var)){
                    matrix.get()[rowSize*variables[expr_var]+id_index] = 1;
                }
            }     
            

            matrices.push_back(matrix);
        }

        void visit_functiondef(FunctionDefinition<LatticeType>& node){

        }
        
        void visit_assignReturn(AssignReturnNode<LatticeType>& node){
        }

        void visit_assignment(AssignmentNode<LatticeType>& node){}
        void visit_functioncall(FunctionCall<LatticeType>& node){}
        void visit_if(IfNode<LatticeType>& node){}
        void visit_return(ReturnNode<LatticeType>& node){}
        void visit_whileloop(WhileLoop<LatticeType>& node){}
        void visit_emptyReturn(EmptyReturnNode<LatticeType>& node){}
        void visit_functionEntry(FunctionEntryNode<LatticeType>& node){}
        void visit_functionExit(FunctionExitNode<LatticeType>& node) {}
};