/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#ifndef INTERMEDIATE_CODE_NEGATION_INSTRUCTION_H
#define INTERMEDIATE_CODE_NEGATION_INSTRUCTION_H

#include "instruction.h"

class NegationInstruction : public Instruction
{
public:

    NegationInstruction(InstructionArgument *src, InstructionArgument *dest);

    void setSourceArgument(InstructionArgument *src);
    InstructionArgument *getSourceArgument() const ;

    void setDestinationArgument(InstructionArgument *dest);
    InstructionArgument *getDestinationArgument() const ;

    vector<ArgumentInformation *> *getArgumentsInformation();

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);
private:

    ArgumentInformation src_;
    ArgumentInformation dest_;
};

#endif


