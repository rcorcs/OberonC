/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "relational_node.h"
#include "integer_literal_node.h"
#include "boolean_literal_node.h"

#include "../../code_generator/intermediate/instruction/goto_instruction.h"
#include "../../code_generator/intermediate/instruction/conditional_goto_instruction.h"

RelationalNode::RelationalNode(ExpressionNode *leftOperand,
                               RelationalOperator operation,
                               ExpressionNode *rightOperand)
    : ExpressionNode(NODE_TYPE_RELATIONAL)
{
    this->leftOperand_ = leftOperand;
    this->operation_ = operation;
    this->rightOperand_ = rightOperand;
}

RelationalNode::~RelationalNode()
{
    delete this->constantExpression_;
}

DataType RelationalNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    DataType leftType = this->leftOperand_->typeCheck(semanticDebugger);

    if(leftType == DATA_TYPE_INTEGER)
    {
        DataType rightType = this->rightOperand_->typeCheck(semanticDebugger);

        if(rightType == DATA_TYPE_INTEGER)
        {
            this->checkConstant();
            setDataType(DATA_TYPE_BOOLEAN);
            return DATA_TYPE_BOOLEAN;
        }
        else if(rightType != DATA_TYPE_ERROR)
        {
            semanticDebugger->debugExpectedIntegerExpressionError("relational expression right's operand",
                    this->rightOperand_->getFirstLine());
        }
    }
    else if(leftType != DATA_TYPE_ERROR)
    {
        semanticDebugger->debugExpectedIntegerExpressionError("relational expression left's operand",
                this->leftOperand_->getFirstLine());
    }

    setDataType(DATA_TYPE_ERROR);
    return DATA_TYPE_ERROR;
}

void RelationalNode::checkConstant()
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
        int leftOperandValue = ((IntegerLiteralNode*)this->leftOperand_)->getValue();
        int rightOperandValue = ((IntegerLiteralNode*)this->rightOperand_)->getValue();

        bool constValue = false;

        switch(this->operation_)
        {
        case RELATIONAL_OPERATOR_LESS:
            constValue = (leftOperandValue < rightOperandValue);
            break;
        case RELATIONAL_OPERATOR_GREATER:
            constValue = (leftOperandValue > rightOperandValue);
            break;
        case RELATIONAL_OPERATOR_LESS_OR_EQUAL:
            constValue = (leftOperandValue <= rightOperandValue);
            break;
        case RELATIONAL_OPERATOR_GREATER_OR_EQUAL:
            constValue = (leftOperandValue >= rightOperandValue);
            break;
        case RELATIONAL_OPERATOR_EQUAL:
            constValue = (leftOperandValue == rightOperandValue);
            break;
        case RELATIONAL_OPERATOR_DIFFERENT:
            constValue = (leftOperandValue != rightOperandValue);
            break;

        default:
            break;
        }

        this->isConstant_ = true;
        this->constantExpression_ = new BooleanLiteralNode(constValue);
    }

}

void RelationalNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    const char * opName =getRelationalOperatorName(this->operation_);

    astDebugger->openParentNode(opName, nodeLevel);

    this->leftOperand_->debug(astDebugger, nodeLevel + 1);
    this->rightOperand_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode(opName, nodeLevel);
}

void RelationalNode::generateCCode(ostream &out)
{
    out << "(";
    leftOperand_->generateCCode(out);
    out << ") ";
    switch(this->operation_)
    {
    case RELATIONAL_OPERATOR_LESS:
        out << '<';
        break;
    case RELATIONAL_OPERATOR_GREATER:
        out << '>';
        break;
    case RELATIONAL_OPERATOR_LESS_OR_EQUAL:
        out << "<=";
        break;
    case RELATIONAL_OPERATOR_GREATER_OR_EQUAL:
        out << ">=";
        break;
    case RELATIONAL_OPERATOR_EQUAL:
        out << "==";
        break;
    case RELATIONAL_OPERATOR_DIFFERENT:
        out << "!=";
        break;
    default:
        break;

    }
    out << " (";
    rightOperand_->generateCCode(out);
    out << ")";
}

void RelationalNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    InstructionLabel *trueLabel = new InstructionLabel(getTrueLabelNumber());
    InstructionLabel *falseLabel = new InstructionLabel(getFalseLabelNumber());

    leftOperand_->generateIntermediateCode(intermediateCode, instructionVector);
    rightOperand_->generateIntermediateCode(intermediateCode, instructionVector);

    if(this->getFalseLabelNumber()==LABEL_FALL)
    {
        intermediateCode->addInstruction(instructionVector, new ConditionalGotoInstruction(this->operation_, leftOperand_->getAddress(), rightOperand_->getAddress(), trueLabel ) );
    }
    else if(this->getTrueLabelNumber()==LABEL_FALL)
    {
        intermediateCode->addInstruction(instructionVector, new ConditionalGotoInstruction( invertRelationalOperator(this->operation_), leftOperand_->getAddress(), rightOperand_->getAddress(), falseLabel ) );
    }
    else
    {
        intermediateCode->addInstruction(instructionVector, new ConditionalGotoInstruction(this->operation_, leftOperand_->getAddress(), rightOperand_->getAddress(), trueLabel ) );
        intermediateCode->addInstruction(instructionVector, new GotoInstruction( falseLabel ) );
    }

    intermediateCode->addInstructionArgumentToCleanUpList( trueLabel );
    intermediateCode->addInstructionArgumentToCleanUpList( falseLabel );
}
