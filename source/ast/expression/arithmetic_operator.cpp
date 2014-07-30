/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "arithmetic_operator.h"

const char *getArithmeticOperatorName(ArithmeticOperator op)
{
    const char * arithmeticOperatorName = "Undefined Arithmetic Operator";

    switch(op)
    {

    case ARITHMETIC_OPERATOR_ADD:
        arithmeticOperatorName = "Add";
        break;

    case ARITHMETIC_OPERATOR_SUB:
        arithmeticOperatorName = "Sub";
        break;

    case ARITHMETIC_OPERATOR_MULT:
        arithmeticOperatorName = "Mult";
        break;

    case ARITHMETIC_OPERATOR_DIV:
        arithmeticOperatorName = "Div";
        break;

    case ARITHMETIC_OPERATOR_MOD:
        arithmeticOperatorName = "Mod";
        break;


    default:
        break;

    }

    return arithmeticOperatorName;
}
