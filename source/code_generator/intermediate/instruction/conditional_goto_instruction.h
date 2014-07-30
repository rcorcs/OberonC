/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#ifndef INTERMEDIATE_CODE_CONDITIONAL_GOTO_INSTRUCTION_H
#define INTERMEDIATE_CODE_CONDITIONAL_GOTO_INSTRUCTION_H

#include "../../../ast/expression/relational_operator.h"
#include "instruction.h"

class ConditionalGotoInstruction : public Instruction
{
public:

    ConditionalGotoInstruction(RelationalOperator op, InstructionArgument *firstArg, InstructionArgument *secondArg, LabelArgument *label);

    void setRelationalOperator(RelationalOperator op);
    RelationalOperator getRelationalOperator();

    void setFirstArgument(InstructionArgument *firstArg);
    InstructionArgument *getFirstArgument() const ;

    void setSecondArgument(InstructionArgument *secondArg);
    InstructionArgument *getSecondArgument() const ;

    void setLabelArgument(LabelArgument *label);
    LabelArgument *getLabelArgument() const ;

    vector<ArgumentInformation *> *getArgumentsInformation();

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);

private:

    RelationalOperator relationalOperator_;
    ArgumentInformation firstArg_;
    ArgumentInformation secondArg_;
    LabelArgument *label_;
};

#endif


