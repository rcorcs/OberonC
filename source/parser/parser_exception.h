/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef PARSER_EXCEPTION_H
#define PARSER_EXCEPTION_H

#include <string>
#include <exception>
using namespace std;

/**
   Definição da classe ParserException.

   Esta classe é utilizada para identificar exceções geradas pelo Parser ao
   manipular um arquivo de código.
*/
class ParserException : public exception
{

public:

    // Construtor/destrutor.
    ParserException(string errorMessage = "") throw();
    ~ParserException() throw();

    // Causa da exceção.
    const char* what() const throw();

private:

    string errorMessage_;
};

#endif
