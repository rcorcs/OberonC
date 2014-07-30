/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "simple_scanner_debugger.h"

#include <iostream>
#include <cstring>
using namespace std;


SimpleScannerDebugger::SimpleScannerDebugger()
{

}

void SimpleScannerDebugger::createDebugFile(const char *baseFileName)
{
    if(baseFileName == NULL)
    {
        // Se um nome de arquivo base não for especificado (NULL),
        // será lançada uma exceção.
        throw ScannerException("Base filename cannot be NULL !");
    }

    // Do contrário, define-se um nome para o arquivo de debug que segue o formato:
    // <NomeDoArquivoFonteDeEntradaSemExtensao>.LEXICO
    char * debugFileName = getDebugFileName(baseFileName, "LEXICO");


    // Abre arquivo de debug.
    this->debugFile_.open(debugFileName);

    if (!this->debugFile_.good())
    {
        string errorMessage = "Error opening scanner's debug file: \"";
        errorMessage += debugFileName;
        errorMessage += "\" .";

        delete [] debugFileName;

        // Erros ao tentar abrir o arquivo de debug resultam em exceções.
        throw ScannerException(errorMessage);
    }

    delete [] debugFileName;
}


void SimpleScannerDebugger::debugToken(TokenType tokenType, const char *lexeme, int line, int start_column)
{
    if (this->enabled_)
    {
        // Obtém nome do token.
        char *tokenTypeName = getTokenTypeName(tokenType);

        // Se o modo debug estiver ativado, insere linha de debug no
        // arquivo correspondente.
        this->debugFile_
        << tokenTypeName        << "(" << lexeme
        << ") at line "         << line
        << ", start at column " << start_column
        << ", end at column "   << (start_column  + strlen(lexeme) )
        << endl;

        delete [] tokenTypeName;
    }
}



void SimpleScannerDebugger::debugUnterminatedStringError(const char *lexeme, int line, int start_column)
{
    // Exibe linha de erro na tela.
    cout
        << "Unterminated string: " << lexeme
        << " at line "             << line
        << ", start at column "    << start_column
        << ", end at column "      << (start_column + strlen(lexeme) )
        << endl;
}

void SimpleScannerDebugger::debugInvalidStringCharacterError(const char *lexeme, int line, int start_column)
{
    // Exibe linha de erro na tela.
    cout
        << "String with an invalid character: " << lexeme
        << " at line "             << line
        << ", start at column "    << start_column
        << ", end at column "      << (start_column + strlen(lexeme) )
        << endl;
}


void SimpleScannerDebugger::debugInvalidSymbolError(const char *lexeme, int line, int start_column)
{
    // Exibe linha de erro na tela.
    cout
        << "Unkown symbol: " << lexeme
        << " at line " << line
        << ", start at column " << start_column
        << ", end at column " << (start_column + strlen(lexeme) )
        << endl;
}


void SimpleScannerDebugger::debugUnexpectedEOF(int line)
{
    // Exibe linha de erro na tela.
    cout  << "Unexpected End-Of-File found on line: " << line << endl;
}
