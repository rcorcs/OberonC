#include "node.h"

Node::Node(const NodeType nodeType)
{
    setNodeType(nodeType);
}

Node::~Node()
{

}

NodeType Node::getNodeType() const
{
    return this->nodeType_;
}

void Node::setNodeType(const NodeType nodeType)
{
    this->nodeType_ = nodeType;
}

int Node::getFirstLine() const
{

    return this->firstLine_;
}

void Node::setFirstLine(int firstLine)
{

    this->firstLine_ = firstLine;
}
