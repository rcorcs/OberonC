/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef NOT_NODE_H
#define NOT_NODE_H

#include "expression_node.h"

class NotNode : public ExpressionNode
{

public:

    NotNode(ExpressionNode *operand);
    ~NotNode();

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

