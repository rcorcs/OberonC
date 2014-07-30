/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef RELATIONAL_NODE_H
#define RELATIONAL_NODE_H

#include "expression_node.h"
#include "relational_operator.h"

class RelationalNode : public ExpressionNode
{

public:

    RelationalNode(ExpressionNode *leftOperand, RelationalOperator operation, ExpressionNode *rightOperand);
    ~RelationalNode();

    DataType typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

protected:


    void checkConstant();

private:

    ExpressionNode *leftOperand_;
    RelationalOperator operation_;
    ExpressionNode *rightOperand_;
};


#endif
