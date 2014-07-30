/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "variable_list_node.h"


VariableListNode::VariableListNode()
    : DeclarationNode(NODE_TYPE_VARIABLE_LIST)
{

}

VariableListNode::~VariableListNode()
{

}


void VariableListNode::addVariableSequence(DeclarationSequenceNode *variableSequence,
        DataType type)
{
    if(variableSequence->getNextDeclaration() != NULL)
    {
        this->addVariableSequence((DeclarationSequenceNode*)variableSequence->getNextDeclaration(), type);
    }

    VariableNode *variable = (VariableNode*)variableSequence->getFirstDeclaration();
    variable->setType(type);


    this->variableList_.push_back(variable);
    variable->getIdentifierInformation()->setOffset(this->variableList_.size());
}

void VariableListNode::typeCheck(SemanticDebugger *semanticDebugger)
{

    list<VariableNode*>::iterator it = this->variableList_.begin();

    while(it != this->variableList_.end())
    {
        (*it)->typeCheck(semanticDebugger);
        it++;
    }
}

void VariableListNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Variable List", nodeLevel);

    if(this->variableList_.size() == 0)
    {
        astDebugger->insertLeafNode("{Empty Variable List}", nodeLevel + 1);
    }
    else
    {
        list<VariableNode *>::iterator it = this->variableList_.begin();

        while(it != this->variableList_.end())
        {
            (*it)->debug(astDebugger, nodeLevel + 1);
            it++;
        }
    }

    astDebugger->closeParentNode("Variable List", nodeLevel);
}

void VariableListNode::generateCCode(ostream &out)
{
    for(list<VariableNode*>::iterator it = this->variableList_.begin(); it != this->variableList_.end(); it++)
    {
        (*it)->generateCCode(out);
    }
}
