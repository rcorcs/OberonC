/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SCANNER_DEBUGGER_H
#define SCANNER_DEBUGGER_H

#include "../debugger.h"
#include "../../scanner/token_type.h"
#include "../../scanner/scanner_exception.h"

class ScannerDebugger: public Debugger
{

public:

    /**
      Método debug chamado pela função yy_lex() ao identificar, no arquivo de código fonte,
      um token VÁLIDO.

      @param tokenType
         tipo do token lido.

      @param lexeme
         lexema do arquivo de código fonte que casou com o token especificado.

      @param line
         linha do lexema no arquivo de código fonte.

      @param start_column
         posição inicial da coluna do lexema no arquivo de código fonte.

      @see TokenType

    */
    virtual void debugToken(TokenType tokenType, const char *lexeme, int line, int start_column) = 0;

    /**
      Método debug chamado pela função yy_lex() ao identificar, no arquivo de código fonte,
      um símbolo inválido.

      @param lexeme
         lexema do arquivo de código fonte que causou o erro léxico.

      @param line
         linha do lexema no arquivo de código fonte.

      @param start_column
         posição inicial da coluna do lexema no arquivo de código fonte.

    */
    virtual void debugInvalidSymbolError(const char *lexeme, int line, int start_column) = 0;

    /**
      Método debug chamado pela função yy_lex() ao identificar, no arquivo de código fonte,
      uma string não terminada.

      @param lexeme
         lexema do arquivo de código fonte que causou o erro léxico.

      @param line
         linha do lexema no arquivo de código fonte.

      @param start_column
        posição inicial da coluna do lexema no arquivo de código fonte.

    */
    virtual void debugUnterminatedStringError(const char *lexeme, int line, int start_column) = 0;

    /**
      Método debug chamado pela função yy_lex() ao identificar, no arquivo de código fonte,
      uma string contendo um caractere inválido.

      @param errorTokenType
         tipo do token que identifica o erro encontrado encontrado.

      @param lexeme
         lexema do arquivo de código fonte que causou o erro léxico.

      @param line
         linha do lexema no arquivo de código fonte.

      @param start_column
         posição inicial da coluna do lexema no arquivo de código fonte.
    */
    virtual void debugInvalidStringCharacterError(const char *lexeme, int line, int start_column) = 0;

    /**
      Método debug chamado pela função yy_lex() ao identificar, no arquivo de código fonte,
      um fim inesperado de arquivo.

      @param line
         linha de erro no arquivo de código fonte.
    */
    virtual void debugUnexpectedEOF(int line) = 0;

};


#endif
