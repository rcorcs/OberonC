/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef CONTINUE_NODE_H
#define CONTINUE_NODE_H

#include "statement_node.h"

class ContinueNode : public StatementNode
{

public:

    ContinueNode();
    ~ContinueNode();

    void typeCheck(SemanticDebugger *semanticDebugger);
    bool checkRepetition(const bool inRepetition, SemanticDebugger * semanticDebugger);

    void debug(ASTDebugger *astDebugger, int nodeLevel);


    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);
};

#endif
