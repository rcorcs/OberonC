/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "negation_instruction.h"

NegationInstruction::NegationInstruction(InstructionArgument *src, InstructionArgument *dest)
    : Instruction(INSTRUCTION_TYPE_NEGATION)
{
    setSourceArgument(src);
    setDestinationArgument(dest);
}

void NegationInstruction::setSourceArgument(InstructionArgument *src)
{
    this->src_.setInstructionArgument( src );
}

InstructionArgument *NegationInstruction::getSourceArgument() const
{
    return this->src_.getInstructionArgument();
}

void NegationInstruction::setDestinationArgument(InstructionArgument *dest)
{
    this->dest_.setInstructionArgument( dest );
}

InstructionArgument *NegationInstruction::getDestinationArgument() const
{
    return this->dest_.getInstructionArgument();
}

vector<ArgumentInformation *> *NegationInstruction::getArgumentsInformation()
{
    vector<ArgumentInformation *> *args = new vector<ArgumentInformation *>();
    args->push_back(&dest_);
    args->push_back(&src_);
    return args;
}

void NegationInstruction::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{

    if(getLabel())
    {
        getLabel()->debug(codeGeneratorDebugger);
        codeGeneratorDebugger->debugCode(":");
    }


    codeGeneratorDebugger->debugCode("\tNeg (");
    src_.getInstructionArgument()->debug(codeGeneratorDebugger);

    codeGeneratorDebugger->debugCode(", ");
    dest_.getInstructionArgument()->debug(codeGeneratorDebugger);

    codeGeneratorDebugger->debugCode(")\n");

}


void NegationInstruction::debug(ostream &out)
{

    if(getLabel())
    {
        getLabel()->debug(out);
        out << ": ";
    }


    out << "\tNeg (";
    src_.getInstructionArgument()->debug(out);

    out << ", ";
    dest_.getInstructionArgument()->debug(out);

    out << ")";

    out << "\t\t\t " << dest_.getStatusPrefix();
    out << "\t " << src_.getStatusPrefix();
    out << "\t ---";



}
