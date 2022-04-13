
// Generated from sc.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"
#include "scParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by scParser.
 */
class  scVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by scParser.
   */
    virtual std::any visitProg(scParser::ProgContext *context) = 0;

    virtual std::any visitFunctionDef(scParser::FunctionDefContext *context) = 0;

    virtual std::any visitStatements(scParser::StatementsContext *context) = 0;

    virtual std::any visitStatement(scParser::StatementContext *context) = 0;

    virtual std::any visitStatementassign(scParser::StatementassignContext *context) = 0;

    virtual std::any visitStatementinit(scParser::StatementinitContext *context) = 0;

    virtual std::any visitStatementinitarray(scParser::StatementinitarrayContext *context) = 0;

    virtual std::any visitArrayelement(scParser::ArrayelementContext *context) = 0;

    virtual std::any visitWhileloop(scParser::WhileloopContext *context) = 0;

    virtual std::any visitStatementif(scParser::StatementifContext *context) = 0;

    virtual std::any visitArgs(scParser::ArgsContext *context) = 0;

    virtual std::any visitExpression(scParser::ExpressionContext *context) = 0;

    virtual std::any visitExpressionM(scParser::ExpressionMContext *context) = 0;

    virtual std::any visitFunctionCallInit(scParser::FunctionCallInitContext *context) = 0;

    virtual std::any visitFunctionCall(scParser::FunctionCallContext *context) = 0;

    virtual std::any visitOpt_parameters(scParser::Opt_parametersContext *context) = 0;

    virtual std::any visitParameters(scParser::ParametersContext *context) = 0;

    virtual std::any visitParameter(scParser::ParameterContext *context) = 0;

    virtual std::any visitType(scParser::TypeContext *context) = 0;


};

