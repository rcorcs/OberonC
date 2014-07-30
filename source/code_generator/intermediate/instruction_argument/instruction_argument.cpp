/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "instruction_argument.h"

InstructionArgument::InstructionArgument(const InstructionArgumentType type)
{
    this->type_ = type;
}

InstructionArgument::~InstructionArgument()
{

}


const InstructionArgumentType  InstructionArgument::getType()
{

    return this->type_;
}
