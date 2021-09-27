#pragma once

#include "antlr4-runtime/scBaseVisitor.h"
#include <memory>
#include "antlr4-runtime/scParser.h"
#include "cfg.h"
#include <vector>
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
        std::cout << "Function " << ctx->ID()->getText() << std::endl;
        
        auto* param = ctx->opt_parameters()->parameters();
        std::cout << (param == nullptr) << std::endl;
        while(param != nullptr){
            param = param->parameters();
            parameters.push_back(param->parameter()->getText());
        }

        std::cout << "Function push" << std::endl;

        if (ctx->type() != nullptr){
        last = std::make_shared<FunctionDefinition<LatticeType>>(ctx->ID()->getText(), parameters, ctx->type()->getText());
        }else{
        last = std::make_shared<FunctionDefinition<LatticeType>>(ctx->ID()->getText(), parameters);
        }
        std::cout << "Function created" << std::endl;
        functionNodes.push_back(last);

        std::cout << "Children " << std::endl;
        auto out = visitChildren(ctx);
        std::cout << "After" << std::endl;

        if (ctx->expression() != nullptr){
            auto node = std::make_shared<ReturnNode<LatticeType>>(ctx->expression()->getText());
            node->predecessors.insert(last);
            last->successors.insert(node);
            last = node;
        }
        
        return out;
    }

    virtual antlrcpp::Any visitStatementassign(scParser::StatementassignContext *ctx) override
    {
        //auto node = std::make_shared<AssignmentNode<LatticeType>>(ctx->ID()->getText(), ctx->expression()->getText());
        //node->predecessors.insert(last);
        //last->successors.insert(node);
        //last = node;

        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitStatementinit(scParser::StatementinitContext *ctx) override
    {
        //auto node = std::make_shared<InitializerNode<LatticeType>>(ctx->type()->getText(), ctx->ID()->getText(), ctx->expression()->getText());
        //node->predecessors.insert(last);
        //last->successors.insert(node);
        //last = node;

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