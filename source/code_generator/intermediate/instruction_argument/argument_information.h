/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef ARGUMENT_INFORMATION_H
#define ARGUMENT_INFORMATION_H

#include "instruction_argument.h"

#define ARGUMENT_INFORMATION_STATUS_UNDEFINED     -999
#define ARGUMENT_INFORMATION_STATUS_NOT_ALIVE     -1
#define ARGUMENT_INFORMATION_STATUS_ALIVE_ON_EXIT -2

class ArgumentInformation
{
public:
    ArgumentInformation();
    ~ArgumentInformation();

    InstructionArgument * getInstructionArgument() const;
    void setInstructionArgument(InstructionArgument * instructionArgument);

    int getStatus() const;
    void setStatus(int status);

    const char * getStatusPrefix() const;

private:

    InstructionArgument * instructionArgument_;
    int status_;
    char statusPrefix_[32];
};

#endif
