#pragma once

#include <any>
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

private:
    std::vector<std::shared_ptr<Node>> last{};

    void link_to_lasts(std::shared_ptr<Node> node){
        for(auto& other : last){
            node->add_predecessor(other);
            other->add_successor(node);
        }
    }

    void add_node(std::shared_ptr<Node> node){
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

public:


    std::any visitFunctionDef(scParser::FunctionDefContext *ctx) override
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
            std::any result = ctx->expression()->accept(this);
            std::shared_ptr<Expression> expression = std::any_cast<std::shared_ptr<Expression>>(result);

            auto node = std::make_shared<ReturnNode>(expression, ctx->ID()->getText());
            link_to_lasts(node);
            add_node(node);
            link_to_lasts(entry->exit);
            add_node(entry->exit);

            last = {};
        }
        return nullptr;
    }

    virtual std::any visitStatementassign(scParser::StatementassignContext *ctx) override
    {
        if (ctx->expression().size() == 2)
        {
            std::any indexResult = ctx->expression()[0]->accept(this);
            std::shared_ptr<Expression> indexExpression = std::any_cast<std::shared_ptr<Expression>>(indexResult);
            std::any result = ctx->expression()[1]->accept(this);
            std::shared_ptr<Expression> expression = std::any_cast<std::shared_ptr<Expression>>(result);
            std::string id = ctx->ID()->getText() + "[" + indexExpression->dotPrint() + "]";
            auto node = std::make_shared<ArrayAssignmentNode>(id, ctx->ID()->getText(), expression);
            link_to_lasts(node);
            add_node(node);
        }else{
            std::any result = ctx->expression()[0]->accept(this);
            std::shared_ptr<Expression> expression = std::any_cast<std::shared_ptr<Expression>>(result);
            
            auto node = std::make_shared<AssignmentNode>(ctx->ID()->getText(), expression);
            link_to_lasts(node);
            add_node(node);
        }
        return nullptr;
    }

    virtual std::any visitStatementinit(scParser::StatementinitContext *ctx) override
    {
        std::any result = ctx->expression()->accept(this);
        std::shared_ptr<Expression> expression = std::any_cast<std::shared_ptr<Expression>>(result);

        auto node = std::make_shared<AssignmentNode>(ctx->ID()->getText(), expression);
        link_to_lasts(node);
        add_node(node);

        return nullptr;
    }

    virtual std::any visitStatementif(scParser::StatementifContext *ctx) override
    {
        std::any result = ctx->expression()->accept(this);
        std::shared_ptr<Expression> expression = std::any_cast<std::shared_ptr<Expression>>(result);

        std::string syntax = "if(" + expression->dotPrint() + ")";

        auto node = std::make_shared<PropagationNode>(syntax);
        link_to_lasts(node);
        add_node(node);

        std::vector<std::shared_ptr<Node>> endif;
        for (auto& s : ctx->statements()){
            last={node};
            std::any statement = s->accept(this);
            endif.insert(endif.end(), last.begin(), last.end());
        }
        last=endif;
        return nullptr;
    }

    virtual std::any visitExpression(scParser::ExpressionContext *ctx) override
    {
        std::shared_ptr<Expression> expression;
        if (ctx->ID() != nullptr){
            if (ctx->expression() != nullptr){
                std::any result = ctx->expression()->accept(this);
                std::shared_ptr<Expression> indexExpression = std::any_cast<std::shared_ptr<Expression>>(result);
                expression = std::make_shared<ArrayExpression>(ctx->ID()->getText(), indexExpression);
            }else{   
                expression = std::make_shared<VariableExpression>(ctx->ID()->getText());
            }
        }else if(ctx->INTEGER() != nullptr){
            expression = std::make_shared<LiteralExpression>(ctx->INTEGER()->getText());
        }else{
            std::any result = ctx->expression()->accept(this);
            std::shared_ptr<Expression> inner = std::any_cast<std::shared_ptr<Expression>>(result);
            expression = std::make_shared<ParanthesisExpression>(inner);
        }
        
        if (ctx->expressionM() != nullptr && ctx->expressionM()->expression() != nullptr){
            
            std::any result = ctx->expressionM()->accept(this);
            auto rhs = std::any_cast<std::shared_ptr<BinaryOperatorExpression>>(result);
            rhs->lhs = expression;


            return (std::shared_ptr<Expression>)rhs;
        }

        return expression;
    }

    virtual std::any visitFunctionCallInit(scParser::FunctionCallInitContext *ctx) override {
        std::any result = ctx->functionCall()->accept(this);
        auto node = std::any_cast<std::shared_ptr<PropagationNode>>(result);

        auto expr = std::make_shared<VariableExpression>(RETURN_VAR);
        last.push_back(node);
        auto assign = std::make_shared<AssignReturnNode>(ctx->ID()->getText());
        link_to_lasts(assign);
        add_node(assign);

        return nullptr;
    }

    virtual std::any visitFunctionCall(scParser::FunctionCallContext *ctx) override 
    {
        std::vector<std::shared_ptr<Expression>> args;
        if(ctx->args() != nullptr){
            std::any result = ctx->args()->accept(this);
            args = std::any_cast<std::vector<std::shared_ptr<Expression>>>(result);
        }
        auto id = ctx->ID()->getText();
        std::shared_ptr<FunctionEntryNode> functionEntry = std::static_pointer_cast<FunctionEntryNode>(functions[id]);
        auto successor = clone_entry(functionEntry, &nodes);
        std::reverse(args.begin(), args.end());
        successor->arguments = args;
    
        entryNodes.push_back(successor);

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

    virtual std::any visitArgs(scParser::ArgsContext *ctx) override
    {
        std::any expResult = ctx->expression()->accept(this);
        auto exp = std::any_cast<std::shared_ptr<Expression>>(expResult);

        if(ctx->args() != nullptr){
            std::any argResult = ctx->args()->accept(this);
            auto args = std::any_cast<std::vector<std::shared_ptr<Expression>>>(argResult);
            args.push_back(exp);
            return args;
        }else{
            std::vector<std::shared_ptr<Expression>> args{exp};
            return args;
        }
    }

    virtual std::any visitWhileloop(scParser::WhileloopContext *ctx) override {
        std::any result = ctx->expression()->accept(this);
        std::shared_ptr<Expression> conditional = std::any_cast<std::shared_ptr<Expression>>(result);

        std::string syntax = "while(" + conditional->dotPrint() + ")";

        auto node = std::make_shared<PropagationNode>(syntax);
        link_to_lasts(node);
        add_node(node);

        ctx->statements()->accept(this);
        link_to_lasts(node);
        last = {node};

        return nullptr;
    }

    virtual std::any visitExpressionM(scParser::ExpressionMContext *ctx) override
    {
        if (ctx->expression() == nullptr){
            return nullptr;
        }

        std::string op = ctx->op->getText();

        if (ctx->expressionM() != nullptr && ctx->expressionM()->expression() != nullptr){
            std::any rhs_result = ctx->expressionM()->accept(this);
            std::any lhs_result = ctx->expression()->accept(this);
            std::shared_ptr<BinaryOperatorExpression> rhs_expr = std::any_cast<std::shared_ptr<BinaryOperatorExpression>>(rhs_result);
            rhs_expr->lhs = std::any_cast<std::shared_ptr<Expression>>(lhs_result);

            return std::make_shared<BinaryOperatorExpression>(nullptr, op, rhs_expr);
        }else{
            std::any result = ctx->expression()->accept(this);
            std::shared_ptr<Expression> rhs = std::any_cast<std::shared_ptr<Expression>>(result);
            return std::make_shared<BinaryOperatorExpression>(nullptr, op, rhs);
        }
    }

    virtual std::any visitStatementinitarray(scParser::StatementinitarrayContext *ctx) override
    {
        std::vector<std::shared_ptr<Expression>> arrayExpressions;

        
        

        std::any result1 = ctx->expression()->accept(this);
        std::shared_ptr<Expression> arrayExpression = std::any_cast<std::shared_ptr<Expression>>(result1);

        if (ctx->arrayelement() != nullptr)
        {
            std::any result2 = ctx->arrayelement()->accept(this);
            std::vector<std::shared_ptr<Expression>> arrayelements = std::any_cast<std::vector<std::shared_ptr<Expression>>>(result2);

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

    virtual std::any visitArrayelement(scParser::ArrayelementContext *ctx) override
    {
        std::vector<std::shared_ptr<Expression>> expressionIndexes;
        if (ctx->expression() != nullptr){

            std::any result = ctx->expression()->accept(this);
            std::shared_ptr<Expression> expression = std::any_cast<std::shared_ptr<Expression>>(result);

            expressionIndexes.push_back(expression);

            if (ctx->arrayelement() != nullptr)
            {
                std::any result2 = ctx->arrayelement()->accept(this);
                std::vector<std::shared_ptr<Expression>> arrayelements = std::any_cast<std::vector<std::shared_ptr<Expression>>>(result2);
                
                for (auto &i: arrayelements)
                {
                    expressionIndexes.push_back(i);
                }   
            }
        }

        return expressionIndexes;
        
    }
};

ScTransformer parse_to_cfg_transformer(antlr4::ANTLRInputStream& stream);
std::vector<std::shared_ptr<Node>> parse_to_cfg(antlr4::ANTLRInputStream stream);
void remove_function_nodes(ScTransformer& transformer);