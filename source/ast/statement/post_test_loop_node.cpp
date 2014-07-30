/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "post_test_loop_node.h"

#include "../../code_generator/intermediate/instruction/goto_instruction.h"

PostTestLoopNode::PostTestLoopNode(StatementNode *statement, ExpressionNode *expression)
    : LoopNode(NODE_TYPE_POST_TEST_LOOP, statement, expression)
{}

PostTestLoopNode::~PostTestLoopNode()
{}


void PostTestLoopNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Post-Test Loop", nodeLevel);

    this->getStatement()->debug(astDebugger, nodeLevel + 1);
    this->getExpression()->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Post-Test Loop", nodeLevel);
}


void PostTestLoopNode::generateCCode(ostream &out)
{
    out << "do {";
    getStatement()->generateCCode(out);
    out << "} while (";
    getExpression()->generateCCode(out);
    out << ");" << endl;
}

void PostTestLoopNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    int expression_label = intermediateCode->getNextLabelNumber();
    int after_loop_label = (this->getNextLabelNumber()==LABEL_FALL)?intermediateCode->getNextLabelNumber():this->getNextLabelNumber();

    //getStatement()->setNextLabelNumber(LABEL_FALL);
    getStatement()->setNextLabelNumber(expression_label);
    getExpression()->setFalseLabelNumber( after_loop_label );

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
}
