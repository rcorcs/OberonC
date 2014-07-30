/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SYMBOL_TABLE_DEBUGGER_H
#define SYMBOL_TABLE_DEBUGGER_H

#include "../debugger.h"
#include "../../parser/parser_exception.h"

// Função para exibição de erros sintáticos, definida externamente (yy_parser.cpp),
// que será utilizada por implementações de debuggers para a Tabela de Símbolos.
extern void yyerror(const char* errmsg);

class SymbolTableDebugger: public Debugger
{

public:

    virtual void debugScopeStart(const char *scopeName) = 0;
    virtual void debugScopeEnd() = 0;

    virtual void debugIdentifierInfo(const char *name) = 0;
    virtual void debugIdentifierInfoAttribute(const char *name, const char *value) = 0;

    virtual void newLine() = 0;

    virtual void debugIdentifierNotDeclared(const char *identifier, int lineNumber) = 0;
    virtual void debugIdentifierAlreadyDeclared(const char *identifier, int lineNumber) = 0;
    virtual void debugUnexpectedUseOfIdentifier(const char *identifier, int lineNumber) = 0;

};

#endif
