#pragma once

#include <string>
#include <set>
#include <memory>
#include <algorithm>
#include <map>
#include <cfg.h>
#include <matrix.h>
#include "bool_matrix.h"

#define RETURN_VAR "£return"
#define TAINT_VAR "£"

template <typename LatticeType>
class BoolMatrixTransforms : public CfgVisitor<LatticeType>
{
    public:
        std::vector<std::pair<std::string, int>> variables{};
        std::map<std::string, int> variable_map{};
        std::vector<BoolMatrix> matrices{};
        int size;
        int rowSize;

        BoolMatrixTransforms(const std::set<std::string>& progVariables){
            rowSize = progVariables.size() + 2;
            size = rowSize * rowSize;
            int i = 0;
            std::set<std::string>::iterator it;
            for (it=progVariables.begin(); it!=progVariables.end(); it++){
                if(*it != TAINT_VAR && *it != RETURN_VAR){
                    variables.emplace_back(*it, i);
                    variable_map[*it] = i++;
                }
            }
            variables.emplace_back(RETURN_VAR, i);
            variable_map[RETURN_VAR] = i++;
            variables.emplace_back(TAINT_VAR, i);
            variable_map[TAINT_VAR] = i++;
        }

        void add_assignment_matrix(std::string& dst, std::shared_ptr<Expression> src){
            BoolMatrix matrix(rowSize, rowSize);
            std::set<std::string> expr_vars = src->get_variables();
            int id_index = variable_map[dst];

            for(auto& it : variables){
                if(it.second == id_index){
                    for(auto& var : expr_vars){
                        matrix.add_safe(id_index, variable_map[var]);
                    }
                }else{
                    matrix.add_safe(it.second, it.second);
                }
            }

            matrices.push_back(matrix);
        }

        void add_unit(){
            BoolMatrix matrix(rowSize, rowSize);
            for(size_t i = 0; i < variables.size(); ++i){
                matrix.add_safe(i,i);
            }

            matrices.push_back(matrix);
        }


        void visit_initializtion(InitializerNode<LatticeType>& node){
            add_assignment_matrix(node.id, node.expression);
        }

        void visit_functiondef(FunctionDefinition<LatticeType>&){
            add_unit();
        }
        
        void visit_assignReturn(AssignReturnNode<LatticeType>& node){
            BoolMatrix matrix(rowSize, rowSize);
            int id_index = variable_map[node.id];

            for(auto& it : variables){
                if(it.second == id_index){
                    matrix.add_safe(id_index, variable_map[RETURN_VAR]);
                }else if(it.first != RETURN_VAR){
                    matrix.add_safe(it.second, it.second);
                }
            }

            matrices.push_back(matrix);
        }

        void visit_assignment(AssignmentNode<LatticeType>& node){
            add_assignment_matrix(node.id, node.expression);
        }

        void visit_functioncall(FunctionCall<LatticeType>&){
            add_unit();
        }

        void visit_if(IfNode<LatticeType>&){
            add_unit();
        }

        void visit_return(ReturnNode<LatticeType>& node){
            std::string x = RETURN_VAR;
            add_assignment_matrix(x, node.expression);
        }

        void visit_whileloop(WhileLoop<LatticeType>&){
            add_unit();
        }

        void visit_emptyReturn(EmptyReturnNode<LatticeType>&){
            add_unit();
        }

        void visit_functionEntry(FunctionEntryNode<LatticeType>& node){
            BoolMatrix matrix(rowSize, rowSize);
            if (node.successors.size() == 0)
                return;

            auto def = std::static_pointer_cast<FunctionDefinition<LatticeType>>(*(node.successors.begin()));


            for(auto& pred : node.predecessors){
                auto call = std::static_pointer_cast<FunctionCall<LatticeType>>(pred);

                
                if (call->arguments.size() != def->formalParameters.size()){
                    throw "Function call " + call->functionId + " didnt match the number of arguments";
                }


                for(size_t i = 0; i < call->arguments.size(); ++i){
                    auto vars = call->arguments[i]->get_variables();
                    int param_id = variable_map[def->formalParameters[i]];
                    for(auto& var : vars) {
                        int arg_id = variable_map[var];
                        matrix.add_safe(param_id, arg_id);
                    }
                }
            }
            matrices.push_back(matrix);
        }

        void visit_functionExit(FunctionExitNode<LatticeType>&) {
            add_unit();
        }
};

template<typename LatticeType>
BoolMatrix get_successor_matrix(std::vector<std::shared_ptr<Node<LatticeType>>> nodes){
    BoolMatrix matrix(nodes.size(), nodes.size());
    std::map<std::shared_ptr<Node<LatticeType>>, int> node_map{};

    int i = 0;
    for(auto node : nodes){
        node_map[node] = i++;
    }

    for(auto node : nodes){
        int node_index = node_map[node];

        std::set<int> sorted_set{node_index};
        for (auto succ_node : node->successors){
            sorted_set.insert(node_map[succ_node]);
        }

        for(auto id : sorted_set){
            matrix.add_safe(node_index, id);
        }
    }
    return matrix;
}