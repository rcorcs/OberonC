/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef INTERMEDIATE_CODE_LABEL_ARGUMENT_H
#define INTERMEDIATE_CODE_LABEL_ARGUMENT_H

#include "instruction_argument.h"

#define LABEL_NONE  0
#define LABEL_FALL  -1


class LabelArgument : public InstructionArgument
{
public:

    LabelArgument(const InstructionArgumentType type);
    virtual ~LabelArgument(){};

    virtual void debug(CodeGeneratorDebugger * codeGeneratorDebugger) = 0;
    virtual void debug(ostream &out) = 0;
};

#endif
