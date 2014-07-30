/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef STRING_LITERAL_NODE_H
#define STRING_LITERAL_NODE_H

#include "expression_node.h"

class StringLiteralNode : public ExpressionNode
{

public:

    StringLiteralNode(const char *value);
    ~StringLiteralNode();

    DataType typeCheck(SemanticDebugger *semanticDebugger);
    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

protected:


    void checkConstant();

private:

    char *value_;
};

#endif



