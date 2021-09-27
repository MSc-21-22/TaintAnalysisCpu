#include "cfg.h"
#include "set"

bool evaluateExpression(std::shared_ptr<Expression>, std::set<std::string>*);

class transferFunction : public CfgVisitor<std::set<std::string>>{


    void visit_initializtion(InitializerNode<std::set<std::string>>& node) override{

        if (evaluateExpression(node.expression, &node.state)){
            node.state.insert(node.id);
        }

        for (auto& succ : node.successors){
            succ->accept(*this);
        }
    }
    void visit_assignment(AssignmentNode<std::set<std::string>>& node) override{

        if (!evaluateExpression(node.expression, &node.state)){
            node.state.erase(node.id);
        }

        for (auto& succ : node.successors){
            succ->accept(*this);
        }
    }
    void visit_functioncall(FunctionCall<std::set<std::string>>& node) override{

        for (auto& succ : node.successors){
            succ->accept(*this);
        }
    }
    void visit_functiondef(FunctionDefinition<std::set<std::string>>& node) override{

        for (auto& succ : node.successors){
            succ->accept(*this);
        }
    };
    void visit_return(ReturnNode<std::set<std::string>>& node) override{


        for (auto& succ : node.successors){
            succ->accept(*this);
        }
    }

};

bool evaluateExpression(std::shared_ptr<Expression> expression, std::set<std::string>& state){
    return expression->evaluate(state);
}


