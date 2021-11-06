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

        void visit_functioncall(FunctionCall<LatticeType>& node){}
        void visit_if(IfNode<LatticeType>& node){}
        void visit_return(ReturnNode<LatticeType>& node){}
        void visit_whileloop(WhileLoop<LatticeType>& node){}
        void visit_emptyReturn(EmptyReturnNode<LatticeType>& node){}
        void visit_functionEntry(FunctionEntryNode<LatticeType>& node){}
        void visit_functionExit(FunctionExitNode<LatticeType>& node) {}
};