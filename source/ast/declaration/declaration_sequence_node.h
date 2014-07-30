/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef DECLARATION_SEQUENCE_NODE_H
#define DECLARATION_SEQUENCE_NODE_H

#include "declaration_node.h"

class DeclarationSequenceNode : public DeclarationNode
{

public:

    DeclarationSequenceNode(DeclarationNode *firstDeclaration,
                            DeclarationNode *nextDeclaration);

    ~DeclarationSequenceNode();

    DeclarationNode * getFirstDeclaration() const;
    DeclarationNode * getNextDeclaration() const;

    void typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger * astDebugger, int nodeLevel);
    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode);



private:

    DeclarationNode *firstDeclaration_;
    DeclarationNode *nextDeclaration_;

};

#endif
