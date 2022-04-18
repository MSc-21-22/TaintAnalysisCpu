#pragma once

#include "set"
#include "string"
#include "algorithm"
#include <map>
#include <functional>
#include <memory>
#include <string_view>

class Expression
{
public:
    virtual bool evaluate(const std::set<std::string> &state) = 0;
    virtual std::set<std::string> get_variables() = 0;
    virtual std::set<int> get_indicies() = 0;
    virtual std::string dotPrint() = 0;
    virtual void replace_names(std::map<std::string, int>& names) = 0;
    virtual std::shared_ptr<Expression> deep_copy() = 0;
    virtual void each_variable(std::function<void(int)> function) = 0;
};

class EmptyExpression : public Expression
{
public:
    EmptyExpression() {}

    bool evaluate(const std::set<std::string>&)
    {
        return true;
    }

    std::set<std::string> get_variables(){
        return {};
    }

    std::set<int> get_indicies(){
        return {};
    }

    std::string dotPrint() override
    {
        std::string out;
        out.append("so empty");
        return out;
    }

    void replace_names(std::map<std::string, int>& names){

    }

    std::shared_ptr<Expression> deep_copy(){
        return std::make_shared<EmptyExpression>();
    }

    void each_variable(std::function<void(int)> function) {

    }
};

class BinaryOperatorExpression : public Expression
{
public:
    std::string op;
    std::shared_ptr<Expression> lhs;
    std::shared_ptr<Expression> rhs;

    BinaryOperatorExpression(std::shared_ptr<Expression> lhs, std::string op, std::shared_ptr<Expression> rhs): op(op), lhs(lhs), rhs(rhs){}

    bool evaluate(const std::set<std::string> &state)
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

    std::set<int> get_indicies(){
        std::set<int> out;
        auto left = lhs->get_indicies();
        auto right = rhs->get_indicies();
        std::set_union(left.begin(), left.end(), right.begin(), right.end(), std::inserter(out, out.begin()));

        return out;
    }

    std::string dotPrint() override
    {
        std::string out;
        out.append(lhs->dotPrint()).append(" "+ op +" ").append(rhs->dotPrint());
        return out;
    }

    void replace_names(std::map<std::string, int>& names){
        lhs->replace_names(names);
        rhs->replace_names(names);
    }

    std::shared_ptr<Expression> deep_copy(){
        return std::make_shared<BinaryOperatorExpression>(lhs->deep_copy(), op, rhs->deep_copy());
    }

    void each_variable(std::function<void(int)> function) {
        lhs->each_variable(function);
        rhs->each_variable(function);
    }
};

class LiteralExpression : public Expression
{
public:
    std::string literal;

    LiteralExpression(std::string literal): literal(literal){}

    bool evaluate(const std::set<std::string>&)
    {
        return false;
    }
    
    std::set<std::string> get_variables(){
        return {};
    }

    std::set<int> get_indicies(){
        return {};
    }

    std::string dotPrint() override
    {
        return literal;
    }

    void replace_names(std::map<std::string, int>& names){

    }

    std::shared_ptr<Expression> deep_copy(){
        return std::make_shared<LiteralExpression>(literal);
    }

    void each_variable(std::function<void(int)> function) {

    }
};

class VariableExpression : public Expression
{
public:
    std::string id;
    int var_index{-1};

    VariableExpression(std::string id): id(id){}

    bool evaluate(const std::set<std::string> &state)
    {
        return state.find(id) != state.end();
    }

    std::set<std::string> get_variables(){
        return {id};
    }

    std::set<int> get_indicies(){
        return {var_index};
    }

    std::string dotPrint() override
    {
        return id;
    }

    void replace_names(std::map<std::string, int>& names){
        auto new_id = names.find(id);
        if(new_id != names.end()){
            var_index = new_id->second;
        }else{
            names[id] = names.size();
            var_index = names.size() - 1;
        }
    }

    std::shared_ptr<Expression> deep_copy(){
        return std::make_shared<VariableExpression>(id);
    }

    void each_variable(std::function<void(int)> function) {
        function(var_index);
    }
};

class ParanthesisExpression : public Expression{
public:
    std::shared_ptr<Expression> expression;

    ParanthesisExpression(std::shared_ptr<Expression> expression): expression(expression){}

    bool evaluate(const std::set<std::string> &state)
    {
        return expression->evaluate(state);
    }

    std::set<std::string> get_variables(){
        return expression->get_variables();
    }

    std::set<int> get_indicies(){
        return expression->get_indicies();
    }

    std::string dotPrint() override
    {
        return "("+expression->dotPrint()+")";
    }

    void replace_names(std::map<std::string, int>& names){
        expression->replace_names(names);
    }

    std::shared_ptr<Expression> deep_copy(){
        return std::make_shared<ParanthesisExpression>(expression->deep_copy());
    }

    void each_variable(std::function<void(int)> function) {
        expression->each_variable(function);
    }
};

class ArrayExpression : public Expression
{
public:
    std::string id;
    int var_index{ -1 };
    std::shared_ptr<Expression> indexExpression;

    ArrayExpression(std::string id, std::shared_ptr<Expression> index): id(id), indexExpression(index){}

    bool evaluate(const std::set<std::string> &state)
    {
        if (state.find(id) != state.end())
            return true;
        return indexExpression->evaluate(state);
    }

    std::set<std::string> get_variables()
    {
        return {id};
    }

    std::set<int> get_indicies(){
        return {var_index};
    }

    std::string dotPrint() override
    {
        return id + "[" + indexExpression->dotPrint() + "]";
    }

    void replace_names(std::map<std::string, int>& names){
        auto new_id = names.find(id);
        if (new_id != names.end()) {
            var_index = new_id->second;
        }
        else {
            names[id] = names.size();
            var_index = names.size() - 1;
        }
        indexExpression->replace_names(names);
    }

    std::shared_ptr<Expression> deep_copy(){
        return std::make_shared<ArrayExpression>(id, indexExpression->deep_copy());
    }

    void each_variable(std::function<void(int)> function) {
        function(var_index);
    }
};
