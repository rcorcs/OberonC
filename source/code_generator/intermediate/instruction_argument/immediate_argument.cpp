/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "immediate_argument.h"

#include <sstream>
using namespace std;

ImmediateArgument::ImmediateArgument(const long immediateValue)
    : InstructionArgument(INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE)
{
    setImmediateValue(immediateValue);
}

void ImmediateArgument::setImmediateValue(const long immediateValue)
{
    this->immediateValue_ = immediateValue;
}

long ImmediateArgument::getImmediateValue() const
{
    return this->immediateValue_;
}

void ImmediateArgument::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{
    stringstream strValue;

    strValue << immediateValue_;
    codeGeneratorDebugger->debugCode(strValue.str().c_str());
}

void ImmediateArgument::debug(ostream &out)
{
    stringstream strValue;

    strValue << immediateValue_;
    out << strValue.str().c_str();
}
