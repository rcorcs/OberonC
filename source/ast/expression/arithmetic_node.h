/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef ARITHMETIC_NODE_H
#define ARITHMETIC_NODE_H

#include "expression_node.h"

#include "arithmetic_operator.h"

class ArithmeticNode : public ExpressionNode
{

public:

    ArithmeticNode(ExpressionNode *leftOperand, ArithmeticOperator operation, ExpressionNode *rightOperand);
    ~ArithmeticNode();

    DataType typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

protected:

    void checkConstant();

private:

    ExpressionNode *leftOperand_;
    ArithmeticOperator operation_;
    ExpressionNode *rightOperand_;
};

#endif
