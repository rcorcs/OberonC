/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SCANNER_EXCEPTION_H
#define SCANNER_EXCEPTION_H

#include <string>
#include <exception>
using namespace std;

/**
   Definição da classe ScannerException.

   Esta classe é utilizada para identificar exceções geradas pelo Scanner ao
   manipular um arquivo de código fonte.
*/
class ScannerException : public exception
{

public:

    // Construtor/destrutor.
    ScannerException(string errorMessage) throw();
    ~ScannerException() throw();

    // Causa da exceção.
    const char* what() const throw();

private:

    string errorMessage_;
};

#endif
