
// Generated from /home/nhug/TaintAnalysisCpu/sc.g4 by ANTLR 4.8


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
    setState(37);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == scParser::T__0

    || _la == scParser::T__9) {
      setState(34);
      functionDef();
      setState(39);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(40);
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
    setState(63);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(42);
        match(scParser::T__0);
        setState(43);
        match(scParser::ID);
        setState(44);
        match(scParser::LPAREN);
        setState(45);
        opt_parameters();
        setState(46);
        match(scParser::RPAREN);
        setState(47);
        match(scParser::T__1);
        setState(48);
        statements();
        setState(49);
        match(scParser::T__2);
        break;
      }

      case scParser::T__9: {
        enterOuterAlt(_localctx, 2);
        setState(51);
        type();
        setState(52);
        match(scParser::ID);
        setState(53);
        match(scParser::LPAREN);
        setState(54);
        opt_parameters();
        setState(55);
        match(scParser::RPAREN);
        setState(56);
        match(scParser::T__1);
        setState(57);
        statements();
        setState(58);
        match(scParser::T__3);
        setState(59);
        expression();
        setState(60);
        match(scParser::T__4);
        setState(61);
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

scParser::StatementifContext* scParser::StatementsContext::statementif() {
  return getRuleContext<scParser::StatementifContext>(0);
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
    setState(76);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__9:
      case scParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(65);
        statement();
        setState(66);
        match(scParser::T__4);
        setState(67);
        statements();
        break;
      }

      case scParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(69);
        whileloop();
        setState(70);
        statements();
        break;
      }

      case scParser::T__6: {
        enterOuterAlt(_localctx, 3);
        setState(72);
        statementif();
        setState(73);
        statements();
        break;
      }

      case scParser::T__2:
      case scParser::T__3: {
        enterOuterAlt(_localctx, 4);

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

scParser::FunctionCallInitContext* scParser::StatementContext::functionCallInit() {
  return getRuleContext<scParser::FunctionCallInitContext>(0);
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
    setState(81);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(78);
      statementinit();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(79);
      statementassign();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(80);
      functionCallInit();
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
    setState(83);
    match(scParser::ID);
    setState(84);
    match(scParser::ASSIGN);
    setState(85);
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
    setState(87);
    type();
    setState(88);
    match(scParser::ID);
    setState(89);
    match(scParser::ASSIGN);
    setState(90);
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
    setState(92);
    match(scParser::T__5);
    setState(93);
    match(scParser::LPAREN);
    setState(94);
    expression();
    setState(95);
    match(scParser::RPAREN);
    setState(96);
    match(scParser::T__1);
    setState(97);
    statements();
    setState(98);
    match(scParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementifContext ------------------------------------------------------------------

scParser::StatementifContext::StatementifContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* scParser::StatementifContext::LPAREN() {
  return getToken(scParser::LPAREN, 0);
}

scParser::ExpressionContext* scParser::StatementifContext::expression() {
  return getRuleContext<scParser::ExpressionContext>(0);
}

tree::TerminalNode* scParser::StatementifContext::RPAREN() {
  return getToken(scParser::RPAREN, 0);
}

std::vector<scParser::StatementsContext *> scParser::StatementifContext::statements() {
  return getRuleContexts<scParser::StatementsContext>();
}

scParser::StatementsContext* scParser::StatementifContext::statements(size_t i) {
  return getRuleContext<scParser::StatementsContext>(i);
}


size_t scParser::StatementifContext::getRuleIndex() const {
  return scParser::RuleStatementif;
}


antlrcpp::Any scParser::StatementifContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitStatementif(this);
  else
    return visitor->visitChildren(this);
}

scParser::StatementifContext* scParser::statementif() {
  StatementifContext *_localctx = _tracker.createInstance<StatementifContext>(_ctx, getState());
  enterRule(_localctx, 14, scParser::RuleStatementif);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    match(scParser::T__6);
    setState(101);
    match(scParser::LPAREN);
    setState(102);
    expression();
    setState(103);
    match(scParser::RPAREN);
    setState(104);
    match(scParser::T__1);
    setState(105);
    statements();
    setState(106);
    match(scParser::T__2);
    setState(107);
    match(scParser::T__7);
    setState(108);
    match(scParser::T__1);
    setState(109);
    statements();
    setState(110);
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
  enterRule(_localctx, 16, scParser::RuleArgs);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(117);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(112);
      expression();
      setState(113);
      match(scParser::T__8);
      setState(114);
      args();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(116);
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
  enterRule(_localctx, 18, scParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(128);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(119);
        match(scParser::LPAREN);
        setState(120);
        expression();
        setState(121);
        match(scParser::RPAREN);
        setState(122);
        expressionM();
        break;
      }

      case scParser::INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(124);
        match(scParser::INTEGER);
        setState(125);
        expressionM();
        break;
      }

      case scParser::ID: {
        enterOuterAlt(_localctx, 3);
        setState(126);
        match(scParser::ID);
        setState(127);
        expressionM();
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
  enterRule(_localctx, 20, scParser::RuleExpressionM);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(135);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(130);
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
      setState(131);
      expression();
      setState(132);
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

//----------------- FunctionCallInitContext ------------------------------------------------------------------

scParser::FunctionCallInitContext::FunctionCallInitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::TypeContext* scParser::FunctionCallInitContext::type() {
  return getRuleContext<scParser::TypeContext>(0);
}

tree::TerminalNode* scParser::FunctionCallInitContext::ID() {
  return getToken(scParser::ID, 0);
}

tree::TerminalNode* scParser::FunctionCallInitContext::ASSIGN() {
  return getToken(scParser::ASSIGN, 0);
}

scParser::FunctionCallContext* scParser::FunctionCallInitContext::functionCall() {
  return getRuleContext<scParser::FunctionCallContext>(0);
}


size_t scParser::FunctionCallInitContext::getRuleIndex() const {
  return scParser::RuleFunctionCallInit;
}


antlrcpp::Any scParser::FunctionCallInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitFunctionCallInit(this);
  else
    return visitor->visitChildren(this);
}

scParser::FunctionCallInitContext* scParser::functionCallInit() {
  FunctionCallInitContext *_localctx = _tracker.createInstance<FunctionCallInitContext>(_ctx, getState());
  enterRule(_localctx, 22, scParser::RuleFunctionCallInit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    type();
    setState(138);
    match(scParser::ID);
    setState(139);
    match(scParser::ASSIGN);
    setState(140);
    functionCall();
   
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
  enterRule(_localctx, 24, scParser::RuleFunctionCall);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(150);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(142);
      match(scParser::ID);
      setState(143);
      match(scParser::LPAREN);
      setState(144);
      match(scParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(145);
      match(scParser::ID);
      setState(146);
      match(scParser::LPAREN);
      setState(147);
      args();
      setState(148);
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
  enterRule(_localctx, 26, scParser::RuleOpt_parameters);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(154);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__9: {
        enterOuterAlt(_localctx, 1);
        setState(152);
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
  enterRule(_localctx, 28, scParser::RuleParameters);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(161);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(156);
      parameter();
      setState(157);
      match(scParser::T__8);
      setState(158);
      parameters();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(160);
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
  enterRule(_localctx, 30, scParser::RuleParameter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(163);
    type();
    setState(164);
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
  enterRule(_localctx, 32, scParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(166);
    match(scParser::T__9);
   
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
  "whileloop", "statementif", "args", "expression", "expressionM", "functionCallInit", 
  "functionCall", "opt_parameters", "parameters", "parameter", "type"
};

std::vector<std::string> scParser::_literalNames = {
  "", "'void'", "'{'", "'}'", "'return'", "';'", "'while'", "'if'", "'else'", 
  "','", "'int'", "", "'+'", "'-'", "'/'", "'*'", "'='", "'('", "')'", "'<='", 
  "'>='", "'<'", "'>'"
};

std::vector<std::string> scParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "INTEGER", "PLUS", "MINUS", 
  "DIVISION", "MULTIPLICATION", "ASSIGN", "LPAREN", "RPAREN", "LEQ", "GEQ", 
  "LT", "GT", "ID", "WS"
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
    0x3, 0x1a, 0xab, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x3, 0x2, 0x7, 0x2, 0x26, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x29, 
    0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x42, 0xa, 0x3, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x4f, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x5, 0x5, 0x54, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x78, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x5, 0xb, 0x83, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x5, 0xc, 0x8a, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x99, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 0x5, 
    0xf, 0x9d, 0xa, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x5, 0x10, 0xa4, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x12, 0x2, 0x2, 0x13, 0x2, 0x4, 0x6, 0x8, 0xa, 
    0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 
    0x2, 0x3, 0x3, 0x2, 0xe, 0x11, 0x2, 0xa7, 0x2, 0x27, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0x41, 0x3, 0x2, 0x2, 0x2, 0x6, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0x53, 0x3, 0x2, 0x2, 0x2, 0xa, 0x55, 0x3, 0x2, 0x2, 0x2, 0xc, 0x59, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x10, 0x66, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x77, 0x3, 0x2, 0x2, 0x2, 0x14, 0x82, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0x89, 0x3, 0x2, 0x2, 0x2, 0x18, 0x8b, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0x98, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x9c, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x20, 0xa5, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0xa8, 0x3, 0x2, 0x2, 0x2, 0x24, 0x26, 0x5, 0x4, 0x3, 0x2, 0x25, 0x24, 
    0x3, 0x2, 0x2, 0x2, 0x26, 0x29, 0x3, 0x2, 0x2, 0x2, 0x27, 0x25, 0x3, 
    0x2, 0x2, 0x2, 0x27, 0x28, 0x3, 0x2, 0x2, 0x2, 0x28, 0x2a, 0x3, 0x2, 
    0x2, 0x2, 0x29, 0x27, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2b, 0x7, 0x2, 0x2, 
    0x3, 0x2b, 0x3, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x7, 0x3, 0x2, 0x2, 
    0x2d, 0x2e, 0x7, 0x19, 0x2, 0x2, 0x2e, 0x2f, 0x7, 0x13, 0x2, 0x2, 0x2f, 
    0x30, 0x5, 0x1c, 0xf, 0x2, 0x30, 0x31, 0x7, 0x14, 0x2, 0x2, 0x31, 0x32, 
    0x7, 0x4, 0x2, 0x2, 0x32, 0x33, 0x5, 0x6, 0x4, 0x2, 0x33, 0x34, 0x7, 
    0x5, 0x2, 0x2, 0x34, 0x42, 0x3, 0x2, 0x2, 0x2, 0x35, 0x36, 0x5, 0x22, 
    0x12, 0x2, 0x36, 0x37, 0x7, 0x19, 0x2, 0x2, 0x37, 0x38, 0x7, 0x13, 0x2, 
    0x2, 0x38, 0x39, 0x5, 0x1c, 0xf, 0x2, 0x39, 0x3a, 0x7, 0x14, 0x2, 0x2, 
    0x3a, 0x3b, 0x7, 0x4, 0x2, 0x2, 0x3b, 0x3c, 0x5, 0x6, 0x4, 0x2, 0x3c, 
    0x3d, 0x7, 0x6, 0x2, 0x2, 0x3d, 0x3e, 0x5, 0x14, 0xb, 0x2, 0x3e, 0x3f, 
    0x7, 0x7, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x5, 0x2, 0x2, 0x40, 0x42, 0x3, 
    0x2, 0x2, 0x2, 0x41, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x41, 0x35, 0x3, 0x2, 
    0x2, 0x2, 0x42, 0x5, 0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0x5, 0x8, 0x5, 
    0x2, 0x44, 0x45, 0x7, 0x7, 0x2, 0x2, 0x45, 0x46, 0x5, 0x6, 0x4, 0x2, 
    0x46, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x5, 0xe, 0x8, 0x2, 0x48, 
    0x49, 0x5, 0x6, 0x4, 0x2, 0x49, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 
    0x5, 0x10, 0x9, 0x2, 0x4b, 0x4c, 0x5, 0x6, 0x4, 0x2, 0x4c, 0x4f, 0x3, 
    0x2, 0x2, 0x2, 0x4d, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x43, 0x3, 0x2, 
    0x2, 0x2, 0x4e, 0x47, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4a, 0x3, 0x2, 0x2, 
    0x2, 0x4e, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x7, 0x3, 0x2, 0x2, 0x2, 
    0x50, 0x54, 0x5, 0xc, 0x7, 0x2, 0x51, 0x54, 0x5, 0xa, 0x6, 0x2, 0x52, 
    0x54, 0x5, 0x18, 0xd, 0x2, 0x53, 0x50, 0x3, 0x2, 0x2, 0x2, 0x53, 0x51, 
    0x3, 0x2, 0x2, 0x2, 0x53, 0x52, 0x3, 0x2, 0x2, 0x2, 0x54, 0x9, 0x3, 
    0x2, 0x2, 0x2, 0x55, 0x56, 0x7, 0x19, 0x2, 0x2, 0x56, 0x57, 0x7, 0x12, 
    0x2, 0x2, 0x57, 0x58, 0x5, 0x14, 0xb, 0x2, 0x58, 0xb, 0x3, 0x2, 0x2, 
    0x2, 0x59, 0x5a, 0x5, 0x22, 0x12, 0x2, 0x5a, 0x5b, 0x7, 0x19, 0x2, 0x2, 
    0x5b, 0x5c, 0x7, 0x12, 0x2, 0x2, 0x5c, 0x5d, 0x5, 0x14, 0xb, 0x2, 0x5d, 
    0xd, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x7, 0x8, 0x2, 0x2, 0x5f, 0x60, 
    0x7, 0x13, 0x2, 0x2, 0x60, 0x61, 0x5, 0x14, 0xb, 0x2, 0x61, 0x62, 0x7, 
    0x14, 0x2, 0x2, 0x62, 0x63, 0x7, 0x4, 0x2, 0x2, 0x63, 0x64, 0x5, 0x6, 
    0x4, 0x2, 0x64, 0x65, 0x7, 0x5, 0x2, 0x2, 0x65, 0xf, 0x3, 0x2, 0x2, 
    0x2, 0x66, 0x67, 0x7, 0x9, 0x2, 0x2, 0x67, 0x68, 0x7, 0x13, 0x2, 0x2, 
    0x68, 0x69, 0x5, 0x14, 0xb, 0x2, 0x69, 0x6a, 0x7, 0x14, 0x2, 0x2, 0x6a, 
    0x6b, 0x7, 0x4, 0x2, 0x2, 0x6b, 0x6c, 0x5, 0x6, 0x4, 0x2, 0x6c, 0x6d, 
    0x7, 0x5, 0x2, 0x2, 0x6d, 0x6e, 0x7, 0xa, 0x2, 0x2, 0x6e, 0x6f, 0x7, 
    0x4, 0x2, 0x2, 0x6f, 0x70, 0x5, 0x6, 0x4, 0x2, 0x70, 0x71, 0x7, 0x5, 
    0x2, 0x2, 0x71, 0x11, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x5, 0x14, 0xb, 
    0x2, 0x73, 0x74, 0x7, 0xb, 0x2, 0x2, 0x74, 0x75, 0x5, 0x12, 0xa, 0x2, 
    0x75, 0x78, 0x3, 0x2, 0x2, 0x2, 0x76, 0x78, 0x5, 0x14, 0xb, 0x2, 0x77, 
    0x72, 0x3, 0x2, 0x2, 0x2, 0x77, 0x76, 0x3, 0x2, 0x2, 0x2, 0x78, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 0x7, 0x13, 0x2, 0x2, 0x7a, 0x7b, 0x5, 
    0x14, 0xb, 0x2, 0x7b, 0x7c, 0x7, 0x14, 0x2, 0x2, 0x7c, 0x7d, 0x5, 0x16, 
    0xc, 0x2, 0x7d, 0x83, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7f, 0x7, 0xd, 0x2, 
    0x2, 0x7f, 0x83, 0x5, 0x16, 0xc, 0x2, 0x80, 0x81, 0x7, 0x19, 0x2, 0x2, 
    0x81, 0x83, 0x5, 0x16, 0xc, 0x2, 0x82, 0x79, 0x3, 0x2, 0x2, 0x2, 0x82, 
    0x7e, 0x3, 0x2, 0x2, 0x2, 0x82, 0x80, 0x3, 0x2, 0x2, 0x2, 0x83, 0x15, 
    0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x9, 0x2, 0x2, 0x2, 0x85, 0x86, 0x5, 
    0x14, 0xb, 0x2, 0x86, 0x87, 0x5, 0x16, 0xc, 0x2, 0x87, 0x8a, 0x3, 0x2, 
    0x2, 0x2, 0x88, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x89, 0x84, 0x3, 0x2, 0x2, 
    0x2, 0x89, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x17, 0x3, 0x2, 0x2, 0x2, 
    0x8b, 0x8c, 0x5, 0x22, 0x12, 0x2, 0x8c, 0x8d, 0x7, 0x19, 0x2, 0x2, 0x8d, 
    0x8e, 0x7, 0x12, 0x2, 0x2, 0x8e, 0x8f, 0x5, 0x1a, 0xe, 0x2, 0x8f, 0x19, 
    0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 0x7, 0x19, 0x2, 0x2, 0x91, 0x92, 0x7, 
    0x13, 0x2, 0x2, 0x92, 0x99, 0x7, 0x14, 0x2, 0x2, 0x93, 0x94, 0x7, 0x19, 
    0x2, 0x2, 0x94, 0x95, 0x7, 0x13, 0x2, 0x2, 0x95, 0x96, 0x5, 0x12, 0xa, 
    0x2, 0x96, 0x97, 0x7, 0x14, 0x2, 0x2, 0x97, 0x99, 0x3, 0x2, 0x2, 0x2, 
    0x98, 0x90, 0x3, 0x2, 0x2, 0x2, 0x98, 0x93, 0x3, 0x2, 0x2, 0x2, 0x99, 
    0x1b, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9d, 0x5, 0x1e, 0x10, 0x2, 0x9b, 0x9d, 
    0x3, 0x2, 0x2, 0x2, 0x9c, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9b, 0x3, 
    0x2, 0x2, 0x2, 0x9d, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0x5, 0x20, 
    0x11, 0x2, 0x9f, 0xa0, 0x7, 0xb, 0x2, 0x2, 0xa0, 0xa1, 0x5, 0x1e, 0x10, 
    0x2, 0xa1, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa4, 0x5, 0x20, 0x11, 0x2, 
    0xa3, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa4, 
    0x1f, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa6, 0x5, 0x22, 0x12, 0x2, 0xa6, 0xa7, 
    0x7, 0x19, 0x2, 0x2, 0xa7, 0x21, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x7, 
    0xc, 0x2, 0x2, 0xa9, 0x23, 0x3, 0x2, 0x2, 0x2, 0xc, 0x27, 0x41, 0x4e, 
    0x53, 0x77, 0x82, 0x89, 0x98, 0x9c, 0xa3, 
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
