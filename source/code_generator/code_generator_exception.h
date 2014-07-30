/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef CODE_GENERATOR_EXCEPTION_H
#define CODE_GENERATOR_EXCEPTION_H

#include <string>
#include <exception>
using namespace std;

/**
   Definição da classe CodeGeneratorException.

   Esta classe é utilizada para identificar exceções geradas pelo Gerador de Código.
*/
class CodeGeneratorException : public exception
{

public:

    // Construtor/destrutor.
    CodeGeneratorException(string errorMessage = "") throw();
    ~CodeGeneratorException() throw();

    // Causa da exceção.
    const char* what() const throw();

private:

    string errorMessage_;
};

#endif
