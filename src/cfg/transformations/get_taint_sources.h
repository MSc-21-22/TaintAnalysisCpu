#pragma once
#include <cfg/cfg.h>

class TaintSourceChecker : public CfgVisitor {
    std::set<std::string> taint_constant{TAINT_VAR};

public:
    bool is_taint_source = false;

    void visit_assignment(AssignmentNode& node){
        is_taint_source = node.expression->evaluate(taint_constant);
    }
    void visit_return(ReturnNode& node){
        is_taint_source = node.expression->evaluate(taint_constant);
    }
    void visit_emptyReturn(EmptyReturnNode& node){
        is_taint_source = false;
    }
    void visit_functionEntry(FunctionEntryNode& node){
        for(std::shared_ptr<Expression> arg : node.arguments){
            if(arg->evaluate(taint_constant)){
                is_taint_source = true;
                return;
            }
        }
    }
    void visit_assignReturn(AssignReturnNode& node){
        is_taint_source = false;
    }
    void visit_arrayAssignment(ArrayAssignmentNode& node){
        is_taint_source = node.expression->evaluate(taint_constant);
    }
    void visit_arrayinit(ArrayInitializerNode& node){
        for(std::shared_ptr<Expression> arg : node.arrayContent){
            if(arg->evaluate(taint_constant)){
                is_taint_source = true;
                return;
            }
        }
    }
    void visit_propagation(PropagationNode& node){
        is_taint_source = false;
    }
};

std::vector<std::shared_ptr<Node>> get_taint_sources(const std::vector<std::shared_ptr<Node>>& nodes);

template<typename LatticeType>
std::vector<StatefulNode<LatticeType>> get_taint_sources(std::vector<StatefulNode<LatticeType>>& nodes) {
    std::vector<StatefulNode<LatticeType>> result;
    
    TaintSourceChecker checker;
    for(auto& node : nodes){
        node.accept(checker);
        if(checker.is_taint_source){
            result.push_back(node);
        }
    }
    return result;
}