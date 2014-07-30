/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "identifier_category_type.h"

const char *getIdentifierCategoryTypeName(IdentifierCategoryType categoryType)
{
    const char * categoryTypeName = 0;

    switch(categoryType)
    {

    case IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER:
        categoryTypeName = "Formal Parameter";
        break;

    case IDENTIFIER_CATEGORY_TYPE_FUNCTION:
        categoryTypeName = "Function";
        break;

    case IDENTIFIER_CATEGORY_TYPE_MODULE:
        categoryTypeName = "Module";
        break;

    case IDENTIFIER_CATEGORY_TYPE_PROCEDURE:
        categoryTypeName = "Procedure";
        break;

    case IDENTIFIER_CATEGORY_TYPE_UNDEFINED:
        categoryTypeName = "Undefined";
        break;

    case IDENTIFIER_CATEGORY_TYPE_CONSTANT:
        categoryTypeName = "Constant";
        break;

    case IDENTIFIER_CATEGORY_TYPE_VARIABLE:
        categoryTypeName = "Variable";
        break;


    case IDENTIFIER_CATEGORY_TYPE_TEMPORARY:
        categoryTypeName = "Temporary";
        break;
    }

    return categoryTypeName;
}
