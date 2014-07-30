/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "data_type.h"

const char *getDataTypeName(DataType DataType)
{
    const char * typeName = 0;

    switch(DataType)
    {

    case DATA_TYPE_UNDEFINED:
        typeName = "Undefined Type";
        break;

    case DATA_TYPE_ERROR:
        typeName = "Invalid Type";
        break;

    case DATA_TYPE_BOOLEAN:
        typeName = "Boolean";
        break;

    case DATA_TYPE_INTEGER:
        typeName = "Integer";
        break;

    case DATA_TYPE_VOID:
        typeName = "Void";
        break;

    case DATA_TYPE_STRING:
        typeName = "String";
        break;

    }

    return typeName;
}
