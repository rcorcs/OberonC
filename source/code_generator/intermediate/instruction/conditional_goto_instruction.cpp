/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "conditional_goto_instruction.h"

ConditionalGotoInstruction::ConditionalGotoInstruction(RelationalOperator op, InstructionArgument *firstArg, InstructionArgument *secondArg, LabelArgument *label)
    : Instruction(INSTRUCTION_TYPE_CONDITIONAL_GOTO)
{
    setRelationalOperator(op);
    setFirstArgument(firstArg);
    setSecondArgument(secondArg);
    setLabelArgument(label);
}

void ConditionalGotoInstruction::setRelationalOperator(RelationalOperator op)
{
    this->relationalOperator_ = op;
}

RelationalOperator ConditionalGotoInstruction::getRelationalOperator()
{
    return this->relationalOperator_;
}

void ConditionalGotoInstruction::setFirstArgument(InstructionArgument *firstArg)
{
    this->firstArg_.setInstructionArgument( firstArg );
}

InstructionArgument *ConditionalGotoInstruction::getFirstArgument() const
{
    return this->firstArg_.getInstructionArgument();
}

void ConditionalGotoInstruction::setSecondArgument(InstructionArgument *secondArg)
{
    this->secondArg_.setInstructionArgument( secondArg );
}

InstructionArgument *ConditionalGotoInstruction::getSecondArgument() const
{
    return this->secondArg_.getInstructionArgument();
}

void ConditionalGotoInstruction::setLabelArgument(LabelArgument *label)
{
    this->label_ = label;
}

LabelArgument *ConditionalGotoInstruction::getLabelArgument() const
{
    return this->label_;
}

vector<ArgumentInformation *> *ConditionalGotoInstruction::getArgumentsInformation()
{
    vector<ArgumentInformation *> *args = new vector<ArgumentInformation *>();
    args->push_back(NULL);
    args->push_back(&firstArg_);
    args->push_back(&secondArg_);
    return args;
}

void ConditionalGotoInstruction::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{

    if(getLabel())
    {
        getLabel()->debug(codeGeneratorDebugger);
        codeGeneratorDebugger->debugCode(":");
    }

    codeGeneratorDebugger->debugCode("\tIf (");
    firstArg_.getInstructionArgument()->debug(codeGeneratorDebugger);

    codeGeneratorDebugger->debugCode(" ");

    const char * op = "{NO OP}";

    switch(this->relationalOperator_)
    {
    case RELATIONAL_OPERATOR_LESS:
        op = "<";
        break;

    case RELATIONAL_OPERATOR_GREATER:
        op = ">";
        break;

    case RELATIONAL_OPERATOR_LESS_OR_EQUAL:
        op = "<=";
        break;

    case RELATIONAL_OPERATOR_GREATER_OR_EQUAL:
        op = ">=";
        break;

    case RELATIONAL_OPERATOR_EQUAL:
        op = "==";
        break;

    case RELATIONAL_OPERATOR_DIFFERENT:
        op = "!=";
        break;


    default:
        break;
    }

    codeGeneratorDebugger->debugCode(op);
    codeGeneratorDebugger->debugCode(" ");;
    this->secondArg_.getInstructionArgument()->debug(codeGeneratorDebugger);

    codeGeneratorDebugger->debugCode(") Goto ");
    this->label_->debug(codeGeneratorDebugger);
    codeGeneratorDebugger->debugCode("\n");

}

void ConditionalGotoInstruction::debug(ostream &out)
{

    if(getLabel())
    {
        getLabel()->debug(out);
        out << ": ";
    }

    out << "If (";
    firstArg_.getInstructionArgument()->debug(out);

    out << " ";

    const char * op = "{NO OP}";

    switch(this->relationalOperator_)
    {
    case RELATIONAL_OPERATOR_LESS:
        op = "<";
        break;

    case RELATIONAL_OPERATOR_GREATER:
        op = ">";
        break;

    case RELATIONAL_OPERATOR_LESS_OR_EQUAL:
        op = "<=";
        break;

    case RELATIONAL_OPERATOR_GREATER_OR_EQUAL:
        op = ">=";
        break;

    case RELATIONAL_OPERATOR_EQUAL:
        op = "==";
        break;

    case RELATIONAL_OPERATOR_DIFFERENT:
        op = "!=";
        break;


    default:
        break;
    }

    out << op;
    out << " ";
    this->secondArg_.getInstructionArgument()->debug(out);

    out << ") Goto ";
    this->label_->debug(out);


    out << "\t\t ---";

    out << "\t " << firstArg_.getStatusPrefix();
    out << "\t " << secondArg_.getStatusPrefix();

    out << endl;


}
