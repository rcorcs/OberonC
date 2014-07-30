/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "nop_instruction.h"

NopInstruction::NopInstruction()
    : Instruction(INSTRUCTION_TYPE_NOP)
{}

vector<ArgumentInformation *> *NopInstruction::getArgumentsInformation()
{
    vector<ArgumentInformation *> *args = new vector<ArgumentInformation *>();
    args->push_back(NULL);
    return args;
}

void NopInstruction::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{

    if(getLabel())
    {
        getLabel()->debug(codeGeneratorDebugger);


        codeGeneratorDebugger->debugCode(":");
    }


    codeGeneratorDebugger->debugCode("\tNop ( )\n");
}

void NopInstruction::debug(ostream &out)
{

    if(getLabel())
    {
        getLabel()->debug(out);
        out << ": ";
    }

    out << "Nop ( )";
    out << "\t\t\t ---";
    out << "\t ---";
    out << "\t ---";

    out << endl;
}
