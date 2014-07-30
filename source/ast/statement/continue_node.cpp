/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "continue_node.h"

#include "../../code_generator/intermediate/instruction/goto_instruction.h"

ContinueNode::ContinueNode() : StatementNode(NODE_TYPE_CONTINUE)
{

}

ContinueNode::~ContinueNode()
{

}

void ContinueNode::typeCheck(SemanticDebugger *semanticDebugger)
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

bool ContinueNode::checkRepetition(const bool inRepetition,
                                   SemanticDebugger *semanticDebugger)
{
    if(!inRepetition)
    {
        semanticDebugger->debugContinueOutOfRepetitionError(this->getFirstLine());
    }

    return true;
}


void ContinueNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->insertLeafNode("{Continue}", nodeLevel);
}

void ContinueNode::generateCCode(ostream &out)
{
    out << "continue;" << endl;
}

void ContinueNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    InstructionLabel *continueLabel = new InstructionLabel( this->getContinueLabelNumber() );
    intermediateCode->addInstruction(instructionVector, new GotoInstruction( continueLabel ));
    intermediateCode->addInstructionArgumentToCleanUpList( continueLabel );
}
