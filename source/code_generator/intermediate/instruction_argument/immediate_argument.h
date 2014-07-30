/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef INTERMEDIATE_CODE_IMMEDIATE_ARGUMENT_H
#define INTERMEDIATE_CODE_IMMEDIATE_ARGUMENT_H

#include "instruction_argument.h"

class ImmediateArgument : public InstructionArgument
{

public:

    ImmediateArgument(const long immediateValue);

    void setImmediateValue(const long immediateValue);
    long getImmediateValue() const;

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);
private:

    long immediateValue_;
};

#endif
