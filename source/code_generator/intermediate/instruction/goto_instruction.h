/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#ifndef INTERMEDIATE_CODE_GOTO_INSTRUCTION_H
#define INTERMEDIATE_CODE_GOTO_INSTRUCTION_H

#include "instruction.h"

class GotoInstruction : public Instruction
{
public:

    GotoInstruction(LabelArgument *label);

    void setLabelArgument(LabelArgument *label);
    LabelArgument *getLabelArgument() const ;

    vector<ArgumentInformation *> *getArgumentsInformation();

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);
private:

    LabelArgument *label_;
};

#endif


