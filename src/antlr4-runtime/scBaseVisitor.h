
// Generated from /home/nhug/TaintAnalysisCpu/sc.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "scVisitor.h"


/**
 * This class provides an empty implementation of scVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  scBaseVisitor : public scVisitor {
public:

  virtual antlrcpp::Any visitProg(scParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionDef(scParser::FunctionDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatements(scParser::StatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(scParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatementassign(scParser::StatementassignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatementinit(scParser::StatementinitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatementinitarray(scParser::StatementinitarrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayelement(scParser::ArrayelementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhileloop(scParser::WhileloopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatementif(scParser::StatementifContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArgs(scParser::ArgsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(scParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressionM(scParser::ExpressionMContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionCallInit(scParser::FunctionCallInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionCall(scParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOpt_parameters(scParser::Opt_parametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameters(scParser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameter(scParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType(scParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }


};

