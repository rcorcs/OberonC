/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef FORMATTED_AST_DEBUGGER_H
#define FORMATTED_AST_DEBUGGER_H

#include "../debugger_interfaces/ast_debugger.h"


class FormattedASTDebugger: public ASTDebugger
{

public:

    FormattedASTDebugger();

    void openParentNode(const char *node,  int nodeLevel);
    void closeParentNode(const char *node, int nodeLevel);
    void insertLeafNode(const char *nome, int nodeLevel);

protected:

    void createDebugFile(const char *baseFileName);
    void preCloseDebugFile();


};

#endif
