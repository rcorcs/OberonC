/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "simple_symbol_table_debugger.h"

#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;


SimpleSymbolTableDebugger::SimpleSymbolTableDebugger()
{

}

void SimpleSymbolTableDebugger::createDebugFile(const char *baseFileName)
{
    if(baseFileName == NULL)
    {
        // Se um nome de arquivo base não for especificado (NULL),
        // será lançada uma exceção.
        throw ParserException("Base filename cannot be NULL !");
    }

    // Do contrário, define-se um nome para o arquivo de debug que segue o formato:
    // <NomeDoArquivoFonteDeEntradaSemExtensao>.TS

    char * debugFileName = getDebugFileName(baseFileName, "TS");

    // Abre arquivo de debug.
    this->debugFile_.open(debugFileName);

    if (!this->debugFile_.good())
    {
        string errorMessage = "Error opening symbol table's debug file: \"";
        errorMessage += debugFileName;
        errorMessage += "\" .";

        delete [] debugFileName;

        // Erros ao tentar abrir o arquivo de debug resultam em exceções.
        throw ParserException(errorMessage);
    }

    delete [] debugFileName;
}


void SimpleSymbolTableDebugger::debugScopeStart(const char *scopeName)
{
    debugFile_ << "==================================================" << endl;
    debugFile_ << scopeName << endl;
    debugFile_ << "==================================================" << endl;

    debugFile_ << endl;
}

void SimpleSymbolTableDebugger::debugScopeEnd()
{
    debugFile_ << endl;
}

void SimpleSymbolTableDebugger::debugIdentifierInfo(const char *name)
{
    debugFile_ << "[+] " << name << endl << endl;
}

void SimpleSymbolTableDebugger::debugIdentifierInfoAttribute(const char *name, const char *value)
{
    debugFile_ <<  "  [-] " << name << ": " << value << endl;
}

void SimpleSymbolTableDebugger::debugIdentifierInfoAttribute(const char *name, int value)
{
    debugFile_ << "  [-] " << name << ": " << value << endl;
}

void SimpleSymbolTableDebugger::newLine()
{
    debugFile_ << endl;
}

/**
  Método debug, chamado pela função yy_parser(), ao identificar, no arquivo de código fonte,
  o uso de um identificador não declarado.

  @param identifier
     string que indica o identificador não declarado.
*/
void SimpleSymbolTableDebugger::debugIdentifierNotDeclared(const char *identifier, int lineNumber)
{
    stringstream strError;

    strError << lineNumber << ": Identifier \"" << identifier << "\" has not been declared.";

    // Chama função externa (yy_parser.cpp) para tratmento de erros.
    yyerror(strError.str().c_str());
}

/**
  Método debug, chamado pela função yy_parser(), ao identificar, no arquivo de código fonte,
  a declaração de um identificador que já foi declarado previamente.

  @param identifier
     string que indica o identificador já declarado.
*/
void SimpleSymbolTableDebugger::debugIdentifierAlreadyDeclared(const char *identifier, int lineNumber)
{
    stringstream strError;

    strError << lineNumber << ": Identifier \"" << identifier << "\" has already been declared.";

    // Chama função externa (yy_parser.cpp) para tratmento de erros.
    yyerror(strError.str().c_str());
}


void SimpleSymbolTableDebugger::debugUnexpectedUseOfIdentifier(const char *identifier, int lineNumber)
{
    stringstream strError;

    strError << lineNumber << ": Unexpected use of identifier \"" << identifier << "\".";

    // Chama função externa (yy_parser.cpp) para tratmento de erros.
    yyerror(strError.str().c_str());
}
