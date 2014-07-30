/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "assignment_node.h"

#include "../../code_generator/intermediate/instruction/copy_instruction.h"
#include "../../code_generator/intermediate/instruction/goto_instruction.h"

#include "../../code_generator/intermediate/instruction_argument/identifier_argument.h"
#include "../../code_generator/intermediate/instruction_argument/immediate_argument.h"

AssignmentNode::AssignmentNode(IdentifierNode * identifier,
                               ExpressionNode *rightExpression)
    : StatementNode(NODE_TYPE_ASSIGNMENT)
{
    this->identifier_ = identifier;
    this->rightExpression_ = rightExpression;
}

AssignmentNode::~AssignmentNode()
{

}

IdentifierNode * AssignmentNode::getIdentifier() const
{
    return this->identifier_;
}

void AssignmentNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    DataType expectedType = this->identifier_->typeCheck(semanticDebugger);
    DataType expressionType = this->rightExpression_->typeCheck(semanticDebugger);

    if(expressionType != expectedType && expressionType != DATA_TYPE_ERROR)
    {
        const char *expectedTypeName = getDataTypeName(expectedType);
        const char *expressionTypeName = getDataTypeName(expressionType);

        semanticDebugger->debugTypeMismatchError("assignment statement",
                expectedTypeName,
                expressionTypeName,
                this->rightExpression_->getFirstLine());
    }
    else if(expressionType == expectedType && this->rightExpression_->isConstant())
    {
        this->rightExpression_ = this->rightExpression_->getConstantExpression();
    }
}

void AssignmentNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Assignment", nodeLevel);

    this->identifier_->debug(astDebugger, nodeLevel + 1);
    this->rightExpression_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Assignment", nodeLevel);
}

void AssignmentNode::generateCCode(ostream &out)
{
    const char *str = identifier_->getIdentifier();
    while(*str)
    {
        out << (char)tolower(*str);
        str++;
    }
    out << " = ";
    rightExpression_->generateCCode(out);
    out << ";" << endl;
}

void AssignmentNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    ImmediateArgument *zeroImmediate = new ImmediateArgument(0);
    ImmediateArgument *oneImmediate = new ImmediateArgument(1);

    if(identifier_->getType()==DATA_TYPE_BOOLEAN)
    {
        rightExpression_->setFalseLabelNumber( intermediateCode->getNextLabelNumber() );
        rightExpression_->setTrueLabelNumber( LABEL_FALL );
    }

    IdentifierArgument * identifierArgument = new  IdentifierArgument(identifier_->getIdentifierInformation());
    identifier_->setAddress( identifierArgument );

    rightExpression_->generateIntermediateCode(intermediateCode, instructionVector);

    if(identifier_->getType()==DATA_TYPE_INTEGER)
        intermediateCode->addInstruction(instructionVector, new CopyInstruction(rightExpression_->getAddress(), identifierArgument));
    else if(identifier_->getType()==DATA_TYPE_BOOLEAN)
    {
        int label = (getNextLabelNumber()==LABEL_FALL)?intermediateCode->getNextLabelNumber():getNextLabelNumber();
        InstructionLabel *instructionLabel = new InstructionLabel(label);
        intermediateCode->addInstruction(instructionVector, new CopyInstruction( oneImmediate, identifierArgument));
        intermediateCode->addInstruction(instructionVector, new GotoInstruction( instructionLabel ));

        intermediateCode->setPendingLabelNumber( rightExpression_->getFalseLabelNumber() );

        intermediateCode->addInstruction(instructionVector, new CopyInstruction( zeroImmediate, identifierArgument));
        if(getNextLabelNumber()==LABEL_FALL)
            intermediateCode->setPendingLabelNumber( label );

        intermediateCode->addInstructionArgumentToCleanUpList( instructionLabel );
    }

    intermediateCode->addInstructionArgumentToCleanUpList( identifierArgument );
    intermediateCode->addInstructionArgumentToCleanUpList( zeroImmediate );
    intermediateCode->addInstructionArgumentToCleanUpList( oneImmediate );

}
