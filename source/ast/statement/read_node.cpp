/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "read_node.h"

#include "../../code_generator/intermediate/instruction/read_instruction.h"

ReadNode::ReadNode(IdentifierNode *identifier) : StatementNode(NODE_TYPE_READ)
{
    this->identifier_ = identifier;
}

ReadNode::~ReadNode()
{

}

IdentifierNode * ReadNode::getIdentifier() const
{
    return this->identifier_;
}



void ReadNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    if( this->identifier_->typeCheck(semanticDebugger) != DATA_TYPE_INTEGER)
    {
        semanticDebugger->debugExpectedNonConstIntegerIdentifierError("Read statement",
                this->identifier_->getFirstLine());
    }
    else if( this->identifier_->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_CONSTANT)
    {
        semanticDebugger->debugUnexpectedConstantIdentifierError("Read statement",
                this->identifier_->getFirstLine());
    }
}


void ReadNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Read", nodeLevel);

    this->identifier_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Read", nodeLevel);
}


void ReadNode::generateCCode(ostream &out)
{
    out << "scanf(\"%d\", &";
    const char *str = identifier_->getIdentifier();
    while(*str)
    {
        out << (char)tolower(*str);
        str++;
    }
    out << ");" << endl;
}

void ReadNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    identifier_->generateIntermediateCode(intermediateCode, instructionVector);
    intermediateCode->addInstruction(instructionVector, new ReadInstruction(identifier_->getAddress()));
}
