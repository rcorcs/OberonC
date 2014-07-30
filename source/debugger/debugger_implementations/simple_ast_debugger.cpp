/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "simple_ast_debugger.h"

#include <iostream>
#include <cstring>

using namespace std;

SimpleASTDebugger::SimpleASTDebugger()
{

}

void SimpleASTDebugger::createDebugFile(const char *baseFileName)
{
    if(baseFileName == NULL)
    {
        // Se um nome de arquivo base não for especificado (NULL),
        // será lançada uma exceção.
        throw ParserException("Base filename cannot be NULL !");
    }

    // Do contrário, define-se um nome para o arquivo de debug que segue o formato:
    // <NomeDoArquivoFonteDeEntradaSemExtensao_AST>.AST

    char * debugFileName = getDebugFileName(baseFileName, "AST");

    // Abre arquivo de debug.
    this->debugFile_.open(debugFileName);

    if (!this->debugFile_.good())
    {
        string errorMessage = "Error opening AST's debug file: \"";
        errorMessage += debugFileName;
        errorMessage += "\" .";

        delete [] debugFileName;

        // Erros ao tentar abrir o arquivo de debug resultam em exceções.
        throw ParserException(errorMessage);
    }

    delete [] debugFileName;

}


void SimpleASTDebugger::openParentNode(const char *node, int nodeLevel)
{
    if (this->enabled_)
    {
        while(nodeLevel > 0)
        {
            debugFile_ << "    ";
            nodeLevel--;
        }

        this->debugFile_ << "[+] " << node << endl << endl;
    }
}

void SimpleASTDebugger::closeParentNode(const char *node,  int nodeLevel)
{
    if (this->enabled_)
    {
        this->debugFile_ << endl;
    }
}


void SimpleASTDebugger::insertLeafNode(const char *node,  int nodeLevel)
{

    if (this->enabled_)
    {
        while(nodeLevel > 0)
        {
            debugFile_ << "    ";
            nodeLevel--;
        }
        this->debugFile_ << "[-] " << node << endl;
    }
}
