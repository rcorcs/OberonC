/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include <iostream>
#include <cstdlib>

#include "global/global.h"

using namespace std;

enum CompilerArg
{
    COMPILER_ARG_HELP,
    COMPILER_ARG_DEBUG,
    COMPILER_ARG_PHASE_SCANNER,
    COMPILER_ARG_PHASE_PARSER,
    COMPILER_ARG_PHASE_TYPE_CHECKING,
    COMPILER_ARG_PHASE_INTERMEDIATE_CODE,
    COMPILER_ARG_C_CODE,
    COMPILER_ARG_X64,
    COMPILER_ARG_X86

    // Futuros novos argumentos, sobretudo referentes a fases de compilação,
    // devem ser definidos aqui.
};

void printUsage();

void runAllCompilationPhases(const char *sourceFile);
void runScannerPhase(const char *sourceFile);
void runParserPhase(const char *sourceFile);
void runTypeCheckingPhase(const char *sourceFile);
void runIntermediateCodeGenerationPhase(const char *sourceFile);

void generateCCode();
/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

int main(int argc, char ** argv)
{
    bool runHelp = false;
    bool enableDebug = false;
    bool runScanner = false;
    bool runParser = false;
    bool runTypeChecking = false;
    bool runIntermediateCodeGeneration = false;
    bool genCCode = false;
    bool runAll = true;
#ifdef _WIN32
    bool x64 = false;
    bool x86 = true;
#else
    bool x64 = true;
    bool x86 = false;
#endif

    if (argc < 2)
    {
        cout << endl;
        cout << "Source file not specified !" << endl;

        printUsage();
        return 1;
    }

    HashTable<CompilerArg> compilerArgTable(14);

    compilerArgTable.set("-h", COMPILER_ARG_HELP);
    compilerArgTable.set("--help", COMPILER_ARG_HELP);

    compilerArgTable.set("-d", COMPILER_ARG_DEBUG);
    compilerArgTable.set("--debug", COMPILER_ARG_DEBUG);

    compilerArgTable.set("-s", COMPILER_ARG_PHASE_SCANNER);
    compilerArgTable.set("--scanner", COMPILER_ARG_PHASE_SCANNER);

    compilerArgTable.set("-p", COMPILER_ARG_PHASE_PARSER);
    compilerArgTable.set("--parser", COMPILER_ARG_PHASE_PARSER);

    compilerArgTable.set("-t", COMPILER_ARG_PHASE_TYPE_CHECKING);
    compilerArgTable.set("--typecheck", COMPILER_ARG_PHASE_TYPE_CHECKING);

    compilerArgTable.set("-i", COMPILER_ARG_PHASE_INTERMEDIATE_CODE);
    compilerArgTable.set("--i-code", COMPILER_ARG_PHASE_INTERMEDIATE_CODE);

    compilerArgTable.set("-c", COMPILER_ARG_C_CODE);
    compilerArgTable.set("--c-code", COMPILER_ARG_C_CODE);

    compilerArgTable.set("-x64", COMPILER_ARG_X64);
    compilerArgTable.set("-x86", COMPILER_ARG_X86);

    // Futuras novas fases devem ser adicionadas à lista de argumentos.

    for (int i = 1; i < argc; i++)
    {
        if (compilerArgTable.contains(argv[i]))
        {
            CompilerArg compilerArg = compilerArgTable.get(argv[i]);

            switch (compilerArg)
            {
            case COMPILER_ARG_HELP:
                runHelp = true;
                break;

            case COMPILER_ARG_DEBUG:
                enableDebug = true;
                break;

            case COMPILER_ARG_PHASE_SCANNER:
                runScanner = true;
                break;

            case COMPILER_ARG_PHASE_PARSER:
                runScanner = true;
                runParser = true;
                break;

            case COMPILER_ARG_PHASE_TYPE_CHECKING:
                runScanner = true;
                runParser = true;
                runTypeChecking = true;
                break;

            case COMPILER_ARG_PHASE_INTERMEDIATE_CODE:
                runScanner = true;
                runParser = true;
                runTypeChecking = true;
                runIntermediateCodeGeneration = true;
                break;

            case COMPILER_ARG_C_CODE:
                runScanner = true;
                runParser = true;
                runTypeChecking = true;
                genCCode = true;
                break;

            case COMPILER_ARG_X64:
                x64 = true;
                break;

            case COMPILER_ARG_X86:
                x86 = true;
                break;
                // Futuras novas fases devem ser checadas aqui.
            }
        }
        else if(i>1)
        {
            cout << endl;
            cout << "Unknown argument: " << argv[i] << endl;
            printUsage();

            return 1;
        }
    }

    if(runHelp)
    {
        printUsage();
        return 0;
    }

    if(x86){
        ::oberonc.setMachineCodeType(MACHINE_CODE_X86);
    } else {
        ::oberonc.setMachineCodeType(MACHINE_CODE_X64);
    }

    ::oberonc.setDebug(enableDebug);

    if (runScanner || runParser || runTypeChecking || runIntermediateCodeGeneration)
    {
        runAll = runScanner && runParser && runTypeChecking && runIntermediateCodeGeneration;
    }

    if (runAll)
    {
        runAllCompilationPhases(argv[1]);

        if(genCCode)
        {
            generateCCode();
        }
    }
    else if(runIntermediateCodeGeneration)
    {
        runIntermediateCodeGenerationPhase(argv[1]);

        if(genCCode)
        {
            generateCCode();
        }
    }
    else if(runTypeChecking)
    {
        runTypeCheckingPhase(argv[1]);

        if(genCCode)
        {
            generateCCode();
        }
    }
    else if (runParser)
    {
        runParserPhase(argv[1]);
    }
    else if (runScanner)
    {

        runScannerPhase(argv[1]);
    }

    // Futuras novas fases devem ser consideradas aqui.

    return 0;
}


void printUsage()
{
    cout << endl;

    cout << "Oberon-0 Compiler" << endl << endl;

    cout << "Usage: oberonc <sourceFile> [options]" << endl << endl;

    cout << "Parameters:" << endl << endl;

    cout <<"\t<sourceFile>    \t- the source file to be compiled."<< endl;

    cout << endl;
    cout << "Options:" << endl << endl;

    cout <<"\t-h, --help      \t- display this help and exit." << endl;
    cout <<"\t-d, --debug     \t- enable debug mode. Disabled by default." << endl;
    cout <<"\t-s, --scanner   \t- perform the scanner compilation phase (default)." << endl;
    cout <<"\t-p, --parser    \t- perform the parser compilation phase (default)." << endl;
    cout <<"\t                \t  Implies --scanner." << endl;
    cout <<"\t-t, --typecheck \t- perform type checking (default)." << endl;
    cout <<"\t                \t  Implies --parser." << endl;
    cout <<"\t-i, --i_code    \t- perform the code generation compilation phase (default)." << endl;
    cout <<"\t                \t  Implies --typecheck." << endl;
    cout <<"\t-c, --c_code    \t- generates the file with an equivalent code written in C." << endl;
    cout <<"\t                \t  Implies --typecheck." << endl;

    // Futuras novos argumentos devem ser exibidos aqui.

}

void generateCCode()
{
//    ::oberonc.generateCCode("out.c");
}

void runAllCompilationPhases(const char *sourceFile)
{
    runIntermediateCodeGenerationPhase(sourceFile);
}


void runScannerPhase(const char *sourceFile)
{
    try
    {
        ::oberonc.setSourceFileName(sourceFile);
        ::oberonc.runScanner();
    }
    catch(OberonC_Exception & e)
    {
        cout << "OberonC_Exception: " << e.what() << endl;
    }
    catch (ScannerException & e)
    {
        cout << "ScannerException: " << e.what() << endl;
    }

}

void runParserPhase(const char *sourceFile)
{
    try
    {
        ::oberonc.setSourceFileName(sourceFile);
        ::oberonc.runParser();
    }
    catch(OberonC_Exception & e)
    {
        cout << "OberonC_Exception: " << e.what() << endl;
    }
    catch (ScannerException & e)
    {
        cout << "ScannerException: " << e.what() << endl;
    }
    catch (ParserException & e)
    {
        cout << "ParserException: " << e.what() << endl;
    }
}


void runTypeCheckingPhase(const char *sourceFile)
{
    try
    {
        ::oberonc.setSourceFileName(sourceFile);
        ::oberonc.runTypeChecking();
    }
    catch(OberonC_Exception & e)
    {
        cout << "OberonC_Exception: " << e.what() << endl;
    }
    catch (ScannerException & e)
    {
        cout << "ScannerException: " << e.what() << endl;
    }
    catch (ParserException & e)
    {
        cout << "ParserException: " << e.what() << endl;
    }
}

void runIntermediateCodeGenerationPhase(const char *sourceFile)
{
    try
    {
        ::oberonc.setSourceFileName(sourceFile);
        ::oberonc.runIntermediateCodeGeneration();
    }
    catch(OberonC_Exception & e)
    {
        cout << "OberonC_Exception: " << e.what() << endl;
    }
    catch (ScannerException & e)
    {
        cout << "ScannerException: " << e.what() << endl;
    }
    catch (ParserException & e)
    {
        cout << "ParserException: " << e.what() << endl;
    }
    catch(CodeGeneratorException & e)
    {
        cout << "ParserException: " << e.what() << endl;

    }

}



