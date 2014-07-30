/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "return_node.h"


#include "../../code_generator/intermediate/instruction/return_instruction.h"
#include "../../code_generator/intermediate/instruction/goto_instruction.h"

#include "../../code_generator/intermediate/instruction_argument/immediate_argument.h"

ReturnNode::ReturnNode(ExpressionNode *expression) : StatementNode(NODE_TYPE_RETURN), returnType_(DATA_TYPE_UNDEFINED)
{
    this->expression_ = expression;
}

ReturnNode::~ReturnNode()
{

}

void ReturnNode::typeCheck(SemanticDebugger *semanticDebugger)
{

    // Type checking não aplicável a este nó.

    // A verificação pertinente é quanto ao escopo de uso do sequenciador
    // correspondente, ou seja, se o mesmo foi utilizado dentro
    // do escopo de uma função/procedimento e/ou se existem comandos que
    // aparecem sucedendo-o (e, portanto, inalcançáveis).

    // A primeira verificação é realizada pelo método
    // checkReturn() desta classe.

    // A segunda é realizada pelo mesmo método implementado na
    // classe StatementSequenceNode.

}

DataType ReturnNode::getReturnType()
{
    return returnType_;
}

bool ReturnNode::checkReturn(DataType returnType, SemanticDebugger *semanticDebugger)
{
    if(returnType != DATA_TYPE_UNDEFINED && returnType != DATA_TYPE_VOID)
    {
        DataType expressionType = this->expression_->typeCheck(semanticDebugger);
        this->returnType_ = expressionType;

        if(expressionType != returnType && expressionType != DATA_TYPE_ERROR)
        {
            const char *returnTypeName = getDataTypeName(returnType);
            const char *expressionTypeName = getDataTypeName(expressionType);

            semanticDebugger->debugTypeMismatchError("return",
                    returnTypeName,
                    expressionTypeName,
                    this->expression_->getFirstLine());
        }
        else if(expressionType == returnType && this->expression_->isConstant())
        {
            this->expression_ = this->expression_->getConstantExpression();
        }
    }
    else if(returnType ==DATA_TYPE_VOID)
    {
        semanticDebugger->debugReturnInProcedureError(this->getFirstLine());
    }
    else
    {
        semanticDebugger->debugReturnOutOfFunctionError(this->getFirstLine());
    }

    return true;
}

void ReturnNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{

    astDebugger->openParentNode("Return", nodeLevel);

    this->expression_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Return", nodeLevel);
}


void ReturnNode::generateCCode(ostream &out)
{
    out << "return ";
    expression_->generateCCode(out);
    out << ";" << endl;
}

void ReturnNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    ImmediateArgument *zeroImmediate = new ImmediateArgument(0);
    ImmediateArgument *oneImmediate = new ImmediateArgument(1);

    if(getReturnType()==DATA_TYPE_BOOLEAN){
        expression_->setFalseLabelNumber( intermediateCode->getNextLabelNumber() );
        expression_->setTrueLabelNumber( LABEL_FALL );
    }

    expression_->generateIntermediateCode(intermediateCode, instructionVector);

    if(getReturnType()==DATA_TYPE_INTEGER)
        intermediateCode->addInstruction(instructionVector, new ReturnInstruction(expression_->getAddress()));
    else if(getReturnType()==DATA_TYPE_BOOLEAN){
        int label = (getNextLabelNumber()==LABEL_FALL)?intermediateCode->getNextLabelNumber():getNextLabelNumber();
        InstructionLabel *instructionLabel = new InstructionLabel(label);

        intermediateCode->addInstruction(instructionVector, new ReturnInstruction( oneImmediate ));
        intermediateCode->addInstruction(instructionVector, new GotoInstruction( instructionLabel ));

        intermediateCode->setPendingLabelNumber( expression_->getFalseLabelNumber() );

        intermediateCode->addInstruction(instructionVector, new ReturnInstruction( zeroImmediate ));
        if(getNextLabelNumber()==LABEL_FALL)
            intermediateCode->setPendingLabelNumber( label );

        intermediateCode->addInstructionArgumentToCleanUpList( instructionLabel );
    }

    intermediateCode->addInstructionArgumentToCleanUpList( oneImmediate );
    intermediateCode->addInstructionArgumentToCleanUpList( zeroImmediate );

}
