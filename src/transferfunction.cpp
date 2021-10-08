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
    std::cout << "8" <<std::endl;
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
    std::cout << "7" <<std::endl;
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

void TaintAnalyzer::visit_if(IfNode<std::set<std::string>> &node){
    std::cout << "6" <<std::endl;
    join(node);
}

void TaintAnalyzer::visit_functioncall(FunctionCall<std::set<std::string>> &node)
{
    std::cout << "5" <<std::endl;
    join(node);
}

void TaintAnalyzer::visit_functiondef(FunctionDefinition<std::set<std::string>> &node)
{
    join(node);
}

void TaintAnalyzer::visit_return(ReturnNode<std::set<std::string>> &node)
{
    std::cout << "3" <<std::endl;
    join(node);

    if (evaluateExpression(node.expression, node.state))
    {
        node.state = {"£return"};
    }
    else
    {
        node.state = {};
    }
}

void TaintAnalyzer::visit_emptyReturn(EmptyReturnNode<std::set<std::string>> &node)
{
    std::cout << "2" <<std::endl;
    
}

void TaintAnalyzer::visit_whileloop(WhileLoop<std::set<std::string>> &node){
    std::cout << "1" <<std::endl;
    join(node);
}


void TaintAnalyzer::visit_functionEntry(FunctionEntryNode<std::set<std::string>>& node){
    std::cout << "Entry" <<std::endl;
    auto def = std::static_pointer_cast<FunctionDefinition<std::set<std::string>>>(*(node.successors.begin()));

    for(auto& pred : node.predecessors){
        auto call = std::static_pointer_cast<FunctionCall<std::set<std::string>>>(pred);
        
        if (call->arguments.size() != def->formalParameters.size()){
            throw "Function call " + call->functionId + " didnt match the number of arguments";
        }


        for(int i = 0; i < call->arguments.size(); ++i){
            bool isTainted = call->arguments[i]->evaluate(pred->state);
            if(isTainted){
                auto parameter = def->formalParameters[i];
                node.state.insert(parameter);
            }
        }
    }
}
void TaintAnalyzer::visit_functionExit(FunctionExitNode<std::set<std::string>>& node){
    std::cout << "Exit" <<std::endl;
    join(node);
}

bool evaluateExpression(std::shared_ptr<Expression> expression, std::set<std::string> &state)
{
    return expression->evaluate(state);
}
