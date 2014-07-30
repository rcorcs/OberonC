/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#ifndef INTEGER_LITERAL_NODE_H
#define INTEGER_LITERAL_NODE_H

#include "expression_node.h"

class IntegerLiteralNode : public ExpressionNode
{

public:

    IntegerLiteralNode(long value);
    ~IntegerLiteralNode();

    long getValue() const;

    DataType typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

protected:


    void checkConstant();

private:

    long value_;
};

#endif


