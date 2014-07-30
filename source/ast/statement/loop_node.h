/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef LOOP_NODE_H
#define LOOP_NODE_H

#include "statement_node.h"
#include "statement_sequence_node.h"
#include "../expression/expression_node.h"

class LoopNode : public StatementNode
{

public:

    LoopNode(const NodeType nodeType, StatementNode *statement, ExpressionNode *expression);
    ~LoopNode();

    void typeCheck(SemanticDebugger *semanticDebugger);
    bool checkRepetition(const bool inRepetition, SemanticDebugger * semanticDebugger);
    bool checkReturn(DataType returnType, SemanticDebugger *semanticDebugger);

    StatementNode *getStatement();
    void setStatement(StatementNode *statement);

    ExpressionNode *getExpression();
    void setExpression(ExpressionNode *expression);

    virtual void debug(ASTDebugger *astDebugger, int nodeLevel) = 0;

    virtual void generateCCode(ostream &out) = 0;
    virtual void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector) = 0;

private:

    StatementNode *statement_;
    ExpressionNode *expression_;

};

#endif
