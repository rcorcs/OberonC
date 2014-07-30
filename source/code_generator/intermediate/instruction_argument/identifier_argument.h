/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef INTERMEDIATE_CODE_IDENTIFIER_ARGUMENT_H
#define INTERMEDIATE_CODE_IDENTIFIER_ARGUMENT_H

#include "instruction_argument.h"
#include "../../../symbol_table/identifier_information.h"

class IdentifierArgument : public InstructionArgument
{

public:

    IdentifierArgument(IdentifierInformation *information);

    void setIdentifierInformation(IdentifierInformation *information);
    IdentifierInformation *getIdentifierInformation();

    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);
    void debug(ostream &out);
private:

    IdentifierInformation *information_;
};

#endif
