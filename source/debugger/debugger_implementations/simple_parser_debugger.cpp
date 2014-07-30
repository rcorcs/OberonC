/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "simple_parser_debugger.h"


#include <cstring>
#include <sstream>
using namespace std;

SimpleParserDebugger::SimpleParserDebugger()
{

}

void SimpleParserDebugger::createDebugFile(const char *baseFileName)
{

    if(baseFileName == NULL)
    {
        // Se um nome de arquivo base não for especificado (NULL),
        // será lançada uma exceção.
        throw ParserException("Base filename cannot be NULL !");
    }

    // Do contrário, define-se um nome para o arquivo de debug que segue o formato:
    // <NomeDoArquivoFonteDeEntradaSemExtensao>.SINTATICO

    char * debugFileName = getDebugFileName(baseFileName, "SINTATICO");

    // Abre arquivo de debug.
    this->debugFile_.open(debugFileName);

    if (!this->debugFile_.good())
    {
        string errorMessage = "Error opening parser's debug file: \"";
        errorMessage += debugFileName;
        errorMessage += "\" .";

        delete [] debugFileName;

        // Erros ao tentar abrir o arquivo de debug resultam em exceções.
        throw ParserException(errorMessage);
    }

    delete [] debugFileName;
}

/**
  Método debug, chamado pela função yy_parse(), ao identificar (reduzir), no arquivo de
  código fonte, uma produção de gramática válida para a linguagem Oberon-0.

  @param nonTerminalSymbol
     símbolo não-terminal da gramática que gerou a produção.

  @param production
     produção de gramática encontrada.

  @param lookaheadLine
     número da linha do lookahead.
*/
void SimpleParserDebugger::debugReduction(const char* nonTerminalSymbol, const char *production, int lookaheadLine)
{
    if (this->enabled_)
    {
        // Se o modo debug estiver ativado, insere linha de debug no arquivo correspondente.
        debugFile_
        << lookaheadLine << ": "
        << nonTerminalSymbol << " -> "
        << production << endl;
    }
}

/**
  Método debug, chamado pela função yy_parser(), ao identificar, no arquivo de código fonte,
  um erro sintático recuperado por meio de uma produção de erro na gramática.

  @param erroMessage
     descrição relativa ao erro de sintaxe recuperado.
*/
void SimpleParserDebugger::debugRecoveredError(const char *errorMessage, int lineNumber)
{
    stringstream strError;

    strError << lineNumber << ": " << errorMessage;

    // Chama função externa (yy_parser.cpp) para tratmento de erros sintáticos.
    yyerror(strError.str().c_str());
}
