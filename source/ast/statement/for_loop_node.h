/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef FOR_LOOP_NODE_H
#define FOR_LOOP_NODE_H

#include "loop_node.h"
#include "statement_node.h"
#include "statement_sequence_node.h"
#include "../expression/expression_node.h"

class ForLoopNode : public StatementNode
{

public:

    ForLoopNode(StatementNode *initialisingStatement, ExpressionNode *expression, StatementNode *incrementStatement, StatementNode *loopBodyStatement);
    ~ForLoopNode();

    ExpressionNode *getExpression();
    void setExpression(ExpressionNode *expression);

    StatementNode *getInitialisingStatement();
    void setInitialisingStatement(StatementNode *statement);

    StatementNode *getIncrementStatement();
    void setIncrementStatement(StatementNode *statement);

    StatementNode *getLoopBodyStatement();
    void setLoopBodyStatement(StatementNode *statement);

    void typeCheck(SemanticDebugger *semanticDebugger);
    bool checkRepetition(const bool inRepetition, SemanticDebugger * semanticDebugger);
    bool checkReturn(DataType returnType, SemanticDebugger *semanticDebugger);

    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

private:
    ExpressionNode *expression_;
    StatementNode *initialisingStatement_;
    StatementNode *incrementStatement_;
    StatementNode *loopBodyStatement_;
};

#endif
