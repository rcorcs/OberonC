/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef IDENTIFIER_CATEGORY_TYPE_H
#define IDENTIFIER_CATEGORY_TYPE_H

/**
  Enumeração dos possíveis tipos de categorias vinculadas a identificadores.
  Esses tipos são especificados em subclasses da classe Information, sendo objetos
  destas subclasses inseridas na tabela de símbolos durante a fase de parsing.

  @see Parser

  @see Information

  @see ModuleInfo
  @see ProcedureInfo
  @see FunctionInfo
  @see ConstantInformation
  @see VariableInformation
  @see FormalParameterInformation

  @see SymbolTable

*/
enum IdentifierCategoryType
{
    IDENTIFIER_CATEGORY_TYPE_UNDEFINED,
    IDENTIFIER_CATEGORY_TYPE_MODULE,
    IDENTIFIER_CATEGORY_TYPE_PROCEDURE,
    IDENTIFIER_CATEGORY_TYPE_FUNCTION,
    IDENTIFIER_CATEGORY_TYPE_CONSTANT,
    IDENTIFIER_CATEGORY_TYPE_VARIABLE,
    IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER,
    IDENTIFIER_CATEGORY_TYPE_TEMPORARY
};

// Retorna o nome associado a uma categoria de identificador.
const char *getIdentifierCategoryTypeName(IdentifierCategoryType categoryType);

#endif
