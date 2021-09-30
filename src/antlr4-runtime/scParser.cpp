
// Generated from /mnt/c/dev/TaintAnalysisCpu/sc.g4 by ANTLR 4.8


#include "scVisitor.h"

#include "scParser.h"


using namespace antlrcpp;
using namespace antlr4;

scParser::scParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

scParser::~scParser() {
  delete _interpreter;
}

std::string scParser::getGrammarFileName() const {
  return "sc.g4";
}

const std::vector<std::string>& scParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& scParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

scParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* scParser::ProgContext::EOF() {
  return getToken(scParser::EOF, 0);
}

std::vector<scParser::FunctionDefContext *> scParser::ProgContext::functionDef() {
  return getRuleContexts<scParser::FunctionDefContext>();
}

scParser::FunctionDefContext* scParser::ProgContext::functionDef(size_t i) {
  return getRuleContext<scParser::FunctionDefContext>(i);
}


size_t scParser::ProgContext::getRuleIndex() const {
  return scParser::RuleProg;
}


antlrcpp::Any scParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

scParser::ProgContext* scParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, scParser::RuleProg);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(33);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == scParser::T__0

    || _la == scParser::T__7) {
      setState(30);
      functionDef();
      setState(35);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(36);
    match(scParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefContext ------------------------------------------------------------------

scParser::FunctionDefContext::FunctionDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* scParser::FunctionDefContext::ID() {
  return getToken(scParser::ID, 0);
}

tree::TerminalNode* scParser::FunctionDefContext::LPAREN() {
  return getToken(scParser::LPAREN, 0);
}

scParser::Opt_parametersContext* scParser::FunctionDefContext::opt_parameters() {
  return getRuleContext<scParser::Opt_parametersContext>(0);
}

tree::TerminalNode* scParser::FunctionDefContext::RPAREN() {
  return getToken(scParser::RPAREN, 0);
}

scParser::StatementsContext* scParser::FunctionDefContext::statements() {
  return getRuleContext<scParser::StatementsContext>(0);
}

scParser::TypeContext* scParser::FunctionDefContext::type() {
  return getRuleContext<scParser::TypeContext>(0);
}

scParser::ExpressionContext* scParser::FunctionDefContext::expression() {
  return getRuleContext<scParser::ExpressionContext>(0);
}


size_t scParser::FunctionDefContext::getRuleIndex() const {
  return scParser::RuleFunctionDef;
}


antlrcpp::Any scParser::FunctionDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitFunctionDef(this);
  else
    return visitor->visitChildren(this);
}

scParser::FunctionDefContext* scParser::functionDef() {
  FunctionDefContext *_localctx = _tracker.createInstance<FunctionDefContext>(_ctx, getState());
  enterRule(_localctx, 2, scParser::RuleFunctionDef);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(60);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(38);
        match(scParser::T__0);
        setState(39);
        match(scParser::ID);
        setState(40);
        match(scParser::LPAREN);
        setState(41);
        opt_parameters();
        setState(42);
        match(scParser::RPAREN);
        setState(43);
        match(scParser::T__1);
        setState(44);
        statements();
        setState(45);
        match(scParser::T__2);
        break;
      }

      case scParser::T__7: {
        enterOuterAlt(_localctx, 2);
        setState(47);
        type();
        setState(48);
        match(scParser::ID);
        setState(49);
        match(scParser::LPAREN);
        setState(50);
        opt_parameters();
        setState(51);
        match(scParser::RPAREN);
        setState(52);
        match(scParser::T__1);
        setState(53);
        statements();
        setState(54);
        match(scParser::T__3);
        setState(55);
        match(scParser::T__4);
        setState(56);
        expression();
        setState(57);
        match(scParser::T__3);
        setState(58);
        match(scParser::T__2);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementsContext ------------------------------------------------------------------

scParser::StatementsContext::StatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::StatementContext* scParser::StatementsContext::statement() {
  return getRuleContext<scParser::StatementContext>(0);
}

scParser::StatementsContext* scParser::StatementsContext::statements() {
  return getRuleContext<scParser::StatementsContext>(0);
}

scParser::WhileloopContext* scParser::StatementsContext::whileloop() {
  return getRuleContext<scParser::WhileloopContext>(0);
}


size_t scParser::StatementsContext::getRuleIndex() const {
  return scParser::RuleStatements;
}


antlrcpp::Any scParser::StatementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitStatements(this);
  else
    return visitor->visitChildren(this);
}

scParser::StatementsContext* scParser::statements() {
  StatementsContext *_localctx = _tracker.createInstance<StatementsContext>(_ctx, getState());
  enterRule(_localctx, 4, scParser::RuleStatements);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(70);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__7:
      case scParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(62);
        statement();
        setState(63);
        match(scParser::T__3);
        setState(64);
        statements();
        break;
      }

      case scParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(66);
        whileloop();
        setState(67);
        statements();
        break;
      }

      case scParser::T__2:
      case scParser::T__3: {
        enterOuterAlt(_localctx, 3);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

scParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::StatementinitContext* scParser::StatementContext::statementinit() {
  return getRuleContext<scParser::StatementinitContext>(0);
}

scParser::StatementassignContext* scParser::StatementContext::statementassign() {
  return getRuleContext<scParser::StatementassignContext>(0);
}

scParser::FunctionCallContext* scParser::StatementContext::functionCall() {
  return getRuleContext<scParser::FunctionCallContext>(0);
}


size_t scParser::StatementContext::getRuleIndex() const {
  return scParser::RuleStatement;
}


antlrcpp::Any scParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

scParser::StatementContext* scParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 6, scParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(75);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(72);
      statementinit();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(73);
      statementassign();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(74);
      functionCall();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementassignContext ------------------------------------------------------------------

scParser::StatementassignContext::StatementassignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* scParser::StatementassignContext::ID() {
  return getToken(scParser::ID, 0);
}

tree::TerminalNode* scParser::StatementassignContext::ASSIGN() {
  return getToken(scParser::ASSIGN, 0);
}

scParser::ExpressionContext* scParser::StatementassignContext::expression() {
  return getRuleContext<scParser::ExpressionContext>(0);
}


size_t scParser::StatementassignContext::getRuleIndex() const {
  return scParser::RuleStatementassign;
}


antlrcpp::Any scParser::StatementassignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitStatementassign(this);
  else
    return visitor->visitChildren(this);
}

scParser::StatementassignContext* scParser::statementassign() {
  StatementassignContext *_localctx = _tracker.createInstance<StatementassignContext>(_ctx, getState());
  enterRule(_localctx, 8, scParser::RuleStatementassign);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    match(scParser::ID);
    setState(78);
    match(scParser::ASSIGN);
    setState(79);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementinitContext ------------------------------------------------------------------

scParser::StatementinitContext::StatementinitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::TypeContext* scParser::StatementinitContext::type() {
  return getRuleContext<scParser::TypeContext>(0);
}

tree::TerminalNode* scParser::StatementinitContext::ID() {
  return getToken(scParser::ID, 0);
}

tree::TerminalNode* scParser::StatementinitContext::ASSIGN() {
  return getToken(scParser::ASSIGN, 0);
}

scParser::ExpressionContext* scParser::StatementinitContext::expression() {
  return getRuleContext<scParser::ExpressionContext>(0);
}


size_t scParser::StatementinitContext::getRuleIndex() const {
  return scParser::RuleStatementinit;
}


antlrcpp::Any scParser::StatementinitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitStatementinit(this);
  else
    return visitor->visitChildren(this);
}

scParser::StatementinitContext* scParser::statementinit() {
  StatementinitContext *_localctx = _tracker.createInstance<StatementinitContext>(_ctx, getState());
  enterRule(_localctx, 10, scParser::RuleStatementinit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    type();
    setState(82);
    match(scParser::ID);
    setState(83);
    match(scParser::ASSIGN);
    setState(84);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileloopContext ------------------------------------------------------------------

scParser::WhileloopContext::WhileloopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* scParser::WhileloopContext::LPAREN() {
  return getToken(scParser::LPAREN, 0);
}

scParser::ExpressionContext* scParser::WhileloopContext::expression() {
  return getRuleContext<scParser::ExpressionContext>(0);
}

tree::TerminalNode* scParser::WhileloopContext::RPAREN() {
  return getToken(scParser::RPAREN, 0);
}

scParser::StatementsContext* scParser::WhileloopContext::statements() {
  return getRuleContext<scParser::StatementsContext>(0);
}


size_t scParser::WhileloopContext::getRuleIndex() const {
  return scParser::RuleWhileloop;
}


antlrcpp::Any scParser::WhileloopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitWhileloop(this);
  else
    return visitor->visitChildren(this);
}

scParser::WhileloopContext* scParser::whileloop() {
  WhileloopContext *_localctx = _tracker.createInstance<WhileloopContext>(_ctx, getState());
  enterRule(_localctx, 12, scParser::RuleWhileloop);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    match(scParser::T__5);
    setState(87);
    match(scParser::LPAREN);
    setState(88);
    expression();
    setState(89);
    match(scParser::RPAREN);
    setState(90);
    match(scParser::T__1);
    setState(91);
    statements();
    setState(92);
    match(scParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgsContext ------------------------------------------------------------------

scParser::ArgsContext::ArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::ExpressionContext* scParser::ArgsContext::expression() {
  return getRuleContext<scParser::ExpressionContext>(0);
}

scParser::ArgsContext* scParser::ArgsContext::args() {
  return getRuleContext<scParser::ArgsContext>(0);
}


size_t scParser::ArgsContext::getRuleIndex() const {
  return scParser::RuleArgs;
}


antlrcpp::Any scParser::ArgsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitArgs(this);
  else
    return visitor->visitChildren(this);
}

scParser::ArgsContext* scParser::args() {
  ArgsContext *_localctx = _tracker.createInstance<ArgsContext>(_ctx, getState());
  enterRule(_localctx, 14, scParser::RuleArgs);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(99);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(94);
      expression();
      setState(95);
      match(scParser::T__6);
      setState(96);
      args();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(98);
      expression();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

scParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* scParser::ExpressionContext::LPAREN() {
  return getToken(scParser::LPAREN, 0);
}

scParser::ExpressionContext* scParser::ExpressionContext::expression() {
  return getRuleContext<scParser::ExpressionContext>(0);
}

tree::TerminalNode* scParser::ExpressionContext::RPAREN() {
  return getToken(scParser::RPAREN, 0);
}

scParser::ExpressionMContext* scParser::ExpressionContext::expressionM() {
  return getRuleContext<scParser::ExpressionMContext>(0);
}

tree::TerminalNode* scParser::ExpressionContext::INTEGER() {
  return getToken(scParser::INTEGER, 0);
}

tree::TerminalNode* scParser::ExpressionContext::ID() {
  return getToken(scParser::ID, 0);
}

scParser::FunctionCallContext* scParser::ExpressionContext::functionCall() {
  return getRuleContext<scParser::FunctionCallContext>(0);
}


size_t scParser::ExpressionContext::getRuleIndex() const {
  return scParser::RuleExpression;
}


antlrcpp::Any scParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

scParser::ExpressionContext* scParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 16, scParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(113);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(101);
      match(scParser::LPAREN);
      setState(102);
      expression();
      setState(103);
      match(scParser::RPAREN);
      setState(104);
      expressionM();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(106);
      match(scParser::INTEGER);
      setState(107);
      expressionM();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(108);
      match(scParser::ID);
      setState(109);
      expressionM();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(110);
      functionCall();
      setState(111);
      expressionM();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionMContext ------------------------------------------------------------------

scParser::ExpressionMContext::ExpressionMContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::ExpressionContext* scParser::ExpressionMContext::expression() {
  return getRuleContext<scParser::ExpressionContext>(0);
}

scParser::ExpressionMContext* scParser::ExpressionMContext::expressionM() {
  return getRuleContext<scParser::ExpressionMContext>(0);
}

tree::TerminalNode* scParser::ExpressionMContext::PLUS() {
  return getToken(scParser::PLUS, 0);
}

tree::TerminalNode* scParser::ExpressionMContext::MINUS() {
  return getToken(scParser::MINUS, 0);
}

tree::TerminalNode* scParser::ExpressionMContext::DIVISION() {
  return getToken(scParser::DIVISION, 0);
}

tree::TerminalNode* scParser::ExpressionMContext::MULTIPLICATION() {
  return getToken(scParser::MULTIPLICATION, 0);
}


size_t scParser::ExpressionMContext::getRuleIndex() const {
  return scParser::RuleExpressionM;
}


antlrcpp::Any scParser::ExpressionMContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitExpressionM(this);
  else
    return visitor->visitChildren(this);
}

scParser::ExpressionMContext* scParser::expressionM() {
  ExpressionMContext *_localctx = _tracker.createInstance<ExpressionMContext>(_ctx, getState());
  enterRule(_localctx, 18, scParser::RuleExpressionM);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(120);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(115);
      dynamic_cast<ExpressionMContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << scParser::PLUS)
        | (1ULL << scParser::MINUS)
        | (1ULL << scParser::DIVISION)
        | (1ULL << scParser::MULTIPLICATION))) != 0))) {
        dynamic_cast<ExpressionMContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(116);
      expression();
      setState(117);
      expressionM();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);

      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

scParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* scParser::FunctionCallContext::ID() {
  return getToken(scParser::ID, 0);
}

tree::TerminalNode* scParser::FunctionCallContext::LPAREN() {
  return getToken(scParser::LPAREN, 0);
}

tree::TerminalNode* scParser::FunctionCallContext::RPAREN() {
  return getToken(scParser::RPAREN, 0);
}

scParser::ArgsContext* scParser::FunctionCallContext::args() {
  return getRuleContext<scParser::ArgsContext>(0);
}


size_t scParser::FunctionCallContext::getRuleIndex() const {
  return scParser::RuleFunctionCall;
}


antlrcpp::Any scParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

scParser::FunctionCallContext* scParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 20, scParser::RuleFunctionCall);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(130);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(122);
      match(scParser::ID);
      setState(123);
      match(scParser::LPAREN);
      setState(124);
      match(scParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(125);
      match(scParser::ID);
      setState(126);
      match(scParser::LPAREN);
      setState(127);
      args();
      setState(128);
      match(scParser::RPAREN);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Opt_parametersContext ------------------------------------------------------------------

scParser::Opt_parametersContext::Opt_parametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::ParametersContext* scParser::Opt_parametersContext::parameters() {
  return getRuleContext<scParser::ParametersContext>(0);
}


size_t scParser::Opt_parametersContext::getRuleIndex() const {
  return scParser::RuleOpt_parameters;
}


antlrcpp::Any scParser::Opt_parametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitOpt_parameters(this);
  else
    return visitor->visitChildren(this);
}

scParser::Opt_parametersContext* scParser::opt_parameters() {
  Opt_parametersContext *_localctx = _tracker.createInstance<Opt_parametersContext>(_ctx, getState());
  enterRule(_localctx, 22, scParser::RuleOpt_parameters);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(134);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__7: {
        enterOuterAlt(_localctx, 1);
        setState(132);
        parameters();
        break;
      }

      case scParser::RPAREN: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParametersContext ------------------------------------------------------------------

scParser::ParametersContext::ParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::ParameterContext* scParser::ParametersContext::parameter() {
  return getRuleContext<scParser::ParameterContext>(0);
}

scParser::ParametersContext* scParser::ParametersContext::parameters() {
  return getRuleContext<scParser::ParametersContext>(0);
}


size_t scParser::ParametersContext::getRuleIndex() const {
  return scParser::RuleParameters;
}


antlrcpp::Any scParser::ParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitParameters(this);
  else
    return visitor->visitChildren(this);
}

scParser::ParametersContext* scParser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 24, scParser::RuleParameters);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(141);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(136);
      parameter();
      setState(137);
      match(scParser::T__6);
      setState(138);
      parameters();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(140);
      parameter();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterContext ------------------------------------------------------------------

scParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::TypeContext* scParser::ParameterContext::type() {
  return getRuleContext<scParser::TypeContext>(0);
}

tree::TerminalNode* scParser::ParameterContext::ID() {
  return getToken(scParser::ID, 0);
}


size_t scParser::ParameterContext::getRuleIndex() const {
  return scParser::RuleParameter;
}


antlrcpp::Any scParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

scParser::ParameterContext* scParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 26, scParser::RuleParameter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    type();
    setState(144);
    match(scParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

scParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t scParser::TypeContext::getRuleIndex() const {
  return scParser::RuleType;
}


antlrcpp::Any scParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

scParser::TypeContext* scParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 28, scParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    match(scParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> scParser::_decisionToDFA;
atn::PredictionContextCache scParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN scParser::_atn;
std::vector<uint16_t> scParser::_serializedATN;

std::vector<std::string> scParser::_ruleNames = {
  "prog", "functionDef", "statements", "statement", "statementassign", "statementinit", 
  "whileloop", "args", "expression", "expressionM", "functionCall", "opt_parameters", 
  "parameters", "parameter", "type"
};

std::vector<std::string> scParser::_literalNames = {
  "", "'void'", "'{'", "'}'", "';'", "'return'", "'while'", "','", "'int'", 
  "", "'+'", "'-'", "'/'", "'*'", "'='", "'('", "')'"
};

std::vector<std::string> scParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "INTEGER", "PLUS", "MINUS", "DIVISION", 
  "MULTIPLICATION", "ASSIGN", "LPAREN", "RPAREN", "ID", "WS"
};

dfa::Vocabulary scParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> scParser::_tokenNames;

scParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x14, 0x97, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x3, 0x2, 0x7, 0x2, 0x22, 0xa, 
    0x2, 0xc, 0x2, 0xe, 0x2, 0x25, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x5, 0x3, 0x3f, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x49, 0xa, 0x4, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x4e, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x66, 
    0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 
    0x74, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 
    0xb, 0x7b, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x85, 0xa, 0xc, 0x3, 0xd, 0x3, 
    0xd, 0x5, 0xd, 0x89, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x5, 0xe, 0x90, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x2, 0x2, 0x11, 0x2, 0x4, 0x6, 0x8, 0xa, 
    0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x2, 0x3, 
    0x3, 0x2, 0xc, 0xf, 0x2, 0x95, 0x2, 0x23, 0x3, 0x2, 0x2, 0x2, 0x4, 0x3e, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0x48, 0x3, 0x2, 0x2, 0x2, 0x8, 0x4d, 0x3, 0x2, 
    0x2, 0x2, 0xa, 0x4f, 0x3, 0x2, 0x2, 0x2, 0xc, 0x53, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0x58, 0x3, 0x2, 0x2, 0x2, 0x10, 0x65, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x73, 0x3, 0x2, 0x2, 0x2, 0x14, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x16, 0x84, 
    0x3, 0x2, 0x2, 0x2, 0x18, 0x88, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x8f, 0x3, 
    0x2, 0x2, 0x2, 0x1c, 0x91, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x94, 0x3, 0x2, 
    0x2, 0x2, 0x20, 0x22, 0x5, 0x4, 0x3, 0x2, 0x21, 0x20, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0x25, 0x3, 0x2, 0x2, 0x2, 0x23, 0x21, 0x3, 0x2, 0x2, 0x2, 
    0x23, 0x24, 0x3, 0x2, 0x2, 0x2, 0x24, 0x26, 0x3, 0x2, 0x2, 0x2, 0x25, 
    0x23, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x7, 0x2, 0x2, 0x3, 0x27, 0x3, 
    0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x7, 0x3, 0x2, 0x2, 0x29, 0x2a, 0x7, 
    0x13, 0x2, 0x2, 0x2a, 0x2b, 0x7, 0x11, 0x2, 0x2, 0x2b, 0x2c, 0x5, 0x18, 
    0xd, 0x2, 0x2c, 0x2d, 0x7, 0x12, 0x2, 0x2, 0x2d, 0x2e, 0x7, 0x4, 0x2, 
    0x2, 0x2e, 0x2f, 0x5, 0x6, 0x4, 0x2, 0x2f, 0x30, 0x7, 0x5, 0x2, 0x2, 
    0x30, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x32, 0x5, 0x1e, 0x10, 0x2, 0x32, 
    0x33, 0x7, 0x13, 0x2, 0x2, 0x33, 0x34, 0x7, 0x11, 0x2, 0x2, 0x34, 0x35, 
    0x5, 0x18, 0xd, 0x2, 0x35, 0x36, 0x7, 0x12, 0x2, 0x2, 0x36, 0x37, 0x7, 
    0x4, 0x2, 0x2, 0x37, 0x38, 0x5, 0x6, 0x4, 0x2, 0x38, 0x39, 0x7, 0x6, 
    0x2, 0x2, 0x39, 0x3a, 0x7, 0x7, 0x2, 0x2, 0x3a, 0x3b, 0x5, 0x12, 0xa, 
    0x2, 0x3b, 0x3c, 0x7, 0x6, 0x2, 0x2, 0x3c, 0x3d, 0x7, 0x5, 0x2, 0x2, 
    0x3d, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x28, 0x3, 0x2, 0x2, 0x2, 0x3e, 
    0x31, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x5, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 
    0x5, 0x8, 0x5, 0x2, 0x41, 0x42, 0x7, 0x6, 0x2, 0x2, 0x42, 0x43, 0x5, 
    0x6, 0x4, 0x2, 0x43, 0x49, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 0x5, 0xe, 
    0x8, 0x2, 0x45, 0x46, 0x5, 0x6, 0x4, 0x2, 0x46, 0x49, 0x3, 0x2, 0x2, 
    0x2, 0x47, 0x49, 0x3, 0x2, 0x2, 0x2, 0x48, 0x40, 0x3, 0x2, 0x2, 0x2, 
    0x48, 0x44, 0x3, 0x2, 0x2, 0x2, 0x48, 0x47, 0x3, 0x2, 0x2, 0x2, 0x49, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4e, 0x5, 0xc, 0x7, 0x2, 0x4b, 0x4e, 
    0x5, 0xa, 0x6, 0x2, 0x4c, 0x4e, 0x5, 0x16, 0xc, 0x2, 0x4d, 0x4a, 0x3, 
    0x2, 0x2, 0x2, 0x4d, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4c, 0x3, 0x2, 
    0x2, 0x2, 0x4e, 0x9, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x13, 0x2, 
    0x2, 0x50, 0x51, 0x7, 0x10, 0x2, 0x2, 0x51, 0x52, 0x5, 0x12, 0xa, 0x2, 
    0x52, 0xb, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x5, 0x1e, 0x10, 0x2, 0x54, 
    0x55, 0x7, 0x13, 0x2, 0x2, 0x55, 0x56, 0x7, 0x10, 0x2, 0x2, 0x56, 0x57, 
    0x5, 0x12, 0xa, 0x2, 0x57, 0xd, 0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 0x7, 
    0x8, 0x2, 0x2, 0x59, 0x5a, 0x7, 0x11, 0x2, 0x2, 0x5a, 0x5b, 0x5, 0x12, 
    0xa, 0x2, 0x5b, 0x5c, 0x7, 0x12, 0x2, 0x2, 0x5c, 0x5d, 0x7, 0x4, 0x2, 
    0x2, 0x5d, 0x5e, 0x5, 0x6, 0x4, 0x2, 0x5e, 0x5f, 0x7, 0x5, 0x2, 0x2, 
    0x5f, 0xf, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x5, 0x12, 0xa, 0x2, 0x61, 
    0x62, 0x7, 0x9, 0x2, 0x2, 0x62, 0x63, 0x5, 0x10, 0x9, 0x2, 0x63, 0x66, 
    0x3, 0x2, 0x2, 0x2, 0x64, 0x66, 0x5, 0x12, 0xa, 0x2, 0x65, 0x60, 0x3, 
    0x2, 0x2, 0x2, 0x65, 0x64, 0x3, 0x2, 0x2, 0x2, 0x66, 0x11, 0x3, 0x2, 
    0x2, 0x2, 0x67, 0x68, 0x7, 0x11, 0x2, 0x2, 0x68, 0x69, 0x5, 0x12, 0xa, 
    0x2, 0x69, 0x6a, 0x7, 0x12, 0x2, 0x2, 0x6a, 0x6b, 0x5, 0x14, 0xb, 0x2, 
    0x6b, 0x74, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x7, 0xb, 0x2, 0x2, 0x6d, 
    0x74, 0x5, 0x14, 0xb, 0x2, 0x6e, 0x6f, 0x7, 0x13, 0x2, 0x2, 0x6f, 0x74, 
    0x5, 0x14, 0xb, 0x2, 0x70, 0x71, 0x5, 0x16, 0xc, 0x2, 0x71, 0x72, 0x5, 
    0x14, 0xb, 0x2, 0x72, 0x74, 0x3, 0x2, 0x2, 0x2, 0x73, 0x67, 0x3, 0x2, 
    0x2, 0x2, 0x73, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x73, 0x6e, 0x3, 0x2, 0x2, 
    0x2, 0x73, 0x70, 0x3, 0x2, 0x2, 0x2, 0x74, 0x13, 0x3, 0x2, 0x2, 0x2, 
    0x75, 0x76, 0x9, 0x2, 0x2, 0x2, 0x76, 0x77, 0x5, 0x12, 0xa, 0x2, 0x77, 
    0x78, 0x5, 0x14, 0xb, 0x2, 0x78, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7b, 
    0x3, 0x2, 0x2, 0x2, 0x7a, 0x75, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x79, 0x3, 
    0x2, 0x2, 0x2, 0x7b, 0x15, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x7, 0x13, 
    0x2, 0x2, 0x7d, 0x7e, 0x7, 0x11, 0x2, 0x2, 0x7e, 0x85, 0x7, 0x12, 0x2, 
    0x2, 0x7f, 0x80, 0x7, 0x13, 0x2, 0x2, 0x80, 0x81, 0x7, 0x11, 0x2, 0x2, 
    0x81, 0x82, 0x5, 0x10, 0x9, 0x2, 0x82, 0x83, 0x7, 0x12, 0x2, 0x2, 0x83, 
    0x85, 0x3, 0x2, 0x2, 0x2, 0x84, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x84, 0x7f, 
    0x3, 0x2, 0x2, 0x2, 0x85, 0x17, 0x3, 0x2, 0x2, 0x2, 0x86, 0x89, 0x5, 
    0x1a, 0xe, 0x2, 0x87, 0x89, 0x3, 0x2, 0x2, 0x2, 0x88, 0x86, 0x3, 0x2, 
    0x2, 0x2, 0x88, 0x87, 0x3, 0x2, 0x2, 0x2, 0x89, 0x19, 0x3, 0x2, 0x2, 
    0x2, 0x8a, 0x8b, 0x5, 0x1c, 0xf, 0x2, 0x8b, 0x8c, 0x7, 0x9, 0x2, 0x2, 
    0x8c, 0x8d, 0x5, 0x1a, 0xe, 0x2, 0x8d, 0x90, 0x3, 0x2, 0x2, 0x2, 0x8e, 
    0x90, 0x5, 0x1c, 0xf, 0x2, 0x8f, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x8e, 
    0x3, 0x2, 0x2, 0x2, 0x90, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x5, 
    0x1e, 0x10, 0x2, 0x92, 0x93, 0x7, 0x13, 0x2, 0x2, 0x93, 0x1d, 0x3, 0x2, 
    0x2, 0x2, 0x94, 0x95, 0x7, 0xa, 0x2, 0x2, 0x95, 0x1f, 0x3, 0x2, 0x2, 
    0x2, 0xc, 0x23, 0x3e, 0x48, 0x4d, 0x65, 0x73, 0x7a, 0x84, 0x88, 0x8f, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

scParser::Initializer scParser::_init;
