/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef INTERMEDIATE_CODE_STRING_ARGUMENT_H
#define INTERMEDIATE_CODE_STRING_ARGUMENT_H

#include "instruction_argument.h"

class StringArgument : public InstructionArgument
{

public:

    StringArgument(const char *stringValue);
    ~StringArgument();

    void setStringValue(const char *stringValue);
    char *getStringValue() const;

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);
private:

    char *stringValue_;
};

#endif

