/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "variable_descriptor.h"

VariableDescriptor::VariableDescriptor()
{
    this->inMemory_ = false;
    this->alive_ = false;
}

VariableDescriptor::~VariableDescriptor()
{

}

void VariableDescriptor::addRegister(int reg)
{
    bool contains = false;

    for(list<int>::iterator it = this->registersList_.begin(); it != this->registersList_.end(); it++)
    {
        if( (*it) == reg )
        {
            contains = true;
            break;
        }
    }

    if(!contains)
    {
        this->registersList_.push_back(reg);
    }
}

void VariableDescriptor::removeRegister(int reg)
{
    this->registersList_.remove(reg);
}

void VariableDescriptor::removeAllRegisters()
{
    this->registersList_.clear();
}

void VariableDescriptor::addRegisters(list<int> *registers)
{
    for(list<int>::iterator it = registers->begin(); it != registers->end(); it++)
    {
        this->addRegister( (*it) );
    }
}

list<int> * VariableDescriptor::getRegistersList()
{
    return &this->registersList_;
}

void VariableDescriptor::setInMemory(bool inMemory)
{

    this->inMemory_ = inMemory;
}

bool VariableDescriptor::isInMemory() const
{

    return this->inMemory_;
}

void VariableDescriptor::setAlive(bool alive)
{
    this->alive_ = alive;
}

bool VariableDescriptor::isAlive() const
{
    return this->alive_;
}
