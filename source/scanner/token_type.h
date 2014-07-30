/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

/**
    Este arquivo abstrai tokens definidos no arquivo "yy_parser.h", gerados pelo Bison,
    em uma representação interna de tokens (TokenType) no Scanner.

    Define-se uma função que, dado o tipo do token (TokenType), recupera-se e retorna-se
    o respectivo nome associado a este token.
*/
#include "../parser/yy_parser.h"

// Abstrai definição dos tipos de tokens gerados no arquivo
// "yy_parser.h" em uma representação interna ao Scanner.
typedef yytokentype TokenType;

// Retorna o nome de um token com base em seu tipo.
char *getTokenTypeName(TokenType tokenType);

#endif
