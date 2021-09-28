#pragma once

#include "antlr4-runtime/scBaseVisitor.h"
#include <memory>
#include "antlr4-runtime/scParser.h"
#include "cfg.h"
#include <vector>
#include "Expression.h"
#include <iostream>

template <typename LatticeType>
class ScTransformer : public scBaseVisitor
{
public:
    std::vector<std::shared_ptr<FunctionDefinition<LatticeType>>> functionNodes{};
    std::vector<std::shared_ptr<Node<LatticeType>>> nodes{};

    std::shared_ptr<Node<LatticeType>> last{};

    void add_node(std::shared_ptr<Node<LatticeType>> node){
        last = node;
        nodes.push_back(node);
    }

    antlrcpp::Any visitFunctionDef(scParser::FunctionDefContext *ctx) override
    {
        std::vector<std::string> parameters{};

        if (ctx->opt_parameters()->parameters() != nullptr)
        {
            auto *param = ctx->opt_parameters()->parameters();
            while (param != nullptr)
            {
                parameters.push_back(param->parameter()->type()->getText() + " " + param->parameter()->ID()->getText());
                param = param->parameters();
            }
        }


        std::shared_ptr<FunctionDefinition<LatticeType>> functionDef;
        if (ctx->type() != nullptr)
        {
            functionDef = std::make_shared<FunctionDefinition<LatticeType>>(ctx->ID()->getText(), parameters, ctx->type()->getText());
        }
        else
        {
            functionDef = std::make_shared<FunctionDefinition<LatticeType>>(ctx->ID()->getText(), parameters);
        }
        add_node(functionDef);
        functionNodes.push_back(functionDef);

        auto out = visitChildren(ctx);

        if (ctx->expression() != nullptr)
        {
            antlrcpp::Any result = ctx->expression()->accept(this);
            std::shared_ptr<Expression> expression = result.as<std::shared_ptr<Expression>>();

            auto node = std::make_shared<ReturnNode<LatticeType>>(expression, functionDef->functionId);
            node->predecessors.insert(last);
            last->successors.insert(node);
            add_node(node);

            last = nullptr;
        }

        return out;
    }

    virtual antlrcpp::Any visitStatementassign(scParser::StatementassignContext *ctx) override
    {
        antlrcpp::Any result = ctx->expression()->accept(this);
        std::shared_ptr<Expression> expression = result.as<std::shared_ptr<Expression>>();
        
        auto node = std::make_shared<AssignmentNode<LatticeType>>(ctx->ID()->getText(), expression);
        node->predecessors.insert(last);
        last->successors.insert(node);
        add_node(node);

        return nullptr;
    }

    virtual antlrcpp::Any visitStatementinit(scParser::StatementinitContext *ctx) override
    {
        antlrcpp::Any result = ctx->expression()->accept(this);
        std::shared_ptr<Expression> expression = result.as<std::shared_ptr<Expression>>();

        auto node = std::make_shared<InitializerNode<LatticeType>>(ctx->type()->getText(), ctx->ID()->getText(), expression);
        node->predecessors.insert(last);
        last->successors.insert(node);
        add_node(node);

        return nullptr;
    }

    virtual antlrcpp::Any visitExpression(scParser::ExpressionContext *ctx) override
    {
        std::shared_ptr<Expression> expression;
        if (ctx->ID() != nullptr){
            expression = std::make_shared<VariableExpression>(ctx->ID()->getText());
        }else if(ctx->INTEGER() != nullptr){
            expression = std::make_shared<LiteralExpression>(ctx->INTEGER()->getText());
        }
        else if(ctx->functionCall() != nullptr){
            return ctx->functionCall()->accept(this);
        }else{
            antlrcpp::Any result = ctx->expression()->accept(this);
            std::shared_ptr<Expression> inner = result.as<std::shared_ptr<Expression>>();
            expression = std::make_shared<ParanthesisExpression>(inner);
        }
        
        if (ctx->expressionM() != nullptr && ctx->expressionM()->expression() != nullptr){
            
            antlrcpp::Any result = ctx->expressionM()->accept(this);
            auto rhs = result.as<std::shared_ptr<BinaryOperatorExpression>>();
            rhs->lhs = expression;


            return (std::shared_ptr<Expression>)rhs;
        }

        return expression;
    }

    virtual antlrcpp::Any visitFunctionCall(scParser::FunctionCallContext *ctx) override 
    {
        antlrcpp::Any result = ctx->args()->accept(this);
        auto args = result.as<std::vector<std::shared_ptr<Expression>>>();
        auto id = ctx->ID()->getText();
        std::shared_ptr<FunctionDefinition<LatticeType>> successor{};

        for (std::shared_ptr<FunctionDefinition<LatticeType>> functionNode : functionNodes){
            if(functionNode->functionId == id) {
                successor = functionNode;
            }
        }

        auto node = std::make_shared<FunctionCall<LatticeType>>(id, args);
        node->predecessors.insert(last);
        last->successors.insert(node);
        node->successors.insert(successor);
        add_node(node);
        
        return nullptr;
    }

    virtual antlrcpp::Any visitArgs(scParser::ArgsContext *ctx) override
    {
        antlrcpp::Any expResult = ctx->expression()->accept(this);
        auto exp = expResult.as<std::shared_ptr<Expression>>();

        if(ctx->args() != nullptr){
            antlrcpp::Any argResult = ctx->args()->accept(this);
            auto args = argResult.as<std::vector<std::shared_ptr<Expression>>>();
            args.push_back(exp);
            return args;
        }else{
            std::vector<std::shared_ptr<Expression>> args{exp};
            return args;
        }
    }

    virtual antlrcpp::Any visitExpressionM(scParser::ExpressionMContext *ctx) override
    {
        if (ctx->expression() == nullptr){
            return nullptr;
        }

        std::string op = ctx->op->getText();

        if (ctx->expressionM() != nullptr && ctx->expressionM()->expression() != nullptr){
            antlrcpp::Any rhs_result = ctx->expressionM()->accept(this);
            antlrcpp::Any lhs_result = ctx->expression()->accept(this);
            std::shared_ptr<BinaryOperatorExpression> rhs_expr = rhs_result.as<std::shared_ptr<BinaryOperatorExpression>>();
            rhs_expr->lhs = lhs_result.as<std::shared_ptr<Expression>>();

            return std::make_shared<BinaryOperatorExpression>(nullptr, op, rhs_expr);
        }else{
            antlrcpp::Any result = ctx->expression()->accept(this);
            std::shared_ptr<Expression> rhs = result.as<std::shared_ptr<Expression>>();
            return std::make_shared<BinaryOperatorExpression>(nullptr, op, rhs);
        }
    }
};

template <typename LatticeType>
std::vector<std::shared_ptr<FunctionDefinition<LatticeType>>> parse_to_cfg_function_defs(antlr4::ANTLRInputStream &stream)
{
    scLexer lexer(&stream);
    antlr4::CommonTokenStream tokens(&lexer);
    scParser parser(&tokens);

    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    ScTransformer<LatticeType> transformer;
    parser.prog()->accept(&transformer);

    return transformer.functionNodes;
}

template <typename LatticeType>
std::vector<std::shared_ptr<Node<LatticeType>>> parse_to_cfg(antlr4::ANTLRInputStream &stream)
{
    scLexer lexer(&stream);
    antlr4::CommonTokenStream tokens(&lexer);
    scParser parser(&tokens);

    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    ScTransformer<LatticeType> transformer;
    parser.prog()->accept(&transformer);

    return transformer.nodes;
}