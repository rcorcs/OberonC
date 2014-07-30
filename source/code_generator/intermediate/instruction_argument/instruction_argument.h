/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef INTERMEDIATE_CODE_INSTRUCTION_ARGUMENT_H
#define INTERMEDIATE_CODE_INSTRUCTION_ARGUMENT_H

#include "../../../debugger/debugger_interfaces/code_generator_debugger.h"

enum InstructionArgumentType
{
    INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER,
    INSTRUCTION_ARGUMENT_TYPE_IMMEDIATE,
    INSTRUCTION_ARGUMENT_TYPE_LABEL,
    INSTRUCTION_ARGUMENT_TYPE_INSTUCTION_LABEL,
    INSTRUCTION_ARGUMENT_TYPE_FUNCTION_LABEL,
    INSTRUCTION_ARGUMENT_TYPE_TEMPORARY,
    INSTRUCTION_ARGUMENT_TYPE_STRING
};

class InstructionArgument
{

public:

    InstructionArgument(const InstructionArgumentType type);
    virtual ~InstructionArgument();

    virtual void debug(CodeGeneratorDebugger * codeGeneratorDebugger) = 0;
    virtual void debug(ostream &out) = 0;

    const InstructionArgumentType  getType();

private:
    InstructionArgumentType type_;


};

#endif


