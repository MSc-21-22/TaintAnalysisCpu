
// Generated from /home/nhug/dev/TaintAnalysisCpu/sc.g4 by ANTLR 4.8

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
    virtual antlrcpp::Any visitProg(scParser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDef(scParser::FunctionDefContext *context) = 0;

    virtual antlrcpp::Any visitStatements(scParser::StatementsContext *context) = 0;

    virtual antlrcpp::Any visitStatement(scParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitArgs(scParser::ArgsContext *context) = 0;

    virtual antlrcpp::Any visitExpression(scParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitExpressionM(scParser::ExpressionMContext *context) = 0;

    virtual antlrcpp::Any visitParameters(scParser::ParametersContext *context) = 0;

    virtual antlrcpp::Any visitParametersM(scParser::ParametersMContext *context) = 0;

    virtual antlrcpp::Any visitParameter(scParser::ParameterContext *context) = 0;

    virtual antlrcpp::Any visitType(scParser::TypeContext *context) = 0;


};

