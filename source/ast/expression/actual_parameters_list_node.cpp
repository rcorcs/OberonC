/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "actual_parameter_list_node.h"

#include "../../code_generator/intermediate/instruction/parameter_instruction.h"
#include "../../code_generator/intermediate/instruction/goto_instruction.h"

#include "../../code_generator/intermediate/instruction_argument/identifier_argument.h"
#include "../../code_generator/intermediate/instruction_argument/immediate_argument.h"

ActualParameterListNode::ActualParameterListNode()
    : ExpressionNode(NODE_TYPE_ACTUAL_PARAMETER_LIST)
{

}

ActualParameterListNode::~ActualParameterListNode()
{

}

list <ExpressionNode*> & ActualParameterListNode::getActualParameterList()
{
    return this->actualParameterList_;

}

void ActualParameterListNode::addActualParameter(ExpressionNode *expression)
{
    this->actualParameterList_.push_back(expression);
}


DataType ActualParameterListNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    // A operação de type checking sobre este nó específico não é necessária.
    // No entanto, para cada elemento encapsulado no mesmo (nós de expressões)
    // será feita uma chamada de type checking dentro do escopo das classes
    // FunctionCallNode e ProcedureCallNode.
    /*
    list<ExpressionNode*>::iterator it = this->actualParameterList_.begin();

    while(it != this->actualParameterList_.end())
    {
        (*it)->typeCheck(semanticDebugger);
        it++;
    }
    */
    return DATA_TYPE_UNDEFINED;
}

void ActualParameterListNode::checkConstant()
{
    /*
    list<ExpressionNode*>::iterator it = this->actualParameterList_.begin();

    while(it != this->actualParameterList_.end())
    {
        (*it)->checkConstant();
        it++;
    }
    */
    // Nenhuma checagem de valores constantes se aplica a este nó.
}

void ActualParameterListNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Actual Parameter List", nodeLevel);

    if(this->actualParameterList_.size() == 0)
    {
        astDebugger->insertLeafNode("{Actual Parameter List}", nodeLevel + 1);
    }
    else
    {
        list<ExpressionNode *>::iterator it = this->actualParameterList_.begin();

        while(it != this->actualParameterList_.end())
        {
            (*it)->debug(astDebugger, nodeLevel + 1);
            it++;
        }

    }

    astDebugger->closeParentNode("Actual Parameter List", nodeLevel);

}

void ActualParameterListNode::generateCCode(ostream &out)
{
    int count = this->actualParameterList_.size();

    for(list<ExpressionNode*>::reverse_iterator rit = this->actualParameterList_.rbegin(); rit != this->actualParameterList_.rend(); rit++)
    {
        (*rit)->generateCCode(out);
        if(--count)
            out << ", ";
    }
}

void ActualParameterListNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    setAddress( new ImmediateArgument(this->actualParameterList_.size()) );

    for(list<ExpressionNode*>::reverse_iterator rit = this->actualParameterList_.rbegin(); rit != this->actualParameterList_.rend(); rit++)
    {
        /*
        (*rit)->generateIntermediateCode(intermediateCode);
        intermediateCode->addInstruction( new ParameterInstruction((*rit)->getAddress()) );
        */
        ExpressionNode *expression = (*rit);

        ImmediateArgument *zeroImmediate = new ImmediateArgument(0);
        ImmediateArgument *oneImmediate = new ImmediateArgument(1);

        if(expression->getDataType()==DATA_TYPE_BOOLEAN){
            expression->setFalseLabelNumber( intermediateCode->getNextLabelNumber() );
            expression->setTrueLabelNumber( LABEL_FALL );
        }

        expression->generateIntermediateCode(intermediateCode, instructionVector);

        if(expression->getDataType()==DATA_TYPE_INTEGER)
            intermediateCode->addInstruction(instructionVector, new ParameterInstruction(expression->getAddress()) );
        else if(expression->getDataType()==DATA_TYPE_BOOLEAN){
            int label = intermediateCode->getNextLabelNumber();//(getNextLabelNumber()==LABEL_FALL)?intermediateCode->getNextLabelNumber():getNextLabelNumber();
            InstructionLabel *instructionLabel = new InstructionLabel(label);

            intermediateCode->addInstruction(instructionVector, new ParameterInstruction( oneImmediate ) );
            intermediateCode->addInstruction(instructionVector, new GotoInstruction( instructionLabel ) );

            intermediateCode->setPendingLabelNumber( expression->getFalseLabelNumber() );

            intermediateCode->addInstruction(instructionVector, new ParameterInstruction( zeroImmediate ) );
            //if(getNextLabelNumber()==LABEL_FALL)
            intermediateCode->setPendingLabelNumber( label );

            intermediateCode->addInstructionArgumentToCleanUpList( instructionLabel );
        }

        intermediateCode->addInstructionArgumentToCleanUpList( oneImmediate );
        intermediateCode->addInstructionArgumentToCleanUpList( zeroImmediate );
    }
}
