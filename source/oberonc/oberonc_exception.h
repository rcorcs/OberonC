/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef OBERONC_EXCEPTION_H
#define OBERONC_EXCEPTION_H

#include <string>
#include <exception>

using namespace std;

/**
  Definição da classe OberonC_Exception.

  Esta classe é utilizada para identificar exceções lançadas pela classe principal
  do Oberon-0 Compiler.

  @see OberonC
*/
class OberonC_Exception : public exception
{

public:

    // Construtor/destrutor.
    OberonC_Exception(string errorMessage = "") throw();
    ~OberonC_Exception() throw();

    // Causa da exceção.
    const char* what() const throw();

private:

    string errorMessage_;
};

#endif
