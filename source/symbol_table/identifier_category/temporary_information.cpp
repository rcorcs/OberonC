/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "temporary_information.h"
#include <sstream>

TemporaryInformation::TemporaryInformation()
{
    this->setCategoryType(IDENTIFIER_CATEGORY_TYPE_TEMPORARY);
    this->number_ = -1;
}

TemporaryInformation::TemporaryInformation(int number)
{
    this->setCategoryType(IDENTIFIER_CATEGORY_TYPE_TEMPORARY);
    this->number_ = number;

}

int TemporaryInformation::getNumber() const
{
    return this->number_;
}


void TemporaryInformation::setNumber(int number)
{
    this->number_ = number;
}

void TemporaryInformation::debug(SymbolTableDebugger *symbolTableDebugger)
{
    // Debug não aplicável a esta classe uma vez em que objetos da mesma são
    // instanciados após a análise de escopos do programa.
}
