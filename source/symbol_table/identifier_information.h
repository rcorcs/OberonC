/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef IDENTIFIER_INFORMATION_H
#define IDENTIFIER_INFORMATION_H

#include "identifier_category/identifier_category_type.h"

#include "../debugger/debugger_interfaces/symbol_table_debugger.h"

/**

  Classe base que representa informações sobre identificadores encontrados em um programa
  durante a fase de parsing. Atributos comuns a qualquer tipo específico de informação
  sobre identificadores incluem o identificador (string) em si, sua respectiva categoria
  e nível de escopo em o mesmo é declarado/utilizado.

*/
class IdentifierInformation
{

public:

    // Construtores/Destrutor.
    IdentifierInformation();
    IdentifierInformation(IdentifierCategoryType categoryType, const char *identifier);
    virtual ~IdentifierInformation();

    // Getters/setters.
    IdentifierCategoryType getCategoryType() const;
    void setCategoryType(IdentifierCategoryType categoryType);

    const char *getIdentifier() const;
    void setIdentifier(const char *identifier);

    unsigned int getScopeLevel() const;
    void setScopeLevel(const unsigned int scopeLevel);

    // Método abstrato para fins de debug.
    virtual void debug(SymbolTableDebugger *symbolTableDebugger) = 0;

private:

    IdentifierCategoryType categoryType_;
    char *identifier_;
    unsigned int scopeLevel_;
};

#endif
