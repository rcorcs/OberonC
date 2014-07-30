/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "or_node.h"
#include "boolean_literal_node.h"

OrNode::OrNode(ExpressionNode *leftOperand, ExpressionNode *rightOperand)
    : ExpressionNode(NODE_TYPE_OR)
{
    this->leftOperand_ = leftOperand;
    this->rightOperand_ = rightOperand;
}

OrNode::~OrNode()
{
    delete this->constantExpression_;
}

DataType OrNode::typeCheck(SemanticDebugger *semanticDebugger)
{

    DataType leftType = this->leftOperand_->typeCheck(semanticDebugger);

    if(leftType == DATA_TYPE_BOOLEAN)
    {
        DataType rightType = this->rightOperand_->typeCheck(semanticDebugger);

        if(rightType == DATA_TYPE_BOOLEAN)
        {
            this->checkConstant();
            setDataType(DATA_TYPE_BOOLEAN);
            return DATA_TYPE_BOOLEAN;
        }
        else if(rightType != DATA_TYPE_ERROR)
        {
            semanticDebugger->debugExpectedBooleanExpressionError("OR expression right's operand",
                    this->rightOperand_->getFirstLine());
        }

    }
    else if(leftType != DATA_TYPE_ERROR)
    {
        semanticDebugger->debugExpectedBooleanExpressionError("OR expression left's operand",
                this->leftOperand_->getFirstLine());
    }

    setDataType(DATA_TYPE_ERROR);
    return DATA_TYPE_ERROR;

}

void OrNode::checkConstant()
{
    if(this->leftOperand_->isConstant())
    {
        this->leftOperand_ = this->leftOperand_->getConstantExpression();
    }

    if(this->rightOperand_->isConstant())
    {
        this->rightOperand_ = this->rightOperand_->getConstantExpression();
    }

    if(this->leftOperand_->isConstant() && this->rightOperand_->isConstant())
    {
        bool leftOperandValue = ((BooleanLiteralNode*)this->leftOperand_)->getValue();
        bool rightOperandValue = ((BooleanLiteralNode*)this->rightOperand_)->getValue();

        bool constValue = (leftOperandValue || rightOperandValue);

        this->isConstant_ = true;
        this->constantExpression_ = new BooleanLiteralNode(constValue);
    }
}


void OrNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Or", nodeLevel);

    this->leftOperand_->debug(astDebugger, nodeLevel + 1);
    this->rightOperand_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Or", nodeLevel);
}

void OrNode::generateCCode(ostream &out)
{
    out << "(";
    leftOperand_->generateCCode(out);
    out << ") || (";
    rightOperand_->generateCCode(out);
    out << ")";
}


void OrNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    this->leftOperand_->setTrueLabelNumber( (getTrueLabelNumber()==LABEL_FALL)?intermediateCode->getNextLabelNumber():getTrueLabelNumber() );
    this->leftOperand_->setFalseLabelNumber( LABEL_FALL );

    this->rightOperand_->setTrueLabelNumber( getTrueLabelNumber() );
    this->rightOperand_->setFalseLabelNumber( getFalseLabelNumber() );

    this->leftOperand_->generateIntermediateCode(intermediateCode, instructionVector);
    this->rightOperand_->generateIntermediateCode(intermediateCode, instructionVector);

    if(getTrueLabelNumber()==LABEL_FALL)
        intermediateCode->setPendingLabelNumber( leftOperand_->getTrueLabelNumber() );
}

