#include "set"
#include "string"
#include "algorithm"

class Expression {
public:
    Expression* lhs;
    Expression* rhs;
    virtual bool evaluate(std::set<std::string>& state);
    virtual std::string dotPrint();
};

class BinaryOperatorExpression : Expression {

    bool evaluate(std::set<std::string>& state){
        return lhs->evaluate(state) || rhs->evaluate(state);
    }

    std::string dotPrint() override{
        std::string out;
        out.append(lhs->dotPrint()).append(" -op- ").append(rhs->dotPrint());
        return out;
    }
};

class LiteralExpression : Expression {

    bool evaluate(std::set<std::string>& state){
        return false;
    }

    std::string dotPrint() override{
        return "Literal";
    }
};

class VariableExpression : Expression {
public:
    std::string id;

    bool evaluate(std::set<std::string>& state){
        return state.find(id) != state.end();
    }

    std::string dotPrint() override{
        return id;
    }
};
