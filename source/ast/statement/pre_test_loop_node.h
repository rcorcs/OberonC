/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef PRE_TEST_LOOP_NODE_H
#define PRE_TEST_LOOP_NODE_H

#include "loop_node.h"
#include "statement_node.h"
#include "statement_sequence_node.h"
#include "../expression/expression_node.h"

class PreTestLoopNode : public LoopNode
{

public:

    PreTestLoopNode(ExpressionNode *expression, StatementNode *statement);
    ~PreTestLoopNode();

    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

private:

};

#endif
