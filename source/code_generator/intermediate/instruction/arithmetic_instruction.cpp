/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "arithmetic_instruction.h"

ArithmeticInstruction::ArithmeticInstruction(ArithmeticOperator op, InstructionArgument *firstArg, InstructionArgument *secondArg, InstructionArgument *dest)
    : Instruction(INSTRUCTION_TYPE_ARITHMETIC)
{
    setArithmeticOperator(op);
    setFirstArgument(firstArg);
    setSecondArgument(secondArg);
    setDestinationArgument(dest);
}

void ArithmeticInstruction::setArithmeticOperator(ArithmeticOperator op)
{
    this->arithmeticOperator_ = op;
}

ArithmeticOperator ArithmeticInstruction::getArithmeticOperator()
{
    return this->arithmeticOperator_;
}

void ArithmeticInstruction::setFirstArgument(InstructionArgument *firstArg)
{
    this->firstArg_.setInstructionArgument( firstArg );
}

InstructionArgument *ArithmeticInstruction::getFirstArgument() const
{
    return this->firstArg_.getInstructionArgument( );
}

void ArithmeticInstruction::setSecondArgument(InstructionArgument *secondArg)
{
    this->secondArg_.setInstructionArgument( secondArg );
}

InstructionArgument *ArithmeticInstruction::getSecondArgument() const
{
    return this->secondArg_.getInstructionArgument( );
}

void ArithmeticInstruction::setDestinationArgument(InstructionArgument *dest)
{
    this->dest_.setInstructionArgument( dest );
}

InstructionArgument *ArithmeticInstruction::getDestinationArgument() const
{
    return this->dest_.getInstructionArgument( );
}

vector<ArgumentInformation *> *ArithmeticInstruction::getArgumentsInformation()
{
    vector<ArgumentInformation *> *args = new vector<ArgumentInformation *>();
    args->push_back(&dest_);
    args->push_back(&firstArg_);
    args->push_back(&secondArg_);
    return args;
}

void ArithmeticInstruction::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{
    const char * opName = getArithmeticOperatorName(this->arithmeticOperator_);

    if(getLabel())
    {
        getLabel()->debug(codeGeneratorDebugger);
        codeGeneratorDebugger->debugCode(":");
    }

    codeGeneratorDebugger->debugCode("\t");
    codeGeneratorDebugger->debugCode(opName);
    codeGeneratorDebugger->debugCode(" (");
    firstArg_.getInstructionArgument()->debug(codeGeneratorDebugger);

    codeGeneratorDebugger->debugCode(", ");
    secondArg_.getInstructionArgument()->debug(codeGeneratorDebugger);

    codeGeneratorDebugger->debugCode(", ");
    dest_.getInstructionArgument()->debug(codeGeneratorDebugger);

    codeGeneratorDebugger->debugCode(")\n");
}

void ArithmeticInstruction::debug(ostream &out)
{
    const char * opName = getArithmeticOperatorName(this->arithmeticOperator_);

    if(getLabel())
    {
        getLabel()->debug(out);
        out << ": ";
    }


    out << opName;
    out << " (";
    firstArg_.getInstructionArgument()->debug(out);

    out << ", ";
    secondArg_.getInstructionArgument()->debug(out);

    out << ", ";

    dest_.getInstructionArgument()->debug(out);

    out << ")";

    out << "\t\t " << dest_.getStatusPrefix();
    out << "\t " << firstArg_.getStatusPrefix();
    out << "\t " << secondArg_.getStatusPrefix();

    out << endl;

}
