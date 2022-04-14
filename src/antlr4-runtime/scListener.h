
// Generated from sc.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "scParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by scParser.
 */
class  scListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(scParser::ProgContext *ctx) = 0;
  virtual void exitProg(scParser::ProgContext *ctx) = 0;

  virtual void enterFunctionDef(scParser::FunctionDefContext *ctx) = 0;
  virtual void exitFunctionDef(scParser::FunctionDefContext *ctx) = 0;

  virtual void enterStatements(scParser::StatementsContext *ctx) = 0;
  virtual void exitStatements(scParser::StatementsContext *ctx) = 0;

  virtual void enterStatement(scParser::StatementContext *ctx) = 0;
  virtual void exitStatement(scParser::StatementContext *ctx) = 0;

  virtual void enterStatementassign(scParser::StatementassignContext *ctx) = 0;
  virtual void exitStatementassign(scParser::StatementassignContext *ctx) = 0;

  virtual void enterStatementinit(scParser::StatementinitContext *ctx) = 0;
  virtual void exitStatementinit(scParser::StatementinitContext *ctx) = 0;

  virtual void enterStatementinitarray(scParser::StatementinitarrayContext *ctx) = 0;
  virtual void exitStatementinitarray(scParser::StatementinitarrayContext *ctx) = 0;

  virtual void enterStatementcallduping(scParser::StatementcalldupingContext *ctx) = 0;
  virtual void exitStatementcallduping(scParser::StatementcalldupingContext *ctx) = 0;

  virtual void enterArrayelement(scParser::ArrayelementContext *ctx) = 0;
  virtual void exitArrayelement(scParser::ArrayelementContext *ctx) = 0;

  virtual void enterWhileloop(scParser::WhileloopContext *ctx) = 0;
  virtual void exitWhileloop(scParser::WhileloopContext *ctx) = 0;

  virtual void enterStatementif(scParser::StatementifContext *ctx) = 0;
  virtual void exitStatementif(scParser::StatementifContext *ctx) = 0;

  virtual void enterArgs(scParser::ArgsContext *ctx) = 0;
  virtual void exitArgs(scParser::ArgsContext *ctx) = 0;

  virtual void enterExpression(scParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(scParser::ExpressionContext *ctx) = 0;

  virtual void enterExpressionM(scParser::ExpressionMContext *ctx) = 0;
  virtual void exitExpressionM(scParser::ExpressionMContext *ctx) = 0;

  virtual void enterFunctionCallInit(scParser::FunctionCallInitContext *ctx) = 0;
  virtual void exitFunctionCallInit(scParser::FunctionCallInitContext *ctx) = 0;

  virtual void enterFunctionCall(scParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(scParser::FunctionCallContext *ctx) = 0;

  virtual void enterOpt_parameters(scParser::Opt_parametersContext *ctx) = 0;
  virtual void exitOpt_parameters(scParser::Opt_parametersContext *ctx) = 0;

  virtual void enterParameters(scParser::ParametersContext *ctx) = 0;
  virtual void exitParameters(scParser::ParametersContext *ctx) = 0;

  virtual void enterParameter(scParser::ParameterContext *ctx) = 0;
  virtual void exitParameter(scParser::ParameterContext *ctx) = 0;

  virtual void enterType(scParser::TypeContext *ctx) = 0;
  virtual void exitType(scParser::TypeContext *ctx) = 0;


};

