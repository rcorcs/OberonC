/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef INTERMEDIATE_CODE_INSTRUCTION_LABEL_ARGUMENT_H
#define INTERMEDIATE_CODE_INSTRUCTION_LABEL_ARGUMENT_H


#include "instruction_argument.h"
#include "label_argument.h"

class InstructionLabel : public LabelArgument
{

public:

    InstructionLabel(const int labelNumber);

    void setLabelNumber(const int labelNumber);
    int getLabelNumber() const;

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);
private:

    int labelNumber_;
};

#endif

