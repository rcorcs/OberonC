/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef WRITE_NODE_H
#define WRITE_NODE_H

#include "statement_node.h"
#include "../expression/expression_node.h"

class WriteNode : public StatementNode
{

public:

    WriteNode(ExpressionNode *expression);
    ~WriteNode();

    void typeCheck(SemanticDebugger *semanticDebugger);

    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

private:

    ExpressionNode *expression_;

};

#endif
