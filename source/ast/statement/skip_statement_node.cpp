/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "skip_statement_node.h"

#include "../../code_generator/intermediate/instruction/nop_instruction.h"

SkipStatementNode::SkipStatementNode() : StatementNode(NODE_TYPE_SKIP_STATEMENT)
{

}

SkipStatementNode::~SkipStatementNode()
{

}

void SkipStatementNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    // Type checking não aplicável a este nó.
}

void SkipStatementNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->insertLeafNode("{Skip Statement}", nodeLevel);
}

void SkipStatementNode::generateCCode(ostream &out)
{
}

void SkipStatementNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    intermediateCode->addInstruction(instructionVector, new NopInstruction());
}
