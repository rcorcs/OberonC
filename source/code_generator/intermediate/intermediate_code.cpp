/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "intermediate_code.h"
#include <iostream>
using namespace std;

IntermediateCode::IntermediateCode(SymbolTable * symbolTable)
{
    // Movido da definição do construtor para dentro do corpo devido a um
    // warning de inicialização.
    nextLabelNumber_ = 0;
    nextTemporaryNumber_ = 0;
    pendingLabelNumber_ = 0;

    this->symbolTable_ = symbolTable;
    functionHashTable_ = new HashTable<vector<Instruction *>*>(10);

}

IntermediateCode::~IntermediateCode()
{

    for(vector<const char *>::iterator it = this->functionNames_.begin(); it != this->functionNames_.end(); it++)
    {
        const char * functionName = (*it);

        vector <Instruction *> * functionPair = functionHashTable_->get(functionName);
        delete functionPair;

        delete (*it);
    }


    for(list<InstructionArgument *>::iterator it = this->cleanUpArgumentList_.begin(); it != this->cleanUpArgumentList_.end(); it++)
    {
        delete (*it);
    }



    delete functionHashTable_;
}

/*
void IntermediateCode::addInstruction(Instruction *instruction, bool usingPendingLabel)
{
    if(usingPendingLabel){
        if(getPendingLabelNumber()>LABEL_NONE)
            instruction->setLabel( new InstructionLabel(usePendingLabelNumber()) );
    }
    instructionVector_.push_back(instruction);
}
*/
void IntermediateCode::addInstruction(const char *functionName, Instruction *instruction, bool usingPendingLabel)
{
    if(usingPendingLabel)
    {
        if(getPendingLabelNumber()>LABEL_NONE)
            instruction->setLabel( new InstructionLabel(usePendingLabelNumber()) );
    }
    getInstructionVector(functionName)->push_back(instruction);
}

void IntermediateCode::addInstruction(vector<Instruction *> *instructionVector, Instruction *instruction, bool usingPendingLabel)
{
    if(usingPendingLabel)
    {
        if(getPendingLabelNumber()>LABEL_NONE)
            instruction->setLabel( new InstructionLabel(usePendingLabelNumber()) );
    }
    instructionVector->push_back(instruction);
}


void IntermediateCode::setPendingLabelNumber(int pendingLabelNumber)
{
    this->pendingLabelNumber_ = pendingLabelNumber;
}

int IntermediateCode::getPendingLabelNumber()
{
    return this->pendingLabelNumber_;
}

int IntermediateCode::usePendingLabelNumber()
{
    int label = this->pendingLabelNumber_;
    this->pendingLabelNumber_ = LABEL_NONE;
    return label;
}

int IntermediateCode::getNextLabelNumber()
{
    return(++nextLabelNumber_);
}



TemporaryArgument * IntermediateCode::getNextTemporary()
{
    TemporaryInformation * temporaryInformation = new TemporaryInformation(++this->nextTemporaryNumber_);
    TemporaryArgument * temp = new TemporaryArgument(temporaryInformation);

    this->symbolTable_->getIdentifierInfoList()->push_back(temporaryInformation);
this->cleanUpArgumentList_.push_back(temp);

    return temp;
}

void IntermediateCode::setMainFunctionName(const char *functionName)
{
    mainFunctionName_ = functionName;
}

const char *IntermediateCode::getMainFunctionName()
{
    return mainFunctionName_;
}

vector<Instruction *> *IntermediateCode::addInstructionVector(const char *functionName)
{
    char *functionNameCopy = new char[strlen(functionName)+1];
    strcpy(functionNameCopy, functionName);
    functionNames_.push_back(functionNameCopy);
    vector<Instruction *> *instructionVector = new vector<Instruction *>();
    functionHashTable_->set(functionNameCopy, instructionVector);
    return instructionVector;
}

vector<Instruction *> *IntermediateCode::getInstructionVector(const char *functionName)
{
    vector<Instruction *>  * functionPair = functionHashTable_->get(functionName);
    return functionPair;
}

void IntermediateCode::addInstructionArgumentToCleanUpList(InstructionArgument * argument)
{
    cleanUpArgumentList_.push_back(argument);
}

vector<const char *> *IntermediateCode::getFunctionNames()
{
    return &functionNames_;
}

vector<BasicBlock *> *IntermediateCode::getBasicBlocks()
{
    vector<Instruction *> *instructionVector;

    vector<BasicBlock *> *basicBlocks = new vector<BasicBlock *>();
    BasicBlock *basicBlock = 0;
    for(size_t i = 0; i<functionNames_.size(); i++)
    {
        instructionVector = getInstructionVector(functionNames_.at(i));

        for(vector<Instruction*>::iterator it = instructionVector->begin(); it!=instructionVector->end(); it++)
        {
            if(it==instructionVector->begin())
            {
                basicBlock = new BasicBlock();
                basicBlock->setStartingFunction(true);
                basicBlock->setFunctionName(functionNames_.at(i));
                basicBlock->setBeginIterator(it);
            }
            else if( (*it)->getLabel()!=NULL)
            {
                basicBlock->setEndIterator(it);
                basicBlocks->push_back(basicBlock);

                basicBlock = new BasicBlock();
                basicBlock->setStartingFunction(false);
                basicBlock->setFunctionName(functionNames_.at(i));
                basicBlock->setBeginIterator(it);
            }
//            else if( (*(it))->getInstructionType()==INSTRUCTION_TYPE_CALL )
//            {
//                basicBlock->setEndIterator(it);
//                basicBlocks->push_back(basicBlock);
//
//                basicBlock = new BasicBlock();
//                basicBlock->setStartingFunction(false);
//                basicBlock->setFunctionName(functionNames_.at(i));
//                basicBlock->setBeginIterator(it);
//            }

            else if( (*(it-1))->getInstructionType()==INSTRUCTION_TYPE_CONDITIONAL_GOTO ||
                     (*(it-1))->getInstructionType()==INSTRUCTION_TYPE_GOTO ||
                     (*(it-1))->getInstructionType()==INSTRUCTION_TYPE_RETURN
            ) {
                basicBlock->setEndIterator(it);
                basicBlocks->push_back(basicBlock);

                basicBlock = new BasicBlock();
                basicBlock->setStartingFunction(false);
                basicBlock->setFunctionName(functionNames_.at(i));
                basicBlock->setBeginIterator(it);
            }
        }
        basicBlock->setEndIterator(instructionVector->end());
        basicBlock->setLastFunctionBlock(true);
        basicBlocks->push_back(basicBlock);
    }
    return basicBlocks;
}


void IntermediateCode::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{
    vector<Instruction *> *instructionVector;
    for(size_t i = 0; i<functionNames_.size(); i++)
    {
        instructionVector = getInstructionVector(functionNames_.at(i));

        codeGeneratorDebugger->debugCode( "\n" );
        codeGeneratorDebugger->debugCode(functionNames_.at(i) );
        codeGeneratorDebugger->debugCode( ":\n" );

        for(size_t j = 0; j<instructionVector->size(); j++)
            instructionVector->at(j)->debug(codeGeneratorDebugger);
    }

}
