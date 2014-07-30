/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "formal_parameter_node.h"

#include <string>
using namespace std;

FormalParameterNode::FormalParameterNode(FormalParameterInformation *formalParameterInfo)
    : DeclarationNode(NODE_TYPE_FORMAL_PARAMETER)
{
    this->formalParameterInfo_ = formalParameterInfo;
}

FormalParameterNode::~FormalParameterNode()
{

}

const char *FormalParameterNode::getIdentifier() const
{
    return this->formalParameterInfo_->getIdentifier();
}

FormalParameterInformation *FormalParameterNode::getIdentifierInformation()
{
    return this->formalParameterInfo_;
}

DataType FormalParameterNode::getType() const
{
    return this->formalParameterInfo_->getType();
}

void FormalParameterNode::setType(const DataType type)
{
    this->formalParameterInfo_->setType(type);
}


void FormalParameterNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    // Type Check não aplicável a este nó.
}

void FormalParameterNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Formal Parameter", nodeLevel);

    string id = "Identifier: ";
    string type = "Type: ";

    id += getIdentifier();
    type += getDataTypeName( this->getType() );

    astDebugger->insertLeafNode(id.c_str(), nodeLevel + 1);
    astDebugger->insertLeafNode(type.c_str(), nodeLevel + 1);

    astDebugger->closeParentNode("Formal Parameter", nodeLevel);
}


void FormalParameterNode::generateCCode(ostream &out)
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
}
