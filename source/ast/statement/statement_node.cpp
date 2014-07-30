/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "statement_node.h"

StatementNode::StatementNode(const NodeType nodeType) : Node(nodeType),
    nextLabelNumber_(LABEL_NONE), breakLabelNumber_(LABEL_NONE), continueLabelNumber_(LABEL_NONE)
{

}

StatementNode::~StatementNode()
{

}


bool StatementNode::checkRepetition(const bool inRepetition,
                                    SemanticDebugger *semanticDebugger)
{
    return false;
}


bool StatementNode::checkReturn(DataType returnType,
                                SemanticDebugger *semanticDebugger)
{
    return false;
}

void StatementNode::setNextLabelNumber(const int nextLabelNumber)
{
    this->nextLabelNumber_ = nextLabelNumber;
}

int StatementNode::getNextLabelNumber() const
{
    return this->nextLabelNumber_;
}

void StatementNode::setBreakLabelNumber(const int breakLabelNumber)
{
    this->breakLabelNumber_ = breakLabelNumber;
}

int StatementNode::getBreakLabelNumber() const
{
    return this->breakLabelNumber_;
}

void StatementNode::setContinueLabelNumber(const int continueLabelNumber)
{
    this->continueLabelNumber_ = continueLabelNumber;
}

int StatementNode::getContinueLabelNumber() const
{
    return this->continueLabelNumber_;
}
