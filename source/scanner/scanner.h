/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SCANNER_H
#define SCANNER_H

#include "token_type.h"
#include "scanner_exception.h"
#include "../util/hash_table.h"

#define KEYWORDS_HASH_TABLE_SIZE 31

/**
  Definição da classe Scanner.

  Esta classe encapsula os métodos e funções necessários para executar a análise léxica
  (scanning) em um arquivo de código fonte.
*/
class Scanner
{

public:

    // Construtor/destrutor.
    Scanner();
    ~Scanner();

    // Executa análise léxica no arquivo de código fonte.
    void scanSourceFile();

    // Verifica se houve erros ao realizar a análise léxica no arquivo de código fonte.
    bool hasError() const;

    // Retorna o número erros encontrados ao realizar a análise léxica no
    // arquivo de código fonte.
    unsigned getErrorsCount() const;

    // Função auxiliar para recuperar o valor lógico (bool) associado ao respectivo
    // literal (true", "false") que o representa.
    bool getBooleanValueFromString(const char *lexeme);

    // Função auxiliar para determinar se o lexema que representa um identificador
    // é uma palavra chave ou simplesmente um nome de identificador.
    TokenType filterIdentifierTokenType(const char *lexeme);

private:

    // Inicializa tabela de palavras chave da linguagem Oberon-0.
    void initKeywordTable(size_t tableCapacity);
    HashTable<TokenType> * keywordTable_;

};

#endif
