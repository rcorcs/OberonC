/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef BOOLEAN_LITERAL_NODE_H
#define BOOLEAN_LITERAL_NODE_H

#include "expression_node.h"

class BooleanLiteralNode : public ExpressionNode
{
public:

    BooleanLiteralNode(bool value);
    ~BooleanLiteralNode();

    bool getValue() const;

    DataType typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

protected:

    void checkConstant();

private:

    bool value_;
};

#endif
