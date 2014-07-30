/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "formal_parameter_list_node.h"

FormalParameterListNode::FormalParameterListNode()
    : DeclarationNode(NODE_TYPE_FORMAL_PARAMETER_LIST)
{

}

FormalParameterListNode::~FormalParameterListNode()
{

}

void FormalParameterListNode::addFormalParameterSequence(DeclarationSequenceNode *formalParameterSequence,
        DataType type)
{
    if(formalParameterSequence->getNextDeclaration() != NULL)
    {
        this->addFormalParameterSequence((DeclarationSequenceNode*)formalParameterSequence->getNextDeclaration(), type);
    }

    FormalParameterNode *formalParameter = (FormalParameterNode*)formalParameterSequence->getFirstDeclaration();
    formalParameter->setType(type);

    this->formalParameterList_.push_back(formalParameter);
    formalParameter->getIdentifierInformation()->setOffset(this->formalParameterList_.size());
}

void FormalParameterListNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    list<FormalParameterNode*>::iterator it = this->formalParameterList_.begin();

    while(it != this->formalParameterList_.end())
    {
        (*it)->typeCheck(semanticDebugger);
        it++;
    }
}

void FormalParameterListNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Formal Parameter List", nodeLevel);

    if(this->formalParameterList_.size() == 0)
    {
        astDebugger->insertLeafNode("{Empty Formal Parameter List}", nodeLevel + 1);
    }
    else
    {
        list<FormalParameterNode *>::iterator it = this->formalParameterList_.begin();

        while(it != this->formalParameterList_.end())
        {
            (*it)->debug(astDebugger, nodeLevel + 1);
            it++;
        }
    }

    astDebugger->closeParentNode("Formal Parameter List", nodeLevel);
}


void FormalParameterListNode::generateCCode(ostream &out)
{
    int count = this->formalParameterList_.size();

    out << "(";
    for(list<FormalParameterNode*>::iterator it = this->formalParameterList_.begin(); it != this->formalParameterList_.end(); it++)
    {
        (*it)->generateCCode(out);
        if(--count)
            out << ", ";
    }
    out << ")" << endl << "{" << endl;
}

