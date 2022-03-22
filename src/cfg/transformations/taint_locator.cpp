#include "taint_locator.h"
#include <cfg/Expression.h>
#include <memory>

bool TaintSourceLocator::is_taintsource(Node& node){
    node.accept(*this);
    return last_is_taintsource;
}

void TaintSourceLocator::visit_assignment(AssignmentNode& node){
    last_is_taintsource = node.expression->evaluate(taint_constant);
}
void TaintSourceLocator::visit_return(ReturnNode& node){
    last_is_taintsource = node.expression->evaluate(taint_constant);
}
void TaintSourceLocator::visit_emptyReturn(EmptyReturnNode& node){
    last_is_taintsource = false;
}
void TaintSourceLocator::visit_functionEntry(FunctionEntryNode& node){
    for(std::shared_ptr<Expression>& arg : node.arguments){
        if(arg->evaluate(taint_constant)){
            last_is_taintsource = true;
            return;
        }
    }
    last_is_taintsource = false;
}
void TaintSourceLocator::visit_assignReturn(AssignReturnNode& node){
    last_is_taintsource = false;
}
void TaintSourceLocator::visit_arrayAssignment(ArrayAssignmentNode& node){    
    last_is_taintsource = node.expression->evaluate(taint_constant);
}
void TaintSourceLocator::visit_arrayinit(ArrayInitializerNode& node){
    for(std::shared_ptr<Expression>& arg : node.arrayContent){
        if(arg->evaluate(taint_constant)){
            last_is_taintsource = true;
            return;
        }
    }
    last_is_taintsource = false;
}
void TaintSourceLocator::visit_propagation(PropagationNode& node){
    last_is_taintsource = false;
}


int count_taint_sources(std::vector<std::shared_ptr<Node>>& nodes){
    TaintSourceLocator locator;
    int count = 0;
    for(std::shared_ptr<Node>& node : nodes){
        if(locator.is_taintsource(*node)){
            ++count;
        }
    }

    return count;
}