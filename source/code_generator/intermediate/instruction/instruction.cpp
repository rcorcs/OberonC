/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "instruction.h"

Instruction::Instruction(InstructionType type)
    : instructionType_(type), label_(0), isDeadCode_(0)
{
}

void Instruction::setInstructionType(const InstructionType type)
{
    this->instructionType_ = type;
}

InstructionType Instruction::getInstructionType() const
{
    return this->instructionType_;
}

void Instruction::setLabel(LabelArgument *label)
{
    this->label_ = label;
}

LabelArgument *Instruction::getLabel()
{
    return this->label_;
}

void Instruction::setDeadCode(bool isDead)
{
    isDeadCode_ = isDead;
}

bool Instruction::isDeadCode()
{
    return isDeadCode_;
}
