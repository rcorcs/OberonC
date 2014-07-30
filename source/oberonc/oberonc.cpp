/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "oberonc.h"

#include <cstdlib>
#include <iostream>
using namespace std;

/**
  Implementação da classe OberonC.
*/

// Ponteiro para o arquivo de entrada, definido externamente (scanner_lex.cpp),
// que será manipulado nesta classe.
extern FILE * yyin;

/**
  Construtor padrão - sem arquivo de código fonte e com modo debug desativado. Será
                      necessário especificar o arquivo de código fonte através
                      do método setSourceFileName(). Para ativar o modo debug,
                      deve-se utilizar o método setDebug().
*/
OberonC::OberonC()
{

#ifdef _WIN32
    machineCodeType_ = MACHINE_CODE_X86;
#else
    machineCodeType_ = MACHINE_CODE_X64;
#endif


    this->sourceFileName_ = NULL;
    this->debugMode_ = false;
    this->moduleNode_ = NULL;
    this->cleanUpNodeList_ = new list<Node*>();

    this->scannerDebugger_ = new SimpleScannerDebugger();
    this->parserDebugger_ = new SimpleParserDebugger();
    this->symbolTableDebugger_ = new SimpleSymbolTableDebugger();
    this->astDebugger_ = new SimpleASTDebugger();
    this->semanticDebugger_ = new SimpleSemanticDebugger();
    this->codeGeneratorDebugger_ = new SimpleCodeGeneratorDebugger();
    this->intermediateCode_ = new IntermediateCode(&this->symbolTable_);

}

/**
  Destrutor.
*/
OberonC::~OberonC()
{
    // Desaloca espaço reservado para armazenar o nome do arquivo de código fonte.
    delete [] this->sourceFileName_;

    if(yyin != NULL)
    {
        // Caso necessário, fecha o arquivo de entrada manipulado.
        fclose(yyin);
    }

    for(list<Node*>::iterator it = this->cleanUpNodeList_->begin(); it != this->cleanUpNodeList_->end(); it++)
    {
        // Desaloca nós internos da AST.
        delete (*it);
    }

    // Desaloca nó raiz da AST.
    delete this->moduleNode_;

    // Desaloca lista de nós.
    delete this->cleanUpNodeList_;

    // Remove (desaloca) debuggers.
    delete this->scannerDebugger_;
    delete this->parserDebugger_;
    delete this->symbolTableDebugger_;
    delete this->astDebugger_;
    delete this->semanticDebugger_;
    delete this->codeGeneratorDebugger_;
    delete this->intermediateCode_;
}

/**
  Especifica o nome do arquivo de código fonte que será manipulado.

  @param sourceFileName
     nome do arquivo de código fonte que será manipulado. Não pode ser NULO.
*/
void OberonC::setSourceFileName(const char *sourceFileName)
{
    if(sourceFileName == NULL)
    {
        throw OberonC_Exception("Source filename cannot be NULL !");
    }

    delete [] this->sourceFileName_;

    size_t sourceFileNameLen = strlen(sourceFileName);
    this->sourceFileName_ = new char[sourceFileNameLen + 1];

    strcpy(this->sourceFileName_, sourceFileName);
}

/**
  Ativa/desativa o modo debug.

  @param enableDebug
     flag que especifica se o modo debug deverá ser ativado (true) ou desativado (false).
*/
void OberonC::setDebug(bool enableDebug)
{
    this->debugMode_ = enableDebug;
}

/**
  Compila um arquivo de código fonte e gera o executável com um nome específico.

  @param executableName
     nome do arquivo executável que deverá ser gerado.
*/
void OberonC::compile(const char *executableFileName)
{
    // Não implementado ainda.
}

/**
  Executa apenas a fase de scanning (análise léxica) sobre o arquivo de código fonte.

  @see Scanner
*/
void OberonC::runScanner()
{
    this->openSourceFile();

    if(this->debugMode_)
    {
        this->scannerDebugger_->start(this->sourceFileName_);
        this->scanner_.scanSourceFile();
        this->scannerDebugger_->stop();
    }
    else
    {
        this->scanner_.scanSourceFile();
    }

    this->closeSourceFile();


    if(this->scanner_.hasError())
    {
        cout << endl << endl << "[-] Scanning finished with " << this->scanner_.getErrorsCount() << " error(s) !" << endl << endl;
    }
    else
    {
        cout << endl << endl << "[+] Scanning finished successfully !" << endl << endl;
    }

}
/**
  Executa apenas a fase de scanning/parsing (análise sintática) sobre
  o arquivo de código fonte.

  @see Scanner
  @see Parser
*/
void OberonC::runParser()
{
    this->openSourceFile();

    if(this->debugMode_)
    {
        this->scannerDebugger_->start(this->sourceFileName_);
        this->parserDebugger_->start(this->sourceFileName_);
        this->symbolTableDebugger_->start(this->sourceFileName_);
    }

    this->parser_.parseSourceFile();
    this->closeSourceFile();

    if(this->scanner_.hasError())
    {
        cout << endl << endl << "[-] Scanning finished with " << this->scanner_.getErrorsCount() << " error(s) !" << endl << endl;
    }
    else
    {
        cout << endl << endl << "[+] Scanning finished successfully !" << endl << endl;

        if(this->parser_.hasError())
        {
            cout << endl << endl << "[-] Parsing finished with " << this->parser_.getErrorsCount() << " error(s) !" << endl << endl;
        }
        else
        {
            this->symbolTable_.getStringList()->unique();
            cout << endl << endl << "[+] Parsing finished successfully !" << endl << endl;
        }
    }

    if(this->debugMode_)
    {
        this->scannerDebugger_->stop();
        this->parserDebugger_->stop();
        this->symbolTableDebugger_->stop();
    }
}

void OberonC::runTypeChecking()
{
    if(this->debugMode_)
    {
        this->astDebugger_->start(this->sourceFileName_);
        this->runParser();
    }
    else
    {
        this->runParser();
    }


    if(!this->scanner_.hasError() && !this->parser_.hasError())
    {
        this->moduleNode_->typeCheck(this->semanticDebugger_);

        if(this->semanticDebugger_->getErrorCounter() == 0)
        {
            if(this->debugMode_)
            {
                this->moduleNode_->debug(this->astDebugger_, 0);
            }

            cout << endl << endl << "[+] Type checking finished successfully !" << endl << endl;
        }
        else
        {
            cout << endl << endl << "[-] Errors found in type checking !" << endl << endl;
        }
    }
    else
    {
        cout << endl << endl << "[-] Type checking not performed." << endl << endl;
    }


    if(this->debugMode_)
    {
        this->astDebugger_->stop();
    }

}

void OberonC::runIntermediateCodeGeneration()
{

    if(this->debugMode_)
    {
        this->codeGeneratorDebugger_->start(this->sourceFileName_);
        this->runTypeChecking();
    }
    else
    {
        this->runTypeChecking();
    }


    if(!this->scanner_.hasError() && !this->parser_.hasError() &&
       this->semanticDebugger_->getErrorCounter() == 0)
    {
        this->moduleNode_->generateIntermediateCode(this->intermediateCode_);

        if(this->debugMode_)
        {
            this->intermediateCode_->debug(this->codeGeneratorDebugger_);
        }

        cout << endl << endl << "[+] Intermediate code generation finished successfully !" << endl << endl;

        //vector<BasicBlock *> *basicBlocks = this->intermediateCode_->getBasicBlocks();
        MachineCode *machineCode;
        if(getMachineCodeType()==MACHINE_CODE_X64){
            machineCode = new X64Architecture(&this->symbolTable_, this->intermediateCode_);
        }else if(getMachineCodeType()==MACHINE_CODE_X86){
            machineCode = new X86Architecture(&this->symbolTable_, this->intermediateCode_);
        }
        machineCode->open(this->sourceFileName_);
        machineCode->generateCode();
        machineCode->close();


    }
    else
    {
        cout << endl << endl << "[-] Intermediate code generation not performed." << endl << endl;
    }


    if(this->debugMode_)
    {
        this->codeGeneratorDebugger_->stop();
    }
}

void OberonC::setMachineCodeType(MachineCodeType machineCodeType)
{
    machineCodeType_ = machineCodeType;
}

MachineCodeType OberonC::getMachineCodeType()
{
    return machineCodeType_;
}
//void OberonC::generateCCode(const char *outputFileName)
//{
////    if(this->moduleNode_)
////    {
////        ofstream outFile(outputFileName);
////        this->moduleNode_->generateCCode(outFile);
////        outFile.close();
////
////        return true;
////    }
//}



/**
  Método privado auxiliar para abrir um arquivo de código fonte.
*/
void OberonC::openSourceFile()
{
    if(this->sourceFileName_ == NULL)
    {
        throw OberonC_Exception("No source file specified !");
    }

    yyin = fopen(this->sourceFileName_, "r");

    if (yyin == NULL)
    {
        string errorMessage = "Error opening source file: \"";
        errorMessage += this->sourceFileName_;
        errorMessage += "\" .";

        throw OberonC_Exception(errorMessage);
    }
}

/**
  Método privado auxiliar para fechar um arquivo de código fonte.
*/
void OberonC::closeSourceFile()
{
    fclose(yyin);
    yyin = NULL;
}

/**
  Obtém referência para o componente de scanning do compilador.

  @see Scanner
*/
Scanner & OberonC::getScanner()
{
    return this->scanner_;
}

/**
  Obtém referência para o componente de parsing do compilador.

  @see Parser
*/
Parser & OberonC::getParser()
{

    return this->parser_;
}

/**
  Obtém referência para a tabela de símbolos manipulada durante a compilação
  do arquivo de código fonte.

  @see SymbolTable
*/
SymbolTable & OberonC::getSymbolTable()
{
    return this->symbolTable_;
}


void OberonC::setASTRoot( ModuleNode *root )
{
    this->moduleNode_ = root;
}

ModuleNode *OberonC::getASTRoot()
{
    return this->moduleNode_;
}


void OberonC::addNodeToCleanUpList(Node * node)
{
    this->cleanUpNodeList_->push_back(node);
}

/**
  Obtém referência para o debugger vinculado ao Scanner.

  @see Scanner
*/
ScannerDebugger * OberonC::getScannerDebugger()
{
    return this->scannerDebugger_;
}


/**
  Obtém referência para o debugger vinculado ao Parser.

  @see Scanner
*/
ParserDebugger * OberonC::getParserDebugger()
{
    return this->parserDebugger_;
}

/**
  Obtém referência para o debugger vinculado ao Parser.

  @see Scanner
*/
SymbolTableDebugger * OberonC::getSymbolTableDebugger()
{
    return this->symbolTableDebugger_;
}



