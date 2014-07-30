/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef DATA_TYPE_H
#define DATA_TYPE_H

/**
  Enumerações dos possíveis tipos de dados da linguagem Oberon-0.
*/
enum DataType
{

    // Tipo criado para simplificar depuração.
    // Não corresponde a um tipo real na definição da linguagem.
    DATA_TYPE_UNDEFINED,

    // Tipo criado para simplificar a análise semântica.
    // Não corresponde a um tipo real na definição da linguagem.
    DATA_TYPE_ERROR,

    DATA_TYPE_BOOLEAN,
    DATA_TYPE_INTEGER,
    DATA_TYPE_STRING,

    // Tipo criado para simplificar a criação da AST e
    // análise semântica. Não corresponde a um tipo real
    // na definição da linguagem.
    DATA_TYPE_VOID,
};

// Retorna o nome de um tipo de dado.
const char *getDataTypeName(DataType dataType);

#endif
