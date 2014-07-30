/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef MACHINE_CODE_H
#define MACHINE_CODE_H

#include "../../symbol_table/symbol_table.h"
#include "../../symbol_table/identifier_information.h"

#include "../intermediate/intermediate_code.h"
#include "../intermediate/instruction_argument/identifier_argument.h"

#include "register_descriptor.h"
#include "variable_descriptor.h"


#include "../../util/integer_hash_table.h"

enum MachineCodeType {
    MACHINE_CODE_X64,
    MACHINE_CODE_X86
};

class MachineCode
{
public:
    MachineCode(SymbolTable * symbolTable, IntermediateCode * intermediateCode);
    ~MachineCode();

    void open(const char *baseFile);
    void close();

    virtual void generateCode() = 0;

    VariableDescriptor * getVariableDescriptor(IdentifierInformation * identifierInformation);
    RegisterDescriptor * getRegisterDescriptor(int registerNumber);


protected:

    //virtual string getVariableAddress(IdentifierArgument *identifierArgument) = 0;
    //virtual string getRegister(int index) = 0;
	//virtual int getTotalRegisters() = 0;
    void gen(const char *instruction);
    void gen(string instruction);

    const char *baseFileName_;
    char *assemblyFileName_;

    SymbolTable * symbolTable_;
    IntermediateCode * intermediateCode_;

    virtual void initDescriptorTables() = 0;

    IdentifierInformation * getInfoFromArgument(InstructionArgument* instructionArgument);

    IntegerHashTable<VariableDescriptor*> variableDescriptorTable_;
    IntegerHashTable<RegisterDescriptor*> registerDescriptorTable_;

private:

    void initVariableStatus();

    IntegerHashTable<int> * getNewStatusAuxTable();

    ofstream assemblyFile_;
};
#endif
