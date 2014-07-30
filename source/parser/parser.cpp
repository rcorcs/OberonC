/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "parser.h"

/**
  Implementação da classe Parser.
*/

// Função para análise sintática, definida externamente (yy_parser.cpp),
// que será utilizada internamente nesta classe.
extern int yyparse();

// Variável definida externamente (yy_parser.cpp) utilizada para contagem de erros
// encontrados (erros sintáticos e também erros semânticos que são identificados pelo Parser,
// como, por exemplo, uso de identificadores não declarados) durante a análise sintática
// realizada pela função yy_parse().
extern unsigned int parserErrors;


/**
  Construtor padrão.
*/
Parser::Parser()
{

}

/**
  Destrutor da classe.
*/
Parser::~Parser()
{

}

/**
  Executa análise sintática no arquivo de código fonte.
  Para tanto, a função yyparse(), implementada no arquivo externo yy_parser.cpp,
  gerado pelo Bison, será chamada.

  A presença e o número de erros sintáticos (recuperados ou não) podem ser obtidos,
  respectivamente, através dos métodos hasError() e getErrorsCount().
*/
void Parser::parseSourceFile()
{
    // Zera contagem de erros.
    parserErrors = 0;

    // Chama função para realizar análise sintática no arquivo de código fonte.
    // Sempre quando um erro for detectado (seja sintático ou semântico), a função externa
    // yy_error() será chamada e a variável parserErrors será incrementada.
    yyparse();
}

/**
  Verifica se houve erros ao realizar a análise sintática no arquivo de código fonte.

  @return
     flag que indica se houve erros (true) ou não (false) durante a análise léxica.
*/
bool Parser::hasError() const
{
    return (parserErrors > 0);
}

/**
  Retorna o número erros encontrados ao realizar a análise sintática no arquivo de código fonte.

  @return
     número erros encontrados.
*/
unsigned int Parser::getErrorsCount() const
{
    return parserErrors;
}
