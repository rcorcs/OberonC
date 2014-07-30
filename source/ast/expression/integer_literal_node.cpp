/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "integer_literal_node.h"

#include "../../code_generator/intermediate/instruction_argument/immediate_argument.h"

#include <sstream>
using namespace std;

IntegerLiteralNode::IntegerLiteralNode(long value)
    : ExpressionNode(NODE_TYPE_INTEGER_LITERAL)
{
    this->value_ = value;
    this->checkConstant();
    this->setDataType(DATA_TYPE_INTEGER);
}

IntegerLiteralNode::~IntegerLiteralNode()
{}

long IntegerLiteralNode::getValue() const
{
    return this->value_;
}

DataType IntegerLiteralNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    this->checkConstant();
    setDataType(DATA_TYPE_INTEGER);
    return DATA_TYPE_INTEGER;
}

void IntegerLiteralNode::checkConstant()
{
    this->isConstant_ = true;
    this->constantExpression_ = this;
}

void IntegerLiteralNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    stringstream strValue;

    strValue << "Integer: " << this->value_;

    astDebugger->insertLeafNode(strValue.str().c_str(), nodeLevel);
}

void IntegerLiteralNode::generateCCode(ostream &out)
{
    out << this->value_;
}

void IntegerLiteralNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    ImmediateArgument *immediate = new ImmediateArgument(this->value_);
    setAddress( immediate );

    intermediateCode->addInstructionArgumentToCleanUpList( immediate );
}
