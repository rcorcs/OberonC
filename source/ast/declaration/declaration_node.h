/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef DECLARATION_NODE_H
#define DECLARATION_NODE_H

#include "../node.h"

#include "../../code_generator/intermediate/intermediate_code.h"

#include "../../code_generator/intermediate/instruction_argument/instruction_argument.h"
#include "../../code_generator/intermediate/instruction_argument/label_argument.h"
#include "../../code_generator/intermediate/instruction_argument/instruction_label.h"

class DeclarationNode : public Node
{

public:

    DeclarationNode(const NodeType nodeType);
    virtual ~DeclarationNode();

    virtual void typeCheck(SemanticDebugger *semanticDebugger) = 0;

    virtual void generateCCode(ostream &out) = 0;
    virtual void generateIntermediateCode(IntermediateCode *intermediateCode){/*make it pure virtual*/};

};

#endif
