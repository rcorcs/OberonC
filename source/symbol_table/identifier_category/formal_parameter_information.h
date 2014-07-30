/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef FORMAL_PARAMETER_INFORMATION_H
#define FORMAL_PARAMETER_INFORMATION_H

#include "../identifier_information.h"
#include "../data_type.h"

class FormalParameterInformation: public IdentifierInformation
{

public:

    FormalParameterInformation();
    FormalParameterInformation(const char *identifier);

    DataType getType() const;
    void setType(DataType type);

    void setOffset(int offset);
    int getOffset();

    void debug(SymbolTableDebugger *symbolTableDebugger);

private:
    int offset_;
    DataType type_;
};

#endif
