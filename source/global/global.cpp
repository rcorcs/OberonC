/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "global.h"

// Declaração de variáveis compartilhadas.

// Declara a instância do Oberon-0 Compiler que será compartilhada
// nos arquivos:
//
//  main.cpp (entry point do compilador);
//  scanner_lex.cpp (analisador léxico gerado pelo Flex) e
//  yy_parser.cpp (analisador sintático gerado pelo Bison)

OberonC oberonc;
