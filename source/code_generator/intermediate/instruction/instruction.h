/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef INTERMEDIATE_CODE_INSTRUCTION_H
#define INTERMEDIATE_CODE_INSTRUCTION_H

#include <vector>
using std::vector;

#include "../instruction_argument/instruction_argument.h"
#include "../instruction_argument/label_argument.h"
#include "../instruction_argument/argument_information.h"

#include "../../../debugger/debugger_interfaces/code_generator_debugger.h"


enum InstructionType
{
    INSTRUCTION_TYPE_NOP,

    INSTRUCTION_TYPE_ARITHMETIC,
    //INSTRUCTION_TYPE_ADD,
    //INSTRUCTION_TYPE_SUB,
    //INSTRUCTION_TYPE_MULT,
    //INSTRUCTION_TYPE_DIV,
    //INSTRUCTION_TYPE_MOD,

    INSTRUCTION_TYPE_NEGATION,

    INSTRUCTION_TYPE_COPY,

    INSTRUCTION_TYPE_GOTO,

    INSTRUCTION_TYPE_CONDITIONAL_GOTO,
    //INSTRUCTION_TYPE_GOTO_IF_EQUALS,
    //INSTRUCTION_TYPE_GOTO_IF_NOT_EQUALS,
    //INSTRUCTION_TYPE_GOTO_IF_LESS,
    //INSTRUCTION_TYPE_GOTO_IF_GREATER,
    //INSTRUCTION_TYPE_GOTO_IF_LESS_OR_EQUALS,
    //INSTRUCTION_TYPE_GOTO_IF_GREATER_OR_EQUALS,

    //param x
    INSTRUCTION_TYPE_PARAMETER,

    // write x, read x
    INSTRUCTION_TYPE_WRITE,
    INSTRUCTION_TYPE_READ,

    /** TODO */

    //call p n, y = call p n
    INSTRUCTION_TYPE_CALL,

    INSTRUCTION_TYPE_RETURN,

    //´pointers: x = &y, x = *y, *x = y
    INSTRUCTION_TYPE_COPY_REFERENCE,
    INSTRUCTION_TYPE_COPY_FROM_DEREFERENCE,
    INSTRUCTION_TYPE_COPY_TO_DEREFERENCE,

    // x = y[i], x[i] = y
    INSTRUCTION_TYPE_COPY_FROM_INDEXED_VALUE,
    INSTRUCTION_TYPE_COPY_TO_INDEXED_VALUE

};

class Instruction
{

public:

    Instruction(InstructionType type);

    void setInstructionType(const InstructionType type);
    InstructionType getInstructionType() const ;

    void setLabel(LabelArgument *label);
    LabelArgument *getLabel();

    void setDeadCode(bool isDead);
    bool isDeadCode();

    virtual vector<ArgumentInformation *> *getArgumentsInformation() = 0;

    virtual void debug(CodeGeneratorDebugger * codeGeneratorDebugger) = 0;
    virtual void debug(ostream &out) = 0;
private:
    bool isDeadCode_;

    InstructionType instructionType_;
    LabelArgument *label_;
};

#endif


