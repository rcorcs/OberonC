/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SIMPLE_SEMANTIC_DEBUGGER_H
#define SIMPLE_SEMANTIC_DEBUGGER_H

#include "../debugger_interfaces/semantic_debugger.h"


class SimpleSemanticDebugger: public SemanticDebugger
{

public:

    SimpleSemanticDebugger();

    void debugTypeMismatchError(const char *where, const char* expectedType, const char * actualType, int firstLine);

    void debugExpectedBooleanExpressionError(const char *where, int firstLine);
    void debugExpectedIntegerExpressionError(const char *where, int firstLine);

    void debugExpectedNonConstIntegerIdentifierError(const char *where, int firstLine);
    void debugUnexpectedConstantIdentifierError(const char *where, int firstLine);

    void debugUnreachableStatementError(int firstLine);

    void debugBreakOutOfRepetitionError(int firstLine);
    void debugContinueOutOfRepetitionError(int firstLine);
    void debugReturnOutOfFunctionError(int firstLine);


    void  debugMissingReturnError(const char * functionIdentifier, const char* expectedReturnType, int firstLine);
    void  debugReturnInProcedureError(int firstLine);

    void debugIncorrectArgumentNumberError(const char *functionIdentifier, const char * formalParametersTypes, const char *returnType, int firstLine);
    void debugFunctionArgumentMismatchError(const char *functionIdentifier, int paramNum, const char* expectedType, const char* actualType, const char *returnType, int firstLine);


protected:

    void createDebugFile(const char *baseFileName);

};

#endif
