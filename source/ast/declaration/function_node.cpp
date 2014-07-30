/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "function_node.h"

#include "../../code_generator/intermediate/instruction/nop_instruction.h"
#include "../../code_generator/intermediate/instruction/return_instruction.h"
#include "../../code_generator/intermediate/instruction_argument/function_label.h"

FunctionNode::FunctionNode(FunctionInformation *functionInfo,
                           DeclarationNode *declarations,
                           StatementNode *statements)
    : DeclarationNode(NODE_TYPE_FUNCTION)
{
    this->functionInfo_ = functionInfo;
    this->declarations_  = declarations;
    this->statements_ = statements;
}

FunctionNode::~FunctionNode()
{

}

const char *FunctionNode::getIdentifier()
{
    return this->functionInfo_->getIdentifier();
}

DataType FunctionNode::getReturnType() const
{
    return functionInfo_->getReturnType();
}

void FunctionNode::setReturnType(const DataType returnType)
{
    functionInfo_->setReturnType(returnType);
}


DeclarationNode * FunctionNode::getDeclarations() const
{
    return this->declarations_;
}

void FunctionNode::setDeclarations(DeclarationNode *declarations)
{
    this->declarations_ = declarations;
}

StatementNode * FunctionNode::getStatements() const
{
    return this->statements_;
}

void FunctionNode::setStatements(StatementNode *statements)
{
    this->statements_ = statements;
}

void FunctionNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    DataType returnType = this->getReturnType();
    bool inRepetition = false;

    this->declarations_->typeCheck(semanticDebugger);

    this->statements_->typeCheck(semanticDebugger);
    this->statements_->checkRepetition(inRepetition, semanticDebugger);

    if(!this->statements_->checkReturn(returnType, semanticDebugger))
    {
        if(returnType != DATA_TYPE_VOID)
        {
            semanticDebugger->debugMissingReturnError(this->getIdentifier(),
                    getDataTypeName(returnType),
                    this->getFirstLine());
        }

    }
}

void FunctionNode::debug(ASTDebugger * astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Function/Procedure", nodeLevel);

    string functionIdentifier = "Identifier: ";
    functionIdentifier += getIdentifier();

    string functionReturnType = "Return Type: ";
    functionReturnType += getDataTypeName( getReturnType() );

    astDebugger->insertLeafNode(functionIdentifier.c_str(), nodeLevel + 1);
    astDebugger->insertLeafNode(functionReturnType.c_str(), nodeLevel + 1);

    this->declarations_->debug(astDebugger, nodeLevel + 1);
    this->statements_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Function/Procedure", nodeLevel);
}


void FunctionNode::generateCCode(ostream &out)
{
    switch(getReturnType())
    {
    case DATA_TYPE_INTEGER:
        out << "int";
        break;
    case DATA_TYPE_BOOLEAN:
        out << "char";
        break;
    case DATA_TYPE_VOID:
        out << "void";
        break;
    default:
        break;
    }
    out << " ";
    const char *str = getIdentifier();
    while(*str)
    {
        out << (char)tolower(*str);
        str++;
    }

    this->declarations_->generateCCode(out);
    this->statements_->generateCCode(out);
    out << "}" << endl;

}

void FunctionNode::generateIntermediateCode(IntermediateCode *intermediateCode)
{
    declarations_->generateIntermediateCode(intermediateCode);

    //NopInstruction *nopInstruction = new NopInstruction();
    //FunctionLabel *functionLabel = new FunctionLabel(getIdentifier());
    //nopInstruction->setLabel( functionLabel );
    //intermediateCode->addInstruction(nopInstruction, false);

    statements_->setNextLabelNumber( LABEL_FALL );

    vector<Instruction *> *instructionVector = intermediateCode->addInstructionVector(getIdentifier());
    statements_->generateIntermediateCode(intermediateCode, instructionVector );

    if(getReturnType()==DATA_TYPE_VOID){
        intermediateCode->addInstruction(instructionVector, new ReturnInstruction() );
    }else{
        intermediateCode->addInstruction(instructionVector, new NopInstruction() );
    }

    //intermediateCode->addInstructionArgumentToCleanUpList(functionLabel);
}
