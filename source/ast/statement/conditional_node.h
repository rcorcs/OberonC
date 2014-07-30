/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef CONDITIONAL_NODE_H
#define CONDITIONAL_NODE_H

#include "statement_node.h"
#include "../expression/expression_node.h"
#include "statement_sequence_node.h"

#include "../../symbol_table/data_type.h"


class ConditionalNode : public StatementNode
{

public:

    ConditionalNode(ExpressionNode *expression,
                    StatementNode *firstStatement,
                    StatementNode *nextStatement);

    ~ConditionalNode();


    void typeCheck(SemanticDebugger *semanticDebugger);
    bool checkRepetition(const bool inRepetition, SemanticDebugger *semanticDebugger);
    bool checkReturn(DataType returnType, SemanticDebugger *semanticDebugger);

    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

private:

    ExpressionNode *expression_;
    StatementNode *firstStatement_;
    StatementNode *nextStatement_;

};

#endif
