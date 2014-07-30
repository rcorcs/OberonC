/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "write_instruction.h"

WriteInstruction::WriteInstruction(InstructionArgument *src)
    : Instruction(INSTRUCTION_TYPE_WRITE)
{
    setSourceArgument(src);
}

void WriteInstruction::setSourceArgument(InstructionArgument *src)
{
    this->src_.setInstructionArgument( src );
}

InstructionArgument *WriteInstruction::getSourceArgument() const
{
    return this->src_.getInstructionArgument();
}

vector<ArgumentInformation *> *WriteInstruction::getArgumentsInformation()
{
    vector<ArgumentInformation *> *args = new vector<ArgumentInformation *>();
    args->push_back(NULL);
    args->push_back(&src_);
    return args;
}

void WriteInstruction::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{
    if(getLabel())
    {
        getLabel()->debug(codeGeneratorDebugger);
        codeGeneratorDebugger->debugCode(":");
    }


    codeGeneratorDebugger->debugCode("\tWrite (");

    if(this->src_.getInstructionArgument())
    {
        this->src_.getInstructionArgument()->debug(codeGeneratorDebugger);
    }

    codeGeneratorDebugger->debugCode(")\n");
}

void WriteInstruction::debug(ostream &out)
{

    if(getLabel())
    {
        getLabel()->debug(out);
        out << ": ";
    }


    out << "Write (";

    if(this->src_.getInstructionArgument())
    {
        this->src_.getInstructionArgument()->debug(out);
    }

    out << ")";

    if(this->src_.getInstructionArgument())
        out << "\t\t\t " << src_.getStatusPrefix();
    else
        out << "\t\t\t ---";

    out << "\t ---";
    out << "\t ---";

    out << endl;
}
