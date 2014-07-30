/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef VARIABLE_INFORMATION_H
#define VARIABLE_INFORMATION_H

#include "../identifier_information.h"
#include "../data_type.h"

class VariableInformation: public IdentifierInformation
{

public:

    VariableInformation();
    VariableInformation(const char *identifier);

    DataType getType() const;
    void setType(const DataType type);

    void setOffset(int offset);
    int getOffset();

    void debug(SymbolTableDebugger *symbolTableDebugger);

private:
    int offset_;
    DataType type_;
};

#endif
