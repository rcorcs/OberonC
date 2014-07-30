/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SIMPLE_SCANNER_DEBUGGER_H
#define SIMPLE_SCANNER_DEBUGGER_H

#include "../debugger_interfaces/scanner_debugger.h"


class SimpleScannerDebugger: public ScannerDebugger
{

public:

    SimpleScannerDebugger();

    void debugToken(TokenType tokenType, const char *lexeme, int line, int start_column);
    void debugInvalidSymbolError(const char *lexeme, int line, int start_column);
    void debugUnterminatedStringError(const char *lexeme, int line, int start_column);
    void debugInvalidStringCharacterError(const char *lexeme, int line, int start_column);
    void debugUnexpectedEOF(int line);

protected:

    void createDebugFile(const char *baseFileName);

};

#endif
