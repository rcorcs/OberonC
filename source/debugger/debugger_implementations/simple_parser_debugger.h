/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SIMPLE_PARSER_DEBUGGER_H
#define SIMPLE_PARSER_DEBUGGER_H

#include "../debugger_interfaces/parser_debugger.h"


class SimpleParserDebugger: public ParserDebugger
{

public:

    SimpleParserDebugger();

    void debugReduction(const char* nonTerminalSymbol, const char *production, int lookaheadLine);
    void debugRecoveredError(const char *errorMessage, int lineNumber);

protected:

    void createDebugFile(const char *baseFileName);


};

#endif
