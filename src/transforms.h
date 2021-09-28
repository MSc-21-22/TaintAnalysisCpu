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
    std::vector<std::shared_ptr<Node<LatticeType>>> functionNodes{};

    std::shared_ptr<Node<LatticeType>> last{};

    antlrcpp::Any visitFunctionDef(scParser::FunctionDefContext *ctx) override
    {
        std::vector<std::string> parameters{};
        
        auto* param = ctx->opt_parameters()->parameters();
        while(param != nullptr){
            param = param->parameters();
            parameters.push_back(param->parameter()->getText());
        }

        if (ctx->type() != nullptr){
        last = std::make_shared<FunctionDefinition<LatticeType>>(ctx->ID()->getText(), parameters, ctx->type()->getText());
        }else{
        last = std::make_shared<FunctionDefinition<LatticeType>>(ctx->ID()->getText(), parameters);
        }
        functionNodes.push_back(last);

        auto out = visitChildren(ctx);

        if (ctx->expression() != nullptr){
            auto node = std::make_shared<ReturnNode<LatticeType>>(std::make_shared<EmptyExpression>());
            node->predecessors.insert(last);
            last->successors.insert(node);
            last = node;
        }
        
        return out;
    }

    virtual antlrcpp::Any visitStatementassign(scParser::StatementassignContext *ctx) override
    {
        auto node = std::make_shared<AssignmentNode<LatticeType>>(ctx->ID()->getText(), std::make_shared<EmptyExpression>());
        node->predecessors.insert(last);
        last->successors.insert(node);
        last = node;

        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitStatementinit(scParser::StatementinitContext *ctx) override
    {
        auto node = std::make_shared<InitializerNode<LatticeType>>(ctx->type()->getText(), ctx->ID()->getText(), std::make_shared<EmptyExpression>());
        node->predecessors.insert(last);
        last->successors.insert(node);
        last = node;

        return visitChildren(ctx);
    }
};

template <typename LatticeType>
std::vector<std::shared_ptr<Node<LatticeType>>> parse_to_cfg(antlr4::ANTLRInputStream& stream)
{
    scLexer lexer(&stream);
    antlr4::CommonTokenStream tokens(&lexer);
    scParser parser(&tokens);

    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    ScTransformer<int> transformer;
    parser.prog()->accept(&transformer);

    return transformer.functionNodes;
}