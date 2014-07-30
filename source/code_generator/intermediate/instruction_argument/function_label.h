/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef INTERMEDIATE_CODE_FUNCTION_LABEL_ARGUMENT_H
#define INTERMEDIATE_CODE_FUNCTION_LABEL_ARGUMENT_H

#include "instruction_argument.h"
#include "label_argument.h"

class FunctionLabel : public LabelArgument
{
public:

    FunctionLabel(const char *labelString);
    ~FunctionLabel();
    void setLabelString(const char *labelString);
    char *getLabelString() const;

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);
private:

    char *labelString_;
};

#endif


