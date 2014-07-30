/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef PARSER_H
#define PARSER_H

#include "yy_parser.h"
#include "parser_exception.h"


/**
  Definição da classe Parser.

  Esta classe encapsula os métodos e funções necessários para executar a análise sintática
  (parsing) em um arquivo de código fonte.
*/
class Parser
{

public:

    // Construtor/destrutor.
    Parser();
    ~Parser();

    // Executa análise sintática no arquivo de código fonte.
    void parseSourceFile();

    // Verifica se houve erros ao realizar a análise sintática no arquivo de código fonte.
    bool hasError() const;

    // Retorna o número erros encontrados ao realizar a análise sintática no
    // arquivo de código fonte.
    unsigned int getErrorsCount() const;

};


#endif
