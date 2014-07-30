/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef CONSTANT_INFORMATION_H
#define CONSTANT_INFORMATION_H

#include "../identifier_information.h"
#include "../data_type.h"

typedef union _ConstantValue_
{
    long intValue;
    bool boolValue;

} ConstantValue;

class ConstantInformation: public IdentifierInformation
{

public:

    ConstantInformation();
    ConstantInformation(const char *identifier);

    DataType getType() const;
    void setType(const DataType type);

    ConstantValue getValue() const;
    void setValue(ConstantValue constantValue);

    void debug(SymbolTableDebugger *symbolTableDebugger);

private:

    DataType type_;
    ConstantValue constantValue_;
};

#endif
