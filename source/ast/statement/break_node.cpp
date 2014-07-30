/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "break_node.h"

#include "../../code_generator/intermediate/instruction/goto_instruction.h"

BreakNode::BreakNode() : StatementNode(NODE_TYPE_BREAK)
{

}

BreakNode::~BreakNode()
{

}


void BreakNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    // Type checking não aplicável a este nó.

    // A verificação pertinente é quanto ao escopo de uso do sequenciador
    // correspondente, ou seja, se o mesmo foi utilizado dentro
    // do escopo de uma repetição e/ou se existem comandos que
    // aparecem sucedendo-o (e, portanto, inalcançáveis).

    // A primeira verificação é realizada pelo método
    // checkRepetition() desta classe.

    // A segunda é realizada pelo mesmo método implementado na
    // classe StatementSequenceNode.
}

bool BreakNode::checkRepetition(const bool inRepetition,
                                SemanticDebugger *semanticDebugger)
{
    if(!inRepetition)
    {
        semanticDebugger->debugBreakOutOfRepetitionError(this->getFirstLine());
    }

    return true;
}

void BreakNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->insertLeafNode("{Break}", nodeLevel);
}


void BreakNode::generateCCode(ostream &out)
{
    out << "break;" << endl;
}

void BreakNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    InstructionLabel *breakLabel = new InstructionLabel( this->getBreakLabelNumber() );
    intermediateCode->addInstruction(instructionVector, new GotoInstruction( breakLabel ));

    intermediateCode->addInstructionArgumentToCleanUpList( breakLabel );
}
