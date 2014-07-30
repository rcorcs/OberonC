/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#ifndef INTERMEDIATE_CODE_WRITE_INSTRUCTION_H
#define INTERMEDIATE_CODE_WRITE_INSTRUCTION_H

#include "instruction.h"

class WriteInstruction : public Instruction
{

public:

    WriteInstruction(InstructionArgument *src);

    void setSourceArgument(InstructionArgument *src);
    InstructionArgument *getSourceArgument() const ;

    vector<ArgumentInformation *> *getArgumentsInformation();

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);
private:

    ArgumentInformation src_;
};

#endif


