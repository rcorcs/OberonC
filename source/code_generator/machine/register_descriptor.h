/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef REGISTER_DESCRIPTOR_H
#define REGISTER_DESCRIPTOR_H

#include "../intermediate/instruction_argument/temporary_argument.h"
#include "../intermediate/instruction_argument/identifier_argument.h"
#include "../../util/integer_hash_table.h"

#include <iostream>
#include <list>
using std::list;

class RegisterDescriptor
{
public:

    RegisterDescriptor();
    ~RegisterDescriptor();

    void addVariable(IdentifierInformation *variableInfo);
    void addVariables(list<IdentifierInformation *> *variableInfoList);

    void removeVariable(IdentifierInformation *variableInfo);
    void removeAllVariables();

    list<IdentifierInformation*> *getVariablesList();

private:

    list<IdentifierInformation *> identifierInfoList_;

};

#endif
