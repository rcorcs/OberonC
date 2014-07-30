/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "constant_node.h"

#include "../expression/boolean_literal_node.h"
#include "../expression/integer_literal_node.h"

ConstantNode::ConstantNode(ConstantInformation *constantInformation,
                           ExpressionNode *expressionValue)
    : DeclarationNode(NODE_TYPE_CONSTANT)
{
    this->constantInformation_ = constantInformation;
    this->expressionValue_ = expressionValue;
}

ConstantNode::~ConstantNode()
{

}


DataType ConstantNode::getType() const
{
    return this->constantInformation_->getType();
}

void ConstantNode::setType(const DataType type)
{
    this->constantInformation_->setType(type);
}

ExpressionNode *ConstantNode::getExpressionValue() const
{
    return this->expressionValue_;
}

void ConstantNode::setExpressionValue(ExpressionNode *expressionValue)
{
    this->expressionValue_ = expressionValue;
}


const char *ConstantNode::getIdentifier() const
{
    return this->constantInformation_->getIdentifier();
}


void ConstantNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    DataType expectedType = this->getType();
    DataType expressionType = this->expressionValue_->typeCheck(semanticDebugger);

    if(expressionType != DATA_TYPE_ERROR && expressionType != expectedType)
    {
        const char * expectedTypeName = getDataTypeName(expectedType);
        const char * expressionTypeName = getDataTypeName(expressionType);

        semanticDebugger->debugTypeMismatchError("assignment statement",
                expectedTypeName,
                expressionTypeName,
                this->expressionValue_->getFirstLine());
    }
    else if(expressionType == expectedType)
    {
        if(this->expressionValue_->isConstant())
        {
            this->expressionValue_ = this->expressionValue_->getConstantExpression();

            ConstantValue constValue;

            if(this->getType() == DATA_TYPE_BOOLEAN)
            {
                constValue.boolValue = ((BooleanLiteralNode*)this->expressionValue_)->getValue();
            }
            else
            {
                constValue.intValue = ((IntegerLiteralNode*)this->expressionValue_)->getValue();
            }

            this->constantInformation_->setValue(constValue);
        }
    }
}

void ConstantNode::debug(ASTDebugger * astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Constant", nodeLevel);

    string id = "Identifier: ";
    string type = "Type: ";

    id += getIdentifier();
    type += getDataTypeName( this->getType() );

    astDebugger->insertLeafNode(id.c_str(), nodeLevel + 1);
    astDebugger->insertLeafNode(type.c_str(), nodeLevel + 1);

    astDebugger->openParentNode("Value", nodeLevel + 1);
    this->expressionValue_->debug(astDebugger, nodeLevel + 2);
    astDebugger->closeParentNode("Value", nodeLevel + 1);

    astDebugger->closeParentNode("Constant", nodeLevel);
}


void ConstantNode::generateCCode(ostream &out)
{
    out << "const ";
    switch(getType())
    {
    case DATA_TYPE_INTEGER:
        out << "int";
        break;
    case DATA_TYPE_BOOLEAN:
        out << "char";
        break;
    default:
        break;
    }
    out << " ";
    const char *str = getIdentifier();
    while(*str)
    {
        out << (char)tolower(*str);
        str++;
    }
    out << "=";
    getExpressionValue()->generateCCode(out);
    out << ";" << endl;
}
