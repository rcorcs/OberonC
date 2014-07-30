/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SIMPLE_SYMBOL_TABLE_DEBUGGER_H
#define SIMPLE_SYMBOL_TABLE_DEBUGGER_H

#include "../debugger_interfaces/symbol_table_debugger.h"

class SimpleSymbolTableDebugger: public SymbolTableDebugger
{

public:

    SimpleSymbolTableDebugger();

    void debugScopeStart(const char *scopeName);
    void debugScopeEnd();
    void debugIdentifierInfo(const char *name);
    void debugIdentifierInfoAttribute(const char *name, const char *value);
    void debugIdentifierInfoAttribute(const char *name, int value);
    void debugIdentifierInfoAttribute(const char *name, bool value);

    void newLine();

    void debugIdentifierNotDeclared(const char *identifier, int lineNumber);
    void debugIdentifierAlreadyDeclared(const char *identifier,  int lineNumber);
    void debugUnexpectedUseOfIdentifier(const char *identifier,  int lineNumber);

protected:

    void createDebugFile(const char *baseFileName);

};

#endif
