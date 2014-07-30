/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef CODE_GENERATOR_DEBUGGER_H
#define CODE_GENERATOR_DEBUGGER_H

#include "../debugger.h"

class CodeGeneratorDebugger: public Debugger
{

public:

    virtual void debugCode(const char *code) = 0;

};

#endif
