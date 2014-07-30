/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef PARSER_DEBUGGER_H
#define PARSER_DEBUGGER_H

#include "../debugger.h"
#include "../../parser/parser_exception.h"

// Função para exibição de erros sintáticos, definida externamente (yy_parser.cpp),
// que será utilizada por implementações de debuggers para o Parser.
extern void yyerror(const char* errmsg);

class ParserDebugger: public Debugger
{

public:

    /**
      Método debug, chamado pela função yy_parse(), ao identificar (reduzir), no arquivo de
      código fonte, uma produção de gramática válida para a linguagem Oberon-0.

      @param nonTerminalSymbol
         símbolo não-terminal da gramática que gerou a produção.

      @param production
         produção de gramática encontrada.

      @param lookaheadLine
         número da linha do lookahead.
    */
    virtual void debugReduction(const char* nonTerminalSymbol, const char *production, const int lookaheadLine) = 0;

    /**
      Método debug, chamado pela função yy_parser(), ao identificar, no arquivo de código fonte,
      um erro sintático recuperado por meio de uma produção de erro na gramática.

      @param errorMessage
         descrição relativa ao erro de sintaxe recuperado.

      @param lineNumber
         número da linha do erro.
    */
    virtual void debugRecoveredError(const char *errorMessage, int lineNumber) = 0;

};

#endif
