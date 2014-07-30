/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "declaration_sequence_node.h"

DeclarationSequenceNode::DeclarationSequenceNode(DeclarationNode *firstDeclaration,
        DeclarationNode *nextDeclaration)
    : DeclarationNode(NODE_TYPE_DECLARATION_SEQUENCE)
{
    this->firstDeclaration_ = firstDeclaration;
    this->nextDeclaration_ = nextDeclaration;
}

DeclarationSequenceNode::~DeclarationSequenceNode()
{

}

DeclarationNode * DeclarationSequenceNode::getFirstDeclaration() const
{
    return this->firstDeclaration_;
}

DeclarationNode * DeclarationSequenceNode::getNextDeclaration() const
{
    return this->nextDeclaration_;
}


void DeclarationSequenceNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    this->firstDeclaration_->typeCheck(semanticDebugger);
    this->nextDeclaration_->typeCheck(semanticDebugger);
}

void DeclarationSequenceNode::debug(ASTDebugger * astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Declaration Sequence", nodeLevel);

    this->firstDeclaration_->debug(astDebugger, nodeLevel + 1);
    this->nextDeclaration_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Declaration Sequence", nodeLevel);
}


void DeclarationSequenceNode::generateCCode(ostream &out)
{
    this->firstDeclaration_->generateCCode(out);
    this->nextDeclaration_->generateCCode(out);
}

void DeclarationSequenceNode::generateIntermediateCode(IntermediateCode *intermediateCode)
{
    this->firstDeclaration_->generateIntermediateCode(intermediateCode);
    this->nextDeclaration_->generateIntermediateCode(intermediateCode);
}
