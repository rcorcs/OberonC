/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef RELATIONAL_OPERATOR_H
#define RELATIONAL_OPERATOR_H

enum RelationalOperator
{
    RELATIONAL_OPERATOR_UNDEFINED, // Apenas para fins de controle e depuração.
    RELATIONAL_OPERATOR_LESS,
    RELATIONAL_OPERATOR_GREATER,
    RELATIONAL_OPERATOR_LESS_OR_EQUAL,
    RELATIONAL_OPERATOR_GREATER_OR_EQUAL,
    RELATIONAL_OPERATOR_EQUAL,
    RELATIONAL_OPERATOR_DIFFERENT
} ;

RelationalOperator invertRelationalOperator(RelationalOperator op);
RelationalOperator mirrorRelationalOperator(RelationalOperator op);
const char *getRelationalOperatorName(RelationalOperator op);

#endif
