/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef AST_DEBUGGER_H
#define AST_DEBUGGER_H

#include "../debugger.h"
#include "../../parser/parser_exception.h"

class ASTDebugger: public Debugger
{

public:

    virtual void openParentNode(const char *node, int nodeLevel) = 0;
    virtual void closeParentNode(const char *node, int nodeLevel) = 0;
    virtual void insertLeafNode(const char *node, int nodeLevel) = 0;
};

#endif

