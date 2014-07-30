/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SKIP_DECLARATION_NODE_H
#define SKIP_DECLARATION_NODE_H

#include "declaration_node.h"

class SkipDeclarationNode : public DeclarationNode
{

public:

    SkipDeclarationNode();
    ~SkipDeclarationNode();

    void typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);


};

#endif
