/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#ifndef INTERMEDIATE_CODE_ARITHMETIC_INSTRUCTION_H
#define INTERMEDIATE_CODE_ARITHMETIC_INSTRUCTION_H

#include "../../../ast/expression/arithmetic_operator.h"
#include "instruction.h"


class ArithmeticInstruction: public Instruction
{
public:

    ArithmeticInstruction(ArithmeticOperator op, InstructionArgument *firstArg, InstructionArgument *secondArg, InstructionArgument *dest);

    void setArithmeticOperator(ArithmeticOperator op);
    ArithmeticOperator getArithmeticOperator();

    void setFirstArgument(InstructionArgument *firstArg);
    InstructionArgument *getFirstArgument() const ;

    void setSecondArgument(InstructionArgument *secondArg);
    InstructionArgument *getSecondArgument() const ;

    void setDestinationArgument(InstructionArgument *dest);
    InstructionArgument *getDestinationArgument() const ;

    vector<ArgumentInformation *> *getArgumentsInformation();

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);
private:

    ArithmeticOperator arithmeticOperator_;
    ArgumentInformation firstArg_;
    ArgumentInformation secondArg_;
    ArgumentInformation dest_;
    //InstructionArgument *firstArg_;
    //InstructionArgument *secondArg_;
    //InstructionArgument *dest_;
};

#endif


