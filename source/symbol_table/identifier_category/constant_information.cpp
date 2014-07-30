/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "constant_information.h"
#include <sstream>


ConstantInformation::ConstantInformation()
{
    this->setCategoryType(IDENTIFIER_CATEGORY_TYPE_CONSTANT);
}

ConstantInformation::ConstantInformation(const char *identifier)
    : IdentifierInformation(IDENTIFIER_CATEGORY_TYPE_CONSTANT, identifier)
{
    this->type_ = DATA_TYPE_UNDEFINED;
}

void ConstantInformation::setType(const DataType type)
{
    this->type_ = type;
}

DataType ConstantInformation::getType() const
{
    return this->type_;

}

ConstantValue ConstantInformation::getValue() const
{
    return this->constantValue_;
}

void ConstantInformation::setValue(ConstantValue constantValue)
{
    this->constantValue_ = constantValue;
}


void ConstantInformation::debug(SymbolTableDebugger *symbolTableDebugger)
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
