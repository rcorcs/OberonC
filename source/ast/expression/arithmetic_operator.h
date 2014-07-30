/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef ARITHMETIC_OPERATOR_H
#define ARITHMETIC_OPERATOR_H

enum ArithmeticOperator
{
    ARITHMETIC_OPERATOR_UNDEFINED, // Apenas para fins de controle e depuração.
    ARITHMETIC_OPERATOR_ADD,
    ARITHMETIC_OPERATOR_SUB,
    ARITHMETIC_OPERATOR_MULT,
    ARITHMETIC_OPERATOR_DIV,
    ARITHMETIC_OPERATOR_MOD
};

const char *getArithmeticOperatorName(ArithmeticOperator op);

#endif
