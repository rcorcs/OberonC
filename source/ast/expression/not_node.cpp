/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "not_node.h"
#include "boolean_literal_node.h"

NotNode::NotNode(ExpressionNode *operand) : ExpressionNode(NODE_TYPE_NOT)
{
    this->operand_ = operand;
}

NotNode::~NotNode()
{
    delete this->constantExpression_;
}

DataType NotNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    DataType operandType = this->operand_->typeCheck(semanticDebugger);

    if(operandType == DATA_TYPE_BOOLEAN)
    {
        this->checkConstant();
        setDataType(DATA_TYPE_BOOLEAN);
        return DATA_TYPE_BOOLEAN;
    }
    else if(operandType != DATA_TYPE_ERROR)
    {
        semanticDebugger->debugExpectedBooleanExpressionError("not operand",
                this->operand_->getFirstLine());
    }

    setDataType(DATA_TYPE_ERROR);
    return DATA_TYPE_ERROR;
}


void NotNode::checkConstant()
{
    if(this->operand_->isConstant())
    {
        this->operand_ = this->operand_->getConstantExpression();

        bool operandValue = ((BooleanLiteralNode*)this->operand_)->getValue();
        bool constValue = !operandValue;

        this->isConstant_ = true;
        this->constantExpression_ = new BooleanLiteralNode(constValue);

        this->operand_ = this->constantExpression_;
    }
}

void NotNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Not", nodeLevel);

    this->operand_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Not", nodeLevel);

}

void NotNode::generateCCode(ostream &out)
{
    out << "!(";
    operand_->generateCCode(out);
    out << ")";
}

void NotNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    operand_->setTrueLabelNumber( this->getFalseLabelNumber() );
    operand_->setFalseLabelNumber( this->getTrueLabelNumber() );
    operand_->generateIntermediateCode(intermediateCode, instructionVector);
}
