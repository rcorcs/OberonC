/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "scanner_exception.h"

/**
  Implementação da classe ScannerException.
*/


/**
  Construtor padrão - inicializa atributo relativo à mensagem de erro vinculada à exceção.

  @param
     errorMessage - mensagem de erro vinculada à exceção.
*/
ScannerException::ScannerException(string errorMessage = "") throw()
{
    this->errorMessage_ = errorMessage;
}

/**
  Destrutor da classe.
*/
ScannerException::~ScannerException() throw()
{

}

/**
  Retorna a mensagem de erro vinculada à exceção.

  @return
     mensagem de erro vinculada à exceção.
*/
const char* ScannerException::what() const throw()
{
    return this->errorMessage_.c_str();
}
