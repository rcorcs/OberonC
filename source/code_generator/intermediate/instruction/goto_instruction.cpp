/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "goto_instruction.h"

GotoInstruction::GotoInstruction(LabelArgument *label)
    : Instruction(INSTRUCTION_TYPE_GOTO)
{
    setLabelArgument(label);
}

void GotoInstruction::setLabelArgument(LabelArgument *label)
{
    this->label_ = label;
}

LabelArgument *GotoInstruction::getLabelArgument() const
{
    return this->label_;
}

vector<ArgumentInformation *> *GotoInstruction::getArgumentsInformation()
{
    vector<ArgumentInformation *> *args = new vector<ArgumentInformation *>();
    args->push_back(NULL);
    return args;
}

void GotoInstruction::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{
    if(getLabel())
    {
        getLabel()->debug(codeGeneratorDebugger);
        codeGeneratorDebugger->debugCode(":");
    }

    codeGeneratorDebugger->debugCode("\tGoto (");
    this->label_->debug(codeGeneratorDebugger);

    codeGeneratorDebugger->debugCode(")\n");

}

void GotoInstruction::debug(ostream &out)
{
    if(getLabel())
    {
        getLabel()->debug(out);
        out << ": ";
    }

    out << "Goto (";
    this->label_->debug(out);

    out << ")";

     out << "\t\t\t ---";
    out << "\t ---";
    out << "\t ---";

}
