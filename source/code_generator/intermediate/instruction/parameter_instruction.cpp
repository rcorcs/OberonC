/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "parameter_instruction.h"

ParameterInstruction::ParameterInstruction(InstructionArgument *src)
    : Instruction(INSTRUCTION_TYPE_PARAMETER)
{
    setSourceArgument(src);
}

void ParameterInstruction::setSourceArgument(InstructionArgument *src)
{
    this->src_.setInstructionArgument( src );
}

InstructionArgument *ParameterInstruction::getSourceArgument() const
{
    return this->src_.getInstructionArgument();
}

vector<ArgumentInformation *> *ParameterInstruction::getArgumentsInformation()
{
    vector<ArgumentInformation *> *args = new vector<ArgumentInformation *>();
    args->push_back(NULL);
    args->push_back(&src_);
    return args;
}

void ParameterInstruction::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{

    if(getLabel())
    {
        getLabel()->debug(codeGeneratorDebugger);
        codeGeneratorDebugger->debugCode(":");
    }

    codeGeneratorDebugger->debugCode("\tParam (");
    this->src_.getInstructionArgument()->debug(codeGeneratorDebugger);
    codeGeneratorDebugger->debugCode(")\n");
}

void ParameterInstruction::debug(ostream &out)
{

    if(getLabel())
    {
        getLabel()->debug(out);
        out << ": ";
    }

    out << "\aram (";
    this->src_.getInstructionArgument()->debug(out);
    out << ")";


        out << "\t\t\t ---";

        if(this->src_.getInstructionArgument())
        out << "\t" << src_.getStatusPrefix();
    else
        out << "\t ---";

    out << "\t ---";
        out << endl;

}
