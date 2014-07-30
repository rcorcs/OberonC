/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef NEGATION_NODE_H
#define NEGATION_NODE_H

#include "expression_node.h"

class NegationNode : public ExpressionNode
{

public:

    NegationNode(ExpressionNode *operand);
    ~NegationNode();

    DataType typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

protected:

    void checkConstant();

private:

    ExpressionNode *operand_;
};

#endif


