/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "conditional_node.h"

#include "../../code_generator/intermediate/instruction/goto_instruction.h"


ConditionalNode::ConditionalNode(ExpressionNode *expression,
                                 StatementNode *firstStatement,
                                 StatementNode *nextStatement)
    : StatementNode(NODE_TYPE_CONDITIONAL)
{
    this->expression_ = expression;
    this->firstStatement_ = firstStatement;
    this->nextStatement_ = nextStatement;
}

ConditionalNode::~ConditionalNode()
{


}

void ConditionalNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    DataType expressionType = this->expression_->typeCheck(semanticDebugger);

    if(expressionType != DATA_TYPE_BOOLEAN && expressionType != DATA_TYPE_ERROR)
    {
        semanticDebugger->debugExpectedBooleanExpressionError("conditional statement",
                this->expression_->getFirstLine());
    }
    else if(expressionType == DATA_TYPE_BOOLEAN && this->expression_->isConstant())
    {
        this->expression_ = this->expression_->getConstantExpression();
    }

    this->firstStatement_->typeCheck(semanticDebugger);
    this->nextStatement_->typeCheck(semanticDebugger);
}

bool ConditionalNode::checkRepetition(const bool inRepetition,
                                      SemanticDebugger * semanticDebugger)
{
    bool hasBreakOrContinue  =

        ( this->firstStatement_->checkRepetition(inRepetition,
                semanticDebugger)

          &&

          this->nextStatement_->checkRepetition(inRepetition,
                  semanticDebugger)
        );


    return hasBreakOrContinue;
}

bool ConditionalNode::checkReturn(DataType returnType, SemanticDebugger *semanticDebugger)
{
    bool hasReturn =   ( this->firstStatement_->checkReturn(returnType,
                         semanticDebugger)

                         &&

                         this->nextStatement_->checkReturn(returnType,
                                 semanticDebugger)
                       );

    return hasReturn;

}


void ConditionalNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Conditional", nodeLevel);

    this->expression_->debug(astDebugger, nodeLevel + 1);
    this->firstStatement_->debug(astDebugger, nodeLevel + 1);
    this->nextStatement_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Conditional", nodeLevel);

}

void ConditionalNode::generateCCode(ostream &out)
{
    out << "if(";
    expression_->generateCCode(out);
    out << ") {" << endl;
    firstStatement_->generateCCode(out);
    out << "} else {" << endl;
    nextStatement_->generateCCode(out);
    out << "}" << endl;
}

void ConditionalNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    expression_->setTrueLabelNumber( LABEL_FALL );
    expression_->setFalseLabelNumber( intermediateCode->getNextLabelNumber() );

    int label = (this->getNextLabelNumber()==LABEL_FALL)?intermediateCode->getNextLabelNumber():this->getNextLabelNumber();

    firstStatement_->setNextLabelNumber(label);
    firstStatement_->setBreakLabelNumber( this->getBreakLabelNumber() );
    firstStatement_->setContinueLabelNumber( this->getContinueLabelNumber() );

    nextStatement_->setNextLabelNumber(label);
    nextStatement_->setBreakLabelNumber( this->getBreakLabelNumber() );
    nextStatement_->setContinueLabelNumber( this->getContinueLabelNumber() );

    expression_->generateIntermediateCode(intermediateCode, instructionVector);

    firstStatement_->generateIntermediateCode(intermediateCode, instructionVector);

    InstructionLabel *afterIfLabel = new InstructionLabel( firstStatement_->getNextLabelNumber() );
    intermediateCode->addInstruction(instructionVector, new GotoInstruction( afterIfLabel ));
    intermediateCode->setPendingLabelNumber( expression_->getFalseLabelNumber() );

    nextStatement_->generateIntermediateCode(intermediateCode, instructionVector);

    if( this->getNextLabelNumber()==LABEL_FALL )
        intermediateCode->setPendingLabelNumber( label );

    intermediateCode->addInstructionArgumentToCleanUpList( afterIfLabel );
}
