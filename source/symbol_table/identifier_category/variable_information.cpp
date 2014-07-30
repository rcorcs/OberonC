/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "variable_information.h"
#include <sstream>

VariableInformation::VariableInformation()
{
    this->setCategoryType(IDENTIFIER_CATEGORY_TYPE_VARIABLE);
}

VariableInformation::VariableInformation(const char *identifier)
    : IdentifierInformation(IDENTIFIER_CATEGORY_TYPE_VARIABLE, identifier)
{
    this->type_ = DATA_TYPE_UNDEFINED;
}

void VariableInformation::setType(const DataType type)
{
    this->type_ = type;
}

void VariableInformation::setOffset(int offset)
{
    this->offset_ = offset;
}

int VariableInformation::getOffset()
{
    return this->offset_;
}

DataType VariableInformation::getType() const
{
    return this->type_;

}

void VariableInformation::debug(SymbolTableDebugger *symbolTableDebugger)
{
    const char *categoryTypeName = getIdentifierCategoryTypeName( this->getCategoryType() );
    const char *typeName = getDataTypeName( this->getType() );

    stringstream scopeLevelStr;
    scopeLevelStr << this->getScopeLevel();

    symbolTableDebugger->debugIdentifierInfo(categoryTypeName);
    symbolTableDebugger->debugIdentifierInfoAttribute("Identifier", this->getIdentifier());
    symbolTableDebugger->debugIdentifierInfoAttribute("Type", typeName);
    symbolTableDebugger->debugIdentifierInfoAttribute("Scope Level", scopeLevelStr.str().c_str());

    symbolTableDebugger->newLine();


}
