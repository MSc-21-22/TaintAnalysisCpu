
// Generated from sc.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"
#include "scVisitor.h"


/**
 * This class provides an empty implementation of scVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  scBaseVisitor : public scVisitor {
public:

  virtual std::any visitProg(scParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDef(scParser::FunctionDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatements(scParser::StatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(scParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementassign(scParser::StatementassignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementinit(scParser::StatementinitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementinitarray(scParser::StatementinitarrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayelement(scParser::ArrayelementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileloop(scParser::WhileloopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementif(scParser::StatementifContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgs(scParser::ArgsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(scParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionM(scParser::ExpressionMContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCallInit(scParser::FunctionCallInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(scParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOpt_parameters(scParser::Opt_parametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameters(scParser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter(scParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(scParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }


};

