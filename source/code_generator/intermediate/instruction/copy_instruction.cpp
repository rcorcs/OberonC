/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "copy_instruction.h"

CopyInstruction::CopyInstruction(InstructionArgument *src, InstructionArgument *dest)
    : Instruction(INSTRUCTION_TYPE_COPY)
{
    setSourceArgument(src);
    setDestinationArgument(dest);
}

void CopyInstruction::setSourceArgument(InstructionArgument *src)
{
    this->src_.setInstructionArgument( src );
}

InstructionArgument *CopyInstruction::getSourceArgument() const
{
    return this->src_.getInstructionArgument();
}

void CopyInstruction::setDestinationArgument(InstructionArgument *dest)
{
    this->dest_.setInstructionArgument( dest );
}

InstructionArgument *CopyInstruction::getDestinationArgument() const
{
    return this->dest_.getInstructionArgument();
}

vector<ArgumentInformation *> *CopyInstruction::getArgumentsInformation()
{
    vector<ArgumentInformation *> *args = new vector<ArgumentInformation *>();
    args->push_back(&dest_);
    args->push_back(&src_);
    return args;
}

void CopyInstruction::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{

    if(getLabel())
    {
        getLabel()->debug(codeGeneratorDebugger);
        codeGeneratorDebugger->debugCode(":");
    }

    codeGeneratorDebugger->debugCode("\tCopy (");
    src_.getInstructionArgument()->debug(codeGeneratorDebugger);

    codeGeneratorDebugger->debugCode(", ");
    dest_.getInstructionArgument()->debug(codeGeneratorDebugger);

    codeGeneratorDebugger->debugCode(")\n");

}

void CopyInstruction::debug(ostream &out)
{
    if(getLabel())
    {
        getLabel()->debug(out);
        out << ": ";
    }

    out << "Copy (";
    src_.getInstructionArgument()->debug(out);

    out << ", ";
    dest_.getInstructionArgument()->debug(out);

    out << ")";

    out << "\t\t\t " << dest_.getStatusPrefix();
    out << "\t " << src_.getStatusPrefix();
    out << "\t ---";

    out << endl;

}
