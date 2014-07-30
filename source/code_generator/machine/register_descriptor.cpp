/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "register_descriptor.h"

RegisterDescriptor::RegisterDescriptor()
{

}

RegisterDescriptor::~RegisterDescriptor()
{

}

void RegisterDescriptor::addVariable(IdentifierInformation *variableInfo)
{
    bool contains = false;

    for(list<IdentifierInformation*>::iterator it = this->identifierInfoList_.begin(); it != this->identifierInfoList_.end(); it++)
    {
        if( (*it) == variableInfo )
        {
            contains = true;
            break;
        }
    }

    if(!contains)
    {
        this->identifierInfoList_.push_back(variableInfo);
    }

}



void RegisterDescriptor::removeVariable(IdentifierInformation *variableInfo)
{
 this->identifierInfoList_.remove(variableInfo);
}

void RegisterDescriptor::removeAllVariables()
{
    this->identifierInfoList_.clear();
}

void RegisterDescriptor::addVariables(list<IdentifierInformation *> *variableInfoList)
{
    for(list<IdentifierInformation*>::iterator it = variableInfoList->begin(); it != variableInfoList->end(); it++)
    {
        this->addVariable( (*it) );
    }
}

list<IdentifierInformation*> * RegisterDescriptor::getVariablesList()
{
    return &this->identifierInfoList_;
}



