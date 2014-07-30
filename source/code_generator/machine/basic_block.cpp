/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "basic_block.h"
#include <iomanip>
BasicBlock::BasicBlock(vector<Instruction *>::iterator begin, vector<Instruction *>::iterator end)
    : functionName_(0), isStartingFunction_(0)
{
    begin_ = begin;
    end_ = end;
}

BasicBlock::BasicBlock()
    : functionName_(0), isStartingFunction_(0)
{
}

void BasicBlock::setBeginIterator(vector<Instruction *>::iterator begin)
{
    begin_ = begin;
}

void BasicBlock::setEndIterator(vector<Instruction *>::iterator end)
{
    end_ = end;
}

vector<Instruction *>::iterator BasicBlock::getBeginIterator()
{
    return begin_;
}

vector<Instruction *>::iterator BasicBlock::getEndIterator()
{
    return end_;
}

void BasicBlock::setFunctionName(const char *functionName)
{
    functionName_ = functionName;
}

const char *BasicBlock::getFunctionName()
{
    return functionName_;
}

void BasicBlock::setStartingFunction(bool isStarting)
{
    isStartingFunction_ = isStarting;
}

bool BasicBlock::isStartingFunction()
{
    return isStartingFunction_;
}

vector<Instruction*> * BasicBlock::getInstructionVector()
{
     vector<Instruction*> * instructionVector = new vector<Instruction*>(this->begin_, this->end_);

return      instructionVector;
 }

void BasicBlock::setLastFunctionBlock(bool isLast)
{
    isLastFunctionBlock_ = isLast;
}

bool BasicBlock::isLastFunctionBlock()
{
    return isLastFunctionBlock_;
}

void BasicBlock::debug(ostream &out)
{
    cout << "\nID\t Instr. \t\t\t dst \t src1 \t src2" << endl << endl;
    int i = 0;
    for(vector<Instruction *>::iterator it = begin_; it!=end_; it++){
      cout << i++ << "\t ";
      (*it)->debug(out);
    }
}

//AINDA FALTA MODIFICAR O STATUS DOS OPERANDOS DAS INSTRUCOES MORTAS
void BasicBlock::optimise()
{
    return;
    vector<Instruction*> *instructionsVector = getInstructionVector();
    Instruction* instruction;
    vector<ArgumentInformation *> *args;
    vector<int> deadInstruction;
    for(int i = instructionsVector->size()-1; i>=0; i--){
        instruction = instructionsVector->at(i);
        args = instruction->getArgumentsInformation();
        if( args->at(0) ){
            if( args->at(0)->getStatus()==ARGUMENT_INFORMATION_STATUS_NOT_ALIVE ){
                instruction->setDeadCode(true);
                deadInstruction.push_back(i);
            }else {
                for(int j = 0; j<deadInstruction.size(); j++){
                    if(args->at(0)->getStatus()==deadInstruction.at(j)){
                        instruction->setDeadCode(true);
                        deadInstruction.push_back(i);
                        //break;
                    }
                }
            }
        }
    }
}
