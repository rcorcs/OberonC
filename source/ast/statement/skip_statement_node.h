/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef SKIP_STATEMENT_NODE_H
#define SKIP_STATEMENT_NODE_H

#include "statement_node.h"

class SkipStatementNode : public StatementNode
{

public:

    SkipStatementNode();
    ~SkipStatementNode();

    void typeCheck(SemanticDebugger *semanticDebugger);

    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);
private:

};

#endif
