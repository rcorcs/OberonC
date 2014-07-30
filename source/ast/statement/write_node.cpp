/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "write_node.h"

#include "../../code_generator/intermediate/instruction/write_instruction.h"

WriteNode::WriteNode(ExpressionNode *expression) : StatementNode(NODE_TYPE_WRITE)
{
    this->expression_ = expression;
}

WriteNode::~WriteNode()
{

}

void WriteNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    DataType type = this->expression_->typeCheck(semanticDebugger);


    if(type != DATA_TYPE_INTEGER && type != DATA_TYPE_STRING && type != DATA_TYPE_ERROR)
    {
        semanticDebugger->debugTypeMismatchError("Write/WriteLn statement",
                "Integer or String",
                getDataTypeName(type),
                this->expression_->getFirstLine());
    }
    else if( (type == DATA_TYPE_INTEGER || type == DATA_TYPE_STRING) && this->expression_->isConstant())
    {
        this->expression_ = this->expression_->getConstantExpression();
    }
}


void WriteNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Write", nodeLevel);

    this->expression_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Write", nodeLevel);

}

void WriteNode::generateCCode(ostream &out)
{

    if(expression_->getNodeType()==NODE_TYPE_STRING_LITERAL)
        out << "printf(\"%s\",";
    else out << "printf(\"%d\",";
    expression_->generateCCode(out);
    out << ");" << endl;
}

void WriteNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    expression_->generateIntermediateCode(intermediateCode, instructionVector);
    intermediateCode->addInstruction(instructionVector, new WriteInstruction(expression_->getAddress()));
}
