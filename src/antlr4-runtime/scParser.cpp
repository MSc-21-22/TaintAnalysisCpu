
// Generated from /home/thorulf/TaintAnalysisCpu/sc.g4 by ANTLR 4.8


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
    setState(25);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == scParser::T__0

    || _la == scParser::T__6) {
      setState(22);
      functionDef();
      setState(27);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(28);
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

scParser::ParametersContext* scParser::FunctionDefContext::parameters() {
  return getRuleContext<scParser::ParametersContext>(0);
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
    setState(52);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(30);
        match(scParser::T__0);
        setState(31);
        match(scParser::ID);
        setState(32);
        match(scParser::LPAREN);
        setState(33);
        parameters();
        setState(34);
        match(scParser::RPAREN);
        setState(35);
        match(scParser::T__1);
        setState(36);
        statements();
        setState(37);
        match(scParser::T__2);
        break;
      }

      case scParser::T__6: {
        enterOuterAlt(_localctx, 2);
        setState(39);
        type();
        setState(40);
        match(scParser::ID);
        setState(41);
        match(scParser::LPAREN);
        setState(42);
        parameters();
        setState(43);
        match(scParser::RPAREN);
        setState(44);
        match(scParser::T__1);
        setState(45);
        statements();
        setState(46);
        match(scParser::T__3);
        setState(47);
        match(scParser::T__4);
        setState(48);
        expression();
        setState(49);
        match(scParser::T__3);
        setState(50);
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
    setState(59);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__6:
      case scParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(54);
        statement();
        setState(55);
        match(scParser::T__3);
        setState(56);
        statements();
        break;
      }

      case scParser::T__2:
      case scParser::T__3: {
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

//----------------- StatementContext ------------------------------------------------------------------

scParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* scParser::StatementContext::ID() {
  return getToken(scParser::ID, 0);
}

scParser::ArgsContext* scParser::StatementContext::args() {
  return getRuleContext<scParser::ArgsContext>(0);
}

scParser::TypeContext* scParser::StatementContext::type() {
  return getRuleContext<scParser::TypeContext>(0);
}

tree::TerminalNode* scParser::StatementContext::ASSIGN() {
  return getToken(scParser::ASSIGN, 0);
}

scParser::ExpressionContext* scParser::StatementContext::expression() {
  return getRuleContext<scParser::ExpressionContext>(0);
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
    setState(73);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(61);
      match(scParser::ID);


      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(63);
      match(scParser::ID);

      setState(64);
      args();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(65);
      type();
      setState(66);
      match(scParser::ID);
      setState(67);
      match(scParser::ASSIGN);
      setState(68);
      expression();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(70);
      match(scParser::ID);
      setState(71);
      match(scParser::ASSIGN);
      setState(72);
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
  enterRule(_localctx, 8, scParser::RuleArgs);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(80);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(75);
      expression();
      setState(76);
      match(scParser::T__5);
      setState(77);
      args();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(79);
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
  enterRule(_localctx, 10, scParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(91);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(82);
        match(scParser::LPAREN);
        setState(83);
        expression();
        setState(84);
        match(scParser::RPAREN);
        setState(85);
        expressionM();
        break;
      }

      case scParser::INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(87);
        match(scParser::INTEGER);
        setState(88);
        expressionM();
        break;
      }

      case scParser::ID: {
        enterOuterAlt(_localctx, 3);
        setState(89);
        match(scParser::ID);
        setState(90);
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
  enterRule(_localctx, 12, scParser::RuleExpressionM);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(98);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(93);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << scParser::PLUS)
        | (1ULL << scParser::MINUS)
        | (1ULL << scParser::DIVISION))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(94);
      expression();
      setState(95);
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

//----------------- ParametersContext ------------------------------------------------------------------

scParser::ParametersContext::ParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::ParameterContext* scParser::ParametersContext::parameter() {
  return getRuleContext<scParser::ParameterContext>(0);
}

scParser::ParametersMContext* scParser::ParametersContext::parametersM() {
  return getRuleContext<scParser::ParametersMContext>(0);
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
  enterRule(_localctx, 14, scParser::RuleParameters);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(103);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(100);
      parameter();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(101);
      parametersM();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);

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

//----------------- ParametersMContext ------------------------------------------------------------------

scParser::ParametersMContext::ParametersMContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

scParser::ParameterContext* scParser::ParametersMContext::parameter() {
  return getRuleContext<scParser::ParameterContext>(0);
}

scParser::ParametersMContext* scParser::ParametersMContext::parametersM() {
  return getRuleContext<scParser::ParametersMContext>(0);
}


size_t scParser::ParametersMContext::getRuleIndex() const {
  return scParser::RuleParametersM;
}


antlrcpp::Any scParser::ParametersMContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitParametersM(this);
  else
    return visitor->visitChildren(this);
}

scParser::ParametersMContext* scParser::parametersM() {
  ParametersMContext *_localctx = _tracker.createInstance<ParametersMContext>(_ctx, getState());
  enterRule(_localctx, 16, scParser::RuleParametersM);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(110);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__6: {
        enterOuterAlt(_localctx, 1);
        setState(105);
        parameter();
        setState(106);
        match(scParser::T__5);
        setState(107);
        parametersM();
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
  enterRule(_localctx, 18, scParser::RuleParameter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(112);
    type();
    setState(113);
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
  enterRule(_localctx, 20, scParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    match(scParser::T__6);
   
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
  "prog", "functionDef", "statements", "statement", "args", "expression", 
  "expressionM", "parameters", "parametersM", "parameter", "type"
};

std::vector<std::string> scParser::_literalNames = {
  "", "'void'", "'{'", "'}'", "';'", "'return'", "','", "'int'", "", "'+'", 
  "'-'", "'/'", "'='", "'('", "')'"
};

std::vector<std::string> scParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "INTEGER", "PLUS", "MINUS", "DIVISION", 
  "ASSIGN", "LPAREN", "RPAREN", "ID", "WS"
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
    0x3, 0x12, 0x78, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x3, 0x2, 0x7, 0x2, 0x1a, 0xa, 0x2, 0xc, 0x2, 
    0xe, 0x2, 0x1d, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x37, 
    0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 
    0x3e, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 
    0x5, 0x4c, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x5, 0x6, 0x53, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x5e, 0xa, 0x7, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x65, 0xa, 
    0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x6a, 0xa, 0x9, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x71, 0xa, 0xa, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x2, 0x2, 0xd, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x2, 0x3, 
    0x3, 0x2, 0xb, 0xd, 0x2, 0x79, 0x2, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x4, 0x36, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x8, 0x4b, 0x3, 0x2, 
    0x2, 0x2, 0xa, 0x52, 0x3, 0x2, 0x2, 0x2, 0xc, 0x5d, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0x64, 0x3, 0x2, 0x2, 0x2, 0x10, 0x69, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x70, 0x3, 0x2, 0x2, 0x2, 0x14, 0x72, 0x3, 0x2, 0x2, 0x2, 0x16, 0x75, 
    0x3, 0x2, 0x2, 0x2, 0x18, 0x1a, 0x5, 0x4, 0x3, 0x2, 0x19, 0x18, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x19, 0x3, 0x2, 
    0x2, 0x2, 0x1b, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1e, 0x3, 0x2, 0x2, 
    0x2, 0x1d, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x7, 0x2, 0x2, 0x3, 
    0x1f, 0x3, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x7, 0x3, 0x2, 0x2, 0x21, 
    0x22, 0x7, 0x11, 0x2, 0x2, 0x22, 0x23, 0x7, 0xf, 0x2, 0x2, 0x23, 0x24, 
    0x5, 0x10, 0x9, 0x2, 0x24, 0x25, 0x7, 0x10, 0x2, 0x2, 0x25, 0x26, 0x7, 
    0x4, 0x2, 0x2, 0x26, 0x27, 0x5, 0x6, 0x4, 0x2, 0x27, 0x28, 0x7, 0x5, 
    0x2, 0x2, 0x28, 0x37, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x5, 0x16, 0xc, 
    0x2, 0x2a, 0x2b, 0x7, 0x11, 0x2, 0x2, 0x2b, 0x2c, 0x7, 0xf, 0x2, 0x2, 
    0x2c, 0x2d, 0x5, 0x10, 0x9, 0x2, 0x2d, 0x2e, 0x7, 0x10, 0x2, 0x2, 0x2e, 
    0x2f, 0x7, 0x4, 0x2, 0x2, 0x2f, 0x30, 0x5, 0x6, 0x4, 0x2, 0x30, 0x31, 
    0x7, 0x6, 0x2, 0x2, 0x31, 0x32, 0x7, 0x7, 0x2, 0x2, 0x32, 0x33, 0x5, 
    0xc, 0x7, 0x2, 0x33, 0x34, 0x7, 0x6, 0x2, 0x2, 0x34, 0x35, 0x7, 0x5, 
    0x2, 0x2, 0x35, 0x37, 0x3, 0x2, 0x2, 0x2, 0x36, 0x20, 0x3, 0x2, 0x2, 
    0x2, 0x36, 0x29, 0x3, 0x2, 0x2, 0x2, 0x37, 0x5, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0x39, 0x5, 0x8, 0x5, 0x2, 0x39, 0x3a, 0x7, 0x6, 0x2, 0x2, 0x3a, 
    0x3b, 0x5, 0x6, 0x4, 0x2, 0x3b, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3e, 
    0x3, 0x2, 0x2, 0x2, 0x3d, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3c, 0x3, 
    0x2, 0x2, 0x2, 0x3e, 0x7, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x11, 
    0x2, 0x2, 0x40, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 0x7, 0x11, 0x2, 
    0x2, 0x42, 0x4c, 0x5, 0xa, 0x6, 0x2, 0x43, 0x44, 0x5, 0x16, 0xc, 0x2, 
    0x44, 0x45, 0x7, 0x11, 0x2, 0x2, 0x45, 0x46, 0x7, 0xe, 0x2, 0x2, 0x46, 
    0x47, 0x5, 0xc, 0x7, 0x2, 0x47, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 
    0x7, 0x11, 0x2, 0x2, 0x49, 0x4a, 0x7, 0xe, 0x2, 0x2, 0x4a, 0x4c, 0x5, 
    0xc, 0x7, 0x2, 0x4b, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x41, 0x3, 0x2, 
    0x2, 0x2, 0x4b, 0x43, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x48, 0x3, 0x2, 0x2, 
    0x2, 0x4c, 0x9, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x5, 0xc, 0x7, 0x2, 
    0x4e, 0x4f, 0x7, 0x8, 0x2, 0x2, 0x4f, 0x50, 0x5, 0xa, 0x6, 0x2, 0x50, 
    0x53, 0x3, 0x2, 0x2, 0x2, 0x51, 0x53, 0x5, 0xc, 0x7, 0x2, 0x52, 0x4d, 
    0x3, 0x2, 0x2, 0x2, 0x52, 0x51, 0x3, 0x2, 0x2, 0x2, 0x53, 0xb, 0x3, 
    0x2, 0x2, 0x2, 0x54, 0x55, 0x7, 0xf, 0x2, 0x2, 0x55, 0x56, 0x5, 0xc, 
    0x7, 0x2, 0x56, 0x57, 0x7, 0x10, 0x2, 0x2, 0x57, 0x58, 0x5, 0xe, 0x8, 
    0x2, 0x58, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x7, 0xa, 0x2, 0x2, 
    0x5a, 0x5e, 0x5, 0xe, 0x8, 0x2, 0x5b, 0x5c, 0x7, 0x11, 0x2, 0x2, 0x5c, 
    0x5e, 0x5, 0xe, 0x8, 0x2, 0x5d, 0x54, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x59, 
    0x3, 0x2, 0x2, 0x2, 0x5d, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5e, 0xd, 0x3, 
    0x2, 0x2, 0x2, 0x5f, 0x60, 0x9, 0x2, 0x2, 0x2, 0x60, 0x61, 0x5, 0xc, 
    0x7, 0x2, 0x61, 0x62, 0x5, 0xe, 0x8, 0x2, 0x62, 0x65, 0x3, 0x2, 0x2, 
    0x2, 0x63, 0x65, 0x3, 0x2, 0x2, 0x2, 0x64, 0x5f, 0x3, 0x2, 0x2, 0x2, 
    0x64, 0x63, 0x3, 0x2, 0x2, 0x2, 0x65, 0xf, 0x3, 0x2, 0x2, 0x2, 0x66, 
    0x6a, 0x5, 0x14, 0xb, 0x2, 0x67, 0x6a, 0x5, 0x12, 0xa, 0x2, 0x68, 0x6a, 
    0x3, 0x2, 0x2, 0x2, 0x69, 0x66, 0x3, 0x2, 0x2, 0x2, 0x69, 0x67, 0x3, 
    0x2, 0x2, 0x2, 0x69, 0x68, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x11, 0x3, 0x2, 
    0x2, 0x2, 0x6b, 0x6c, 0x5, 0x14, 0xb, 0x2, 0x6c, 0x6d, 0x7, 0x8, 0x2, 
    0x2, 0x6d, 0x6e, 0x5, 0x12, 0xa, 0x2, 0x6e, 0x71, 0x3, 0x2, 0x2, 0x2, 
    0x6f, 0x71, 0x3, 0x2, 0x2, 0x2, 0x70, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x70, 
    0x6f, 0x3, 0x2, 0x2, 0x2, 0x71, 0x13, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 
    0x5, 0x16, 0xc, 0x2, 0x73, 0x74, 0x7, 0x11, 0x2, 0x2, 0x74, 0x15, 0x3, 
    0x2, 0x2, 0x2, 0x75, 0x76, 0x7, 0x9, 0x2, 0x2, 0x76, 0x17, 0x3, 0x2, 
    0x2, 0x2, 0xb, 0x1b, 0x36, 0x3d, 0x4b, 0x52, 0x5d, 0x64, 0x69, 0x70, 
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
