/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef VARIABLE_DESCRIPTOR_H
#define VARIABLE_DESCRIPTOR_H

#include "../intermediate/instruction_argument/identifier_argument.h"
#include "../intermediate/instruction_argument/temporary_argument.h"
#include "../../util/integer_hash_table.h"

#include <iostream>
#include <list>
using std::list;

class VariableDescriptor
{
public:

    VariableDescriptor();
    ~VariableDescriptor();

    void addRegister(int reg);
    void addRegisters(list<int> * registers);

    void removeRegister(int reg);
    void removeAllRegisters();

    list<int> *getRegistersList();

    void setInMemory(bool inMemory);
    bool isInMemory() const;

    void setAlive(bool alive);
    bool isAlive() const;

private:

    list<int> registersList_;
    bool inMemory_;
    bool alive_;

};

#endif
