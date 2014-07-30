/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "for_loop_node.h"

#include "../../code_generator/intermediate/instruction/goto_instruction.h"

ForLoopNode::ForLoopNode(StatementNode *initialisingStatement, ExpressionNode *expression, StatementNode *incrementStatement, StatementNode *loopBodyStatement)
    : StatementNode(NODE_TYPE_FOR_LOOP)
{
    this->initialisingStatement_ = initialisingStatement;
    this->incrementStatement_ = incrementStatement;
    this->loopBodyStatement_ = loopBodyStatement;
    this->expression_ = expression;
}

ForLoopNode::~ForLoopNode()
{}

ExpressionNode *ForLoopNode::getExpression()
{
    return this->expression_;
}

void ForLoopNode::setExpression(ExpressionNode *expression)
{
    this->expression_ = expression;
}

StatementNode *ForLoopNode::getInitialisingStatement()
{
    return this->initialisingStatement_;
}

void ForLoopNode::setInitialisingStatement(StatementNode *statement)
{
    this->initialisingStatement_ = statement;
}

StatementNode *ForLoopNode::getIncrementStatement()
{
    return this->incrementStatement_;
}

void ForLoopNode::setIncrementStatement(StatementNode *statement)
{
    this->incrementStatement_ = statement;
}

StatementNode *ForLoopNode::getLoopBodyStatement()
{
    return this->loopBodyStatement_;
}

void ForLoopNode::setLoopBodyStatement(StatementNode *statement)
{
    this->loopBodyStatement_ = statement;
}

void ForLoopNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("For Loop", nodeLevel);

    //this->getStatement()->debug(astDebugger, nodeLevel + 1);
    //this->getExpression()->debug(astDebugger, nodeLevel + 1);
    this->getInitialisingStatement()->debug(astDebugger, nodeLevel + 1);
    this->getExpression()->debug(astDebugger, nodeLevel + 1);
    this->getIncrementStatement()->debug(astDebugger, nodeLevel + 1);
    this->getLoopBodyStatement()->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("For Loop", nodeLevel);
}

void ForLoopNode::generateCCode(ostream &out)
{
    out << "for (";
    this->getInitialisingStatement()->generateCCode(out);
    out << "; ";
    getExpression()->generateCCode(out);
    out << "; ";
    this->getIncrementStatement()->generateCCode(out);
    out << ") {" << endl;
    getLoopBodyStatement()->generateCCode(out);
    out << "}" << endl;
}


void ForLoopNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    initialisingStatement_->typeCheck(semanticDebugger);

    DataType expressionType = this->expression_->typeCheck(semanticDebugger);

    if(expressionType != DATA_TYPE_BOOLEAN && expressionType != DATA_TYPE_ERROR)
    {
        semanticDebugger->debugExpectedBooleanExpressionError("repetition condition",
                this->expression_->getFirstLine());
    }
    else if(expressionType == DATA_TYPE_BOOLEAN && this->expression_->isConstant())
    {
        this->expression_ = this->expression_->getConstantExpression();
    }

    incrementStatement_->typeCheck(semanticDebugger);
    loopBodyStatement_->typeCheck(semanticDebugger);
    //this->statement_->typeCheck(semanticDebugger);

}

bool ForLoopNode::checkRepetition(const bool inRepetition,
                                     SemanticDebugger *semanticDebugger)
{

    this->loopBodyStatement_->checkRepetition(true, semanticDebugger);

    return false;
}

bool ForLoopNode::checkReturn(DataType returnType, SemanticDebugger *semanticDebugger)
{
    this->loopBodyStatement_->checkReturn(returnType, semanticDebugger);

    return false;

}


void ForLoopNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    int increment_label = intermediateCode->getNextLabelNumber();
    int expression_label = intermediateCode->getNextLabelNumber();
    int after_loop_label = (this->getNextLabelNumber()==LABEL_FALL)?intermediateCode->getNextLabelNumber():this->getNextLabelNumber();

    //getStatement()->setNextLabelNumber(LABEL_FALL);
    getInitialisingStatement()->setNextLabelNumber(LABEL_FALL);
    getLoopBodyStatement()->setNextLabelNumber(increment_label);
    getIncrementStatement()->setNextLabelNumber(expression_label);
    getExpression()->setFalseLabelNumber( after_loop_label );

    getInitialisingStatement()->generateIntermediateCode(intermediateCode, instructionVector);

    InstructionLabel *expressionInstructionLabel = new InstructionLabel(expression_label);
    intermediateCode->addInstruction(instructionVector, new GotoInstruction( expressionInstructionLabel ));

    if(intermediateCode->getPendingLabelNumber()==LABEL_NONE){
        getExpression()->setTrueLabelNumber( intermediateCode->getNextLabelNumber() );
        intermediateCode->setPendingLabelNumber( getExpression()->getTrueLabelNumber() );
    }else{
        getExpression()->setTrueLabelNumber( intermediateCode->getPendingLabelNumber() );
    }

    getLoopBodyStatement()->setBreakLabelNumber( after_loop_label );
    getLoopBodyStatement()->setContinueLabelNumber( increment_label );

    getLoopBodyStatement()->generateIntermediateCode(intermediateCode, instructionVector);

    intermediateCode->setPendingLabelNumber( increment_label );
    getIncrementStatement()->generateIntermediateCode(intermediateCode, instructionVector);

    intermediateCode->setPendingLabelNumber( expression_label );
    getExpression()->generateIntermediateCode( intermediateCode, instructionVector );

    if(this->getNextLabelNumber()==LABEL_FALL)
        intermediateCode->setPendingLabelNumber( after_loop_label );

    intermediateCode->addInstructionArgumentToCleanUpList( expressionInstructionLabel );

}
