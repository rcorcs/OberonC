/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "formal_parameter_information.h"
#include <sstream>

FormalParameterInformation::FormalParameterInformation()
{
    this->setCategoryType(IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER);
}

FormalParameterInformation::FormalParameterInformation(const char *identifier)
    : IdentifierInformation(IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER, identifier)
{
    this->type_ = DATA_TYPE_UNDEFINED;
}

void FormalParameterInformation::setType(DataType type)
{
    this->type_ = type;
}

DataType FormalParameterInformation::getType() const
{
    return this->type_;
}

void FormalParameterInformation::setOffset(int offset)
{
    this->offset_ = offset;
}

int FormalParameterInformation::getOffset()
{
    return this->offset_;
}

void FormalParameterInformation::debug(SymbolTableDebugger *symbolTableDebugger)
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
