#include "taint_analysis.h"

bool evaluateExpression(std::shared_ptr<Expression>, std::set<std::string> &);

std::set<std::string> least_upper_bound(const std::set<std::string>& left, const std::set<std::string>& right){
    std::set<std::string> out;
    std::set_union(left.begin(), left.end(), right.begin(), right.end(), std::inserter(out, out.begin()));
    return out;
}

std::set<std::string> join(const Node &node, std::map<Node*, std::set<std::string>> &states)
{   
    if(node.predecessors.size() == 0)
        return {TAINT_VAR};

    auto it = node.predecessors.begin();
    auto state = states[it->get()];
    it++;
    while(it != node.predecessors.end())
    {
        state = least_upper_bound(states[it->get()], state);
        it++;
    }
    return state;
}

void TaintAnalyzer::visit_arrayinit(ArrayInitializerNode &node, std::map<Node*, std::set<std::string>> &states)
{
    std::set<std::string>& node_state = states[&node];
    node_state = join(node, states);
    for (auto &expression : node.arrayContent)
    {
        if (evaluateExpression(expression, node_state))
        {
            node_state.insert(node.id);
        }
    }
    
}

void TaintAnalyzer::visit_assignment(AssignmentNode &node, std::map<Node*, std::set<std::string>> &states)
{
    std::set<std::string>& node_state = states[&node];
    node_state = join(node, states);

    if (evaluateExpression(node.expression, node_state))
    {
        node_state.insert(node.id);
    }
    else
    {
        node_state.erase(node.id);
    }
}

void TaintAnalyzer::visit_arrayAssignment(ArrayAssignmentNode &node, std::map<Node*, std::set<std::string>> &states)
{
    std::set<std::string>& node_state = states[&node];
    node_state = join(node, states);

    if (evaluateExpression(node.expression, node_state))
    {
        node_state.insert(node.arrayid);
    }
}

void TaintAnalyzer::visit_propagation(PropagationNode &node, std::map<Node*, std::set<std::string>> &states){
    std::set<std::string>& node_state = states[&node];
    node_state = join(node, states);
}

void TaintAnalyzer::visit_return(ReturnNode &node, std::map<Node*, std::set<std::string>> &states)
{
    std::set<std::string>& node_state = states[&node];
    node_state = join(node, states);

    if (evaluateExpression(node.expression, node_state))
    {
        node_state = {TAINT_VAR, RETURN_VAR};
    }
    else
    {
        node_state = {TAINT_VAR};
    }
}

void TaintAnalyzer::visit_emptyReturn(EmptyReturnNode &node, std::map<Node*, std::set<std::string>>& states){

}



void TaintAnalyzer::visit_functionEntry(FunctionEntryNode &node, std::map<Node*, std::set<std::string>>& states){
    std::set<std::string>& node_state = states[&node];
    if (node.successors.size() == 0)
        return;

    auto previous_state = join(node, states);

    for(size_t i = 0; i < node.arguments.size(); ++i){
        bool isTainted = node.arguments[i]->evaluate(previous_state);
        if(isTainted){
            auto parameter = node.formal_parameters[i];
            node_state.insert(parameter);
        }
    }
}

void TaintAnalyzer::visit_assignReturn(AssignReturnNode &node, std::map<Node*, std::set<std::string>>& states){
    std::set<std::string>& node_state = states[&node];
    node_state = join(node, states);
    if (node_state.find(RETURN_VAR) != node_state.end()){
        node_state.insert(node.id);
    }else{
        node_state.erase(node.id);
    }

    node_state.erase(RETURN_VAR);
}

bool evaluateExpression(std::shared_ptr<Expression> expression, std::set<std::string> &state)
{
    return expression->evaluate(state);
}
