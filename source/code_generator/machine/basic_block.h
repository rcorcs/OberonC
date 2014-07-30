/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef MACHINE_CODE_BASIC_BLOCK_H
#define MACHINE_CODE_BASIC_BLOCK_H

#include <iostream>
#include <vector>
using std::vector;

#include "../intermediate/instruction/instruction.h"
#include "../intermediate/instruction_argument/argument_information.h"

class BasicBlock
{
public:
    BasicBlock(vector<Instruction *>::iterator begin, vector<Instruction *>::iterator end);
    BasicBlock();
    void setBeginIterator(vector<Instruction *>::iterator begin);
    void setEndIterator(vector<Instruction *>::iterator end);

    vector<Instruction *>::iterator getBeginIterator();
    vector<Instruction *>::iterator getEndIterator();

    vector<Instruction*> * getInstructionVector();

    void setFunctionName(const char *functionName);
    const char *getFunctionName();

    void setStartingFunction(bool isStarting);
    bool isStartingFunction();

    void setLastFunctionBlock(bool isLast);
    bool isLastFunctionBlock();

    void optimise();

    void debug(ostream &out);



private:
    const char *functionName_;
    bool isStartingFunction_;
    bool isLastFunctionBlock_;
    vector<Instruction *>::iterator begin_;
    vector<Instruction *>::iterator end_;
};

#endif
