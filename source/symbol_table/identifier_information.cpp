/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "identifier_information.h"
#include <cstring>

IdentifierInformation::IdentifierInformation()
{
    this->categoryType_ = IDENTIFIER_CATEGORY_TYPE_UNDEFINED;
    this->identifier_ = NULL;
    this->scopeLevel_ = -1;
}

IdentifierInformation::IdentifierInformation(IdentifierCategoryType categoryType, const char *identifier)
{
    this->categoryType_ = categoryType;

    this->identifier_ = new char[strlen(identifier) + 1];
    strcpy(this->identifier_, identifier);
}

IdentifierInformation::~IdentifierInformation()
{
    delete [] this->identifier_;
}

IdentifierCategoryType IdentifierInformation::getCategoryType() const
{
    return this->categoryType_;
}

void IdentifierInformation::setCategoryType(IdentifierCategoryType categoryType)
{
    this->categoryType_ = categoryType;
}

const char *IdentifierInformation::getIdentifier() const
{
    return this->identifier_;
}

void IdentifierInformation::setIdentifier(const char *identifier)
{
    delete [] this->identifier_;

    this->identifier_ = new char[strlen(identifier) + 1];
    strcpy(this->identifier_, identifier);
}

unsigned int IdentifierInformation::getScopeLevel() const
{
    return this->scopeLevel_;
}

void IdentifierInformation::setScopeLevel(const unsigned int scopeLevel)
{
    this->scopeLevel_ = scopeLevel;
}
