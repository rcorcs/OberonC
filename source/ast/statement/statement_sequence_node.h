/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef STATEMENT_SEQUENCE_NODE_H
#define STATEMENT_SEQUENCE_NODE_H

#include "statement_node.h"
#include "conditional_node.h"
#include "loop_node.h"
#include "break_node.h"
#include "continue_node.h"

class StatementSequenceNode : public StatementNode
{

public:

    StatementSequenceNode(StatementNode *firstStatement, StatementNode *nextStatement);
    ~StatementSequenceNode();
    int getFirstLine() const;

    void typeCheck(SemanticDebugger *semanticDebugger);
    bool checkRepetition(const bool inRepetition, SemanticDebugger * semanticDebugger);
    bool checkReturn(DataType returnType, SemanticDebugger *semanticDebugger);

    void debug(ASTDebugger *astDebugger, int nodeLevel);


    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);
private:

    StatementNode *firstStatement_;
    StatementNode *nextStatement_;

};

#endif
