/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "function_call_node.h"


#include "../../code_generator/intermediate/instruction/call_instruction.h"
#include "../../code_generator/intermediate/instruction/conditional_goto_instruction.h"
#include "../../code_generator/intermediate/instruction/goto_instruction.h"

#include "../../code_generator/intermediate/instruction_argument/immediate_argument.h"
#include "../../code_generator/intermediate/instruction_argument/identifier_argument.h"
#include "../../code_generator/intermediate/instruction_argument/temporary_argument.h"
#include "../../code_generator/intermediate/instruction_argument/instruction_label.h"

FunctionCallNode::FunctionCallNode(FunctionInformation *functionInfo,
                                   ActualParameterListNode *actualParameterList)
    : ExpressionNode(NODE_TYPE_FUNCTION_CALL)
{
    this->functionInfo_ = functionInfo;
    this->actualParameterList_ = actualParameterList;
}

FunctionCallNode::~FunctionCallNode()
{

}

const char *FunctionCallNode::getIdentifier()
{
    return this->functionInfo_->getIdentifier();
}


DataType FunctionCallNode::getReturnType() const
{
    return this->functionInfo_->getReturnType();
}

void FunctionCallNode::setReturnType(const DataType type)
{
    this->functionInfo_->setReturnType(type);
}


DataType FunctionCallNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    list<ExpressionNode *> &expList = this->actualParameterList_->getActualParameterList();
    list<FormalParameterInformation *> &parList = this->functionInfo_->getFormalParameterList();

    if(expList.size() != parList.size())
    {
        string paramListStr = "";
        size_t paramIndex = 0;

        list<FormalParameterInformation *>::iterator formalIt = parList.begin();

        while(paramIndex < parList.size() - 1)
        {
            paramListStr += getDataTypeName( (*formalIt)->getType() );
            paramListStr += ", ";

            formalIt++;
            paramIndex++;
        }

        paramListStr += getDataTypeName( (*formalIt)->getType() );

        const char *returnTypeName = getDataTypeName(this->getReturnType());

        //Incorrect number of arguments calling the function 'data_type name(arg_list)'
        semanticDebugger->debugIncorrectArgumentNumberError(this->getIdentifier(), paramListStr.c_str(),returnTypeName, this->getFirstLine());

        setDataType(DATA_TYPE_ERROR);
        return DATA_TYPE_ERROR;
    }
    else
    {
        list<ExpressionNode *>::iterator actualIt = expList.begin();
        list<FormalParameterInformation *>::iterator formalIt = parList.begin();

        size_t paramNum = 1;

        while(actualIt != expList.end())
        {
            DataType actualType = (*actualIt)->typeCheck(semanticDebugger);
            DataType expectedType = (*formalIt)->getType();


            if(actualType != expectedType)
            {

                if(actualType != DATA_TYPE_ERROR)
                {

                    //Type mismatch while calling the function 'F' in the parameter
                    // of number #. Expected XXX instead of YY.
                    const char *expectedTypeName = getDataTypeName(expectedType);
                    const char *actualTypeName = getDataTypeName(actualType);
                    const char *returnTypeName = getDataTypeName(this->getReturnType());

                    semanticDebugger->debugFunctionArgumentMismatchError(
                        this->getIdentifier(),
                        paramNum,
                        expectedTypeName,
                        actualTypeName,
                        returnTypeName,
                        this->getFirstLine());
                }

                setDataType(DATA_TYPE_ERROR);
                return DATA_TYPE_ERROR;
            }
            else
            {
                if((*actualIt)->isConstant())
                {
                    *actualIt = (*actualIt)->getConstantExpression();
                }
            }

            formalIt++;
            actualIt++;
            paramNum++;
        }

        setDataType(this->getReturnType());
        return this->getReturnType();
    }
}


void FunctionCallNode::checkConstant()
{
    // Embora já definido por padrão na classe base (Expression), é explicitado que
    // este nó não pode ser utilizado como valor constante.
    this->isConstant_ = false;
    this->constantExpression_ = NULL;
}

void FunctionCallNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    string functionIdentifier = "Identifier: ";
    functionIdentifier += getIdentifier();

    astDebugger->openParentNode("Function Call", nodeLevel);

    astDebugger->insertLeafNode(functionIdentifier.c_str(), nodeLevel + 1);
    this->actualParameterList_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Function Call", nodeLevel);
}


void FunctionCallNode::generateCCode(ostream &out)
{
    const char *str = getIdentifier();
    while(*str)
    {
        out << (char)tolower(*str);
        str++;
    }
    out << "(";
    actualParameterList_->generateCCode(out);
    out << ")";
}

void FunctionCallNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    actualParameterList_->generateIntermediateCode(intermediateCode, instructionVector);

    IdentifierArgument *functionIdentifierArgument = new IdentifierArgument(functionInfo_);//remember to delete it somewhere
    TemporaryArgument *dest = intermediateCode->getNextTemporary();
    ImmediateArgument *zeroImmediate = new ImmediateArgument(0);
    InstructionLabel *trueLabel = new InstructionLabel(getTrueLabelNumber());
    InstructionLabel *falseLabel = new InstructionLabel(getFalseLabelNumber());

    this->setAddress(dest);
    intermediateCode->addInstruction(instructionVector, new CallInstruction(functionIdentifierArgument, actualParameterList_->getAddress(), dest) );
    if(getReturnType()==DATA_TYPE_BOOLEAN){
        if(getFalseLabelNumber()==LABEL_FALL)
            intermediateCode->addInstruction(instructionVector, new ConditionalGotoInstruction( RELATIONAL_OPERATOR_DIFFERENT, getAddress(), zeroImmediate, trueLabel ) );
        else if(getTrueLabelNumber()==LABEL_FALL)
            intermediateCode->addInstruction(instructionVector, new ConditionalGotoInstruction( RELATIONAL_OPERATOR_EQUAL, getAddress(), zeroImmediate, falseLabel ) );
        else{
            intermediateCode->addInstruction(instructionVector, new ConditionalGotoInstruction( RELATIONAL_OPERATOR_DIFFERENT, getAddress(), zeroImmediate, trueLabel ) );
            intermediateCode->addInstruction(instructionVector, new GotoInstruction( falseLabel ) );
        }
    }

    intermediateCode->addInstructionArgumentToCleanUpList(functionIdentifierArgument);
    intermediateCode->addInstructionArgumentToCleanUpList(falseLabel);
    intermediateCode->addInstructionArgumentToCleanUpList(trueLabel);
    intermediateCode->addInstructionArgumentToCleanUpList(zeroImmediate);

}
