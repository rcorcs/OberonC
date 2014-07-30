/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "machine_code.h"


MachineCode::MachineCode(SymbolTable * symbolTable, IntermediateCode * intermediateCode)
{
    this->symbolTable_ = symbolTable;
    this->intermediateCode_ = intermediateCode;

    this->initVariableStatus();
}

MachineCode::~MachineCode()
{

}

void MachineCode::open(const char *baseFile)
{
    baseFileName_ = baseFile;
    assemblyFileName_ = getDebugFileName(baseFile, "s");
    assemblyFile_.open(assemblyFileName_);
}

void MachineCode::close()
{
    assemblyFile_.close();
}

void MachineCode::gen(const char *instruction)
{
    assemblyFile_ << instruction << endl;
}

void MachineCode::gen(string instruction)
{
    assemblyFile_ << instruction << endl;
}

/*
VariableDescriptor * MachineCode::getVariableDescriptor(IdentifierArgument * identifierArgument)
{
    return getVariableDescriptor(identifierArgument->getIdentifierInformation());
}
*/
VariableDescriptor * MachineCode::getVariableDescriptor(IdentifierInformation * identifierInformation)
{
    if(this->variableDescriptorTable_.contains((int)identifierInformation))
    {
        return this->variableDescriptorTable_.get((int)identifierInformation);
    }

    return NULL;
}

RegisterDescriptor * MachineCode::getRegisterDescriptor(int registerNumber)
{
    if(this->registerDescriptorTable_.contains(registerNumber))
    {
        return this->registerDescriptorTable_.get( registerNumber );
    }

    return NULL;
}

void MachineCode::initVariableStatus()
{

    vector<BasicBlock *>  * basicBlocks = this->intermediateCode_->getBasicBlocks();

    for(size_t i = 0; i < basicBlocks->size(); i++)
    {
        IntegerHashTable<int> * statusAuxTable = this->getNewStatusAuxTable();

        BasicBlock * basicBlock  = basicBlocks->at(i);
        vector<Instruction *> * instructionVector  = basicBlock->getInstructionVector();

        for(int j = instructionVector->size() - 1; j >= 0; j--)
        {
            Instruction * instruction = instructionVector->at( j );
            vector<ArgumentInformation *> * args = instruction->getArgumentsInformation();

            ArgumentInformation * dst = args->at(0);


            if( dst != NULL )
            {
                IdentifierInformation * identifierInfo = this->getInfoFromArgument(dst->getInstructionArgument());

                if(identifierInfo != NULL)
                {
                    int status = statusAuxTable->get((int)identifierInfo);

                    dst->setStatus( status  );
                    statusAuxTable->set((int)identifierInfo, ARGUMENT_INFORMATION_STATUS_NOT_ALIVE);
                }
            }

            for(size_t k = 1; k < args->size(); k++ )
            {
                ArgumentInformation * src = args->at(k);

                if(src != NULL)
                {
                    IdentifierInformation * identifierInfo = this->getInfoFromArgument(src->getInstructionArgument());

                    if(identifierInfo != NULL)
                    {
                        int status = statusAuxTable->get((int)identifierInfo);

                        src->setStatus( status );
                        statusAuxTable->set((int)identifierInfo, j);
                    }
                }
            }
        }

        delete instructionVector;
        delete basicBlock;
        delete statusAuxTable;
    }

    delete basicBlocks;
}

IntegerHashTable<int> * MachineCode::getNewStatusAuxTable()
{
    IntegerHashTable<int> * statusAuxTable = new IntegerHashTable<int>(32);

    list<IdentifierInformation*>  * identifierInfoList = this->symbolTable_->getIdentifierInfoList();
    list<IdentifierInformation*>::iterator it1 = identifierInfoList->begin();

    while(it1 != identifierInfoList->end())
    {
        IdentifierInformation * identifierInfo = (*it1);

        switch(identifierInfo->getCategoryType())
        {


        case IDENTIFIER_CATEGORY_TYPE_VARIABLE:
        case IDENTIFIER_CATEGORY_TYPE_FORMAL_PARAMETER:

            statusAuxTable->set((int)identifierInfo, ARGUMENT_INFORMATION_STATUS_ALIVE_ON_EXIT);
            break;

        case IDENTIFIER_CATEGORY_TYPE_TEMPORARY:

            statusAuxTable->set((int)identifierInfo , ARGUMENT_INFORMATION_STATUS_NOT_ALIVE);
            break;

        default:
            break;
        }
        it1++;

    }

    return statusAuxTable;

}

IdentifierInformation * MachineCode::getInfoFromArgument(InstructionArgument* instructionArgument)
{
    IdentifierInformation * identifierInfo = NULL;

    if(instructionArgument->getType() == INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER)
    {
        identifierInfo = ((IdentifierArgument*)instructionArgument)->getIdentifierInformation();
    }
    else if(instructionArgument->getType() == INSTRUCTION_ARGUMENT_TYPE_TEMPORARY)
    {
        identifierInfo = ((TemporaryArgument*)instructionArgument)->getTemporaryInformation();
    }

    return identifierInfo;

}

