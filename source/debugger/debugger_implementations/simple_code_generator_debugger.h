/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SIMPLE_CODE_GENERATOR_DEBUGGER_H
#define SIMPLE_CODE_GENERATOR_DEBUGGER_H

#include "../debugger_interfaces/code_generator_debugger.h"


class SimpleCodeGeneratorDebugger: public CodeGeneratorDebugger
{

public:

    SimpleCodeGeneratorDebugger();

    void debugCode(const char *code);

protected:

    void createDebugFile(const char *baseFileName);

};

#endif
