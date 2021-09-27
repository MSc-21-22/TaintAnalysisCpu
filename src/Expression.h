#pragma once

#include "set"
#include "string"
#include "algorithm"

class Expression
{
public:
    virtual bool evaluate(std::set<std::string> &state) = 0;
    virtual std::string dotPrint() = 0;
};

class EmptyExpression : public Expression
{
public:
    EmptyExpression() {}

    bool evaluate(std::set<std::string> &state)
    {
        return true;
    }

    std::string dotPrint() override
    {
        std::string out;
        out.append("so empty");
        return out;
    }
};

class BinaryOperatorExpression : Expression
{
public:
    Expression *lhs;
    Expression *rhs;

    bool evaluate(std::set<std::string> &state)
    {
        return lhs->evaluate(state) || rhs->evaluate(state);
    }

    std::string dotPrint() override
    {
        std::string out;
        out.append(lhs->dotPrint()).append(" -op- ").append(rhs->dotPrint());
        return out;
    }
};

class LiteralExpression : Expression
{

    bool evaluate(std::set<std::string> &state)
    {
        return false;
    }

    std::string dotPrint() override
    {
        return "Literal";
    }
};

class VariableExpression : Expression
{
public:
    std::string id;

    bool evaluate(std::set<std::string> &state)
    {
        return state.find(id) != state.end();
    }

    std::string dotPrint() override
    {
        return id;
    }
};
