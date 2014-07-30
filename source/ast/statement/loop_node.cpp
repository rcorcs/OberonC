/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "loop_node.h"


LoopNode::LoopNode(const NodeType nodeType, StatementNode *statement, ExpressionNode *expression)
    : StatementNode(nodeType)
{
    this->statement_ = statement;
    this->expression_ = expression;
}

LoopNode::~LoopNode()
{

}


void LoopNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    DataType expressionType = this->expression_->typeCheck(semanticDebugger);


    if(expressionType != DATA_TYPE_BOOLEAN && expressionType != DATA_TYPE_ERROR)
    {
        semanticDebugger->debugExpectedBooleanExpressionError("repetition condition",
                this->expression_->getFirstLine());
    }
    else if(expressionType == DATA_TYPE_BOOLEAN && this->expression_->isConstant())
    {
        this->expression_ = this->expression_->getConstantExpression();
    }

    this->statement_->typeCheck(semanticDebugger);

}

bool LoopNode::checkRepetition(const bool inRepetition,
                                     SemanticDebugger *semanticDebugger)
{

    this->statement_->checkRepetition(true, semanticDebugger);

    return false;
}

bool LoopNode::checkReturn(DataType returnType, SemanticDebugger *semanticDebugger)
{
    this->statement_->checkReturn(returnType, semanticDebugger);

    return false;

}

StatementNode *LoopNode::getStatement()
{
    return this->statement_;
}

void LoopNode::setStatement(StatementNode *statement)
{
    this->statement_ = statement;
}

ExpressionNode *LoopNode::getExpression()
{
    return this->expression_;
}

void LoopNode::setExpression(ExpressionNode *expression)
{
    this->expression_ = expression;
}
