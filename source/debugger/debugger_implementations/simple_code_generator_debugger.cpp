/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "simple_code_generator_debugger.h"
#include "../../code_generator/code_generator_exception.h"

#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

SimpleCodeGeneratorDebugger::SimpleCodeGeneratorDebugger()
{

}

void SimpleCodeGeneratorDebugger::createDebugFile(const char *baseFileName)
{
    if(baseFileName == NULL)
    {
        // Se um nome de arquivo base não for especificado (NULL),
        // será lançada uma exceção.
        throw CodeGeneratorException("Base filename cannot be NULL !");
    }

    // Do contrário, define-se um nome para o arquivo de debug que segue o formato:
    // <NomeDoArquivoFonteDeEntradaSemExtensao_AST>.CODINTERM

    char * debugFileName = getDebugFileName(baseFileName, "CODINTERM");

    // Abre arquivo de debug.
    this->debugFile_.open(debugFileName);

    if (!this->debugFile_.good())
    {
        string errorMessage = "Error opening Intermediate Code's debug file: \"";
        errorMessage += debugFileName;
        errorMessage += "\" .";

        delete [] debugFileName;

        // Erros ao tentar abrir o arquivo de debug resultam em exceções.
        throw CodeGeneratorException(errorMessage);
    }

    delete [] debugFileName;
}

void SimpleCodeGeneratorDebugger::debugCode(const char *code)
{
    this->debugFile_ << code;
 //cout << code;
}
