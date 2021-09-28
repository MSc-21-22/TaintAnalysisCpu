#include "taint_analysis.h"

bool evaluateExpression(std::shared_ptr<Expression>, std::set<std::string> &);

void join(Node<std::set<std::string>> &node)
{
    for (auto &pred : node.predecessors)
    {
        node.state.insert(pred->state.begin(), pred->state.end());
    }
}

void TaintAnalyzer::visit_initializtion(InitializerNode<std::set<std::string>> &node)
{
    join(node);

    if (evaluateExpression(node.expression, node.state))
    {
        node.state.insert(node.id);
    }
    else
    {
        node.state.erase(node.id);
    }
}

void TaintAnalyzer::visit_assignment(AssignmentNode<std::set<std::string>> &node)
{
    join(node);

    if (evaluateExpression(node.expression, node.state))
    {
        node.state.insert(node.id);
    }
    else
    {
        node.state.erase(node.id);
    }
}

void TaintAnalyzer::visit_functioncall(FunctionCall<std::set<std::string>> &node)
{
    join(node);
}

void TaintAnalyzer::visit_functiondef(FunctionDefinition<std::set<std::string>> &node)
{
    join(node);
}

void TaintAnalyzer::visit_return(ReturnNode<std::set<std::string>> &node)
{
    join(node);

    if (evaluateExpression(node.expression, node.state))
    {
        auto pred = *node.predecessors.begin();
        while (true)
        {
            auto functionDef = std::dynamic_pointer_cast<FunctionDefinition<std::set<std::string>>>(pred);
            if (functionDef == nullptr && pred->predecessors.size() != 0)
            {
                pred = *pred->predecessors.begin();
            }
            else
            {
                taintedReturns.insert(functionDef->functionId);
            }
        }
    }
}

bool evaluateExpression(std::shared_ptr<Expression> expression, std::set<std::string> &state)
{
    return expression->evaluate(state);
}
