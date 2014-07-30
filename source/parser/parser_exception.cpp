/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "parser_exception.h"

/**
  Implementação da classe ParserException.
*/

/**
  Construtor padrão - inicializa atributo relativo à mensagem de erro vinculada à exceção.

  @param
     errorMessage - mensagem de erro vinculada à exceção.
*/
ParserException::ParserException(string errorMessage) throw()
{
    this->errorMessage_ = errorMessage;
}

/**
  Destrutor da classe.
*/
ParserException::~ParserException() throw()
{

}

/**
  Retorna a mensagem de erro vinculada à exceção.

  @return
     mensagem de erro vinculada à exceção.
*/
const char* ParserException::what() const throw()
{
    return this->errorMessage_.c_str();
}
