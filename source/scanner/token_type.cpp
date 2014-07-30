/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "token_type.h"
#include <cstring>

#define MAX_TOKEN_NAME 25

/**
  Função auxiliar para retornar o nome de um token com base em seu
  respectivo tipo (TokenType).

  @param tokenType
     tipo do token.

  @return
     nome associado ao token.
*/
char *getTokenTypeName(TokenType tokenType)
{
    char *tokenName = new char[MAX_TOKEN_NAME];

    switch(tokenType)
    {
        // Identificador.

    case TOKEN_TYPE_IDENTIFIER:
        strcpy(tokenName, "IDENTIFIER");
        break;


        // Tipos.

    case TOKEN_TYPE_BOOLEAN:
        strcpy(tokenName, "BOOLEAN");
        break;

    case TOKEN_TYPE_INTEGER:
        strcpy(tokenName, "INTEGER");
        break;

    case TOKEN_TYPE_STRING:
        strcpy(tokenName, "STRING");
        break;


        // Literais.

    case TOKEN_TYPE_BOOLEAN_LITERAL:
        strcpy(tokenName, "BOOLEAN_LITERAL");
        break;

    case TOKEN_TYPE_INTEGER_LITERAL:
        strcpy(tokenName, "INTEGER_LITERAL");
        break;

    case TOKEN_TYPE_STRING_LITERAL:
        strcpy(tokenName, "STRING_LITERAL");
        break;


        // Delimitadores de escopo/bloco.

    case TOKEN_TYPE_MODULE:
        strcpy(tokenName, "MODULE");
        break;

    case TOKEN_TYPE_PROCEDURE:
        strcpy(tokenName, "PROCEDURE");
        break;

    case TOKEN_TYPE_FUNCTION:
        strcpy(tokenName, "FUNCTION");
        break;

    case TOKEN_TYPE_VAR:
        strcpy(tokenName, "VAR");
        break;

    case TOKEN_TYPE_BEGIN:
        strcpy(tokenName, "BEGIN");
        break;

    case TOKEN_TYPE_END:
        strcpy(tokenName, "END");
        break;


        // Condicionais.

    case TOKEN_TYPE_IF:
        strcpy(tokenName, "IF");
        break;

    case TOKEN_TYPE_THEN:
        strcpy(tokenName, "THEN");
        break;

    case TOKEN_TYPE_ELSIF:
        strcpy(tokenName, "ELSIF");
        break;

    case TOKEN_TYPE_ELSE:
        strcpy(tokenName, "ELSE");
        break;


        // Repetições/controle de fluxo.

    case TOKEN_TYPE_WHILE:
        strcpy(tokenName, "WHILE");
        break;

    case TOKEN_TYPE_REPEAT:
        strcpy(tokenName, "REPEAT");
        break;

    case TOKEN_TYPE_UNTIL:
        strcpy(tokenName, "UNTIL");
        break;

    case TOKEN_TYPE_FOR:
        strcpy(tokenName, "FOR");
        break;

    case TOKEN_TYPE_CONTINUE:
        strcpy(tokenName, "CONTINUE");
        break;

    case TOKEN_TYPE_BREAK:
        strcpy(tokenName, "BREAK");
        break;

    case TOKEN_TYPE_RETURN:
        strcpy(tokenName, "RETURN");
        break;

    case TOKEN_TYPE_DO:
        strcpy(tokenName, "DO");
        break;

    case TOKEN_TYPE_TO:
        strcpy(tokenName, "TO");
        break;


        // Operadores lógicos.

    case TOKEN_TYPE_AND:
        strcpy(tokenName, "AND");
        break;

    case TOKEN_TYPE_OR:
        strcpy(tokenName, "OR");
        break;

    case TOKEN_TYPE_NOT:
        strcpy(tokenName, "NOT");
        break;


        // Funções I/O nativas.

    case TOKEN_TYPE_WRITE:
        strcpy(tokenName, "WRITE");
        break;

    case TOKEN_TYPE_WRITELN:
        strcpy(tokenName, "WRITELN");
        break;

    case TOKEN_TYPE_READ:
        strcpy(tokenName, "READ");
        break;


        // Operadores relacionais.

    case TOKEN_TYPE_LESS:
        strcpy(tokenName, "LESS");
        break;

    case TOKEN_TYPE_LESS_EQUAL:
        strcpy(tokenName, "LESS_EQUAL");
        break;

    case TOKEN_TYPE_EQUAL:
        strcpy(tokenName, "EQUAL");
        break;

    case TOKEN_TYPE_NOT_EQUAL:
        strcpy(tokenName, "NOT_EQUAL");
        break;

    case TOKEN_TYPE_GREATER_EQUAL:
        strcpy(tokenName, "GREATER_EQUAL");
        break;

    case TOKEN_TYPE_GREATER:
        strcpy(tokenName, "GREATER");
        break;



        // Símbolos delimitadores.

    case TOKEN_TYPE_COLON:
        strcpy(tokenName, "COLON");
        break;

    case TOKEN_TYPE_SEMICOLON:
        strcpy(tokenName, "SEMICOLON");
        break;

    case TOKEN_TYPE_FULL_STOP:
        strcpy(tokenName, "FULL_STOP");
        break;

    case TOKEN_TYPE_COMMA:
        strcpy(tokenName, "COMMA");
        break;

    case TOKEN_TYPE_LEFT_BRACKET:
        strcpy(tokenName, "LEFT_BRACKET");
        break;

    case TOKEN_TYPE_RIGHT_BRACKET:
        strcpy(tokenName, "RIGHT_BRACKET");
        break;

        // Operadores aritiméticos/atribuição.

    case TOKEN_TYPE_ASSIGN:
        strcpy(tokenName, "ASSIGN");
        break;

    case TOKEN_TYPE_PLUS:
        strcpy(tokenName, "PLUS");
        break;

    case TOKEN_TYPE_MINUS:
        strcpy(tokenName, "MINUS");
        break;

    case TOKEN_TYPE_ASTERISK:
        strcpy(tokenName, "ASTERISK");
        break;

    case TOKEN_TYPE_MOD:
        strcpy(tokenName, "MOD");
        break;

    case TOKEN_TYPE_SLASH:
        strcpy(tokenName, "SLASH");
        break;

    default:
        tokenName[0] = 0;
    }

    return tokenName;
}
