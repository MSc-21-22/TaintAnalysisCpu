
// Generated from sc.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"




class  scLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, INTEGER = 13, 
    PLUS = 14, MINUS = 15, DIVISION = 16, MULTIPLICATION = 17, ASSIGN = 18, 
    LPAREN = 19, RPAREN = 20, LEQ = 21, GEQ = 22, LT = 23, GT = 24, ID = 25, 
    WS = 26
  };

  explicit scLexer(antlr4::CharStream *input);

  ~scLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

