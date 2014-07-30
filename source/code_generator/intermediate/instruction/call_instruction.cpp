/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "call_instruction.h"

CallInstruction::CallInstruction(InstructionArgument *firstArg, InstructionArgument *secondArg, InstructionArgument *dest)
    : Instruction(INSTRUCTION_TYPE_CALL)
{
    setFirstArgument(firstArg);
    setSecondArgument(secondArg);
    setDestinationArgument(dest);
}

void CallInstruction::setFirstArgument(InstructionArgument *firstArg)
{
    this->firstArg_.setInstructionArgument( firstArg );
}

InstructionArgument *CallInstruction::getFirstArgument() const
{
    return this->firstArg_.getInstructionArgument();
}

void CallInstruction::setSecondArgument(InstructionArgument *secondArg)
{
    this->secondArg_.setInstructionArgument( secondArg );
}

InstructionArgument *CallInstruction::getSecondArgument() const
{
    return this->secondArg_.getInstructionArgument();
}

void CallInstruction::setDestinationArgument(InstructionArgument *dest)
{
    this->dest_.setInstructionArgument( dest );
}

InstructionArgument *CallInstruction::getDestinationArgument() const
{
    return this->dest_.getInstructionArgument();
}

vector<ArgumentInformation *> *CallInstruction::getArgumentsInformation()
{
    vector<ArgumentInformation *> *args = new vector<ArgumentInformation *>();
    if(dest_.getInstructionArgument())
        args->push_back(&dest_);
    else args->push_back(NULL);



    return args;
}

void CallInstruction::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{

    if(getLabel())
    {
        getLabel()->debug(codeGeneratorDebugger);
        codeGeneratorDebugger->debugCode(":");
    }

    codeGeneratorDebugger->debugCode("\tCall(");
    firstArg_.getInstructionArgument()->debug(codeGeneratorDebugger);

    codeGeneratorDebugger->debugCode(", ");
    secondArg_.getInstructionArgument()->debug(codeGeneratorDebugger);

    if(dest_.getInstructionArgument())
    {
        codeGeneratorDebugger->debugCode(", ");
        dest_.getInstructionArgument()->debug(codeGeneratorDebugger);
    }

    codeGeneratorDebugger->debugCode(")\n");
}

void CallInstruction::debug(ostream &out)
{
    if(getLabel())
    {
        getLabel()->debug(out);
        out << ": ";
    }

    out << "Call(";
    firstArg_.getInstructionArgument()->debug(out);

    out << ", ";
    secondArg_.getInstructionArgument()->debug(out);

    if(dest_.getInstructionArgument())
    {
        out << ", ";
        dest_.getInstructionArgument()->debug(out);
    }

    out << ")";


    if(dest_.getInstructionArgument())
        out << "\t\t\t " << dest_.getStatusPrefix();
    else
        out << "\t\t\t ---";


    out << "\t ---";
    out << "\t ---";

    out << endl;
}
