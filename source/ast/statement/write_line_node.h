/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef WRITE_LINE_NODE_H
#define WRITE_LINE_NODE_H

#include "statement_node.h"

class WriteLineNode : public StatementNode
{

public:

    WriteLineNode();
    ~WriteLineNode();

    void typeCheck(SemanticDebugger *semanticDebugger);

    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

private:

};

#endif
