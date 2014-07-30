/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "write_line_node.h"

#include "../../code_generator/intermediate/instruction/write_instruction.h"

#include "../../code_generator/intermediate/instruction_argument/string_argument.h"

WriteLineNode::WriteLineNode() : StatementNode(NODE_TYPE_WRITE_LINE)
{

}

WriteLineNode::~WriteLineNode()
{

}

void WriteLineNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    // Type Check não aplicável a este nodo.
}

void WriteLineNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->insertLeafNode("{Write New Line}", nodeLevel);
}


void WriteLineNode::generateCCode(ostream &out)
{
    out << "printf(\"\\n\");" << endl;
}

void WriteLineNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    StringArgument *stringArgument = new StringArgument("\"\\n\"");
    intermediateCode->addInstruction(instructionVector, new WriteInstruction( stringArgument ) );
    intermediateCode->addInstructionArgumentToCleanUpList( stringArgument );
}
