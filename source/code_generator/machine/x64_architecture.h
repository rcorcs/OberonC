/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef ARCHITECTURE_X64_H
#define ARCHITECTURE_X64_H

#include "machine_code.h"

#include "register_descriptor.h"
#include "variable_descriptor.h"

#include "../../ast/expression/arithmetic_operator.h"

#include "../intermediate/intermediate_code.h"

#include "../intermediate/instruction/instruction.h"
#include "../intermediate/instruction/arithmetic_instruction.h"
#include "../intermediate/instruction/copy_instruction.h"
#include "../intermediate/instruction/negation_instruction.h"
#include "../intermediate/instruction/write_instruction.h"
#include "../intermediate/instruction/read_instruction.h"
#include "../intermediate/instruction/parameter_instruction.h"
#include "../intermediate/instruction/call_instruction.h"
#include "../intermediate/instruction/nop_instruction.h"
#include "../intermediate/instruction/goto_instruction.h"
#include "../intermediate/instruction/conditional_goto_instruction.h"

#include "../intermediate/instruction_argument/identifier_argument.h"
#include "../intermediate/instruction_argument/label_argument.h"
#include "../intermediate/instruction_argument/instruction_label.h"
#include "../intermediate/instruction_argument/immediate_argument.h"
#include "../intermediate/instruction_argument/instruction_argument.h"
#include "../intermediate/instruction_argument/string_argument.h"
#include "../intermediate/instruction_argument/argument_information.h"



#include "../../symbol_table/symbol_table.h"

#include "../../symbol_table/identifier_category/function_information.h"
#include "../../symbol_table/identifier_category/formal_parameter_information.h"
#include "../../symbol_table/identifier_category/variable_information.h"
#include "../../symbol_table/identifier_information.h"

#include "../../util/integer_hash_table.h"

#include "../../debugger/debugger_utils.h"


#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <fstream>
using namespace std;

#define NO_REGISTER -1

//#ifdef WORD_SIZE
//#undef WORD_SIZE
//#endif
//#define WORD_SIZE 8

class X64Architecture : public MachineCode
{
public:

    static const int WORD_SIZE = 8;

    X64Architecture(SymbolTable * symbolTable, IntermediateCode * intermediateCode);
    void generateCode();

protected:

    //string getVariableAddress(IdentifierArgument *identifierArgument);




    void initDescriptorTables();

private:
    void optmiseArithmeticInstruction(Instruction * instruction);
    void optmiseConditionalInstruction(Instruction * instruction);

    string getMachineString(string str);
    string getMachineString(const char *c_str);
    string getStringLabel(string str);
    string getStringLabel(const char *c_str);

    int getOffset(IdentifierInformation *identifierInformation);
    void genStartingCode();

    string getRegister(int index);
    int getTotalRegisters();

    string getMachineImmediate(long immediate);

    vector<int> *getRegisters(Instruction *instruction); //FAZER AQUI
    int getEmptyRegister(list<int> *avoidList = 0, list<int> *avoidSecondList = 0); //FAZER AQUI

    string getVariableAddress(IdentifierInformation *identifierInformation);
    string getFunctionLabel(IdentifierInformation * functionInfo);
    string getFunctionLabel(const char *functionName);
    string getFunctionLabel(string functionName);

    void genInstruction(Instruction *instruction);

    void genWrite(WriteInstruction *instruction);
    void genRead(ReadInstruction *instruction);

    void genArithmetic(ArithmeticInstruction *instruction);
    void genGoto(GotoInstruction *instruction);
    void genConditionalGoto(ConditionalGotoInstruction *instruction);

    void genNop(NopInstruction *instruction);

    void genLoad(IdentifierInformation *identifierInformation, int registerNumber);
    void genStore(int registerNumber, IdentifierInformation *identifierInformation);

    void genCopy(CopyInstruction *copyInstruction);
    void genNegation(NegationInstruction *negationInstruction);

    string getMachineInstructionLabel(int labelNumber);

    void genLabel(const char *label);
    void genLabel(string label);

    void genWrite(const char *str);
    void genWrite(IdentifierInformation *identifierInformation);
    void genWrite(int registerNumber);
    void genRead(IdentifierInformation *identifierInformation);
    void genMove(long immediate, int reg);
    void genParam(ParameterInstruction * paramInstruction);
    void genCall(CallInstruction * callInstruction);


    //void initDescriptorTables();

    void genPrologue(FunctionInformation * functionInfo);
    void genEpilogue(FunctionInformation * functionInfo);

    void updateVariablesStatus(Instruction * instruction);
    void allocateArithmeticInstructionRegisters(Instruction * instruction,  vector<int> * regs);
    vector<string> registers_;
};

#endif
