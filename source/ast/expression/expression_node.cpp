/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "expression_node.h"

ExpressionNode::ExpressionNode(const NodeType nodeType) : Node(nodeType),
    trueLabelNumber_(LABEL_NONE), falseLabelNumber_(LABEL_NONE), dataType_(DATA_TYPE_UNDEFINED)
{
    this->constantExpression_ = NULL;
    this->isConstant_ = false;
    this->address_ = NULL;
}

ExpressionNode::~ExpressionNode()
{

}

bool ExpressionNode::isConstant() const
{
    return this->isConstant_;
}

ExpressionNode * ExpressionNode::getConstantExpression() const
{
    return this->constantExpression_;
}

InstructionArgument *ExpressionNode::getAddress()
{
    return this->address_;
}

void ExpressionNode::setTrueLabelNumber(const int trueLabelNumber)
{
    this->trueLabelNumber_ = trueLabelNumber;
}

int ExpressionNode::getTrueLabelNumber() const
{
    return this->trueLabelNumber_;
}

void ExpressionNode::setFalseLabelNumber(const int falseLabelNumber)
{
    this->falseLabelNumber_ = falseLabelNumber;
}

int ExpressionNode::getFalseLabelNumber() const
{
    return this->falseLabelNumber_;
}

void ExpressionNode::setAddress(InstructionArgument *address)
{
    this->address_ = address;
}

DataType ExpressionNode::getDataType() const
{
    return this->dataType_;
}

void ExpressionNode::setDataType(const DataType dataType)
{
    this->dataType_ = dataType;
}
