/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "variable_node.h"


VariableNode::VariableNode(VariableInformation *variableInfo)
    : DeclarationNode(NODE_TYPE_VARIABLE)
{
    this->variableInfo_ = variableInfo;
}

VariableNode::~VariableNode()
{

}

const char *VariableNode::getIdentifier() const
{
    return this->variableInfo_->getIdentifier();
}

VariableInformation *VariableNode::getIdentifierInformation()
{
    return this->variableInfo_;
}

DataType VariableNode::getType() const
{
    return this->variableInfo_->getType();
}

void VariableNode::setType(const DataType type)
{
    this->variableInfo_->setType(type);
}


void VariableNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    // Type Check não aplicável a este nó.
}

void VariableNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Variable", nodeLevel);

    string id = "Identifier: ";
    string type = "Type: ";

    id += getIdentifier();
    type += getDataTypeName( this->getType() );

    astDebugger->insertLeafNode(id.c_str(), nodeLevel + 1);
    astDebugger->insertLeafNode(type.c_str(), nodeLevel + 1);

    astDebugger->closeParentNode("Variable", nodeLevel);

}

void VariableNode::generateCCode(ostream &out)
{
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
    out << ";" << endl;
}
