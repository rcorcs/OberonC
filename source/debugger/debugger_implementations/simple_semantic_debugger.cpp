/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "simple_semantic_debugger.h"

#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;

SimpleSemanticDebugger::SimpleSemanticDebugger()
{
    errorCounter_ = 0;
}

void SimpleSemanticDebugger::createDebugFile(const char *baseFileName)
{
    // Este debugger não salva saída em arquivos.
}



void SimpleSemanticDebugger::debugTypeMismatchError(const char *where, const char *expectedType, const char* actualType, int firstLine)
{
    errorCounter_++;
    cout << firstLine << ": type mismatch in '" << where << "'. Expected " << expectedType << " instead of " << actualType << endl;
}



void SimpleSemanticDebugger::debugExpectedBooleanExpressionError(const char *where, int firstLine)
{
    errorCounter_++;
    cout << firstLine << ": expected a boolean expression for '" << where << "'." << endl;
}

void SimpleSemanticDebugger::debugExpectedIntegerExpressionError(const char *where, int firstLine)
{
    errorCounter_++;
    cout << firstLine << ": expected an integer expression for '" << where << "'." << endl;
}



void SimpleSemanticDebugger::debugUnexpectedConstantIdentifierError(const char *where, int firstLine)
{
    errorCounter_++;
    cout << firstLine << ": unexpected constant identifier for '" << where << "'." << endl;
}

void SimpleSemanticDebugger::debugExpectedNonConstIntegerIdentifierError(const char *where, int firstLine)
{
    errorCounter_++;
    cout << firstLine << ": expected an integer non-constant identifier for '" << where  << "'." << endl;
}


void SimpleSemanticDebugger::debugUnreachableStatementError(int firstLine)
{
    errorCounter_++;
    cout << firstLine << ": unreachable statement found after sequencer." << endl;
}


void SimpleSemanticDebugger::debugBreakOutOfRepetitionError(int firstLine)
{
    errorCounter_++;
    cout << firstLine << ": break out of repetition scope." << endl;
}

void SimpleSemanticDebugger::debugContinueOutOfRepetitionError(int firstLine)
{
    errorCounter_++;
    cout << firstLine << ": continue out of repetition scope." << endl;
}

void SimpleSemanticDebugger::debugReturnOutOfFunctionError(int firstLine)
{
    errorCounter_++;
    cout << firstLine << ": return out of function scope." << endl;
}



void  SimpleSemanticDebugger::debugMissingReturnError(const char *functionIdentifier, const char *expectedReturnType, int firstLine)
{
    errorCounter_++;
    cout << firstLine << ": missing a return of " << expectedReturnType << " type for function '" << functionIdentifier << "'." << endl;
}

void  SimpleSemanticDebugger::debugReturnInProcedureError(int firstLine)
{
    errorCounter_++;
    cout << firstLine << ": illegal return found in procedure." << endl;
}


void SimpleSemanticDebugger::debugIncorrectArgumentNumberError(const char *functionIdentifier, const char *formalParametersTypes,  const char *returnType, int firstLine)
{
    errorCounter_++;
    if(returnType != NULL)
    {
        cout <<
             firstLine << ": incorrect number of arguments calling the function'" <<
             functionIdentifier << "(" << formalParametersTypes << "): " <<
             returnType << "'." << endl;
    }
    else
    {

        cout <<
             firstLine << ": incorrect number of arguments calling the procedure'" <<
             functionIdentifier << "(" << formalParametersTypes << ")'." << endl;

    }

}

void SimpleSemanticDebugger::debugFunctionArgumentMismatchError(const char *functionIdentifier, int paramNum, const char* expectedType, const char* actualType, const char* returnType, int firstLine)
{
    errorCounter_++;
    if(returnType != NULL)
    {

        cout << firstLine << ": Type mismatch while calling the function '" << functionIdentifier
             << "'. Incorrect type provided for parameter of number " << paramNum
             << ". Expected " << expectedType << " instead of " << actualType <<
             "." << endl;
    }
    else
    {

        cout << firstLine << ": Type mismatch while calling the procedure '" << functionIdentifier
             << "'. Incorrect type provided for parameter of number " << paramNum
             << ". Expected " << expectedType << " instead of " << actualType <<
             "." << endl;

    }
}
