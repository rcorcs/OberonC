/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#ifndef INTERMEDIATE_CODE_READ_INSTRUCTION_H
#define INTERMEDIATE_CODE_READ_INSTRUCTION_H

#include "instruction.h"

class ReadInstruction : public Instruction
{

public:

    ReadInstruction(InstructionArgument *dest);

    void setDestinationArgument(InstructionArgument *dest);
    InstructionArgument *getDestinationArgument() const ;

    vector<ArgumentInformation *> *getArgumentsInformation();

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);
private:

    ArgumentInformation dest_;
};

#endif


