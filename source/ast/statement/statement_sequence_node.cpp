/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "statement_sequence_node.h"

StatementSequenceNode::StatementSequenceNode(StatementNode *firstStatement,
        StatementNode *nextStatement)
    : StatementNode(NODE_TYPE_STATEMENT_SEQUENCE)
{
    this->firstStatement_ = firstStatement;
    this->nextStatement_ = nextStatement;
}

StatementSequenceNode::~StatementSequenceNode()
{

}

int StatementSequenceNode::getFirstLine() const
{
    return this->firstStatement_->getFirstLine();
}

void StatementSequenceNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    this->firstStatement_->typeCheck(semanticDebugger);
    this->nextStatement_->typeCheck(semanticDebugger);
}

bool StatementSequenceNode::checkRepetition(const bool inRepetition,
        SemanticDebugger *semanticDebugger)
{
    bool hasBreakOrContinue;

    hasBreakOrContinue = this->firstStatement_->checkRepetition(inRepetition,
                         semanticDebugger);

    if(hasBreakOrContinue && this->nextStatement_->getNodeType() != NODE_TYPE_SKIP_STATEMENT)
    {
        semanticDebugger->debugUnreachableStatementError(this->nextStatement_->getFirstLine());
    }

    hasBreakOrContinue = hasBreakOrContinue || this->nextStatement_->checkRepetition(inRepetition, semanticDebugger);

    return hasBreakOrContinue;
}

bool StatementSequenceNode::checkReturn(DataType returnType,
                                        SemanticDebugger *semanticDebugger)
{
    bool hasReturn = this->firstStatement_->checkReturn(returnType, semanticDebugger);

    if(hasReturn && this->nextStatement_->getNodeType() != NODE_TYPE_SKIP_STATEMENT)
    {
        semanticDebugger->debugUnreachableStatementError(this->nextStatement_->getFirstLine());
    }

    hasReturn = hasReturn || this->nextStatement_->checkReturn(returnType, semanticDebugger);

    return hasReturn;
}


void StatementSequenceNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Statement Sequence", nodeLevel);

    this->firstStatement_->debug(astDebugger, nodeLevel + 1);
    this->nextStatement_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Statement SequenceNode", nodeLevel);

}


void StatementSequenceNode::generateCCode(ostream &out)
{
    firstStatement_->generateCCode(out);
    nextStatement_->generateCCode(out);
}

void StatementSequenceNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    firstStatement_->setNextLabelNumber(LABEL_FALL);
    firstStatement_->setBreakLabelNumber( this->getBreakLabelNumber() );
    firstStatement_->setContinueLabelNumber( this->getContinueLabelNumber() );

    //cout << "break label 1o: " << firstStatement_->getBreakLabelNumber() << endl;
    //cout << "continue label 1o: " << firstStatement_->getContinueLabelNumber() << endl;

    nextStatement_->setNextLabelNumber( this->getNextLabelNumber());
    nextStatement_->setBreakLabelNumber( this->getBreakLabelNumber() );
    nextStatement_->setContinueLabelNumber( this->getContinueLabelNumber() );

    //cout << "break label 2o: " << nextStatement_->getBreakLabelNumber() << endl;
    //cout << "continue label 2o: " << nextStatement_->getContinueLabelNumber() << endl;

    firstStatement_->generateIntermediateCode(intermediateCode, instructionVector);
    nextStatement_->generateIntermediateCode(intermediateCode, instructionVector);
}
