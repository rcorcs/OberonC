/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "negation_node.h"
#include "integer_literal_node.h"

#include "../../code_generator/intermediate/instruction/negation_instruction.h"

#include "../../code_generator/intermediate/instruction_argument/temporary_argument.h"

NegationNode::NegationNode(ExpressionNode *operand)
    : ExpressionNode(NODE_TYPE_NEGATION)

{
    this->operand_ = operand;
}

NegationNode::~NegationNode()
{
    delete this->constantExpression_;
}

DataType NegationNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    DataType operandType = this->operand_->typeCheck(semanticDebugger);

    if(operandType == DATA_TYPE_INTEGER)
    {
        this->checkConstant();
        setDataType(DATA_TYPE_INTEGER);
        return DATA_TYPE_INTEGER;
    }
    else if(operandType != DATA_TYPE_ERROR)
    {
        semanticDebugger->debugExpectedIntegerExpressionError("negation operand",
                this->operand_->getFirstLine());
    }

    setDataType(DATA_TYPE_ERROR);
    return DATA_TYPE_ERROR;
}

void NegationNode::checkConstant()
{
    if(this->operand_->isConstant())
    {
        this->operand_->getConstantExpression();

        int operandValue = ((IntegerLiteralNode*)this->operand_)->getValue();

        int constValue = -operandValue;

        this->isConstant_ = true;
        this->constantExpression_ = new IntegerLiteralNode(constValue);

        this->operand_ = this->constantExpression_;

    }
}


void NegationNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Minus", nodeLevel);

    this->operand_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Minus", nodeLevel);
}

void NegationNode::generateCCode(ostream &out)
{
    out << "-(";
    operand_->generateCCode(out);
    out << ")";
}

void NegationNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    this->operand_->generateIntermediateCode(intermediateCode, instructionVector);

    TemporaryArgument *dest = intermediateCode->getNextTemporary();
    this->setAddress(dest);

    intermediateCode->addInstruction(instructionVector, new NegationInstruction(this->operand_->getAddress(), dest) );

}
