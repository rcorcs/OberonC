/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "module_node.h"

#include "../../code_generator/intermediate/instruction/nop_instruction.h"
#include "../../code_generator/intermediate/instruction/return_instruction.h"
#include "../../code_generator/intermediate/instruction_argument/function_label.h"

#include <iostream>
using namespace std;



ModuleNode::ModuleNode(ModuleInformation *moduleInfo, DeclarationNode *declarations, StatementNode *statements)
    : DeclarationNode(NODE_TYPE_MODULE)
{
    this->moduleInfo_ = moduleInfo;
    this->declarations_ = declarations;
    this->statements_ = statements;
}

ModuleNode::~ModuleNode()
{

}

void ModuleNode::typeCheck(SemanticDebugger *semanticDebugger)
{
    DataType returnType = DATA_TYPE_UNDEFINED;
    bool inRepetition = false;

    this->declarations_->typeCheck(semanticDebugger);

    this->statements_->typeCheck(semanticDebugger);
    this->statements_->checkRepetition(inRepetition, semanticDebugger);
    this->statements_->checkReturn(returnType, semanticDebugger);
}


void ModuleNode::debug(ASTDebugger * astDebugger, int nodeLevel)
{
    astDebugger->openParentNode("Module", nodeLevel);

    this->declarations_->debug(astDebugger, nodeLevel + 1);
    this->statements_->debug(astDebugger, nodeLevel + 1);

    astDebugger->closeParentNode("Module", nodeLevel);
}

void ModuleNode::generateCCode(ostream &out)
{
    out << "#include <stdio.h>" << endl;
    out << "#include <stdlib.h>" << endl << endl;

    this->declarations_->generateCCode(out);

    out << endl << "void main()" << endl << "{" << endl;
    this->statements_->generateCCode(out);
    out << "}" << endl;
}

void ModuleNode::generateIntermediateCode(IntermediateCode *intermediateCode)
{
    declarations_->generateIntermediateCode(intermediateCode);

    //NopInstruction *nopInstruction = new NopInstruction();
    //FunctionLabel *functionLabel = new FunctionLabel("main");
    //nopInstruction->setLabel( functionLabel );

    //intermediateCode->addInstruction(nopInstruction, false);

    intermediateCode->setMainFunctionName("main");
    vector<Instruction *> *instructionVector = intermediateCode->addInstructionVector("main");
    statements_->setNextLabelNumber( LABEL_FALL );
    statements_->generateIntermediateCode(intermediateCode, instructionVector);

    intermediateCode->addInstruction(instructionVector, new ReturnInstruction() );

    //intermediateCode->addInstructionArgumentToCleanUpList(functionLabel);
}
