/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "function_information.h"
#include <sstream>

FunctionInformation::FunctionInformation()
{
    this->setCategoryType(IDENTIFIER_CATEGORY_TYPE_FUNCTION);
}

FunctionInformation::FunctionInformation(const char *identifier)
    : IdentifierInformation(IDENTIFIER_CATEGORY_TYPE_FUNCTION, identifier)
{
    this->returnType_ = DATA_TYPE_UNDEFINED;

}

DataType FunctionInformation::getReturnType() const
{
    return this->returnType_;
}

void FunctionInformation::setReturnType(DataType returnType)
{
    this->returnType_ = returnType;
}

list<FormalParameterInformation *> & FunctionInformation::getFormalParameterList()
{
    return this->formalParameterList_;
}

list<VariableInformation *> & FunctionInformation::getVariableList()
{
    return this->variableList_;
}

void FunctionInformation::debug(SymbolTableDebugger *symbolTableDebugger)
{
    const char *categoryTypeName = getIdentifierCategoryTypeName( this->getCategoryType() );
    const char *returnTypeName = getDataTypeName( this->getReturnType() );

    stringstream scopeLevelStr;
    scopeLevelStr << this->getScopeLevel();

    symbolTableDebugger->debugIdentifierInfo(categoryTypeName);
    symbolTableDebugger->debugIdentifierInfoAttribute("Identifier", this->getIdentifier());
    symbolTableDebugger->debugIdentifierInfoAttribute("Return Type", returnTypeName);
    symbolTableDebugger->debugIdentifierInfoAttribute("Scope Level", scopeLevelStr.str().c_str());

    symbolTableDebugger->newLine();

    list<FormalParameterInformation*>::iterator it = getFormalParameterList().begin();

    while(it != getFormalParameterList().end())
    {
        IdentifierInformation *identifierInfo = (IdentifierInformation*)(*it);

        identifierInfo->debug(symbolTableDebugger);
        it++;
    }

    symbolTableDebugger->newLine();
}

