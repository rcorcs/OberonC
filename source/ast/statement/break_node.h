/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef BREAK_NODE_H
#define BREAK_NODE_H

#include "statement_node.h"

class BreakNode : public StatementNode
{

public:

    BreakNode();
    ~BreakNode();

    void typeCheck(SemanticDebugger *semanticDebugger);
    bool checkRepetition(const bool inRepetition, SemanticDebugger * semanticDebugger);

    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);
};

#endif
