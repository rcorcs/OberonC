/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "formatted_ast_debugger.h"

#include <iostream>
#include <cstring>

using namespace std;

FormattedASTDebugger::FormattedASTDebugger()
{

}

void FormattedASTDebugger::createDebugFile(const char *baseFileName)
{
    if(baseFileName == NULL)
    {
        // Se um nome de arquivo base não for especificado (NULL),
        // será lançada uma exceção.
        throw ParserException("Base filename cannot be NULL !");
    }

    // Do contrário, define-se um nome para o arquivo de debug que segue o formato:
    // <NomeDoArquivoFonteDeEntradaSemExtensao_AST>.xhtml

    char * debugFileName = getDebugFileName(baseFileName, "AST.xhtml");

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

    debugFile_ << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\"><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/><title>Abstract Syntax Tree</title><link rel=\"stylesheet\" href=\"mktree.css\" type=\"text/css\" charset=\"utf-8\"/><script src=\"mktree.js\" type=\"text/javascript\" charset=\"utf-8\"/></head><body><ul class=\"mktree\">" << endl << endl;

}

void FormattedASTDebugger::preCloseDebugFile()
{
    debugFile_ << "</ul></body></html>";
}

void FormattedASTDebugger::openParentNode(const char *node,  int nodeLevel)
{
    if (this->enabled_)
    {
        this->debugFile_ << "<li>" << node << "<ul>" << endl;
    }
}

void FormattedASTDebugger::closeParentNode(const char *node,  int nodeLevel)
{
    if (this->enabled_)
    {
        this->debugFile_ << "</ul></li>" << endl << endl;
    }
}


void FormattedASTDebugger::insertLeafNode(const char *node,  int nodeLevel)
{
    if (this->enabled_)
    {
        this->debugFile_ << "<li>" << node << "</li>" << endl;
    }
}
