/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "constant_list_node.h"

ConstantListNode::ConstantListNode() : DeclarationNode(NODE_TYPE_CONSTANT_LIST)
{

}

ConstantListNode::~ConstantListNode()
{

}

void ConstantListNode::addConstantSequence(DeclarationSequenceNode *constSequence,
        DataType type)
{
    if(constSequence->getNextDeclaration() != NULL)
    {
        this->addConstantSequence((DeclarationSequenceNode*)constSequence->getNextDeclaration(), type);
    }

    ConstantNode *constant = (ConstantNode*)constSequence->getFirstDeclaration();
    constant->setType(type);

    this->constantList_.push_back(constant);
}

void ConstantListNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    list<ConstantNode*>::iterator it = this->constantList_.begin();

    while(it != this->constantList_.end())
    {
        (*it)->typeCheck(semanticDebugger);
        it++;
    }
}

void ConstantListNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Constant List", nodeLevel);

    if(this->constantList_.size() == 0)
    {
        astDebugger->insertLeafNode("{Empty Constant List}", nodeLevel + 1);
    }
    else
    {
        list<ConstantNode *>::iterator it = this->constantList_.begin();

        while(it != this->constantList_.end())
        {
            (*it)->debug(astDebugger, nodeLevel + 1);
            it++;
        }
    }

    astDebugger->closeParentNode("Constant List", nodeLevel);
}


void ConstantListNode::generateCCode(ostream &out)
{
    for(list<ConstantNode*>::iterator it = this->constantList_.begin(); it != this->constantList_.end(); it++)
    {
        (*it)->generateCCode(out);
    }
}
