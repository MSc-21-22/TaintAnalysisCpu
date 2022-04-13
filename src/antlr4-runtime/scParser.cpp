
// Generated from sc.g4 by ANTLR 4.10


#include "scListener.h"
#include "scVisitor.h"

#include "scParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct ScParserStaticData final {
  ScParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ScParserStaticData(const ScParserStaticData&) = delete;
  ScParserStaticData(ScParserStaticData&&) = delete;
  ScParserStaticData& operator=(const ScParserStaticData&) = delete;
  ScParserStaticData& operator=(ScParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag scParserOnceFlag;
ScParserStaticData *scParserStaticData = nullptr;

void scParserInitialize() {
  assert(scParserStaticData == nullptr);
  auto staticData = std::make_unique<ScParserStaticData>(
    std::vector<std::string>{
      "prog", "functionDef", "statements", "statement", "statementassign", 
      "statementinit", "statementinitarray", "arrayelement", "whileloop", 
      "statementif", "args", "expression", "expressionM", "functionCallInit", 
      "functionCall", "opt_parameters", "parameters", "parameter", "type"
    },
    std::vector<std::string>{
      "", "'void'", "'{'", "'}'", "'return'", "';'", "'['", "']'", "','", 
      "'while'", "'if'", "'else'", "'int'", "", "'+'", "'-'", "'/'", "'*'", 
      "'='", "'('", "')'", "'<='", "'>='", "'<'", "'>'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "INTEGER", "PLUS", 
      "MINUS", "DIVISION", "MULTIPLICATION", "ASSIGN", "LPAREN", "RPAREN", 
      "LEQ", "GEQ", "LT", "GT", "ID", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,26,206,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,1,0,5,0,40,8,0,10,0,12,0,43,
  	9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,68,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,3,2,81,8,2,1,3,1,3,1,3,1,3,3,3,87,8,3,1,4,1,4,1,4,1,4,1,4,
  	1,4,1,4,1,4,1,4,1,4,3,4,99,8,4,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,
  	6,1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,3,7,122,8,7,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	10,1,10,1,10,1,10,1,10,3,10,149,8,10,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,166,8,11,1,12,1,12,1,
  	12,1,12,1,12,3,12,173,8,12,1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,
  	14,1,14,1,14,1,14,1,14,3,14,188,8,14,1,15,1,15,3,15,192,8,15,1,16,1,16,
  	1,16,1,16,1,16,3,16,199,8,16,1,17,1,17,1,17,1,18,1,18,1,18,0,0,19,0,2,
  	4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,0,1,1,0,14,17,204,0,41,
  	1,0,0,0,2,67,1,0,0,0,4,80,1,0,0,0,6,86,1,0,0,0,8,98,1,0,0,0,10,100,1,
  	0,0,0,12,105,1,0,0,0,14,121,1,0,0,0,16,123,1,0,0,0,18,131,1,0,0,0,20,
  	148,1,0,0,0,22,165,1,0,0,0,24,172,1,0,0,0,26,174,1,0,0,0,28,187,1,0,0,
  	0,30,191,1,0,0,0,32,198,1,0,0,0,34,200,1,0,0,0,36,203,1,0,0,0,38,40,3,
  	2,1,0,39,38,1,0,0,0,40,43,1,0,0,0,41,39,1,0,0,0,41,42,1,0,0,0,42,44,1,
  	0,0,0,43,41,1,0,0,0,44,45,5,0,0,1,45,1,1,0,0,0,46,47,5,1,0,0,47,48,5,
  	25,0,0,48,49,5,19,0,0,49,50,3,30,15,0,50,51,5,20,0,0,51,52,5,2,0,0,52,
  	53,3,4,2,0,53,54,5,3,0,0,54,68,1,0,0,0,55,56,3,36,18,0,56,57,5,25,0,0,
  	57,58,5,19,0,0,58,59,3,30,15,0,59,60,5,20,0,0,60,61,5,2,0,0,61,62,3,4,
  	2,0,62,63,5,4,0,0,63,64,3,22,11,0,64,65,5,5,0,0,65,66,5,3,0,0,66,68,1,
  	0,0,0,67,46,1,0,0,0,67,55,1,0,0,0,68,3,1,0,0,0,69,70,3,6,3,0,70,71,5,
  	5,0,0,71,72,3,4,2,0,72,81,1,0,0,0,73,74,3,16,8,0,74,75,3,4,2,0,75,81,
  	1,0,0,0,76,77,3,18,9,0,77,78,3,4,2,0,78,81,1,0,0,0,79,81,1,0,0,0,80,69,
  	1,0,0,0,80,73,1,0,0,0,80,76,1,0,0,0,80,79,1,0,0,0,81,5,1,0,0,0,82,87,
  	3,10,5,0,83,87,3,8,4,0,84,87,3,26,13,0,85,87,3,12,6,0,86,82,1,0,0,0,86,
  	83,1,0,0,0,86,84,1,0,0,0,86,85,1,0,0,0,87,7,1,0,0,0,88,89,5,25,0,0,89,
  	90,5,18,0,0,90,99,3,22,11,0,91,92,5,25,0,0,92,93,5,6,0,0,93,94,3,22,11,
  	0,94,95,5,7,0,0,95,96,5,18,0,0,96,97,3,22,11,0,97,99,1,0,0,0,98,88,1,
  	0,0,0,98,91,1,0,0,0,99,9,1,0,0,0,100,101,3,36,18,0,101,102,5,25,0,0,102,
  	103,5,18,0,0,103,104,3,22,11,0,104,11,1,0,0,0,105,106,3,36,18,0,106,107,
  	5,25,0,0,107,108,5,6,0,0,108,109,5,13,0,0,109,110,5,7,0,0,110,111,5,18,
  	0,0,111,112,5,2,0,0,112,113,3,22,11,0,113,114,3,14,7,0,114,115,5,3,0,
  	0,115,13,1,0,0,0,116,117,5,8,0,0,117,118,3,22,11,0,118,119,3,14,7,0,119,
  	122,1,0,0,0,120,122,1,0,0,0,121,116,1,0,0,0,121,120,1,0,0,0,122,15,1,
  	0,0,0,123,124,5,9,0,0,124,125,5,19,0,0,125,126,3,22,11,0,126,127,5,20,
  	0,0,127,128,5,2,0,0,128,129,3,4,2,0,129,130,5,3,0,0,130,17,1,0,0,0,131,
  	132,5,10,0,0,132,133,5,19,0,0,133,134,3,22,11,0,134,135,5,20,0,0,135,
  	136,5,2,0,0,136,137,3,4,2,0,137,138,5,3,0,0,138,139,5,11,0,0,139,140,
  	5,2,0,0,140,141,3,4,2,0,141,142,5,3,0,0,142,19,1,0,0,0,143,144,3,22,11,
  	0,144,145,5,8,0,0,145,146,3,20,10,0,146,149,1,0,0,0,147,149,3,22,11,0,
  	148,143,1,0,0,0,148,147,1,0,0,0,149,21,1,0,0,0,150,151,5,19,0,0,151,152,
  	3,22,11,0,152,153,5,20,0,0,153,154,3,24,12,0,154,166,1,0,0,0,155,156,
  	5,13,0,0,156,166,3,24,12,0,157,158,5,25,0,0,158,166,3,24,12,0,159,160,
  	5,25,0,0,160,161,5,6,0,0,161,162,3,22,11,0,162,163,5,7,0,0,163,164,3,
  	24,12,0,164,166,1,0,0,0,165,150,1,0,0,0,165,155,1,0,0,0,165,157,1,0,0,
  	0,165,159,1,0,0,0,166,23,1,0,0,0,167,168,7,0,0,0,168,169,3,22,11,0,169,
  	170,3,24,12,0,170,173,1,0,0,0,171,173,1,0,0,0,172,167,1,0,0,0,172,171,
  	1,0,0,0,173,25,1,0,0,0,174,175,3,36,18,0,175,176,5,25,0,0,176,177,5,18,
  	0,0,177,178,3,28,14,0,178,27,1,0,0,0,179,180,5,25,0,0,180,181,5,19,0,
  	0,181,188,5,20,0,0,182,183,5,25,0,0,183,184,5,19,0,0,184,185,3,20,10,
  	0,185,186,5,20,0,0,186,188,1,0,0,0,187,179,1,0,0,0,187,182,1,0,0,0,188,
  	29,1,0,0,0,189,192,3,32,16,0,190,192,1,0,0,0,191,189,1,0,0,0,191,190,
  	1,0,0,0,192,31,1,0,0,0,193,194,3,34,17,0,194,195,5,8,0,0,195,196,3,32,
  	16,0,196,199,1,0,0,0,197,199,3,34,17,0,198,193,1,0,0,0,198,197,1,0,0,
  	0,199,33,1,0,0,0,200,201,3,36,18,0,201,202,5,25,0,0,202,35,1,0,0,0,203,
  	204,5,12,0,0,204,37,1,0,0,0,12,41,67,80,86,98,121,148,165,172,187,191,
  	198
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  scParserStaticData = staticData.release();
}

}

scParser::scParser(TokenStream *input) : scParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

scParser::scParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  scParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *scParserStaticData->atn, scParserStaticData->decisionToDFA, scParserStaticData->sharedContextCache, options);
}

scParser::~scParser() {
  delete _interpreter;
}

const atn::ATN& scParser::getATN() const {
  return *scParserStaticData->atn;
}

std::string scParser::getGrammarFileName() const {
  return "sc.g4";
}

const std::vector<std::string>& scParser::getRuleNames() const {
  return scParserStaticData->ruleNames;
}

const dfa::Vocabulary& scParser::getVocabulary() const {
  return scParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView scParser::getSerializedATN() const {
  return scParserStaticData->serializedATN;
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


std::any scParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
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
    setState(41);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == scParser::T__0

    || _la == scParser::T__11) {
      setState(38);
      functionDef();
      setState(43);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(44);
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


std::any scParser::FunctionDefContext::accept(tree::ParseTreeVisitor *visitor) {
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
    setState(67);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(46);
        match(scParser::T__0);
        setState(47);
        match(scParser::ID);
        setState(48);
        match(scParser::LPAREN);
        setState(49);
        opt_parameters();
        setState(50);
        match(scParser::RPAREN);
        setState(51);
        match(scParser::T__1);
        setState(52);
        statements();
        setState(53);
        match(scParser::T__2);
        break;
      }

      case scParser::T__11: {
        enterOuterAlt(_localctx, 2);
        setState(55);
        type();
        setState(56);
        match(scParser::ID);
        setState(57);
        match(scParser::LPAREN);
        setState(58);
        opt_parameters();
        setState(59);
        match(scParser::RPAREN);
        setState(60);
        match(scParser::T__1);
        setState(61);
        statements();
        setState(62);
        match(scParser::T__3);
        setState(63);
        expression();
        setState(64);
        match(scParser::T__4);
        setState(65);
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


std::any scParser::StatementsContext::accept(tree::ParseTreeVisitor *visitor) {
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
    setState(80);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__11:
      case scParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(69);
        statement();
        setState(70);
        match(scParser::T__4);
        setState(71);
        statements();
        break;
      }

      case scParser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(73);
        whileloop();
        setState(74);
        statements();
        break;
      }

      case scParser::T__9: {
        enterOuterAlt(_localctx, 3);
        setState(76);
        statementif();
        setState(77);
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


std::any scParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
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
    setState(86);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(82);
      statementinit();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(83);
      statementassign();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(84);
      functionCallInit();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(85);
      statementinitarray();
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


std::any scParser::StatementassignContext::accept(tree::ParseTreeVisitor *visitor) {
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
    setState(98);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(88);
      match(scParser::ID);
      setState(89);
      match(scParser::ASSIGN);
      setState(90);
      expression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(91);
      match(scParser::ID);
      setState(92);
      match(scParser::T__5);
      setState(93);
      expression();
      setState(94);
      match(scParser::T__6);
      setState(95);
      match(scParser::ASSIGN);
      setState(96);
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


std::any scParser::StatementinitContext::accept(tree::ParseTreeVisitor *visitor) {
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
    setState(100);
    type();
    setState(101);
    match(scParser::ID);
    setState(102);
    match(scParser::ASSIGN);
    setState(103);
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


std::any scParser::StatementinitarrayContext::accept(tree::ParseTreeVisitor *visitor) {
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
    setState(105);
    type();
    setState(106);
    match(scParser::ID);
    setState(107);
    match(scParser::T__5);
    setState(108);
    match(scParser::INTEGER);
    setState(109);
    match(scParser::T__6);
    setState(110);
    match(scParser::ASSIGN);
    setState(111);
    match(scParser::T__1);
    setState(112);
    expression();
    setState(113);
    arrayelement();
    setState(114);
    match(scParser::T__2);
   
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


std::any scParser::ArrayelementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitArrayelement(this);
  else
    return visitor->visitChildren(this);
}

scParser::ArrayelementContext* scParser::arrayelement() {
  ArrayelementContext *_localctx = _tracker.createInstance<ArrayelementContext>(_ctx, getState());
  enterRule(_localctx, 14, scParser::RuleArrayelement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(121);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case scParser::T__7: {
        enterOuterAlt(_localctx, 1);
        setState(116);
        match(scParser::T__7);
        setState(117);
        expression();
        setState(118);
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


std::any scParser::WhileloopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitWhileloop(this);
  else
    return visitor->visitChildren(this);
}

scParser::WhileloopContext* scParser::whileloop() {
  WhileloopContext *_localctx = _tracker.createInstance<WhileloopContext>(_ctx, getState());
  enterRule(_localctx, 16, scParser::RuleWhileloop);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123);
    match(scParser::T__8);
    setState(124);
    match(scParser::LPAREN);
    setState(125);
    expression();
    setState(126);
    match(scParser::RPAREN);
    setState(127);
    match(scParser::T__1);
    setState(128);
    statements();
    setState(129);
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


std::any scParser::StatementifContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitStatementif(this);
  else
    return visitor->visitChildren(this);
}

scParser::StatementifContext* scParser::statementif() {
  StatementifContext *_localctx = _tracker.createInstance<StatementifContext>(_ctx, getState());
  enterRule(_localctx, 18, scParser::RuleStatementif);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    match(scParser::T__9);
    setState(132);
    match(scParser::LPAREN);
    setState(133);
    expression();
    setState(134);
    match(scParser::RPAREN);
    setState(135);
    match(scParser::T__1);
    setState(136);
    statements();
    setState(137);
    match(scParser::T__2);
    setState(138);
    match(scParser::T__10);
    setState(139);
    match(scParser::T__1);
    setState(140);
    statements();
    setState(141);
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


std::any scParser::ArgsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitArgs(this);
  else
    return visitor->visitChildren(this);
}

scParser::ArgsContext* scParser::args() {
  ArgsContext *_localctx = _tracker.createInstance<ArgsContext>(_ctx, getState());
  enterRule(_localctx, 20, scParser::RuleArgs);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(148);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(143);
      expression();
      setState(144);
      match(scParser::T__7);
      setState(145);
      args();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(147);
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


std::any scParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

scParser::ExpressionContext* scParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 22, scParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(165);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(150);
      match(scParser::LPAREN);
      setState(151);
      expression();
      setState(152);
      match(scParser::RPAREN);
      setState(153);
      expressionM();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(155);
      match(scParser::INTEGER);
      setState(156);
      expressionM();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(157);
      match(scParser::ID);
      setState(158);
      expressionM();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(159);
      match(scParser::ID);
      setState(160);
      match(scParser::T__5);
      setState(161);
      expression();
      setState(162);
      match(scParser::T__6);
      setState(163);
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


std::any scParser::ExpressionMContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitExpressionM(this);
  else
    return visitor->visitChildren(this);
}

scParser::ExpressionMContext* scParser::expressionM() {
  ExpressionMContext *_localctx = _tracker.createInstance<ExpressionMContext>(_ctx, getState());
  enterRule(_localctx, 24, scParser::RuleExpressionM);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(172);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(167);
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
      setState(168);
      expression();
      setState(169);
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


std::any scParser::FunctionCallInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitFunctionCallInit(this);
  else
    return visitor->visitChildren(this);
}

scParser::FunctionCallInitContext* scParser::functionCallInit() {
  FunctionCallInitContext *_localctx = _tracker.createInstance<FunctionCallInitContext>(_ctx, getState());
  enterRule(_localctx, 26, scParser::RuleFunctionCallInit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(174);
    type();
    setState(175);
    match(scParser::ID);
    setState(176);
    match(scParser::ASSIGN);
    setState(177);
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


std::any scParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

scParser::FunctionCallContext* scParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 28, scParser::RuleFunctionCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(187);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(179);
      match(scParser::ID);
      setState(180);
      match(scParser::LPAREN);
      setState(181);
      match(scParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(182);
      match(scParser::ID);
      setState(183);
      match(scParser::LPAREN);
      setState(184);
      args();
      setState(185);
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


std::any scParser::Opt_parametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitOpt_parameters(this);
  else
    return visitor->visitChildren(this);
}

scParser::Opt_parametersContext* scParser::opt_parameters() {
  Opt_parametersContext *_localctx = _tracker.createInstance<Opt_parametersContext>(_ctx, getState());
  enterRule(_localctx, 30, scParser::RuleOpt_parameters);

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
    switch (_input->LA(1)) {
      case scParser::T__11: {
        enterOuterAlt(_localctx, 1);
        setState(189);
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


std::any scParser::ParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitParameters(this);
  else
    return visitor->visitChildren(this);
}

scParser::ParametersContext* scParser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 32, scParser::RuleParameters);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(198);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(193);
      parameter();
      setState(194);
      match(scParser::T__7);
      setState(195);
      parameters();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(197);
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


std::any scParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

scParser::ParameterContext* scParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 34, scParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(200);
    type();
    setState(201);
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


std::any scParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<scVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

scParser::TypeContext* scParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 36, scParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    match(scParser::T__11);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void scParser::initialize() {
  std::call_once(scParserOnceFlag, scParserInitialize);
}
