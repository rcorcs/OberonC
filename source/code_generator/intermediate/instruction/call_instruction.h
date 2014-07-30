/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#ifndef INTERMEDIATE_CODE_CALL_INSTRUCTION_H
#define INTERMEDIATE_CODE_CALL_INSTRUCTION_H

#include "instruction.h"

class CallInstruction: public Instruction
{
public:
    CallInstruction(InstructionArgument *firstArg, InstructionArgument *secondArg, InstructionArgument *dest=NULL);

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
    ArgumentInformation firstArg_;
    ArgumentInformation secondArg_;
    ArgumentInformation dest_;
};

#endif


