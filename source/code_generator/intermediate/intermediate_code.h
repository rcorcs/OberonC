/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

#include <cstring>

#include <vector>
#include <list>
using std::list;
using std::vector;

#include "../../util/hash_table.h"
#include "../../symbol_table/symbol_table.h"

#include "instruction/instruction.h"
#include "instruction_argument/label_argument.h"
#include "instruction_argument/instruction_label.h"
#include "instruction_argument/temporary_argument.h"


#include "../machine/basic_block.h"

class IntermediateCode
{
public:
    IntermediateCode(SymbolTable * symbolTable);
    ~IntermediateCode();

    //void addInstruction(Instruction *instruction, bool usingPendingLabel=true);
    void addInstruction(const char *functionName, Instruction *instruction, bool usingPendingLabel=true);
    void addInstruction(vector<Instruction *> *instructionVector, Instruction *instruction, bool usingPendingLabel=true);

    void setPendingLabelNumber(int pendingLabelNumber);
    int getPendingLabelNumber();
    int usePendingLabelNumber();

    int getNextLabelNumber();

    TemporaryArgument * getNextTemporary();


    vector<BasicBlock *> *getBasicBlocks();

    void setMainFunctionName(const char *functionName);
    const char *getMainFunctionName();
    vector<Instruction *> *addInstructionVector(const char *functionName);
    vector<Instruction *> *getInstructionVector(const char *functionName);
    vector<const char *> *getFunctionNames();
    list<TemporaryArgument*> * getGeneratedRegisterList();

    void addInstructionArgumentToCleanUpList(InstructionArgument * argument);
    void debug(CodeGeneratorDebugger * codeGeneratorDebugger);

private:

    SymbolTable * symbolTable_;

    HashTable<vector<Instruction *> *> *functionHashTable_;
    vector<const char *> functionNames_;
    list<InstructionArgument*> cleanUpArgumentList_;
    const char *mainFunctionName_;

    int pendingLabelNumber_;
    int nextLabelNumber_;
    int nextTemporaryNumber_;
};

#endif
