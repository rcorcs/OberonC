/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "pre_test_loop_node.h"

#include "../../code_generator/intermediate/instruction/goto_instruction.h"

PreTestLoopNode::PreTestLoopNode(ExpressionNode *expression, StatementNode *statement)
    : LoopNode(NODE_TYPE_PRE_TEST_LOOP, statement, expression)
{}

PreTestLoopNode::~PreTestLoopNode()
{}

void PreTestLoopNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Pre-Test Loop", nodeLevel);

    this->getStatement()->debug(astDebugger, nodeLevel + 1);
    this->getExpression()->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Pre-Test Loop", nodeLevel);
}

void PreTestLoopNode::generateCCode(ostream &out)
{
    out << "while (";
    getExpression()->generateCCode(out);
    out << ") {" << endl;
    getStatement()->generateCCode(out);
    out << "}" << endl;
}

void PreTestLoopNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    int expression_label = intermediateCode->getNextLabelNumber();
    int after_loop_label = (this->getNextLabelNumber()==LABEL_FALL)?intermediateCode->getNextLabelNumber():this->getNextLabelNumber();

    //getStatement()->setNextLabelNumber(LABEL_FALL);
    getStatement()->setNextLabelNumber(expression_label);
    getExpression()->setFalseLabelNumber( after_loop_label );

    InstructionLabel *expressionInstructionLabel = new InstructionLabel(expression_label);
    intermediateCode->addInstruction(instructionVector, new GotoInstruction( expressionInstructionLabel ));

    if(intermediateCode->getPendingLabelNumber()==LABEL_NONE){
        getExpression()->setTrueLabelNumber( intermediateCode->getNextLabelNumber() );
        intermediateCode->setPendingLabelNumber( getExpression()->getTrueLabelNumber() );
    }else{
        getExpression()->setTrueLabelNumber( intermediateCode->getPendingLabelNumber() );
    }

    getStatement()->setBreakLabelNumber( after_loop_label );
    getStatement()->setContinueLabelNumber( expression_label );

    getStatement()->generateIntermediateCode(intermediateCode, instructionVector);

    intermediateCode->setPendingLabelNumber( expression_label );
    getExpression()->generateIntermediateCode( intermediateCode, instructionVector );

    if(this->getNextLabelNumber()==LABEL_FALL)
        intermediateCode->setPendingLabelNumber( after_loop_label );

    intermediateCode->addInstructionArgumentToCleanUpList( expressionInstructionLabel );
}
