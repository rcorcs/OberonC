/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef RETURN_NODE_H
#define RETURN_NODE_H

#include "statement_node.h"
#include "../expression/expression_node.h"

class ReturnNode : public StatementNode
{

public:

    ReturnNode(ExpressionNode *expression);
    ~ReturnNode();

    DataType getReturnType();

    void typeCheck(SemanticDebugger *semanticDebugger);
    bool checkReturn(DataType returnType, SemanticDebugger *semanticDebugger);

    void debug(ASTDebugger *astDebugger, int nodeLevel);


    void generateCCode(ostream &out);
    void generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector);

private:

    ExpressionNode *expression_;
    DataType returnType_;
};

#endif
