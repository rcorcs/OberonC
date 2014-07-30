/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#ifndef INTERMEDIATE_CODE_NOP_INSTRUCTION_H
#define INTERMEDIATE_CODE_NOP_INSTRUCTION_H

#include "instruction.h"

class NopInstruction : public Instruction
{

public:

    NopInstruction();

    vector<ArgumentInformation *> *getArgumentsInformation();

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);


};

#endif


