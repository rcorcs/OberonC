/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef OBERON_C_H
#define OBERON_C_H

#include <vector>
#include <iostream>
using namespace std;

#include "../scanner/scanner.h"
#include "../debugger/debugger_interfaces/scanner_debugger.h"
#include "../debugger/debugger_implementations/simple_scanner_debugger.h"

#include "../parser/parser.h"
#include "../debugger/debugger_interfaces/parser_debugger.h"
#include "../debugger/debugger_implementations/simple_parser_debugger.h"

#include "../symbol_table/symbol_table.h"
#include "../debugger/debugger_interfaces/symbol_table_debugger.h"
#include "../debugger/debugger_implementations/simple_symbol_table_debugger.h"

#include "../ast/declaration/module_node.h"
#include "../debugger/debugger_interfaces/ast_debugger.h"
#include "../debugger/debugger_implementations/formatted_ast_debugger.h"
#include "../debugger/debugger_implementations/simple_ast_debugger.h"

#include "../debugger/debugger_interfaces/semantic_debugger.h"
#include "../debugger/debugger_implementations/simple_semantic_debugger.h"

#include "../code_generator/intermediate/intermediate_code.h"
#include "../code_generator/intermediate/instruction_argument/instruction_argument.h"

#include "../debugger/debugger_implementations/simple_code_generator_debugger.h"
#include "../code_generator/code_generator_exception.h"

#include "../code_generator/machine/machine_code.h"
#include "../code_generator/machine/x64_architecture.h"
#include "../code_generator/machine/x86_architecture.h"
#include "../code_generator/machine/basic_block.h"

#include "oberonc_exception.h"

/**
  Definição da classe principal do Oberon-O Compiler.

  Esta classe define os componentes implementados do compilador, isto é,
  scanner, parser, tabela de símbolos, etc.

  Também são definidos métodos para execução de fases específicas de compilação, como,
  por exemplo, apenas a etapa de análise léxica.

  Uma opção para ativar o modo debug também é fornecida. Neste modo, durante as fases
  da compilação, serão criados arquivos de log contendo o resultado do processamento
  realizado por cada etapa executada. Por padrão, estes arquivos seguem o seguinte padrão:

      Scanner       -> <NomeDoArquivoDeEntradaSemExtensao>.LEXICO
      Parser        -> <NomeDoArquivoDeEntradaSemExtensao>.SINTATICO
      SymbolTable   -> <NomeDoArquivoDeEntradaSemExtensao>.TS
      CodeGenerator -> <NomeDoArquivoDeEntradaSemExtensao>.CODINTERM

  @see Scanner
  @see Parser
  @see SymbolTable
*/
class OberonC
{

public:

    // Construtor/destrutores.
    OberonC();
    ~OberonC();

    // Define/retorna arquivo fonte de entrada.
    void setSourceFileName(const char *sourceFileName);
    const char * getSourceFile() const;

    // Compila um arquivo fonte gerando um executável com um nome especificado.
    void compile(const char *outputFileName);

    // Executa fases específicas de compilação.
    void runScanner();
    void runParser();
    void runTypeChecking();
    void runIntermediateCodeGeneration();

    // Ativa/desativa modo debug.
    void setDebug(bool enableDebug);

    // Getters para os componentes do compilador.
    Scanner & getScanner();
    Parser & getParser();
    SymbolTable & getSymbolTable() ;

    void setASTRoot(ModuleNode *root);
    ModuleNode *getASTRoot();
    void addNodeToCleanUpList(Node * node);

    ScannerDebugger * getScannerDebugger();
    ParserDebugger * getParserDebugger();
    SymbolTableDebugger * getSymbolTableDebugger();

    void setMachineCodeType(MachineCodeType machineCodeType);
    MachineCodeType getMachineCodeType();

private:

    // Inicializa/encerra manipulação do arquivo de código fonte.
    void openSourceFile();
    void closeSourceFile();

    char * sourceFileName_;
    bool debugMode_;

    MachineCodeType machineCodeType_;

    // Componentes do compilador.
    Scanner scanner_;
    Parser parser_;
    SymbolTable symbolTable_;
    ModuleNode *moduleNode_;
    IntermediateCode *intermediateCode_;
    list<Node*> * cleanUpNodeList_;

    // Debuggers.
    ScannerDebugger       * scannerDebugger_;
    ParserDebugger        * parserDebugger_;
    SymbolTableDebugger   * symbolTableDebugger_;
    ASTDebugger           * astDebugger_;
    SemanticDebugger      * semanticDebugger_;
    CodeGeneratorDebugger * codeGeneratorDebugger_;

};

#endif

