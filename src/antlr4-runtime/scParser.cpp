
// Generated from sc.g4 by ANTLR 4.9.3


#include "scListener.h"
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

void scParser::ProgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg(this);
}

void scParser::ProgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg(this);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(43);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == scParser::T__0

    || _la == scParser::T__11) {
      setState(40);
      functionDef();
      setState(45);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(46);
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

void scParser::FunctionDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDef(this);
}

void scParser::FunctionDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDef(this);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(69);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(48);
        match(scParser::T__0);
        setState(49);
        match(scParser::ID);
        setState(50);
        match(scParser::LPAREN);
        setState(51);
        opt_parameters();
        setState(52);
        match(scParser::RPAREN);
        setState(53);
        match(scParser::T__1);
        setState(54);
        statements();
        setState(55);
        match(scParser::T__2);
        break;
      }

      case scParser::T__11: {
        enterOuterAlt(_localctx, 2);
        setState(57);
        type();
        setState(58);
        match(scParser::ID);
        setState(59);
        match(scParser::LPAREN);
        setState(60);
        opt_parameters();
        setState(61);
        match(scParser::RPAREN);
        setState(62);
        match(scParser::T__1);
        setState(63);
        statements();
        setState(64);
        match(scParser::T__3);
        setState(65);
        expression();
        setState(66);
        match(scParser::T__4);
        setState(67);
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

void scParser::StatementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatements(this);
}

void scParser::StatementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatements(this);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(82);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__5:
      case scParser::T__11:
      case scParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(71);
        statement();
        setState(72);
        match(scParser::T__4);
        setState(73);
        statements();
        break;
      }

      case scParser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(75);
        whileloop();
        setState(76);
        statements();
        break;
      }

      case scParser::T__9: {
        enterOuterAlt(_localctx, 3);
        setState(78);
        statementif();
        setState(79);
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

scParser::StatementinitarrayContext* scParser::StatementContext::statementinitarray() {
  return getRuleContext<scParser::StatementinitarrayContext>(0);
}

scParser::StatementcalldupingContext* scParser::StatementContext::statementcallduping() {
  return getRuleContext<scParser::StatementcalldupingContext>(0);
}


size_t scParser::StatementContext::getRuleIndex() const {
  return scParser::RuleStatement;
}

void scParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void scParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(89);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(84);
      statementinit();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(85);
      statementassign();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(86);
      functionCallInit();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(87);
      statementinitarray();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(88);
      statementcallduping();
      break;
    }

    default:
      break;
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

std::vector<scParser::ExpressionContext *> scParser::StatementassignContext::expression() {
  return getRuleContexts<scParser::ExpressionContext>();
}

scParser::ExpressionContext* scParser::StatementassignContext::expression(size_t i) {
  return getRuleContext<scParser::ExpressionContext>(i);
}


size_t scParser::StatementassignContext::getRuleIndex() const {
  return scParser::RuleStatementassign;
}

void scParser::StatementassignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementassign(this);
}

void scParser::StatementassignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementassign(this);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(101);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(91);
      match(scParser::ID);
      setState(92);
      match(scParser::ASSIGN);
      setState(93);
      expression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(94);
      match(scParser::ID);
      setState(95);
      match(scParser::T__5);
      setState(96);
      expression();
      setState(97);
      match(scParser::T__6);
      setState(98);
      match(scParser::ASSIGN);
      setState(99);
      expression();
      break;
    }

    default:
      break;
    }
   
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

void scParser::StatementinitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementinit(this);
}

void scParser::StatementinitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementinit(this);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(103);
    type();
    setState(104);
    match(scParser::ID);
    setState(105);
    match(scParser::ASSIGN);
    setState(106);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementinitarrayContext ------------------------------------------------------------------

scParser::StatementinitarrayContext::StatementinitarrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::TypeContext* scParser::StatementinitarrayContext::type() {
  return getRuleContext<scParser::TypeContext>(0);
}

tree::TerminalNode* scParser::StatementinitarrayContext::ID() {
  return getToken(scParser::ID, 0);
}

tree::TerminalNode* scParser::StatementinitarrayContext::INTEGER() {
  return getToken(scParser::INTEGER, 0);
}

tree::TerminalNode* scParser::StatementinitarrayContext::ASSIGN() {
  return getToken(scParser::ASSIGN, 0);
}

scParser::ExpressionContext* scParser::StatementinitarrayContext::expression() {
  return getRuleContext<scParser::ExpressionContext>(0);
}

scParser::ArrayelementContext* scParser::StatementinitarrayContext::arrayelement() {
  return getRuleContext<scParser::ArrayelementContext>(0);
}


size_t scParser::StatementinitarrayContext::getRuleIndex() const {
  return scParser::RuleStatementinitarray;
}

void scParser::StatementinitarrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementinitarray(this);
}

void scParser::StatementinitarrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementinitarray(this);
}


antlrcpp::Any scParser::StatementinitarrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitStatementinitarray(this);
  else
    return visitor->visitChildren(this);
}

scParser::StatementinitarrayContext* scParser::statementinitarray() {
  StatementinitarrayContext *_localctx = _tracker.createInstance<StatementinitarrayContext>(_ctx, getState());
  enterRule(_localctx, 12, scParser::RuleStatementinitarray);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(108);
    type();
    setState(109);
    match(scParser::ID);
    setState(110);
    match(scParser::T__5);
    setState(111);
    match(scParser::INTEGER);
    setState(112);
    match(scParser::T__6);
    setState(113);
    match(scParser::ASSIGN);
    setState(114);
    match(scParser::T__1);
    setState(115);
    expression();
    setState(116);
    arrayelement();
    setState(117);
    match(scParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementcalldupingContext ------------------------------------------------------------------

scParser::StatementcalldupingContext::StatementcalldupingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* scParser::StatementcalldupingContext::INTEGER() {
  return getToken(scParser::INTEGER, 0);
}

scParser::FunctionCallInitContext* scParser::StatementcalldupingContext::functionCallInit() {
  return getRuleContext<scParser::FunctionCallInitContext>(0);
}

tree::TerminalNode* scParser::StatementcalldupingContext::ID() {
  return getToken(scParser::ID, 0);
}


size_t scParser::StatementcalldupingContext::getRuleIndex() const {
  return scParser::RuleStatementcallduping;
}

void scParser::StatementcalldupingContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementcallduping(this);
}

void scParser::StatementcalldupingContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementcallduping(this);
}


antlrcpp::Any scParser::StatementcalldupingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitStatementcallduping(this);
  else
    return visitor->visitChildren(this);
}

scParser::StatementcalldupingContext* scParser::statementcallduping() {
  StatementcalldupingContext *_localctx = _tracker.createInstance<StatementcalldupingContext>(_ctx, getState());
  enterRule(_localctx, 14, scParser::RuleStatementcallduping);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(133);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(119);
      match(scParser::T__5);
      setState(120);
      match(scParser::INTEGER);
      setState(121);
      match(scParser::T__6);
      setState(122);
      match(scParser::T__1);
      setState(123);
      functionCallInit();
      setState(124);
      match(scParser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(126);
      match(scParser::T__5);
      setState(127);
      match(scParser::ID);
      setState(128);
      match(scParser::T__6);
      setState(129);
      match(scParser::T__1);
      setState(130);
      functionCallInit();
      setState(131);
      match(scParser::T__2);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayelementContext ------------------------------------------------------------------

scParser::ArrayelementContext::ArrayelementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::ExpressionContext* scParser::ArrayelementContext::expression() {
  return getRuleContext<scParser::ExpressionContext>(0);
}

scParser::ArrayelementContext* scParser::ArrayelementContext::arrayelement() {
  return getRuleContext<scParser::ArrayelementContext>(0);
}


size_t scParser::ArrayelementContext::getRuleIndex() const {
  return scParser::RuleArrayelement;
}

void scParser::ArrayelementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayelement(this);
}

void scParser::ArrayelementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayelement(this);
}


antlrcpp::Any scParser::ArrayelementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitArrayelement(this);
  else
    return visitor->visitChildren(this);
}

scParser::ArrayelementContext* scParser::arrayelement() {
  ArrayelementContext *_localctx = _tracker.createInstance<ArrayelementContext>(_ctx, getState());
  enterRule(_localctx, 16, scParser::RuleArrayelement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(140);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__7: {
        enterOuterAlt(_localctx, 1);
        setState(135);
        match(scParser::T__7);
        setState(136);
        expression();
        setState(137);
        arrayelement();
        break;
      }

      case scParser::T__2: {
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

void scParser::WhileloopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileloop(this);
}

void scParser::WhileloopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileloop(this);
}


antlrcpp::Any scParser::WhileloopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitWhileloop(this);
  else
    return visitor->visitChildren(this);
}

scParser::WhileloopContext* scParser::whileloop() {
  WhileloopContext *_localctx = _tracker.createInstance<WhileloopContext>(_ctx, getState());
  enterRule(_localctx, 18, scParser::RuleWhileloop);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(142);
    match(scParser::T__8);
    setState(143);
    match(scParser::LPAREN);
    setState(144);
    expression();
    setState(145);
    match(scParser::RPAREN);
    setState(146);
    match(scParser::T__1);
    setState(147);
    statements();
    setState(148);
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

void scParser::StatementifContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementif(this);
}

void scParser::StatementifContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementif(this);
}


antlrcpp::Any scParser::StatementifContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitStatementif(this);
  else
    return visitor->visitChildren(this);
}

scParser::StatementifContext* scParser::statementif() {
  StatementifContext *_localctx = _tracker.createInstance<StatementifContext>(_ctx, getState());
  enterRule(_localctx, 20, scParser::RuleStatementif);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(150);
    match(scParser::T__9);
    setState(151);
    match(scParser::LPAREN);
    setState(152);
    expression();
    setState(153);
    match(scParser::RPAREN);
    setState(154);
    match(scParser::T__1);
    setState(155);
    statements();
    setState(156);
    match(scParser::T__2);
    setState(157);
    match(scParser::T__10);
    setState(158);
    match(scParser::T__1);
    setState(159);
    statements();
    setState(160);
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

void scParser::ArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgs(this);
}

void scParser::ArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgs(this);
}


antlrcpp::Any scParser::ArgsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitArgs(this);
  else
    return visitor->visitChildren(this);
}

scParser::ArgsContext* scParser::args() {
  ArgsContext *_localctx = _tracker.createInstance<ArgsContext>(_ctx, getState());
  enterRule(_localctx, 22, scParser::RuleArgs);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(167);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(162);
      expression();
      setState(163);
      match(scParser::T__7);
      setState(164);
      args();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(166);
      expression();
      break;
    }

    default:
      break;
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

void scParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void scParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


antlrcpp::Any scParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

scParser::ExpressionContext* scParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 24, scParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(184);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(169);
      match(scParser::LPAREN);
      setState(170);
      expression();
      setState(171);
      match(scParser::RPAREN);
      setState(172);
      expressionM();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(174);
      match(scParser::INTEGER);
      setState(175);
      expressionM();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(176);
      match(scParser::ID);
      setState(177);
      expressionM();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(178);
      match(scParser::ID);
      setState(179);
      match(scParser::T__5);
      setState(180);
      expression();
      setState(181);
      match(scParser::T__6);
      setState(182);
      expressionM();
      break;
    }

    default:
      break;
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

void scParser::ExpressionMContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionM(this);
}

void scParser::ExpressionMContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionM(this);
}


antlrcpp::Any scParser::ExpressionMContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitExpressionM(this);
  else
    return visitor->visitChildren(this);
}

scParser::ExpressionMContext* scParser::expressionM() {
  ExpressionMContext *_localctx = _tracker.createInstance<ExpressionMContext>(_ctx, getState());
  enterRule(_localctx, 26, scParser::RuleExpressionM);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(191);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(186);
      antlrcpp::downCast<ExpressionMContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << scParser::PLUS)
        | (1ULL << scParser::MINUS)
        | (1ULL << scParser::DIVISION)
        | (1ULL << scParser::MULTIPLICATION))) != 0))) {
        antlrcpp::downCast<ExpressionMContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(187);
      expression();
      setState(188);
      expressionM();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);

      break;
    }

    default:
      break;
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

void scParser::FunctionCallInitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallInit(this);
}

void scParser::FunctionCallInitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallInit(this);
}


antlrcpp::Any scParser::FunctionCallInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitFunctionCallInit(this);
  else
    return visitor->visitChildren(this);
}

scParser::FunctionCallInitContext* scParser::functionCallInit() {
  FunctionCallInitContext *_localctx = _tracker.createInstance<FunctionCallInitContext>(_ctx, getState());
  enterRule(_localctx, 28, scParser::RuleFunctionCallInit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(193);
    type();
    setState(194);
    match(scParser::ID);
    setState(195);
    match(scParser::ASSIGN);
    setState(196);
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

void scParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void scParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}


antlrcpp::Any scParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

scParser::FunctionCallContext* scParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 30, scParser::RuleFunctionCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(206);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(198);
      match(scParser::ID);
      setState(199);
      match(scParser::LPAREN);
      setState(200);
      match(scParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(201);
      match(scParser::ID);
      setState(202);
      match(scParser::LPAREN);
      setState(203);
      args();
      setState(204);
      match(scParser::RPAREN);
      break;
    }

    default:
      break;
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

void scParser::Opt_parametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOpt_parameters(this);
}

void scParser::Opt_parametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOpt_parameters(this);
}


antlrcpp::Any scParser::Opt_parametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitOpt_parameters(this);
  else
    return visitor->visitChildren(this);
}

scParser::Opt_parametersContext* scParser::opt_parameters() {
  Opt_parametersContext *_localctx = _tracker.createInstance<Opt_parametersContext>(_ctx, getState());
  enterRule(_localctx, 32, scParser::RuleOpt_parameters);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(210);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__11: {
        enterOuterAlt(_localctx, 1);
        setState(208);
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

void scParser::ParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameters(this);
}

void scParser::ParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameters(this);
}


antlrcpp::Any scParser::ParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitParameters(this);
  else
    return visitor->visitChildren(this);
}

scParser::ParametersContext* scParser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 34, scParser::RuleParameters);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(217);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(212);
      parameter();
      setState(213);
      match(scParser::T__7);
      setState(214);
      parameters();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(216);
      parameter();
      break;
    }

    default:
      break;
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

void scParser::ParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter(this);
}

void scParser::ParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter(this);
}


antlrcpp::Any scParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

scParser::ParameterContext* scParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 36, scParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    type();
    setState(220);
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

void scParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void scParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<scListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}


antlrcpp::Any scParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

scParser::TypeContext* scParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 38, scParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(222);
    match(scParser::T__11);
   
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
  "statementinitarray", "statementcallduping", "arrayelement", "whileloop", 
  "statementif", "args", "expression", "expressionM", "functionCallInit", 
  "functionCall", "opt_parameters", "parameters", "parameter", "type"
};

std::vector<std::string> scParser::_literalNames = {
  "", "'void'", "'{'", "'}'", "'return'", "';'", "'['", "']'", "','", "'while'", 
  "'if'", "'else'", "'int'", "", "'+'", "'-'", "'/'", "'*'", "'='", "'('", 
  "')'", "'<='", "'>='", "'<'", "'>'"
};

std::vector<std::string> scParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "INTEGER", "PLUS", 
  "MINUS", "DIVISION", "MULTIPLICATION", "ASSIGN", "LPAREN", "RPAREN", "LEQ", 
  "GEQ", "LT", "GT", "ID", "WS"
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

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x1c, 0xe3, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 
       0x9, 0x11, 0x4, 0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 
       0x9, 0x14, 0x4, 0x15, 0x9, 0x15, 0x3, 0x2, 0x7, 0x2, 0x2c, 0xa, 0x2, 
       0xc, 0x2, 0xe, 0x2, 0x2f, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x5, 0x3, 0x48, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x5, 0x4, 0x55, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x5c, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 
       0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
       0x6, 0x3, 0x6, 0x5, 0x6, 0x68, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 
       0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
       0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
       0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
       0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
       0x9, 0x3, 0x9, 0x5, 0x9, 0x88, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 
       0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x8f, 0xa, 0xa, 0x3, 0xb, 0x3, 
       0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
       0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
       0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 
       0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xaa, 0xa, 0xd, 
       0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
       0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
       0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0xbb, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 
       0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0xc2, 0xa, 0xf, 0x3, 0x10, 
       0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 
       0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
       0x5, 0x11, 0xd1, 0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0xd5, 
       0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
       0x5, 0x13, 0xdc, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 
       0x15, 0x3, 0x15, 0x3, 0x15, 0x2, 0x2, 0x16, 0x2, 0x4, 0x6, 0x8, 0xa, 
       0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 
       0x24, 0x26, 0x28, 0x2, 0x3, 0x3, 0x2, 0x10, 0x13, 0x2, 0xe2, 0x2, 
       0x2d, 0x3, 0x2, 0x2, 0x2, 0x4, 0x47, 0x3, 0x2, 0x2, 0x2, 0x6, 0x54, 
       0x3, 0x2, 0x2, 0x2, 0x8, 0x5b, 0x3, 0x2, 0x2, 0x2, 0xa, 0x67, 0x3, 
       0x2, 0x2, 0x2, 0xc, 0x69, 0x3, 0x2, 0x2, 0x2, 0xe, 0x6e, 0x3, 0x2, 
       0x2, 0x2, 0x10, 0x87, 0x3, 0x2, 0x2, 0x2, 0x12, 0x8e, 0x3, 0x2, 0x2, 
       0x2, 0x14, 0x90, 0x3, 0x2, 0x2, 0x2, 0x16, 0x98, 0x3, 0x2, 0x2, 0x2, 
       0x18, 0xa9, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xba, 0x3, 0x2, 0x2, 0x2, 0x1c, 
       0xc1, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xc3, 0x3, 0x2, 0x2, 0x2, 0x20, 0xd0, 
       0x3, 0x2, 0x2, 0x2, 0x22, 0xd4, 0x3, 0x2, 0x2, 0x2, 0x24, 0xdb, 0x3, 
       0x2, 0x2, 0x2, 0x26, 0xdd, 0x3, 0x2, 0x2, 0x2, 0x28, 0xe0, 0x3, 0x2, 
       0x2, 0x2, 0x2a, 0x2c, 0x5, 0x4, 0x3, 0x2, 0x2b, 0x2a, 0x3, 0x2, 0x2, 
       0x2, 0x2c, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2b, 0x3, 0x2, 0x2, 0x2, 
       0x2d, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x30, 0x3, 0x2, 0x2, 0x2, 0x2f, 
       0x2d, 0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x7, 0x2, 0x2, 0x3, 0x31, 0x3, 
       0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x7, 0x3, 0x2, 0x2, 0x33, 0x34, 0x7, 
       0x1b, 0x2, 0x2, 0x34, 0x35, 0x7, 0x15, 0x2, 0x2, 0x35, 0x36, 0x5, 
       0x22, 0x12, 0x2, 0x36, 0x37, 0x7, 0x16, 0x2, 0x2, 0x37, 0x38, 0x7, 
       0x4, 0x2, 0x2, 0x38, 0x39, 0x5, 0x6, 0x4, 0x2, 0x39, 0x3a, 0x7, 0x5, 
       0x2, 0x2, 0x3a, 0x48, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3c, 0x5, 0x28, 
       0x15, 0x2, 0x3c, 0x3d, 0x7, 0x1b, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0x15, 
       0x2, 0x2, 0x3e, 0x3f, 0x5, 0x22, 0x12, 0x2, 0x3f, 0x40, 0x7, 0x16, 
       0x2, 0x2, 0x40, 0x41, 0x7, 0x4, 0x2, 0x2, 0x41, 0x42, 0x5, 0x6, 0x4, 
       0x2, 0x42, 0x43, 0x7, 0x6, 0x2, 0x2, 0x43, 0x44, 0x5, 0x1a, 0xe, 
       0x2, 0x44, 0x45, 0x7, 0x7, 0x2, 0x2, 0x45, 0x46, 0x7, 0x5, 0x2, 0x2, 
       0x46, 0x48, 0x3, 0x2, 0x2, 0x2, 0x47, 0x32, 0x3, 0x2, 0x2, 0x2, 0x47, 
       0x3b, 0x3, 0x2, 0x2, 0x2, 0x48, 0x5, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 
       0x5, 0x8, 0x5, 0x2, 0x4a, 0x4b, 0x7, 0x7, 0x2, 0x2, 0x4b, 0x4c, 0x5, 
       0x6, 0x4, 0x2, 0x4c, 0x55, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x5, 0x14, 
       0xb, 0x2, 0x4e, 0x4f, 0x5, 0x6, 0x4, 0x2, 0x4f, 0x55, 0x3, 0x2, 0x2, 
       0x2, 0x50, 0x51, 0x5, 0x16, 0xc, 0x2, 0x51, 0x52, 0x5, 0x6, 0x4, 
       0x2, 0x52, 0x55, 0x3, 0x2, 0x2, 0x2, 0x53, 0x55, 0x3, 0x2, 0x2, 0x2, 
       0x54, 0x49, 0x3, 0x2, 0x2, 0x2, 0x54, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x54, 
       0x50, 0x3, 0x2, 0x2, 0x2, 0x54, 0x53, 0x3, 0x2, 0x2, 0x2, 0x55, 0x7, 
       0x3, 0x2, 0x2, 0x2, 0x56, 0x5c, 0x5, 0xc, 0x7, 0x2, 0x57, 0x5c, 0x5, 
       0xa, 0x6, 0x2, 0x58, 0x5c, 0x5, 0x1e, 0x10, 0x2, 0x59, 0x5c, 0x5, 
       0xe, 0x8, 0x2, 0x5a, 0x5c, 0x5, 0x10, 0x9, 0x2, 0x5b, 0x56, 0x3, 
       0x2, 0x2, 0x2, 0x5b, 0x57, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x58, 0x3, 0x2, 
       0x2, 0x2, 0x5b, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5a, 0x3, 0x2, 0x2, 
       0x2, 0x5c, 0x9, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x7, 0x1b, 0x2, 0x2, 
       0x5e, 0x5f, 0x7, 0x14, 0x2, 0x2, 0x5f, 0x68, 0x5, 0x1a, 0xe, 0x2, 
       0x60, 0x61, 0x7, 0x1b, 0x2, 0x2, 0x61, 0x62, 0x7, 0x8, 0x2, 0x2, 
       0x62, 0x63, 0x5, 0x1a, 0xe, 0x2, 0x63, 0x64, 0x7, 0x9, 0x2, 0x2, 
       0x64, 0x65, 0x7, 0x14, 0x2, 0x2, 0x65, 0x66, 0x5, 0x1a, 0xe, 0x2, 
       0x66, 0x68, 0x3, 0x2, 0x2, 0x2, 0x67, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x67, 
       0x60, 0x3, 0x2, 0x2, 0x2, 0x68, 0xb, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 
       0x5, 0x28, 0x15, 0x2, 0x6a, 0x6b, 0x7, 0x1b, 0x2, 0x2, 0x6b, 0x6c, 
       0x7, 0x14, 0x2, 0x2, 0x6c, 0x6d, 0x5, 0x1a, 0xe, 0x2, 0x6d, 0xd, 
       0x3, 0x2, 0x2, 0x2, 0x6e, 0x6f, 0x5, 0x28, 0x15, 0x2, 0x6f, 0x70, 
       0x7, 0x1b, 0x2, 0x2, 0x70, 0x71, 0x7, 0x8, 0x2, 0x2, 0x71, 0x72, 
       0x7, 0xf, 0x2, 0x2, 0x72, 0x73, 0x7, 0x9, 0x2, 0x2, 0x73, 0x74, 0x7, 
       0x14, 0x2, 0x2, 0x74, 0x75, 0x7, 0x4, 0x2, 0x2, 0x75, 0x76, 0x5, 
       0x1a, 0xe, 0x2, 0x76, 0x77, 0x5, 0x12, 0xa, 0x2, 0x77, 0x78, 0x7, 
       0x5, 0x2, 0x2, 0x78, 0xf, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 0x7, 0x8, 
       0x2, 0x2, 0x7a, 0x7b, 0x7, 0xf, 0x2, 0x2, 0x7b, 0x7c, 0x7, 0x9, 0x2, 
       0x2, 0x7c, 0x7d, 0x7, 0x4, 0x2, 0x2, 0x7d, 0x7e, 0x5, 0x1e, 0x10, 
       0x2, 0x7e, 0x7f, 0x7, 0x5, 0x2, 0x2, 0x7f, 0x88, 0x3, 0x2, 0x2, 0x2, 
       0x80, 0x81, 0x7, 0x8, 0x2, 0x2, 0x81, 0x82, 0x7, 0x1b, 0x2, 0x2, 
       0x82, 0x83, 0x7, 0x9, 0x2, 0x2, 0x83, 0x84, 0x7, 0x4, 0x2, 0x2, 0x84, 
       0x85, 0x5, 0x1e, 0x10, 0x2, 0x85, 0x86, 0x7, 0x5, 0x2, 0x2, 0x86, 
       0x88, 0x3, 0x2, 0x2, 0x2, 0x87, 0x79, 0x3, 0x2, 0x2, 0x2, 0x87, 0x80, 
       0x3, 0x2, 0x2, 0x2, 0x88, 0x11, 0x3, 0x2, 0x2, 0x2, 0x89, 0x8a, 0x7, 
       0xa, 0x2, 0x2, 0x8a, 0x8b, 0x5, 0x1a, 0xe, 0x2, 0x8b, 0x8c, 0x5, 
       0x12, 0xa, 0x2, 0x8c, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8f, 0x3, 
       0x2, 0x2, 0x2, 0x8e, 0x89, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8d, 0x3, 0x2, 
       0x2, 0x2, 0x8f, 0x13, 0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 0x7, 0xb, 0x2, 
       0x2, 0x91, 0x92, 0x7, 0x15, 0x2, 0x2, 0x92, 0x93, 0x5, 0x1a, 0xe, 
       0x2, 0x93, 0x94, 0x7, 0x16, 0x2, 0x2, 0x94, 0x95, 0x7, 0x4, 0x2, 
       0x2, 0x95, 0x96, 0x5, 0x6, 0x4, 0x2, 0x96, 0x97, 0x7, 0x5, 0x2, 0x2, 
       0x97, 0x15, 0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x7, 0xc, 0x2, 0x2, 0x99, 
       0x9a, 0x7, 0x15, 0x2, 0x2, 0x9a, 0x9b, 0x5, 0x1a, 0xe, 0x2, 0x9b, 
       0x9c, 0x7, 0x16, 0x2, 0x2, 0x9c, 0x9d, 0x7, 0x4, 0x2, 0x2, 0x9d, 
       0x9e, 0x5, 0x6, 0x4, 0x2, 0x9e, 0x9f, 0x7, 0x5, 0x2, 0x2, 0x9f, 0xa0, 
       0x7, 0xd, 0x2, 0x2, 0xa0, 0xa1, 0x7, 0x4, 0x2, 0x2, 0xa1, 0xa2, 0x5, 
       0x6, 0x4, 0x2, 0xa2, 0xa3, 0x7, 0x5, 0x2, 0x2, 0xa3, 0x17, 0x3, 0x2, 
       0x2, 0x2, 0xa4, 0xa5, 0x5, 0x1a, 0xe, 0x2, 0xa5, 0xa6, 0x7, 0xa, 
       0x2, 0x2, 0xa6, 0xa7, 0x5, 0x18, 0xd, 0x2, 0xa7, 0xaa, 0x3, 0x2, 
       0x2, 0x2, 0xa8, 0xaa, 0x5, 0x1a, 0xe, 0x2, 0xa9, 0xa4, 0x3, 0x2, 
       0x2, 0x2, 0xa9, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xaa, 0x19, 0x3, 0x2, 0x2, 
       0x2, 0xab, 0xac, 0x7, 0x15, 0x2, 0x2, 0xac, 0xad, 0x5, 0x1a, 0xe, 
       0x2, 0xad, 0xae, 0x7, 0x16, 0x2, 0x2, 0xae, 0xaf, 0x5, 0x1c, 0xf, 
       0x2, 0xaf, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb1, 0x7, 0xf, 0x2, 0x2, 
       0xb1, 0xbb, 0x5, 0x1c, 0xf, 0x2, 0xb2, 0xb3, 0x7, 0x1b, 0x2, 0x2, 
       0xb3, 0xbb, 0x5, 0x1c, 0xf, 0x2, 0xb4, 0xb5, 0x7, 0x1b, 0x2, 0x2, 
       0xb5, 0xb6, 0x7, 0x8, 0x2, 0x2, 0xb6, 0xb7, 0x5, 0x1a, 0xe, 0x2, 
       0xb7, 0xb8, 0x7, 0x9, 0x2, 0x2, 0xb8, 0xb9, 0x5, 0x1c, 0xf, 0x2, 
       0xb9, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xba, 0xab, 0x3, 0x2, 0x2, 0x2, 0xba, 
       0xb0, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb4, 
       0x3, 0x2, 0x2, 0x2, 0xbb, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x9, 
       0x2, 0x2, 0x2, 0xbd, 0xbe, 0x5, 0x1a, 0xe, 0x2, 0xbe, 0xbf, 0x5, 
       0x1c, 0xf, 0x2, 0xbf, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xc2, 0x3, 
       0x2, 0x2, 0x2, 0xc1, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xc0, 0x3, 0x2, 
       0x2, 0x2, 0xc2, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc4, 0x5, 0x28, 
       0x15, 0x2, 0xc4, 0xc5, 0x7, 0x1b, 0x2, 0x2, 0xc5, 0xc6, 0x7, 0x14, 
       0x2, 0x2, 0xc6, 0xc7, 0x5, 0x20, 0x11, 0x2, 0xc7, 0x1f, 0x3, 0x2, 
       0x2, 0x2, 0xc8, 0xc9, 0x7, 0x1b, 0x2, 0x2, 0xc9, 0xca, 0x7, 0x15, 
       0x2, 0x2, 0xca, 0xd1, 0x7, 0x16, 0x2, 0x2, 0xcb, 0xcc, 0x7, 0x1b, 
       0x2, 0x2, 0xcc, 0xcd, 0x7, 0x15, 0x2, 0x2, 0xcd, 0xce, 0x5, 0x18, 
       0xd, 0x2, 0xce, 0xcf, 0x7, 0x16, 0x2, 0x2, 0xcf, 0xd1, 0x3, 0x2, 
       0x2, 0x2, 0xd0, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xcb, 0x3, 0x2, 0x2, 
       0x2, 0xd1, 0x21, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd5, 0x5, 0x24, 0x13, 
       0x2, 0xd3, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xd2, 0x3, 0x2, 0x2, 0x2, 
       0xd4, 0xd3, 0x3, 0x2, 0x2, 0x2, 0xd5, 0x23, 0x3, 0x2, 0x2, 0x2, 0xd6, 
       0xd7, 0x5, 0x26, 0x14, 0x2, 0xd7, 0xd8, 0x7, 0xa, 0x2, 0x2, 0xd8, 
       0xd9, 0x5, 0x24, 0x13, 0x2, 0xd9, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xda, 
       0xdc, 0x5, 0x26, 0x14, 0x2, 0xdb, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xdb, 
       0xda, 0x3, 0x2, 0x2, 0x2, 0xdc, 0x25, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xde, 
       0x5, 0x28, 0x15, 0x2, 0xde, 0xdf, 0x7, 0x1b, 0x2, 0x2, 0xdf, 0x27, 
       0x3, 0x2, 0x2, 0x2, 0xe0, 0xe1, 0x7, 0xe, 0x2, 0x2, 0xe1, 0x29, 0x3, 
       0x2, 0x2, 0x2, 0xf, 0x2d, 0x47, 0x54, 0x5b, 0x67, 0x87, 0x8e, 0xa9, 
       0xba, 0xc1, 0xd0, 0xd4, 0xdb, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

scParser::Initializer scParser::_init;
