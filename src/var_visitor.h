#pragma once

#include <string>
#include <set>
#include "cfg.h"

template <typename LatticeType>
class VarVisitor : public CfgVisitor<LatticeType>
{
    public:
        std::set<std::string> variables{};

        void visit_functionEntry(FunctionEntryNode<LatticeType>& node){
           for(std::string var : node.formal_parameters){
               variables.insert(var);
           }
        }
        
        void visit_assignReturn(AssignReturnNode<LatticeType>& node){
            variables.insert(node.id);
        }

        void visit_assignment(AssignmentNode<LatticeType>& node){
            variables.insert(node.id);
        }

        void visit_arrayinit(ArrayInitializerNode<LatticeType>& node){
            variables.insert(node.id);
        }

        void visit_arrayAssignment(ArrayAssignmentNode<LatticeType>& node){
            variables.insert(node.arrayid);
        }

        void visit_return(ReturnNode<LatticeType>&){}
        void visit_emptyReturn(EmptyReturnNode<LatticeType>&){}
        void visit_propagation(PropagationNode<LatticeType>&){}
};

template<typename LatticeType>
std::set<std::string> get_variables(std::vector<std::shared_ptr<Node<LatticeType>>>& nodes){
    VarVisitor<LatticeType> varAnalyzer;
    for(auto& node : nodes){
        (*node).accept(varAnalyzer);
    }
    return varAnalyzer.variables;
}