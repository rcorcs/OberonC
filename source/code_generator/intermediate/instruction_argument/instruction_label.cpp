/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "instruction_label.h"

#include <sstream>
using namespace std;

InstructionLabel::InstructionLabel(const int labelNumber)
    : LabelArgument(INSTRUCTION_ARGUMENT_TYPE_INSTUCTION_LABEL)
{
    setLabelNumber(labelNumber);
}

void InstructionLabel::setLabelNumber(const int labelNumber)
{
    this->labelNumber_ = labelNumber;
}

int InstructionLabel::getLabelNumber() const
{
    return this->labelNumber_;
}

void InstructionLabel::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{
    stringstream strValue;

    strValue <<  "L" << labelNumber_;
    codeGeneratorDebugger->debugCode(strValue.str().c_str());

}

void InstructionLabel::debug(ostream &out)
{
    stringstream strValue;

    strValue <<  "L" << labelNumber_;
    out << strValue.str().c_str();
}
