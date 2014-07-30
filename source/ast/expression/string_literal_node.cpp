/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "string_literal_node.h"
#include <cstring>

#include "../../code_generator/intermediate/instruction_argument/string_argument.h"

StringLiteralNode::StringLiteralNode(const char *value)
    : ExpressionNode(NODE_TYPE_STRING_LITERAL)
{
    this->value_ = new char[strlen(value) + 1];
    strcpy(this->value_, value);

    this->checkConstant();
}

StringLiteralNode::~StringLiteralNode()
{
    // Desaloca cópia da string.
    delete [] this->value_;
}

DataType StringLiteralNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    this->checkConstant();
    setDataType(DATA_TYPE_STRING);
    return DATA_TYPE_STRING;
}

void StringLiteralNode::checkConstant()
{
    this->isConstant_ = true;
    this->constantExpression_ = this;
}

void StringLiteralNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    string strValue = "String: ";
    strValue += this->value_;

    astDebugger->insertLeafNode(strValue.c_str(), nodeLevel);
}

void StringLiteralNode::generateCCode(ostream &out)
{
    out << this->value_;
}

void StringLiteralNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    StringArgument * stringArgument  =  new StringArgument(this->value_);
    setAddress( stringArgument );

    intermediateCode->addInstructionArgumentToCleanUpList( stringArgument );
}
