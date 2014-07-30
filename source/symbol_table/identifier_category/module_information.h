/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef MODULE_INFORMATION_H
#define MODULE_INFORMATION_H

#include "../identifier_information.h"

#include "variable_information.h"
#include "function_information.h"

class ModuleInformation: public IdentifierInformation
{

public:

    ModuleInformation();
    ModuleInformation(const char *identifier);

    void debug(SymbolTableDebugger *symbolTableDebugger);

};
#endif
