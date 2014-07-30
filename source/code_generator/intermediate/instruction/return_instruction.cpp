/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "return_instruction.h"


ReturnInstruction::ReturnInstruction(InstructionArgument *src)
    : Instruction(INSTRUCTION_TYPE_RETURN)
{
    setSourceArgument(src);
}

void ReturnInstruction::setSourceArgument(InstructionArgument *src)
{
    this->src_.setInstructionArgument( src );
}

InstructionArgument *ReturnInstruction::getSourceArgument() const
{
    return this->src_.getInstructionArgument();
}

vector<ArgumentInformation *> *ReturnInstruction::getArgumentsInformation()
{
    vector<ArgumentInformation *> *args = new vector<ArgumentInformation *>();
    args->push_back(NULL);
    if(src_.getInstructionArgument())
        args->push_back(&src_);
    else args->push_back(NULL);
    return args;
}

void ReturnInstruction::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{
    if(getLabel())
    {
        getLabel()->debug(codeGeneratorDebugger);
        codeGeneratorDebugger->debugCode(":");
    }


    codeGeneratorDebugger->debugCode("\tReturn (");

    if(this->src_.getInstructionArgument())
    {
        this->src_.getInstructionArgument()->debug(codeGeneratorDebugger);
    }
    else
    {
        codeGeneratorDebugger->debugCode(" ");
    }

    codeGeneratorDebugger->debugCode(")\n");

}

void ReturnInstruction::debug(ostream &out)
{
    if(getLabel())
    {
        getLabel()->debug(out);
        out << ": ";
    }


    out << "Return (";

    if(this->src_.getInstructionArgument())
    {
        this->src_.getInstructionArgument()->debug(out);
    }
    else
    {
        out << " ";
    }

    out << ")";


    out << "\t\t\t ---";

    if(this->src_.getInstructionArgument())
        out << "\t" << src_.getStatusPrefix();
    else
        out << "\t ---";


    out << "\t ---";
    out << endl;
}
