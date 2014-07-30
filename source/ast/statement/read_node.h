/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef READ_NODE_H
#define READ_NODE_H

#include "statement_node.h"
#include "../expression/identifier_node.h"

#include "../../symbol_table/data_type.h"

class ReadNode : public StatementNode
{

public:

    ReadNode(IdentifierNode *identifierNode);
    ~ReadNode();

    IdentifierNode *getIdentifier() const;

    void typeCheck(SemanticDebugger *semanticDebugger);

    void debug(ASTDebugger *astDebugger, int nodeLevel);

    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

private:

    IdentifierNode *identifier_;
};

#endif
