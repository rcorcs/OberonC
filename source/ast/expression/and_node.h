/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef AND_NODE_H
#define AND_NODE_H

#include "expression_node.h"

class AndNode : public ExpressionNode
{
public:

    AndNode(ExpressionNode *leftOperand, ExpressionNode *rightOperand);
    ~AndNode();

    DataType typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);


protected:

    void checkConstant();

private:

    ExpressionNode *leftOperand_;
    ExpressionNode *rightOperand_;
};

#endif
