#include "set"
#include "string"
#include "algorithm"

class Expression {
public:
    Expression* lhs;
    Expression* rhs;
    virtual bool evaluate(std::set<std::string>& state);
};

class BinaryOperatorExpression : Expression {

    bool evaluate(std::set<std::string>& state){
        return lhs->evaluate(state) || rhs->evaluate(state);
    }
};

class LiteralExpression : Expression {

    bool evaluate(std::set<std::string>& state){
        return false;
    }
};

class VariableExpression : Expression {
public:
    std::string id;
    bool evaluate(std::set<std::string>& state){
        return state.find(id) != state.end();
    }
};
