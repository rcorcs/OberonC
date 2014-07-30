/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef FUNCTION_INFORMATION_H
#define FUNCTION_INFORMATION_H

#include "../identifier_information.h"
#include "../data_type.h"
#include "formal_parameter_information.h"
#include "variable_information.h"

#include <list>
using namespace std;

class FunctionInformation: public IdentifierInformation
{

public:

    FunctionInformation();
    FunctionInformation(const char *identifier);

    DataType getReturnType() const;
    void setReturnType(DataType returnType);

    list<FormalParameterInformation *> & getFormalParameterList();
    list<VariableInformation *> & getVariableList();

    void debug(SymbolTableDebugger *symbolTableDebugger);

private:

    list<FormalParameterInformation *> formalParameterList_;
    list<VariableInformation *> variableList_;

    DataType returnType_;
};

#endif
