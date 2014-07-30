/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "procedure_call_node.h"

#include "../../code_generator/intermediate/instruction/call_instruction.h"

#include "../../code_generator/intermediate/instruction_argument/identifier_argument.h"

ProcedureCallNode::ProcedureCallNode(FunctionInformation *functionInfo,
                                     ActualParameterListNode * actualParameterList)
    : StatementNode(NODE_TYPE_PROCEDURE_CALL)
{
    this->functionInfo_ = functionInfo;
    this->actualParameterList_ = actualParameterList;
}

ProcedureCallNode::~ProcedureCallNode()
{

}

const char *ProcedureCallNode::getIdentifier()
{
    return this->functionInfo_->getIdentifier();
}


void ProcedureCallNode::typeCheck(SemanticDebugger *semanticDebugger)
{

    list<ExpressionNode *> &actualParList = this->actualParameterList_->getActualParameterList();
    list<FormalParameterInformation *> &fparList = this->functionInfo_->getFormalParameterList();

    if(actualParList.size() != fparList.size())
    {
        string paramListStr = "";
        size_t paramIndex = 0;

        list<FormalParameterInformation *>::iterator formalIt = fparList.begin();

        while(paramIndex < fparList.size() - 1)
        {
            paramListStr += getDataTypeName( (*formalIt)->getType() );
            paramListStr += ", ";

            formalIt++;
            paramIndex++;
        }

        paramListStr += getDataTypeName( (*formalIt)->getType() );

        semanticDebugger->debugIncorrectArgumentNumberError(this->getIdentifier(),
                paramListStr.c_str(), NULL,
                this->getFirstLine());

    }
    else
    {
        list<ExpressionNode *>::iterator actualIt = actualParList.begin();
        list<FormalParameterInformation *>::iterator formalIt = fparList.begin();

        size_t paramNum = 1;

        while(actualIt != actualParList.end())
        {
            DataType actualType = (*actualIt)->typeCheck(semanticDebugger);
            DataType expectedType = (*formalIt)->getType();


            if(actualType != expectedType && actualType != DATA_TYPE_ERROR)
            {

                const char *expectedTypeName = getDataTypeName(expectedType);
                const char *actualTypeName = getDataTypeName(actualType);

                semanticDebugger->debugFunctionArgumentMismatchError(this->getIdentifier(),
                        paramNum,
                        expectedTypeName,
                        actualTypeName,
                        NULL,
                        this->getFirstLine());
                break;
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

    }
}

void ProcedureCallNode::debug(ASTDebugger *astDebugger, int nodeLevel)
{
    string functionIdentifier = "Identifier: ";
    functionIdentifier += getIdentifier();

    astDebugger->openParentNode("Procedure Call", nodeLevel);

    astDebugger->insertLeafNode(functionIdentifier.c_str(), nodeLevel + 1);
    this->actualParameterList_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Procedure Call", nodeLevel);
}


void ProcedureCallNode::generateCCode(ostream &out)
{
    const char *str = getIdentifier();
    while(*str)
    {
        out << (char)tolower(*str);
        str++;
    }
    out << "(";
    actualParameterList_->generateCCode(out);
    out << ");" << endl;
}

void ProcedureCallNode::generateIntermediateCode(IntermediateCode *intermediateCode, vector<Instruction *>*instructionVector)
{
    actualParameterList_->generateIntermediateCode(intermediateCode,instructionVector);
    IdentifierArgument *functionIdentifierArgument = new IdentifierArgument(functionInfo_);//remember to delete it somewhere
    intermediateCode->addInstruction(instructionVector, new CallInstruction(functionIdentifierArgument, actualParameterList_->getAddress()));

    intermediateCode->addInstructionArgumentToCleanUpList( functionIdentifierArgument );
}
