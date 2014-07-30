/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "module_information.h"
#include <sstream>

ModuleInformation::ModuleInformation()
{

    this->setCategoryType(IDENTIFIER_CATEGORY_TYPE_MODULE);
}

ModuleInformation::ModuleInformation(const char *identifier)
    : IdentifierInformation(IDENTIFIER_CATEGORY_TYPE_MODULE, identifier)
{

}

void ModuleInformation::debug(SymbolTableDebugger *symbolTableDebugger)
{
    const char *categoryTypeName = getIdentifierCategoryTypeName( this->getCategoryType() );

    stringstream scopeLevelStr;
    scopeLevelStr << this->getScopeLevel();

    symbolTableDebugger->debugIdentifierInfo(categoryTypeName);
    symbolTableDebugger->debugIdentifierInfoAttribute("Identifier", this->getIdentifier());
    symbolTableDebugger->debugIdentifierInfoAttribute("Scope Level", scopeLevelStr.str().c_str());

    symbolTableDebugger->newLine();

}
