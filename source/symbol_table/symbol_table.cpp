/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "symbol_table.h"

/**
  Implementação da classe SymbolTable.
*/

/**
  Construtor padrão.
*/
SymbolTable::SymbolTable()
{

}

/**
  Destrutor da classe.
*/
SymbolTable::~SymbolTable()
{
    list<IdentifierInformation*>::const_iterator it = identifierInfoList_.begin();

    while(it != identifierInfoList_.end())
    {
        // Desaloca objetos de informações (Information) armazenados na Tabela de Símbolos.
        delete (*it);
        it++;
    }

    while(!scopeList_.empty())
    {
        delete removeScope();
    }
}

void SymbolTable::createScope(const char *name)
{
    Scope *scope = new Scope(name);
    scopeList_.push_back(scope);
}

Scope *SymbolTable::removeScope()
{
    Scope *scope = scopeList_.back();
    scopeList_.pop_back();

    return scope;
}


/**
  Insere objeto de informação (Information) na Tabela de Símbolos.

  @param info
     objeto de informação (Information) que será inserido na Tabela de Símbolos.

  @see Information
*/
void SymbolTable::insertAtCurrentScope(IdentifierInformation *identiferInfo)
{
    identiferInfo->setScopeLevel( getScopeCount() );

    identifierInfoList_.push_back(identiferInfo);
    getCurrentScope()->insertIdentifierInfo(identiferInfo);
}

bool SymbolTable::isAtCurrentScope(const char *identifier) const
{
    return ( scopeList_.back()->findInfoByIdentifier( identifier ) != NULL );
}


IdentifierInformation * SymbolTable::lookup(const char *identifier) const
{
    IdentifierInformation *identiferInfo = 0 ;

    for(list<Scope *>::const_reverse_iterator it = scopeList_.rbegin();  it != scopeList_.rend() && !identiferInfo; it++)
    {
        identiferInfo = (*it)->findInfoByIdentifier( identifier );
    }

    return identiferInfo;
}

Scope * SymbolTable::getCurrentScope() const
{
    return scopeList_.back();
}

unsigned int SymbolTable::getScopeCount() const
{
    return scopeList_.size();
}

list <IdentifierInformation *> * SymbolTable::getIdentifierInfoList()
{
    return &this->identifierInfoList_;
}

list <string> * SymbolTable::getStringList() {

    return &this->stringList_;
}
