/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SIMPLE_AST_DEBUGGER_H
#define SIMPLE_AST_DEBUGGER_H

#include "../debugger_interfaces/ast_debugger.h"

class SimpleASTDebugger: public ASTDebugger
{

public:

    SimpleASTDebugger();

    void openParentNode(const char *node, int nodeLevel);
    void closeParentNode(const char *node, int nodeLevel);
    void insertLeafNode(const char *nome, int nodeLevel);

protected:

    void createDebugFile(const char *baseFileName);

};

#endif
