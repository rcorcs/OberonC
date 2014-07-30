/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "scanner.h"

#include <cstdlib>

/**
  Implementação da classe Scanner.
*/

// Função para análise léxica, definida externamente (scanner_lex.cpp),
// que será utilizada internamente nesta classe.
extern int yylex();


// Variável definida externamente (scanner_lex.cpp) utilizada para contagem de erros
// léxicos enncontrados durante a análise léxica realizada pela função yy_lex().
extern unsigned int scannerErrors;

/**
  Construtor padrão.
*/
Scanner::Scanner()
{
    // Aloca e inicializa a tabela hash de palavras chaves da linguagem Oberon-0.
    this->initKeywordTable(KEYWORDS_HASH_TABLE_SIZE);
}

/**
  Destrutor da classe.

  @see HashTable
*/
Scanner::~Scanner()
{
    // Desaloca tabela hash utilizada para armazenar as palavras chaves da linguagem Oberon-0.
    delete this->keywordTable_;
}

/**
  Método auxiliar para inicializar a tabela de palavras chaves da linguagem Oberon-0.

  @param tableCapacity
     capacidade (número de entradas) da tabela hash que irá armazenar as palavras chaves.

  @see HashTable
*/
void Scanner::initKeywordTable(size_t tableCapacity)
{
    this->keywordTable_ = new HashTable<TokenType>(tableCapacity);

    // Grupo de escopo/bloco.
    this->keywordTable_->set("module", TOKEN_TYPE_MODULE);
    this->keywordTable_->set("procedure", TOKEN_TYPE_PROCEDURE);
    this->keywordTable_->set("function", TOKEN_TYPE_FUNCTION);
    this->keywordTable_->set("var", TOKEN_TYPE_VAR);
    this->keywordTable_->set("const", TOKEN_TYPE_CONST);
    this->keywordTable_->set("begin", TOKEN_TYPE_BEGIN);
    this->keywordTable_->set("end", TOKEN_TYPE_END);

    // Grupo condicional.
    this->keywordTable_->set("if", TOKEN_TYPE_IF);
    this->keywordTable_->set("then", TOKEN_TYPE_THEN);
    this->keywordTable_->set("elsif", TOKEN_TYPE_ELSIF);
    this->keywordTable_->set("else", TOKEN_TYPE_ELSE);

    // Grupo de repetição/controle de fluxo.
    this->keywordTable_->set("while", TOKEN_TYPE_WHILE);
    this->keywordTable_->set("repeat", TOKEN_TYPE_REPEAT);
    this->keywordTable_->set("until", TOKEN_TYPE_UNTIL);
    this->keywordTable_->set("for", TOKEN_TYPE_FOR);
    this->keywordTable_->set("do", TOKEN_TYPE_DO);
    this->keywordTable_->set("to", TOKEN_TYPE_TO);
    this->keywordTable_->set("continue", TOKEN_TYPE_CONTINUE);
    this->keywordTable_->set("break", TOKEN_TYPE_BREAK);
    this->keywordTable_->set("return", TOKEN_TYPE_RETURN);

    // Grupo de repetição/controle de fluxo.
    this->keywordTable_->set("boolean", TOKEN_TYPE_BOOLEAN);
    this->keywordTable_->set("integer", TOKEN_TYPE_INTEGER);

    // Grupo de operadores.
    this->keywordTable_->set("and", TOKEN_TYPE_AND);
    this->keywordTable_->set("or", TOKEN_TYPE_OR);
    this->keywordTable_->set("not", TOKEN_TYPE_NOT);
    this->keywordTable_->set("mod", TOKEN_TYPE_MOD);

    // Grupo de funções I/O nativas.
    this->keywordTable_->set("write", TOKEN_TYPE_WRITE);
    this->keywordTable_->set("writeln", TOKEN_TYPE_WRITELN);
    this->keywordTable_->set("read", TOKEN_TYPE_READ);
}

/**
  Executa análise léxica no arquivo de código fonte.
  Para tanto, a função yylex(), implementada no arquivo externo scanner_lex.cpp,
  gerado pelo Flex, será chamada.

  A presença de erros que ocorreram no processo pode ser verificada através do método
  hasError() e o número de erros pode ser obtido através do método getErrorsCount().
*/
void Scanner::scanSourceFile()
{
    int ch;

    // Zera contagem de erros.
    scannerErrors = 0;


    do
    {
        // Chama função para realizar análise léxica no arquivo de código fonte.
        // Sempre quando um erro léxico for detectado, a função externa yy_lex()
        // irá incrementar a variável scannerErrors.
        ch = yylex();

        switch(ch)
        {

        case TOKEN_TYPE_IDENTIFIER:
            // Desaloca cópia do identificador realizada pela função yy_lex().
            // Esta cópia seria utilizada pelo Parser, no entanto, como apenas a fase de
            // análise léxica será executada, a mesma não tem uso e, por isso, é descartada.
            delete [] yylval.identifier;
            break;

        case TOKEN_TYPE_STRING_LITERAL:
            // Desaloca cópia da string (literal) realizada pela função yy_lex().
            // Esta cópia seria utilizada pelo Parser, no entanto, como apenas a fase de
            // análise léxica será executada, a mesma não tem uso e, por isso, é descartada.
            delete [] yylval.str_value;
            break;

        default:
            break;
        }
    }
    // A função yy_lex() retorna 0 ao encontrar o fim do arquivo de código fonte, isto é,
    // ao finalizar a análise léxica.
    while(ch != 0);

}

/**
  Verifica se houve erros ao realizar a análise léxica no arquivo de código fonte.

  @return
     flag que indica se houve erros (true) ou não (false) durante a análise léxica.
*/
bool Scanner::hasError() const
{
    return (scannerErrors > 0);
}

/**
  Retorna o número erros encontrados ao realizar a análise léxica no arquivo de código fonte.

  @return
     número erros encontrados.
*/
unsigned int Scanner::getErrorsCount() const
{
    return scannerErrors;
}


/**
  Função auxiliar para converter um lexema que representa um literal booleano
  em seu respectivo valor lógico (bool).

  @param lexeme
     lexema que representa o literal booleano.

  @return
     valor lógico (bool) referente literal booleano representado no lexema.

*/
bool Scanner::getBooleanValueFromString(const char *lexeme)
{
    // Assume um valor padrão igual a "true".
    bool booleanValue = true;

    char * src = (char*)lexeme;
    char * dst = (char*)"true";

    if(strlen(lexeme) == strlen(dst))
    {
        // Verifica se o lexema realmente é "true".
        while(*src != '\0' && booleanValue)
        {
            booleanValue = (tolower(*src++) == tolower(*dst++));
        }
    }
    else
    {
        booleanValue = false;
    }

    return booleanValue;
}

/**
  Verifica se um determinado identificador (representado em um lexema)
  corresponde a uma palavra chave ou simplesmente a um nome de identificador e retorna
  o tipo do token (TokenType) apropriado.

  @param lexeme
     lexema do arquivo de código fonte que representa o identificador a ser tratado.

  @return
     tipo do token (TokenType) apropriado para o identificador.

  @see TokenType
  @see HashTable
*/
TokenType Scanner::filterIdentifierTokenType(const char *lexeme)
{
    // Assume que o token corresponde a um simples nome de identificador.
    TokenType tokenType = TOKEN_TYPE_IDENTIFIER;

    // Pesquisa lexema na tabela de palavras chave.
    if (this->keywordTable_->contains(lexeme))
    {
        // Atribui o tipo de token apropriado caso o lexema corresponda a alguma
        // palavra chave.
        tokenType = this->keywordTable_->get(lexeme);
    }

    return tokenType;
}
