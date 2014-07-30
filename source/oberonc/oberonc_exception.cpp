/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "oberonc_exception.h"

/**
  Implementação da classe de exceções para o Oberon-0 Compiler.
*/

/**
  Construtor padrão - inicializa atributo relativo à mensagem de erro vinculada à exceção.

  @param
     errorMessage - mensagem de erro vinculada à exceção.
*/
OberonC_Exception::OberonC_Exception(string errorMessage) throw()
{
    this->errorMessage_ = errorMessage;
}

/**
  Destrutor da classe.
*/
OberonC_Exception::~OberonC_Exception() throw()
{

}

/**
  Retorna a mensagem de erro vinculada à exceção.

  @return
     mensagem de erro vinculada à exceção.
*/
const char* OberonC_Exception::what() const throw()
{
    return this->errorMessage_.c_str();
}
