
// Generated from sc.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "scListener.h"


/**
 * This class provides an empty implementation of scListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  scBaseListener : public scListener {
public:

  virtual void enterProg(scParser::ProgContext * /*ctx*/) override { }
  virtual void exitProg(scParser::ProgContext * /*ctx*/) override { }

  virtual void enterFunctionDef(scParser::FunctionDefContext * /*ctx*/) override { }
  virtual void exitFunctionDef(scParser::FunctionDefContext * /*ctx*/) override { }

  virtual void enterStatements(scParser::StatementsContext * /*ctx*/) override { }
  virtual void exitStatements(scParser::StatementsContext * /*ctx*/) override { }

  virtual void enterStatement(scParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(scParser::StatementContext * /*ctx*/) override { }

  virtual void enterStatementassign(scParser::StatementassignContext * /*ctx*/) override { }
  virtual void exitStatementassign(scParser::StatementassignContext * /*ctx*/) override { }

  virtual void enterStatementinit(scParser::StatementinitContext * /*ctx*/) override { }
  virtual void exitStatementinit(scParser::StatementinitContext * /*ctx*/) override { }

  virtual void enterStatementinitarray(scParser::StatementinitarrayContext * /*ctx*/) override { }
  virtual void exitStatementinitarray(scParser::StatementinitarrayContext * /*ctx*/) override { }

  virtual void enterStatementcallduping(scParser::StatementcalldupingContext * /*ctx*/) override { }
  virtual void exitStatementcallduping(scParser::StatementcalldupingContext * /*ctx*/) override { }

  virtual void enterArrayelement(scParser::ArrayelementContext * /*ctx*/) override { }
  virtual void exitArrayelement(scParser::ArrayelementContext * /*ctx*/) override { }

  virtual void enterWhileloop(scParser::WhileloopContext * /*ctx*/) override { }
  virtual void exitWhileloop(scParser::WhileloopContext * /*ctx*/) override { }

  virtual void enterStatementif(scParser::StatementifContext * /*ctx*/) override { }
  virtual void exitStatementif(scParser::StatementifContext * /*ctx*/) override { }

  virtual void enterArgs(scParser::ArgsContext * /*ctx*/) override { }
  virtual void exitArgs(scParser::ArgsContext * /*ctx*/) override { }

  virtual void enterExpression(scParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(scParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterExpressionM(scParser::ExpressionMContext * /*ctx*/) override { }
  virtual void exitExpressionM(scParser::ExpressionMContext * /*ctx*/) override { }

  virtual void enterFunctionCallInit(scParser::FunctionCallInitContext * /*ctx*/) override { }
  virtual void exitFunctionCallInit(scParser::FunctionCallInitContext * /*ctx*/) override { }

  virtual void enterFunctionCall(scParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(scParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterOpt_parameters(scParser::Opt_parametersContext * /*ctx*/) override { }
  virtual void exitOpt_parameters(scParser::Opt_parametersContext * /*ctx*/) override { }

  virtual void enterParameters(scParser::ParametersContext * /*ctx*/) override { }
  virtual void exitParameters(scParser::ParametersContext * /*ctx*/) override { }

  virtual void enterParameter(scParser::ParameterContext * /*ctx*/) override { }
  virtual void exitParameter(scParser::ParameterContext * /*ctx*/) override { }

  virtual void enterType(scParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(scParser::TypeContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

