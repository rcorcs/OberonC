/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "read_instruction.h"

ReadInstruction::ReadInstruction(InstructionArgument *dest)
    : Instruction(INSTRUCTION_TYPE_READ)
{
    setDestinationArgument(dest);
}

void ReadInstruction::setDestinationArgument(InstructionArgument *dest)
{
    this->dest_.setInstructionArgument( dest );
}

InstructionArgument *ReadInstruction::getDestinationArgument() const
{
    return this->dest_.getInstructionArgument();
}

vector<ArgumentInformation *> *ReadInstruction::getArgumentsInformation()
{
    vector<ArgumentInformation *> *args = new vector<ArgumentInformation *>();
    args->push_back(&dest_);
    return args;
}

void ReadInstruction::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{

    if(getLabel())
    {
        getLabel()->debug(codeGeneratorDebugger);
        codeGeneratorDebugger->debugCode(":");
    }


    codeGeneratorDebugger->debugCode("\tRead (");

    if(this->dest_.getInstructionArgument())
    {
        this->dest_.getInstructionArgument()->debug(codeGeneratorDebugger);
    }

    codeGeneratorDebugger->debugCode(")\n");

}

void ReadInstruction::debug(ostream &out)
{

    if(getLabel())
    {
        getLabel()->debug(out);
        out << ": ";
    }


    out << "Read (";

    if(this->dest_.getInstructionArgument())
    {
        this->dest_.getInstructionArgument()->debug(out);
    }

    out << ")";

    if(this->dest_.getInstructionArgument())
    {
        out << "\t\t\t " << this->dest_.getStatusPrefix();
        out << "\t ---";
        out << "\t ---";
    }
    else
    {
        out << "\t\t\t ---";
        out << "\t ---";
        out << "\t ---";
    }

    out  << endl;

}
