/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "boolean_literal_node.h"


#include "../../code_generator/intermediate/instruction/goto_instruction.h"

#include "../../code_generator/intermediate/instruction_argument/temporary_argument.h"

BooleanLiteralNode::BooleanLiteralNode(bool value)
    : ExpressionNode(NODE_TYPE_BOOLEAN_LITERAL)
{
    this->value_ = value;
    this->checkConstant();
    this->setDataType(DATA_TYPE_BOOLEAN);
}

BooleanLiteralNode::~BooleanLiteralNode()
{

}

bool BooleanLiteralNode::getValue() const
{
    return this->value_;
}

DataType BooleanLiteralNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    this->checkConstant();
    setDataType(DATA_TYPE_BOOLEAN);
    return DATA_TYPE_BOOLEAN;
}

void BooleanLiteralNode::checkConstant()
{
    this->isConstant_ = true;
    this->constantExpression_ = this;
}

void BooleanLiteralNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    string strValue = "Boolean: ";

    strValue += (this->value_ ? "true" : "false");

    astDebugger->insertLeafNode(strValue.c_str(), nodeLevel);
}

void BooleanLiteralNode::generateCCode(ostream &out)
{
    out << (int)this->value_;
}

void BooleanLiteralNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    InstructionLabel *trueLabel = new InstructionLabel(getTrueLabelNumber());
    InstructionLabel *falseLabel = new InstructionLabel(getFalseLabelNumber());

    if(this->value_){
        if(getTrueLabelNumber()>LABEL_FALL)
            intermediateCode->addInstruction(instructionVector, new GotoInstruction( trueLabel ) );
    }else{
        if(getFalseLabelNumber()>LABEL_FALL)
            intermediateCode->addInstruction(instructionVector, new GotoInstruction( falseLabel ) );
    }

    intermediateCode->addInstructionArgumentToCleanUpList(trueLabel);
    intermediateCode->addInstructionArgumentToCleanUpList(falseLabel);
}
