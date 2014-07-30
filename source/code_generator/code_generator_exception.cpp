/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "code_generator_exception.h"

/**
  Implementação da classe CodeGeneratorException.
*/

/**
  Construtor padrão - inicializa atributo relativo à mensagem de erro vinculada à exceção.

  @param
     errorMessage - mensagem de erro vinculada à exceção.
*/
CodeGeneratorException::CodeGeneratorException(string errorMessage) throw()
{
    this->errorMessage_ = errorMessage;
}

/**
  Destrutor da classe.
*/
CodeGeneratorException::~CodeGeneratorException() throw()
{

}

/**
  Retorna a mensagem de erro vinculada à exceção.

  @return
     mensagem de erro vinculada à exceção.
*/
const char* CodeGeneratorException::what() const throw()
{
    return this->errorMessage_.c_str();
}
