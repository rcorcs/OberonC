/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "identifier_node.h"
#include "boolean_literal_node.h"
#include "integer_literal_node.h"


#include "../../code_generator/intermediate/instruction/conditional_goto_instruction.h"
#include "../../code_generator/intermediate/instruction/goto_instruction.h"

#include "../../code_generator/intermediate/instruction_argument/immediate_argument.h"
#include "../../code_generator/intermediate/instruction_argument/identifier_argument.h"

IdentifierNode::IdentifierNode(IdentifierInformation *identifierInfo)
    : ExpressionNode(NODE_TYPE_IDENTIFIER)
{
    this->identifierInfo_ = identifierInfo;
}

IdentifierNode::~IdentifierNode()
{
    delete this->constantExpression_;
}

IdentifierInformation *IdentifierNode::getIdentifierInformation()
{
    return this->identifierInfo_;
}

const char *IdentifierNode::getIdentifier() const
{
    return this->identifierInfo_->getIdentifier();
}


IdentifierCategoryType IdentifierNode::getCategoryType() const
{
    return this->identifierInfo_->getCategoryType();
}


DataType IdentifierNode::getType() const
{
    if(this->identifierInfo_->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_CONSTANT)
    {
        return ((ConstantInformation*)this->identifierInfo_)->getType();
    }
    else if(this->identifierInfo_->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_VARIABLE)
    {
        return ((VariableInformation*)this->identifierInfo_)->getType();
    }
    else
    {
        return ((FormalParameterInformation *)this->identifierInfo_)->getType();
    }
}

DataType IdentifierNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    this->checkConstant();
    setDataType(this->getType());
    return this->getType();
}

void IdentifierNode::checkConstant()
{
    if(this->identifierInfo_->getCategoryType() == IDENTIFIER_CATEGORY_TYPE_CONSTANT)
    {
        if(this->getType() == DATA_TYPE_BOOLEAN)
        {
            this->isConstant_ = true;

            bool constValue = ((ConstantInformation*)this->identifierInfo_)->getValue().boolValue;
            this->constantExpression_ = new BooleanLiteralNode(constValue);
        }
        else if(this->getType() == DATA_TYPE_INTEGER)
        {
            this->isConstant_ = true;

            int constValue = ((ConstantInformation*)this->identifierInfo_)->getValue().intValue;
            this->constantExpression_ = new IntegerLiteralNode(constValue);
        }
    }
}

void IdentifierNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    string id = "ID: ";
    string category = "Category: ";
    string type = "Type: ";

    const char * categoryName;
    const char * typeName;

    IdentifierCategoryType identifierCategory = this->identifierInfo_->getCategoryType() ;

    if(identifierCategory == IDENTIFIER_CATEGORY_TYPE_CONSTANT)
    {
        ConstantInformation * constantInfo = (ConstantInformation *)this->identifierInfo_;

        categoryName = getIdentifierCategoryTypeName(IDENTIFIER_CATEGORY_TYPE_CONSTANT);
        typeName = getDataTypeName( constantInfo->getType() );
    }
    else if(identifierCategory == IDENTIFIER_CATEGORY_TYPE_CONSTANT)
    {
        VariableInformation * variableInfo = (VariableInformation *)this->identifierInfo_;

        categoryName = getIdentifierCategoryTypeName(IDENTIFIER_CATEGORY_TYPE_VARIABLE);
        typeName = getDataTypeName( variableInfo->getType() );
    }
    else
    {
        FormalParameterInformation * formalParameterInfo = (FormalParameterInformation *)this->identifierInfo_;

        categoryName = getIdentifierCategoryTypeName(IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER);
        typeName = getDataTypeName( formalParameterInfo->getType() );
    }



    id += this->identifierInfo_->getIdentifier();
    type += typeName;
    category += categoryName;

    astDebugger->openParentNode("Identifier", nodeLevel);

    astDebugger->insertLeafNode(id.c_str(), nodeLevel + 1);
    astDebugger->insertLeafNode(type.c_str(), nodeLevel + 1);
    astDebugger->insertLeafNode(category.c_str(), nodeLevel + 1);

    astDebugger->closeParentNode("Identifier", nodeLevel);
}

void IdentifierNode::generateCCode(ostream &out)
{
    const char *str = getIdentifier();
    while(*str)
    {
        out << (char)tolower(*str);
        str++;
    }
}

void IdentifierNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    ImmediateArgument *zeroImmediate = new ImmediateArgument(0);
    InstructionLabel *trueLabel = new InstructionLabel(getTrueLabelNumber());
    InstructionLabel *falseLabel = new InstructionLabel(getFalseLabelNumber());

IdentifierArgument * identifierArgument  = new IdentifierArgument(this->identifierInfo_);
    setAddress( identifierArgument );
    if(getType()==DATA_TYPE_BOOLEAN){
        if(getFalseLabelNumber()==LABEL_FALL)
            intermediateCode->addInstruction(instructionVector, new ConditionalGotoInstruction( RELATIONAL_OPERATOR_DIFFERENT, identifierArgument, zeroImmediate, trueLabel ) );
        else if(getTrueLabelNumber()==LABEL_FALL)
            intermediateCode->addInstruction(instructionVector, new ConditionalGotoInstruction( RELATIONAL_OPERATOR_EQUAL, identifierArgument, zeroImmediate, falseLabel ) );
        else{
            intermediateCode->addInstruction(instructionVector, new ConditionalGotoInstruction( RELATIONAL_OPERATOR_DIFFERENT, identifierArgument, zeroImmediate, trueLabel ) );
            intermediateCode->addInstruction(instructionVector, new GotoInstruction( falseLabel ) );
        }
    }

    intermediateCode->addInstructionArgumentToCleanUpList( identifierArgument );
    intermediateCode->addInstructionArgumentToCleanUpList( zeroImmediate );
    intermediateCode->addInstructionArgumentToCleanUpList( trueLabel );
    intermediateCode->addInstructionArgumentToCleanUpList( falseLabel );

}

