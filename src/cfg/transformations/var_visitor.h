#pragma once

#include <string>
#include <set>
#include <cfg/cfg.h>

class VarVisitor : public CfgVisitor
{
    public:
        std::set<std::string> variables{};

        void visit_functionEntry(FunctionEntryNode& node){
           for(std::string var : node.formal_parameters){
               variables.insert(var);
           }
        }
        
        void visit_assignReturn(AssignReturnNode& node){
            variables.insert(node.id);
        }

        void visit_assignment(AssignmentNode& node){
            variables.insert(node.id);
        }

        void visit_arrayinit(ArrayInitializerNode& node){
            variables.insert(node.id);
        }

        void visit_arrayAssignment(ArrayAssignmentNode& node){
            variables.insert(node.arrayid);
        }

        void visit_return(ReturnNode&){}
        void visit_emptyReturn(EmptyReturnNode&){}
        void visit_propagation(PropagationNode&){}
};

std::set<std::string> get_variables(std::vector<std::shared_ptr<Node>>& nodes);