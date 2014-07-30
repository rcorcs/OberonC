/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "identifier_information.h"
#include "scope.h"

#include "../parser/parser_exception.h"

#include <list>
using namespace std;

/**

  Definição da classe utilizada para implementar uma Tabela de Símbolos.

  Esta tabela será consultada e modificada inicialmente pela função externa yy_parser(), gerada
  pelo Bison no arquivo yy_parser.cpp, que irá detectar e extrair informações sobre
  uso/declaração de identificadores e inserir, nest tabela, informações relevantes,
  como, por exemplo, tipos de variáveis e de retornos de funções.

  Terminando sua execução, o Parser fornecerá, junto com a Árvore de Sintaxe Abstrata,
  esta tabela com as informações necessárias ao analisador semântico.

*/

#define GLOBAL_SCOPE 2

class SymbolTable
{

public:

    SymbolTable();
    ~SymbolTable();

    // Criação e remoção de escopos.
    void createScope(const char *name);
    Scope *removeScope();

    // Insere informação sobre identificador em um escopo corrente.
    void insertAtCurrentScope(IdentifierInformation *identiferInfo);

    // Verifica presença de informação sobre identificador em um escopo corrente.
    bool isAtCurrentScope(const char *identifier) const;

    // Verifica presença de informação sobre identificador em todos os escopos empilhados.
    IdentifierInformation *lookup(const char *identifier) const;

    // Escopo atual/quantidade de escopos empilhados.
    Scope *getCurrentScope() const;
    unsigned int getScopeCount() const;

    // Recupera a lista atual contendo informações sobre identificadores.
    list <IdentifierInformation *> * getIdentifierInfoList();

    list <string> * getStringList();

private:

    list <IdentifierInformation *> identifierInfoList_;
    list <Scope *> scopeList_;
    list <string> stringList_;
};

#endif
