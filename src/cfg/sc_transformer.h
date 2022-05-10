#pragma once

#include "antlr4-runtime/scBaseVisitor.h"
#include <memory>
#include "antlr4-runtime/scParser.h"
#include <cfg/cfg.h>
#include <vector>
#include <iostream>
#include <map>
#include <cfg/transformations/cfg_clone.h>
#include <algorithm>

std::string stringify_parameters(std::vector<std::string> content);

class ScTransformer : public scBaseVisitor
{
public:
    std::vector<std::shared_ptr<FunctionEntryNode>> functionNodes{};
    std::map<std::string, std::shared_ptr<FunctionEntryNode>> functions{};
    std::vector<std::shared_ptr<FunctionEntryNode>> entryNodes{};
    std::vector<std::shared_ptr<Node>> nodes{};

    ScTransformer() = default;
    ScTransformer(std::map<std::string, int> function_counts) : function_counts(function_counts){}
private:
    std::map<std::string, int> function_counts{};
    std::vector<std::shared_ptr<Node>> last{};


    void link_to_lasts(std::shared_ptr<Node> node){
        for(auto& other : last){
            node->add_predecessor(other);
            other->add_successor(node);
        }
    }

    void add_node(std::shared_ptr<Node> node){
        node->entry_node = entryNodes.back();
        last = {node};
        nodes.push_back(node);
    }

    std::shared_ptr<FunctionEntryNode> create_entry_node(std::shared_ptr<PropagationNode> function_def, std::vector<std::string> parameters, std::string function_id){
        auto entry = std::make_shared<FunctionEntryNode>(function_id, parameters);
        entryNodes.push_back(entry);
        functions[function_id] = entry;
        add_node(function_def);
        link_to_lasts(function_def);
        add_node(entry);
        functionNodes.push_back(entry);

        return entry;
    }

    int get_call_count(scParser::StatementcalldupingContext *ctx){
        if(ctx->INTEGER() != nullptr){
            return std::stoi(ctx->INTEGER()->getText());
        } else if(ctx->ID() != nullptr){
            return function_counts[ctx->ID()->getText()];
        }else{
            throw "Something went wrong with duplicate calls";
        }
    }

public:

    antlrcpp::Any visitStatementcallduping(scParser::StatementcalldupingContext *ctx) override {
        int iterations_left = get_call_count(ctx);
        while(iterations_left-- > 0){
            ctx->functionCallInit()->accept(this);
        }
        return nullptr;
    }

    antlrcpp::Any visitFunctionDef(scParser::FunctionDefContext *ctx) override
    {
        std::vector<std::string> parameters{};

        if (ctx->opt_parameters()->parameters() != nullptr)
        {
            auto *param = ctx->opt_parameters()->parameters();
            while (param != nullptr)
            {
                parameters.push_back(param->parameter()->ID()->getText());
                param = param->parameters();
            }
        }


        std::shared_ptr<PropagationNode> functionDef;
        std::shared_ptr<FunctionEntryNode> entry;
        if (ctx->type() != nullptr)
        {
            std::string syntax = ctx->type()->getText() + " " + ctx->ID()->getText();
            syntax += stringify_parameters(parameters);

            functionDef = std::make_shared<PropagationNode>(syntax);
            entry = create_entry_node(functionDef, parameters, ctx->ID()->getText());

            auto out = visitChildren(ctx);
        }
        else
        {
            std::string syntax = ctx->ID()->getText();
            syntax += stringify_parameters(parameters);

            functionDef = std::make_shared<PropagationNode>(syntax);
            entry = create_entry_node(functionDef, parameters, ctx->ID()->getText());

            auto out = visitChildren(ctx);
            auto returnNode = std::make_shared<EmptyReturnNode>(ctx->ID()->getText());
            link_to_lasts(returnNode);
            add_node(returnNode);
            link_to_lasts(entry->exit);
            add_node(entry->exit);
        }


        if (ctx->expression() != nullptr)
        {
            antlrcpp::Any result = ctx->expression()->accept(this);
            std::shared_ptr<Expression> expression = result.as<std::shared_ptr<Expression>>();

            auto node = std::make_shared<ReturnNode>(expression, ctx->ID()->getText());
            link_to_lasts(node);
            add_node(node);
            link_to_lasts(entry->exit);
            add_node(entry->exit);

            last = {};
        }
        return nullptr;
    }

    virtual antlrcpp::Any visitStatementassign(scParser::StatementassignContext *ctx) override
    {
        if (ctx->expression().size() == 2)
        {
            antlrcpp::Any indexResult = ctx->expression()[0]->accept(this);
            std::shared_ptr<Expression> indexExpression = indexResult.as<std::shared_ptr<Expression>>();
            antlrcpp::Any result = ctx->expression()[1]->accept(this);
            std::shared_ptr<Expression> expression = result.as<std::shared_ptr<Expression>>();
            std::string id = ctx->ID()->getText() + "[" + indexExpression->dotPrint() + "]";
            auto node = std::make_shared<ArrayAssignmentNode>(id, ctx->ID()->getText(), expression);
            link_to_lasts(node);
            add_node(node);
        }else{
            antlrcpp::Any result = ctx->expression()[0]->accept(this);
            std::shared_ptr<Expression> expression = result.as<std::shared_ptr<Expression>>();
            
            auto node = std::make_shared<AssignmentNode>(ctx->ID()->getText(), expression);
            link_to_lasts(node);
            add_node(node);
        }
        return nullptr;
    }

    virtual antlrcpp::Any visitStatementinit(scParser::StatementinitContext *ctx) override
    {
        antlrcpp::Any result = ctx->expression()->accept(this);
        std::shared_ptr<Expression> expression = result.as<std::shared_ptr<Expression>>();

        auto node = std::make_shared<AssignmentNode>(ctx->ID()->getText(), expression);
        link_to_lasts(node);
        add_node(node);

        return nullptr;
    }

    virtual antlrcpp::Any visitStatementif(scParser::StatementifContext *ctx) override
    {
        antlrcpp::Any result = ctx->expression()->accept(this);
        std::shared_ptr<Expression> expression = result.as<std::shared_ptr<Expression>>();

        std::string syntax = "if(" + expression->dotPrint() + ")";

        auto node = std::make_shared<PropagationNode>(syntax);
        link_to_lasts(node);
        add_node(node);

        std::vector<std::shared_ptr<Node>> endif;
        for (auto& s : ctx->statements()){
            last={node};
            antlrcpp::Any statement = s->accept(this);
            endif.insert(endif.end(), last.begin(), last.end());
        }
        last=endif;
        return nullptr;
    }

    virtual antlrcpp::Any visitExpression(scParser::ExpressionContext *ctx) override
    {
        std::shared_ptr<Expression> expression;
        if (ctx->ID() != nullptr){
            if (ctx->expression() != nullptr){
                antlrcpp::Any result = ctx->expression()->accept(this);
                std::shared_ptr<Expression> indexExpression = result.as<std::shared_ptr<Expression>>();
                expression = std::make_shared<ArrayExpression>(ctx->ID()->getText(), indexExpression);
            }else{   
                expression = std::make_shared<VariableExpression>(ctx->ID()->getText());
            }
        }else if(ctx->INTEGER() != nullptr){
            expression = std::make_shared<LiteralExpression>(ctx->INTEGER()->getText());
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

    virtual antlrcpp::Any visitFunctionCallInit(scParser::FunctionCallInitContext *ctx) override {
        antlrcpp::Any result = ctx->functionCall()->accept(this);
        auto node = result.as<std::shared_ptr<PropagationNode>>();

        auto expr = std::make_shared<VariableExpression>(RETURN_VAR);
        last.push_back(node);
        auto assign = std::make_shared<AssignReturnNode>(ctx->ID()->getText());
        link_to_lasts(assign);
        add_node(assign);

        return nullptr;
    }

    virtual antlrcpp::Any visitFunctionCall(scParser::FunctionCallContext *ctx) override 
    {
        std::vector<std::shared_ptr<Expression>> args;
        if(ctx->args() != nullptr){
            antlrcpp::Any result = ctx->args()->accept(this);
            args = result.as<std::vector<std::shared_ptr<Expression>>>();
        }
        auto id = ctx->ID()->getText();
        std::shared_ptr<FunctionEntryNode> functionEntry = std::static_pointer_cast<FunctionEntryNode>(functions[id]);
        auto successor = clone_entry(functionEntry, &nodes, entryNodes);
        std::reverse(args.begin(), args.end());
        successor->arguments = args;

        std::string args_string = "(";
        if(args.size() > 0){
            args_string += args.front()->dotPrint();
            for(auto it = args.begin() + 1; it != args.end(); ++it){
                args_string += ", " + it->get()->dotPrint();
            }
        }
        args_string += ")";
        
        auto node = std::make_shared<PropagationNode>(id + args_string); 
        link_to_lasts(node);
        add_node(node);
        link_to_lasts(successor);

        last = {successor->exit};
        
        return node;
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

    virtual antlrcpp::Any visitWhileloop(scParser::WhileloopContext *ctx) override {
        antlrcpp::Any result = ctx->expression()->accept(this);
        std::shared_ptr<Expression> conditional = result.as<std::shared_ptr<Expression>>();

        std::string syntax = "while(" + conditional->dotPrint() + ")";

        auto node = std::make_shared<PropagationNode>(syntax);
        link_to_lasts(node);
        add_node(node);

        ctx->statements()->accept(this);
        link_to_lasts(node);
        last = {node};

        return nullptr;
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

    virtual antlrcpp::Any visitStatementinitarray(scParser::StatementinitarrayContext *ctx) override
    {
        std::vector<std::shared_ptr<Expression>> arrayExpressions;

        
        

        antlrcpp::Any result = ctx->expression()->accept(this);
        std::shared_ptr<Expression> arrayExpression = result.as<std::shared_ptr<Expression>>();

        if (ctx->arrayelement() != nullptr)
        {
            antlrcpp::Any result = ctx->arrayelement()->accept(this);
            std::vector<std::shared_ptr<Expression>> arrayelements = result.as<std::vector<std::shared_ptr<Expression>>>();

            arrayExpressions.push_back(arrayExpression);
            for (auto &i: arrayelements)
            {
                arrayExpressions.push_back(i);
            }
            
        }else{
            arrayExpressions.push_back(arrayExpression);
        }  
        auto node = std::make_shared<ArrayInitializerNode>(ctx->type()->getText(), ctx->ID()->getText(), ctx->INTEGER()->getText(), arrayExpressions);
        link_to_lasts(node);
        add_node(node);
        
        return nullptr;
    }

    virtual antlrcpp::Any visitArrayelement(scParser::ArrayelementContext *ctx) override
    {
        std::vector<std::shared_ptr<Expression>> expressionIndexes;
        if (ctx->expression() != nullptr){

            antlrcpp::Any result = ctx->expression()->accept(this);
            std::shared_ptr<Expression> expression = result.as<std::shared_ptr<Expression>>();

            expressionIndexes.push_back(expression);

            if (ctx->arrayelement() != nullptr)
            {
                antlrcpp::Any result2 = ctx->arrayelement()->accept(this);
                std::vector<std::shared_ptr<Expression>> arrayelements = result2.as<std::vector<std::shared_ptr<Expression>>>();
                
                for (auto &i: arrayelements)
                {
                    expressionIndexes.push_back(i);
                }   
            }
        }

        return expressionIndexes;
        
    }
};

ScTransformer parse_to_cfg_transformer(antlr4::ANTLRInputStream stream,  std::map<std::string, int>& call_counts);
std::vector<std::shared_ptr<Node>> parse_to_cfg(antlr4::ANTLRInputStream stream,  std::map<std::string, int>& call_counts);
void remove_function_nodes(ScTransformer& transformer);