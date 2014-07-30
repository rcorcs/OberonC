/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SCOPE_H
#define SCOPE_H

#include "identifier_information.h"
#include "../debugger/debugger_interfaces/symbol_table_debugger.h"
#include "../util/hash_table.h"

#include <list>
using namespace std;

#define SCOPE_HASH_TABLE_SIZE 127

/**
  Definição da classe utilizada para representar um escopo de um programa.
*/
class Scope
{

public:

    Scope(const char *name);
    ~Scope();

    const char *getName() const;
    void setName(const char *name);

    void insertIdentifierInfo(IdentifierInformation *identifierInfo);
    IdentifierInformation *findInfoByIdentifier(const char *identifier);


    void debug(SymbolTableDebugger *symbolTableDebugger);

private:
    char *name_;

    HashTable <IdentifierInformation *> *identifierInfoMap_;
    list<IdentifierInformation *> orderedInsertedInfo_;
};

#endif
