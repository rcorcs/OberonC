/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "arithmetic_node.h"
#include "integer_literal_node.h"
#include "boolean_literal_node.h"

#include "../../code_generator/intermediate/instruction/arithmetic_instruction.h"

#include "../../code_generator/intermediate/instruction_argument/temporary_argument.h"


ArithmeticNode::ArithmeticNode(ExpressionNode *leftOperand, ArithmeticOperator operation, ExpressionNode *rightOperand)
    : ExpressionNode(NODE_TYPE_ARITHMETIC)
{
    this->leftOperand_ = leftOperand;
    this->operation_ = operation;
    this->rightOperand_ = rightOperand;
}

ArithmeticNode::~ArithmeticNode()
{
    delete this->constantExpression_;
}


DataType ArithmeticNode::typeCheck(SemanticDebugger *semanticDebugger)
{

    DataType leftType = this->leftOperand_->typeCheck(semanticDebugger);

    if(leftType == DATA_TYPE_INTEGER)
    {
        DataType rightType = this->rightOperand_->typeCheck(semanticDebugger);

        if(rightType == DATA_TYPE_INTEGER)
        {
            this->checkConstant();
            setDataType(DATA_TYPE_INTEGER);
            return DATA_TYPE_INTEGER;
        }
        else if(rightType != DATA_TYPE_ERROR)
        {
            semanticDebugger->debugExpectedIntegerExpressionError("arithmetic expression right's operand", this->rightOperand_->getFirstLine());
        }
    }
    else if(leftType != DATA_TYPE_ERROR)
    {
        semanticDebugger->debugExpectedIntegerExpressionError("arithmetic expression left's operand", this->leftOperand_->getFirstLine());
    }

    setDataType(DATA_TYPE_ERROR);
    return DATA_TYPE_ERROR;
}


void ArithmeticNode::checkConstant()
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

        bool hasError = false;
        int constValue = 0;

        switch(this->operation_)
        {
        case ARITHMETIC_OPERATOR_ADD:
            constValue = (leftOperandValue + rightOperandValue);
            break;

        case ARITHMETIC_OPERATOR_SUB:
            constValue = (leftOperandValue - rightOperandValue);
            break;

        case ARITHMETIC_OPERATOR_MULT:
            constValue = (leftOperandValue * rightOperandValue);
            break;

        case ARITHMETIC_OPERATOR_DIV:

            if(rightOperandValue == 0)
            {
                hasError = true;
            }
            else
            {
                constValue = (leftOperandValue / rightOperandValue);
            }

            break;

        case ARITHMETIC_OPERATOR_MOD:

            if(rightOperandValue == 0)
            {
                hasError = true;
            }
            else
            {
                constValue = (leftOperandValue % rightOperandValue);
            }

            break;

            default:break;

        }

        if(!hasError)
        {
            this->isConstant_ = true;
            this->constantExpression_ = new IntegerLiteralNode(constValue);

        }
        else
        {
            // DIV by zero...
        }
    }
}


void ArithmeticNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    const char * opName = getArithmeticOperatorName(this->operation_);

    astDebugger->openParentNode(opName, nodeLevel);

    this->leftOperand_->debug(astDebugger, nodeLevel + 1);
    this->rightOperand_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode(opName, nodeLevel);

}

void ArithmeticNode::generateCCode(ostream &out)
{
    out << "(";
    leftOperand_->generateCCode(out);
    out << ") ";
    switch(this->operation_)
    {
    case ARITHMETIC_OPERATOR_ADD:
        out << '+';
        break;
    case ARITHMETIC_OPERATOR_SUB:
        out << '-';
        break;
    case ARITHMETIC_OPERATOR_MULT:
        out << '*';
        break;
    case ARITHMETIC_OPERATOR_DIV:
        out << '/';
        break;
    case ARITHMETIC_OPERATOR_MOD:
        out << '%';
        break;
    default:
        break;
    }
    out << " (";
    rightOperand_->generateCCode(out);
    out << ")";
}

void ArithmeticNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    this->leftOperand_->generateIntermediateCode(intermediateCode, instructionVector);
    this->rightOperand_->generateIntermediateCode(intermediateCode, instructionVector);

    TemporaryArgument *dest = intermediateCode->getNextTemporary();
    this->setAddress(dest);

    intermediateCode->addInstruction(instructionVector, new ArithmeticInstruction(this->operation_, this->leftOperand_->getAddress(), this->rightOperand_->getAddress(), dest) );

}
