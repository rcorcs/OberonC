/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SEMANTIC_DEBUGGER_H
#define SEMANTIC_DEBUGGER_H

#include "../debugger.h"

class SemanticDebugger: public Debugger
{

public:

    virtual void debugTypeMismatchError(const char *where,
                                        const char* expectedType,
                                        const char * actualType,
                                        int firstLine) = 0;


    virtual void debugExpectedBooleanExpressionError(const char *where,
            int firstLine) = 0;

    virtual void debugExpectedIntegerExpressionError(const char *where,
            int firstLine) = 0;

    virtual void debugExpectedNonConstIntegerIdentifierError(const char *where,
            int firstLine) = 0;

    virtual void debugUnexpectedConstantIdentifierError(const char *where,
            int firstLine) = 0;


    virtual void debugUnreachableStatementError(int firstLine) = 0;



    virtual void debugBreakOutOfRepetitionError(int firstLine) = 0;

    virtual void debugContinueOutOfRepetitionError(int firstLine) = 0;

    virtual void debugReturnOutOfFunctionError(int firstLine) = 0;


    virtual void  debugMissingReturnError(const char * functionIdentifier,
                                          const char* expectedReturnType,
                                          int firstLine) = 0;

    virtual void  debugReturnInProcedureError(int firstLine) = 0;



    virtual void debugIncorrectArgumentNumberError(const char *functionIdentifier,
            const char * formalParametersTypes, const char *returnType,
            int firstLine) = 0;

    virtual void debugFunctionArgumentMismatchError(const char *functionIdentifier,
            int paramNum,
            const char* expectedType,
            const char* actualType,
            const char *returnType,
            int firstLine) = 0;

    void setErrorCounter(int errorCounter)
    {
        errorCounter_ = errorCounter;
    }
    int getErrorCounter()
    {
        return errorCounter_;
    }

protected:

    int errorCounter_;

};

#endif

