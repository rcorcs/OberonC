/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef TEMPORARY_INFORMATION_H
#define TEMPORARY_INFORMATION_H

#include "../identifier_information.h"
#include "../data_type.h"

class TemporaryInformation: public IdentifierInformation
{

public:

    TemporaryInformation();
    TemporaryInformation(int number);


    int getNumber() const;
    void setNumber(int number);

    void debug(SymbolTableDebugger *symbolTableDebugger);

private:

    int number_;
};

#endif
