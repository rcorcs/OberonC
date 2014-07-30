/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "temporary_argument.h"
#include <sstream>
using namespace std;

TemporaryArgument::TemporaryArgument(TemporaryInformation * temporaryInformation)
    : InstructionArgument(INSTRUCTION_ARGUMENT_TYPE_TEMPORARY)
{
    this->temporaryInformation_ = temporaryInformation;
}

void TemporaryArgument::setNumber(const int number)
{
    this->temporaryInformation_->setNumber(number);
}

int TemporaryArgument::getNumber() const
{
    return this->temporaryInformation_->getNumber();
}

TemporaryInformation *TemporaryArgument::getTemporaryInformation() const
{

    return this->temporaryInformation_;
}

void TemporaryArgument::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{
    stringstream strValue;

    strValue <<  "%reg" << this->getNumber();
    codeGeneratorDebugger->debugCode(strValue.str().c_str());
}

void TemporaryArgument::debug(ostream &out)
{
    stringstream strValue;

    strValue <<  "%reg" << this->getNumber();
    out << strValue.str().c_str();
}
