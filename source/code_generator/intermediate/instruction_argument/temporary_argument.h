/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef INTERMEDIATE_CODE_TEMPORARY_ARGUMENT_H
#define INTERMEDIATE_CODE_TEMPORARY_ARGUMENT_H

#include "instruction_argument.h"
#include "../../../symbol_table/identifier_category/temporary_information.h"

class TemporaryArgument : public InstructionArgument
{

public:

    TemporaryArgument(TemporaryInformation * temporaryInformation);

    void setNumber(const int number);
    int getNumber() const;

 TemporaryInformation *getTemporaryInformation() const;

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);

private:

    TemporaryInformation * temporaryInformation_;
};

#endif
