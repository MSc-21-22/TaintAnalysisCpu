#pragma once

#include <string>
#include <set>
#include "cfg.h"

template <typename LatticeType>
class VarVisitor : public CfgVisitor<LatticeType>
{
    public:
        std::set<std::string> variables{};

        void visit_initializtion(InitializerNode<LatticeType>& node){
            variables.insert(node.id);
        }

        void visit_functiondef(FunctionDefinition<LatticeType>& node){
           for(std::string var : node.formalParameters){
               variables.insert(var);
           }
        }
        
        void visit_assignReturn(AssignReturnNode<LatticeType>& node){
            variables.insert(node.id);
        }

        void visit_assignment(AssignmentNode<LatticeType>& node){
            variables.insert(node.id);
        }

        void visit_functioncall(FunctionCall<LatticeType>&){}
        void visit_if(IfNode<LatticeType>&){}
        void visit_return(ReturnNode<LatticeType>&){}
        void visit_whileloop(WhileLoop<LatticeType>&){}
        void visit_emptyReturn(EmptyReturnNode<LatticeType>&){}
        void visit_functionEntry(FunctionEntryNode<LatticeType>&){}
        void visit_functionExit(FunctionExitNode<LatticeType>&) {}
};

template<typename LatticeType>
std::set<std::string> get_variables(std::vector<std::shared_ptr<Node<LatticeType>>>& nodes){
    VarVisitor<LatticeType> varAnalyzer;
    for(auto& node : nodes){
        (*node).accept(varAnalyzer);
    }
    return varAnalyzer.variables;
}