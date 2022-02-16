#include "taint_analysis.h"

bool evaluateExpression(std::shared_ptr<Expression>, std::set<std::string> &);

std::set<std::string> least_upper_bound(const std::set<std::string>& left, const std::set<std::string>& right){
    std::set<std::string> out;
    std::set_union(left.begin(), left.end(), right.begin(), right.end(), std::inserter(out, out.begin()));
    return out;
}

std::set<std::string> join(const Node<std::set<std::string>> &node)
{   
    if(node.predecessors.size() == 0)
        return {};

    auto it = node.predecessors.begin();
    auto state = (*it)->state;
    it++;
    while(it != node.predecessors.end())
    {
        state = least_upper_bound((*it)->state, state);
        it++;
    }
    return state;
}

void TaintAnalyzer::visit_arrayinit(ArrayInitializerNode<std::set<std::string>> &node)
{
    node.state = join(node);
    for (auto &expression : node.arrayContent)
    {
        if (evaluateExpression(expression, node.state))
        {
            node.state.insert(node.id);
        }
    }
    
}

void TaintAnalyzer::visit_assignment(AssignmentNode<std::set<std::string>> &node)
{
    node.state = join(node);

    if (evaluateExpression(node.expression, node.state))
    {
        node.state.insert(node.id);
    }
    else
    {
        node.state.erase(node.id);
    }
}

void TaintAnalyzer::visit_arrayAssignment(ArrayAssignmentNode<std::set<std::string>> &node)
{
    node.state = join(node);

    if (evaluateExpression(node.expression, node.state))
    {
        node.state.insert(node.arrayid);
    }
}

void TaintAnalyzer::visit_propagation(PropagationNode<std::set<std::string>> &node){
    node.state = join(node);
}

void TaintAnalyzer::visit_return(ReturnNode<std::set<std::string>> &node)
{
    node.state = join(node);

    if (evaluateExpression(node.expression, node.state))
    {
        node.state = {RETURN_VAR};
    }
    else
    {
        node.state = {};
    }
}

void TaintAnalyzer::visit_emptyReturn(EmptyReturnNode<std::set<std::string>>&)
{

}



void TaintAnalyzer::visit_functionEntry(FunctionEntryNode<std::set<std::string>>& node){
    if (node.successors.size() == 0)
        return;

    auto previous_state = join(node);

    for(size_t i = 0; i < node.arguments.size(); ++i){
        bool isTainted = node.arguments[i]->evaluate(previous_state);
        if(isTainted){
            auto parameter = node.formal_parameters[i];
            node.state.insert(parameter);
        }
    }
}

void TaintAnalyzer::visit_assignReturn(AssignReturnNode<std::set<std::string>>& node){
    node.state = join(node);
    if (node.state.find(RETURN_VAR) != node.state.end()){
        node.state.insert(node.id);
    }else{
        node.state.erase(node.id);
    }

    node.state.erase(RETURN_VAR);
}

bool evaluateExpression(std::shared_ptr<Expression> expression, std::set<std::string> &state)
{
    return expression->evaluate(state);
}
