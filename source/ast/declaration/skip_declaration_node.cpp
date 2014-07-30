/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "skip_declaration_node.h"

SkipDeclarationNode::SkipDeclarationNode() : DeclarationNode(NODE_TYPE_SKIP_DECLARATION)
{

}

SkipDeclarationNode::~SkipDeclarationNode()
{

}

void SkipDeclarationNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    // Type Check não aplicável a este nodo.
}

void SkipDeclarationNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->insertLeafNode("{Skip Declaration}", nodeLevel);
}

void SkipDeclarationNode::generateCCode(ostream &out)
{

}
