#pragma once

#include "set"
#include "string"
#include "algorithm"

class Expression
{
public:
    virtual bool evaluate(std::set<std::string> &state) = 0;
    virtual std::set<std::string> get_variables() = 0;
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

    std::set<std::string> get_variables(){
        return {};
    }

    std::string dotPrint() override
    {
        std::string out;
        out.append("so empty");
        return out;
    }
};

class BinaryOperatorExpression : public Expression
{
public:
    std::string op;
    std::shared_ptr<Expression> lhs;
    std::shared_ptr<Expression> rhs;

    BinaryOperatorExpression(std::shared_ptr<Expression> lhs, std::string op, std::shared_ptr<Expression> rhs): lhs(lhs), op(op), rhs(rhs){}

    bool evaluate(std::set<std::string> &state)
    {
        return lhs->evaluate(state) || rhs->evaluate(state);
    }

    std::set<std::string> get_variables(){
        std::set<std::string> out;
        auto left = lhs->get_variables();
        auto right = rhs->get_variables();
        std::set_union(left.begin(), left.end(), right.begin(), right.end(), std::inserter(out, out.begin()));

        return out;
    }

    std::string dotPrint() override
    {
        std::string out;
        out.append(lhs->dotPrint()).append(" "+ op +" ").append(rhs->dotPrint());
        return out;
    }
};

class LiteralExpression : public Expression
{
public:
    std::string literal;

    LiteralExpression(std::string literal): literal(literal){}

    bool evaluate(std::set<std::string> &state)
    {
        return false;
    }
    
    std::set<std::string> get_variables(){
        return {};
    }

    std::string dotPrint() override
    {
        return literal;
    }
};

class VariableExpression : public Expression
{
public:
    std::string id;

    VariableExpression(std::string id): id(id){}

    bool evaluate(std::set<std::string> &state)
    {
        return state.find(id) != state.end();
    }

    std::set<std::string> get_variables(){
        return {id};
    }

    std::string dotPrint() override
    {
        return id;
    }
};

class ParanthesisExpression : public Expression{
public:
    std::shared_ptr<Expression> expression;

    ParanthesisExpression(std::shared_ptr<Expression> expression): expression(expression){}

    bool evaluate(std::set<std::string> &state)
    {
        return expression->evaluate(state);
    }

    std::set<std::string> get_variables(){
        return expression->get_variables();
    }

    std::string dotPrint() override
    {
        return "("+expression->dotPrint()+")";
    }
};