/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "scope.h"

Scope::Scope(const char *name)
{
    this->name_ = new char[strlen(name)+1];
    strcpy(this->name_, name);

    this->identifierInfoMap_ = new HashTable<IdentifierInformation *>(SCOPE_HASH_TABLE_SIZE);
}

Scope::~Scope()
{
    delete [] this->name_;
    delete this->identifierInfoMap_;
}

const char *Scope::getName() const
{
    return name_;
}

void Scope::setName(const char *name)
{
    if(name)
    {
        delete [] name_;

        name_ = new char[strlen(name)+1];
        strcpy(name_, name);
    }
}


void Scope::insertIdentifierInfo(IdentifierInformation *identifierInfo)
{
    this->identifierInfoMap_->set(identifierInfo->getIdentifier(), identifierInfo);
    this->orderedInsertedInfo_.push_back(identifierInfo);
}

IdentifierInformation *Scope::findInfoByIdentifier(const char *identifier)
{
    IdentifierInformation * identifierInfo = 0;

    if(identifierInfoMap_->contains(identifier))
    {
        identifierInfo = identifierInfoMap_->get(identifier);
    }

    return identifierInfo;
}

void Scope::debug(SymbolTableDebugger *symbolTableDebugger)
{

    list<IdentifierInformation *>::iterator it;

    symbolTableDebugger->debugScopeStart( this->getName() );

    for(it = this->orderedInsertedInfo_.begin(); it != this->orderedInsertedInfo_.end(); it++)
    {
        (*it)->debug(symbolTableDebugger);
    }

    symbolTableDebugger->debugScopeEnd();

}
