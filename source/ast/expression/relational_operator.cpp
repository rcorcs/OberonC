/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "relational_operator.h"

RelationalOperator invertRelationalOperator(RelationalOperator op)
{

    switch(op)
    {
    case RELATIONAL_OPERATOR_LESS: /* <  >= */
        return RELATIONAL_OPERATOR_GREATER_OR_EQUAL;
        break;

    case RELATIONAL_OPERATOR_GREATER: /* >  <= */
        return RELATIONAL_OPERATOR_LESS_OR_EQUAL;
        break;

    case RELATIONAL_OPERATOR_LESS_OR_EQUAL: /* <=  > */
        return RELATIONAL_OPERATOR_GREATER;
        break;

    case RELATIONAL_OPERATOR_GREATER_OR_EQUAL: /* >=  < */
        return RELATIONAL_OPERATOR_LESS;
        break;

    case RELATIONAL_OPERATOR_EQUAL: /* =  != */
        return RELATIONAL_OPERATOR_DIFFERENT;
        break;

    case RELATIONAL_OPERATOR_DIFFERENT: /* !=  = */
        return RELATIONAL_OPERATOR_EQUAL;
        break;

    default:
        return RELATIONAL_OPERATOR_UNDEFINED;
        break;
    }
}



RelationalOperator mirrorRelationalOperator(RelationalOperator op)
{

    switch(op)
    {
    case RELATIONAL_OPERATOR_LESS: /* < ( > */
        return RELATIONAL_OPERATOR_GREATER;
        break;

    case RELATIONAL_OPERATOR_GREATER: /* > ( < */
        return RELATIONAL_OPERATOR_LESS;
        break;

    case RELATIONAL_OPERATOR_LESS_OR_EQUAL: /* <= ( >= */
        return RELATIONAL_OPERATOR_GREATER_OR_EQUAL;
        break;

    case RELATIONAL_OPERATOR_GREATER_OR_EQUAL: /* >= ( <= */
        return RELATIONAL_OPERATOR_LESS_OR_EQUAL;
        break;

    case RELATIONAL_OPERATOR_EQUAL: /* = ( = */
        return RELATIONAL_OPERATOR_EQUAL;
        break;

    case RELATIONAL_OPERATOR_DIFFERENT: /* != ( != */
        return RELATIONAL_OPERATOR_DIFFERENT;
        break;

    default:
        return RELATIONAL_OPERATOR_UNDEFINED;
        break;
    }
}

const char *getRelationalOperatorName(RelationalOperator op)
{
    const char * relationalOperatorName = "Undefined Relation Operator";

    switch(op)
    {

    case RELATIONAL_OPERATOR_LESS:
        relationalOperatorName = "Less";
        break;

    case RELATIONAL_OPERATOR_GREATER:
        relationalOperatorName = "Greater";
        break;

    case RELATIONAL_OPERATOR_LESS_OR_EQUAL:
        relationalOperatorName = "Less or Equal";
        break;

    case RELATIONAL_OPERATOR_GREATER_OR_EQUAL:
        relationalOperatorName = "Greater or Equal";
        break;

    case RELATIONAL_OPERATOR_EQUAL:
        relationalOperatorName = "Equal";
        break;

    case RELATIONAL_OPERATOR_DIFFERENT:
        relationalOperatorName = "Diferrent";
        break;


    default:
        break;

    }

    return relationalOperatorName;
}
